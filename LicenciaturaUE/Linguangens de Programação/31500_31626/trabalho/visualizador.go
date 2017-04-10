package main

// os pacotes a serem utilizados
import (
	"fmt"
	"strings"
	"time"
	"net"
	"bufio"
	"os"
	"strconv"
)

// comandos do visualisador
func esperar(toWho net.Conn)(wait bool){
	var input string;

	for true{
		input,_ = bufio.NewReader(os.Stdin).ReadString('\n');                   //aguarda input do visualizador
		newinput:=strings.TrimSpace(input)										//  eliminar os espacos
		
		switch{
			case strings.EqualFold(newinput,"espera"):	// envia ao outro parqa esperar
				toWho.Write([]byte("espera\n"));
				break;
				
			case strings.EqualFold(newinput,"joga"):	// envia ao outro que pode jogar
				toWho.Write([]byte("joga\n"));									// envia ao outro que pode jogar (gera uma jogada)
				return false;

			default:
				break;
		}
	}
	return false;
}

func handleRequests(who net.Conn, isName string, toWho net.Conn, toWhoName string, messagePlayer string)(bool){
		
		wait := true;					// continua a espera de input	
		ainda_nao_jogou := true;				// para que nao haja multiplas jogadas
		wait_some_more_pls := false;					// diz ao jogador para esperar

		for wait {
			messagePlayer,_ = bufio.NewReader(who).ReadString('\n'); 		// mensagens do jogador X para jogador O

			switch{	

				// se 
				case len(messagePlayer) > 4 && ainda_nao_jogou && strings.EqualFold(messagePlayer[0:4],"jogo"):	// apos receber jogo L C tem de esperar para receber joga para puder jogar
					toWho.Write([]byte(messagePlayer));	// envia ao outro jogador a posicao em que este jogou para puder actualizar o seu tabuleiro
					fmt.Println(string(isName)," -> ",string(toWhoName),": ", string(messagePlayer));
					
					ainda_nao_jogou = false;
					wait_some_more_pls = esperar(toWho);		// se o comando for espera, entao envia ao outro jogador para esperar e volta a ler novo input

					if(!wait_some_more_pls){					// o comando e' do visualizador nao e' "espera"	
						wait = false;									
					}

					return false;

					break;

				case strings.EqualFold(messagePlayer,"ganhei\n") || strings.EqualFold(messagePlayer,"empatamos\n") || strings.EqualFold(messagePlayer,"desisto\n"):
					fmt.Println(string(isName)," -> ",string(toWhoName),": ", string(messagePlayer));
					toWho.Write([]byte(messagePlayer));
					wait = false;
					
					return true;
					break;
					
				default: // unwated messages wont disrupt the flow
					break;
			}
		}

		return false;
}

// o comando recebido e' comando + Nome, 
// esta funcao separa o comando do nome e retorna so o nome
func splitName(nome1 string, nome2 string)(nnome1 string, nnome2 string){

	nnome1 = nome1[5:len(nome1)-1];
	nnome2 = nome2[5:len(nome2)-1];

	return nnome1,nnome2;
}

// jogo entre dois jogadores
func handlePlayers(player1 net.Conn, player2 net.Conn){		// the goroutine

	var size string;						// tamanho do tabuleiro
	var nomePlayer1 string;					// nome do jogador 1
	var nomePlayer2 string;					// nome do jogador 2
	var messagePlayer1 string;				// messagens do jogador 1
	var messagePlayer2 string;				// mensagens do jogador 2

	player1.Write([]byte("nome\n"));							// envia ao primeiro que se conectou o nome
	nomePlayer1,_ = bufio.NewReader(player1).ReadString('\n');
	
	player2.Write([]byte("nome\n"));							// apos receber resposta envia este
	nomePlayer2,_ = bufio.NewReader(player2).ReadString('\n');

	nomePlayer1,nomePlayer2 = splitName(nomePlayer1,nomePlayer2);	// faz split do comando + nome
	for true{
		fmt.Print("Tamanho do jogo: ");
		fmt.Scan(&size);											// scan for input
		if _, err := strconv.Atoi(size); err == nil{				// so permite input valido
			fmt.Print("\n");
			break;
		} 	
	}

	time.Sleep(100 * time.Millisecond);
	player1.Write([]byte("tamanho "+size+"\n"));		// envia aos jogadores o tamanho do tabuleiro
	player2.Write([]byte("tamanho "+size+"\n"));		//

	time.Sleep(100 * time.Millisecond);
	player1.Write([]byte("comeca X"+"\n"));				// envia aos jogadores quem e' quem
	player2.Write([]byte("comeca O"+"\n"));				// o primeiro a se conectar e' sempre o X

	time.Sleep(100 * time.Millisecond);
	player1.Write([]byte("joga\n"));				// primeiro a jogar e' o player1

	var endGame = false;

	for !endGame{

		endGame = handleRequests(player1,nomePlayer1,player2,nomePlayer2,messagePlayer1);	// redireciona o output para o jogador 2
		endGame = handleRequests(player2,nomePlayer2,player1,nomePlayer1,messagePlayer2);	// redireciona o output para o jogador 1

	}

	fmt.Println("\n\nGame between "+nomePlayer1 + "and "+nomePlayer2+" has ended\n\n");
	
	player1.Close();		// fecha a conecao
	player2.Close();		//
}

func main(){
	ln,_ := net.Listen("tcp",":31626"); // start server 

	for true{			// continue listening for ever and ever

		// can accept as many players as possible but needs two to start the game
		player1,_:= ln.Accept(); 				// listen for player 1
		player2,_ := ln.Accept();				// listen for player 2

		go handlePlayers(player1,player2); 		// goroutine for playing tic tac toe between two players (goroutines are fun)
	}

}


