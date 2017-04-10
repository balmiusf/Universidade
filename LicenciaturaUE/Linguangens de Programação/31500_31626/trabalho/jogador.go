package main

// os pacotes 
import (
	"fmt"
	"strings"
	"strconv"
	"math"
	"net"
	"bufio"
	"os"
)

var tabuleiro [] string;		// tabuleiro
var current_symbol string;		// simbolo do jogador
var opositeSymbol string;		// simbolo do outro jogador
var conn net.Conn;				// conneccao ao servidor
var continueGame bool; 			// simboliza o estado do jogo
var tamanho int;				// tamanho do array


func offset(x int,y int,n int)(int){
	return (x-1)*n+(y-1)	// calcula a posicao
}

func verifica_linha(tabuleiro [] string)(bool,string){
	tamanho := int(math.Sqrt(float64(len(tabuleiro))))
	size:= tamanho;	// tamanho de uma linha
	var i int;	
	n_certos:= 0;	// numero de certos seguidos - 1  
	for i = 1; i < tamanho*tamanho; i++{

		if(strings.Compare(tabuleiro[i-1], tabuleiro[i]) == 0){
			n_certos++
			
			// faz verificacoes dois a dois, sendo que o numero de certos numa linha basta ser so tamanho da linha - 1
			// se houver dois simbolos seguidos iguais incrementa	
			if(n_certos == tamanho-1){		// faz tamanho-1 verificacoes
				return true,tabuleiro[i];
			}
		}

		if(size-1 == i){	// mudanca de linha
			size=size+tamanho
			i += 1
			n_certos = 0	// nova linha significa que nao houve victoria na anterior logo da reset ao numero de certos 
		}
	}
	return false,tabuleiro[0];
}

func verifica_coluna(tabuleiro [] string)(bool,string){
	tamanho := int(math.Sqrt(float64(len(tabuleiro))))
	var pos int;
	for i := 1; i <= tamanho; i++{
		n_certos:= 0
		for j := 2; j <= tamanho; j++{
			pos = offset(j,i,tamanho)
			MenosUmPos := offset(j-1,i,tamanho) // posicao menos 1 em coluna

			if(strings.Compare(tabuleiro[MenosUmPos],tabuleiro[pos]) == 0){
				n_certos++;			// numero de certos e' igual a N-1 para verifica uma sequencia
				
				// ver explicacao na funcao verifica_linhas
				if(n_certos == tamanho-1){		// faz N-1 verificacoes
					return true,tabuleiro[pos];
				}
			}
		}
	}
	return false,tabuleiro[pos];
}

func verifica_diagonais(tabuleiro [] string)(bool, string){
	tamanho := int(math.Sqrt(float64(len(tabuleiro))))	// tamanho de uma coluna/linha
	n_certos:= 0
	var pos int;										// numero de certos
														
	for i:=2; i <= tamanho; i++{						// diagonal esquerda

		posMenoUm := offset(i-1,i-1,tamanho)
		pos = offset(i,i,tamanho)
		
		if(strings.Compare(tabuleiro[posMenoUm],tabuleiro[pos]) == 0){
			n_certos++;
			
			// ver explicacao na funcao verifica_linhas
			if(n_certos == tamanho-1){		// faz n-1 verificacoes
				return true,tabuleiro[pos];
			}
		}
	}
	j:= 1
	n_certos = 0

	for i:= tamanho ; i > 1; i--{						// diagonal direita
		posMaisUm:= offset(i-1,j+1,tamanho);
		pos = offset(i,j,tamanho)
		
		if(strings.Compare(tabuleiro[posMaisUm] , tabuleiro[pos]) == 0){
			n_certos++;
			
			// ver explicacao na funcao verifica_linhas
			if(n_certos == tamanho-1){					// faz n-1 verificacoes
				return true,tabuleiro[pos];
			}
		}
		j++;
	}

	return false,tabuleiro[pos];
}


//	verifica victoria em linha, coluna e diagonal

func verifica_victoria(tabuleiro [] string)(bool,string){

	boolean,simbolo:=verifica_linha(tabuleiro);				// veririca victoria nas linhas
	if(!boolean){											// se nao houver victoria em linhas verifica em colunas
		boolean,simbolo = verifica_coluna(tabuleiro);
		if(!boolean){										// se nao houver victoria em coluna verifica diagonais
			boolean,simbolo= verifica_diagonais(tabuleiro)
		}	
	}	
	return boolean, simbolo
}

// verifica empate se tiver tudo preenchido
// se um elemento for diferente de X e de O entao nao ha empate porque ainda ha espaços a preencher
func verifica_empate(tabuleiro [] string)(bool){	
	for i:=0; i<len(tabuleiro);i++{
		if (tabuleiro[i]!= "X" && tabuleiro[i]!="O"){
			return false
		}
	}
	return true
}

func print_tabuleiro(tabuleiro [] string){
	fmt.Println("\n");
	tamanho := int(math.Sqrt(float64(len(tabuleiro))));
	for i:= 0 ; i < tamanho; i++{
		for j:= 0; j < tamanho; j++{
			pos:= offset(i+1,j+1,tamanho)
			fmt.Print(" ");
			fmt.Printf("%3s",tabuleiro[pos]);
			fmt.Print(" ");
		}
		fmt.Print("\n\n");
	}
	fmt.Print("\n");
}

// gera um tabuleiro vazio (explica isto kebab)
func tabuleirovazio(n int)([] string){
	tabuleiro:= [] string {}
	n = n*n
	for j:=0;j<n;j++{
		newK := strconv.Itoa(j)
		tabuleiro = append(tabuleiro,newK);
	}
	return tabuleiro;
}

// verifica se os input corresponde a uma posição fora ou dentro do tabuleiro
func verifica(tabuleiro [] string,z int)(bool){
	return strings.EqualFold(tabuleiro[z], current_symbol) || strings.EqualFold(tabuleiro[z], opositeSymbol) || z>=len(tabuleiro) || z<0;

}

// executa uma jogada no seu tabuleiro
func preencheposicoes(tabuleiro [] string, posicao int , jogada string)([] string){
	tabuleiro[posicao] = jogada
	return tabuleiro
}

// avalia a jogada
func play_the_game(tabuleiro [] string, L int, C int){

	var n int;																
	n = int(math.Sqrt(float64(len(tabuleiro))));							// tamanho
	pos := offset(L,C,n);													// calcula posicao

	fmt.Print("\n");
	tabuleiro = preencheposicoes(tabuleiro,pos,current_symbol);				// preenche posicao
	print_tabuleiro(tabuleiro);												
	boolean,simbolo := verifica_victoria(tabuleiro);						// verifica se alguem ganhou e qual o simbolo que ganhou

	var	messageToSend = "";													// mensagem a enviar para o visualizador

	switch{
		
		case boolean && strings.EqualFold(simbolo,current_symbol):		// verifica se ganhou
			fmt.Println("Tu: ganhei");
			messageToSend = "ganhei";
			continueGame = false;
		break;

		case verifica_empate(tabuleiro):								// se for empate
			fmt.Println("Tu: empatamos");
			messageToSend = "empatamos";
			continueGame = false;
			break;

		case boolean && strings.EqualFold(simbolo,opositeSymbol):		// verifica se perdeu
			messageToSend = "desisto";
			fmt.Println("Tu: desisto");
			continueGame = false;
			break;

		default:
			Ls := strconv.Itoa(L);			// conversao de int para string
			Cs := strconv.Itoa(C);			//
			messageToSend = "jogo "+Ls+"/"+Cs;	
			break;
		}
		
		fmt.Fprintf(conn, messageToSend + "\n");			// escreve output
}

// avalia o input 
/*
	ou envia jogo X/L ou envia desisto
	caso contrario continua a pedir input ate ser valido
*/
func evalInput(){

	stop_input := true;			// variavel de controlo
	var input string;			// input do jogador
	var message []string;		// string auxiliar
	for stop_input{				// enquanto nao houver um comando valido continua em loop

		input,_ = bufio.NewReader(os.Stdin).ReadString('\n');				

		switch{		// enquanto o input nao for um dos seguintes continua a pedir
			
			case len(input) > 4 && strings.EqualFold(input[0:4],"jogo"):	// gera a jogada e envia ao visualizador
				
				message = strings.Split(input, " ");						// faz split da msg
			    message2 := strings.Split(message[1],"/");					// split novamente por causa do /
			    L := message2[0];											// ja tem L
			    C2  := strings.Split(message2[1],"\n");						// split do \n e agora tem C 

				Ls,err := strconv.Atoi(L);				// conversao de string para int
				Cs,err2 := strconv.Atoi(C2[0]);			//

				if(err != nil && err2 != nil){			// se forem valores nao inteiros (so e' aceite inteiros)
					fmt.Println("Valores errados");

				}else{	
					pos:= offset(int(Ls),int(Cs),tamanho);					// calcula posicao

					if (!verifica(tabuleiro,pos)) {							// se nao gerar erro faz uma jogada,  caso contrario, erro
						play_the_game(tabuleiro, Ls,Cs);			// permite o jogador jogar
						stop_input = false;									// para o ciclo

					}else{
						fmt.Println("Posicao invalida");					// msg de erro
					}
				}
		
				break;

			case strings.EqualFold(input,"desisto\n"):				// se for desisto
				stop_input = false;
				continueGame = false;								// termina o jogo
				fmt.Fprintf(conn,input);							// escreve output
				break;

			default:
					// ignora
				break;
		}

		fmt.Print("\n");
	}				
}

// faz um print da mensagem recebida 
func printOtherPlayerMessage(who string, message string){
	fmt.Print(who);
	fmt.Print(": ");
	fmt.Println(message+"\n");
}

func main(){
	
	// connection to server
	conn , _ = net.Dial("tcp","localhost:31626");					// connecao ao servidor
	var message string;												// mensagem

	continueGame = true;											//  estado do jogo. false significa que o jogo começou

	for continueGame {

		message , _  = bufio.NewReader(conn).ReadString('\n');		// le input (output do outro jogador)

		switch{	// reage ao input

			case strings.EqualFold(message,"nome\n"):				// se for nome
				printOtherPlayerMessage("Visualizador",message);	// print da msg do outro						

				for true{
					nome,_ := bufio.NewReader(os.Stdin).ReadString('\n');	// pede input
					if strings.EqualFold(nome[0:5],"nome "){ 				// so envia o comando valido
						fmt.Fprintf(conn, nome + "\n");						// escreve output
						break;
					}
				}
				break;

			case len(message) > 7 && strings.EqualFold(message[0:7],"tamanho"):	// 	recebe tamanho
				b := strings.Split(message, " ");								// split da msg

				c := strings.Split(b[1],"\n");									// split novamente por causa do \n
				size,_ := strconv.Atoi(c[0]);									// ja tem o tamanho

				tamanho = int(size);
				tabuleiro = tabuleirovazio(tamanho);							// gera tabuleiro vazio
				printOtherPlayerMessage("Visualizador",message);				
				break;

			case strings.EqualFold(message,"tamanho\n"):						// quando so recebe o comando tamanho (default size = 3)
				tabuleiro = tabuleirovazio(3);			
				tamanho = 3;
				break;

			case strings.EqualFold(message,"comeca X\n"):			// define os simbolos
				current_symbol = "X";								// o seu simbolo
				opositeSymbol = "O";								// simbolo do outro jogador
				printOtherPlayerMessage("Visualizador",message);
				break;

			case strings.EqualFold(message,"comeca O\n"):			// define os simbolos
				current_symbol = "O";								// o seu simbolo
				opositeSymbol = "X";								// simbolo do outro
				printOtherPlayerMessage("Visualizador",message);
				break;

			case strings.EqualFold(message,"desisto\n"):			// jogo termina porque o outro desistiu			
				printOtherPlayerMessage(opositeSymbol,message);
				continueGame = false;
				break;

			case strings.EqualFold(message, "ganhei\n"):			// termina porque o outro ganhou
				continueGame = false;
				printOtherPlayerMessage(opositeSymbol,message);
				break;

			case strings.EqualFold(message,"empatamos\n"):			// termina porque empataram
				continueGame = false;					
				printOtherPlayerMessage(opositeSymbol,message);
				break;

			case strings.EqualFold(message,"espera\n"):				// fica a espera de outro comando
				printOtherPlayerMessage("Visualizador",message);
				break; 
 
			case strings.EqualFold(message,"joga\n"):				// permite jogar
				printOtherPlayerMessage("Visualizador",message);
				evalInput();		// enviar um comando
				break;

			case len(message) > 4 && strings.EqualFold(message[0:4],"jogo"):	// recebe joga L/C
				printOtherPlayerMessage(opositeSymbol,message);

				message2 := strings.Split(message, " ");					// split dos spacos
			    message3 := strings.Split(message2[1],"/");					// split por causa da /
			    L := message3[0];											// ja tem L
			    C2  := strings.Split(message3[1],"\n");						// split por causa do \n e agora ja tem C

				Ls,_ := strconv.Atoi(L);								// conversao de string para int
				Cs,_ := strconv.Atoi(C2[0]);							//
				pos := offset(int(Ls),int(Cs),tamanho);					// calcula posicao

				fmt.Println("Updated board:\n");
				preencheposicoes(tabuleiro,pos,opositeSymbol); 		// preenche posicao no seu tabuleiro
				print_tabuleiro(tabuleiro);							// um printzito do tabuleiro
				break;
				
			default:												// inputs descartados (seja recebido algo invalido nao influenciar o flow)
				break;
		}
	}
}
