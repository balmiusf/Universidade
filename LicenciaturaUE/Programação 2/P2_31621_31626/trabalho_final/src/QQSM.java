///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Random;
import java.util.Scanner;
import java.util.ArrayList;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

public class QQSM {
	/// VARIABLES ///
	static int i = 1;			//incrementa peruntas
	static int j = 15;			//decrementa perguntas
	static String jogador;		//nome jogador
	static String current_lvl;  //nivel que o concorrente se encontra
	static String ficheiro;		//ficheiro + caminho
	static Questao_QQSM p;		//objecto temporario
	static File finess;			//objecto file (contem o caminho do ficheiro que e passado por argumento)
	 /// END ///
	 
	 /// ARRAYS ///
	static String[] amigos = {"969837575","919756348","923981269"};									//array com 3 numeros de telefones prontos a ser usados se o utilizador usar a ajuda telefone
	static ArrayList<Questao_QQSM> jogo = new ArrayList<Questao_QQSM>();									//array com todas as perguntas extraidas do ficheiro
	static ArrayList<String> lista_ajudas = new ArrayList<String>();										//array com as ajudas disponiveis
	static int[] moneypatamar = {500,7500,250000};															//patamar segurança
	static int[] moneygiveup = {0,25,50,125,500,750,1500,2500,5000,7500,12500,25000,50000,100000,250000};	//quando desistir
	
	 /// END ///

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	QQSM(){ //constructor
		
	}
	public static File getFiness(){				//saber o valor
		return finess;
	}
	//funçao que simplesmente contem os passos necessarios
	//metodo que contem todos as ajudas e o modo de as processar
	private static void ajudas() throws InterruptedException{

		String[] menorcerteza = {p.getResposta_certa(),p.getResposta_certa(),p.getResposta_certa(),"A","B","C","D"};	//array em que a maior percentagem e' a resposta certa
		String[] aleatorio = {"A","B","C","D"};																		//array com respostas aleatorias
		System.out.println("\n");
		System.out.println("Ajudas disponiveis: ");
		for (int i = 0;i<lista_ajudas.size();i++){									//mostra ao utilizadar as ajudas disponiveis
			System.out.println(i+1+": "+lista_ajudas.get(i));
			
		}
	System.out.println("4 - para sair do menu das ajudas");
		
		Scanner ajuda = new Scanner(System.in);
		String ajuda0 = ajuda.nextLine();

		String[] rv = {"1","2","3","4"};			//respostas de niveis valida
		int valido = 0;								//restricao
		while(valido == 0){							//enquanto for = 0, nao sai do ciclo
			System.out.print("Repita Valor: ");		//este ciclo funciona como restricao de input, ou seja so se pode escrever o que esta dentro do array
			ajuda0 = ajuda.nextLine();				//como tambem serve de "safety check" que permite ao utilizador uma hipotese de pensar se o que escreveu e' o que realmente pretende.
			for (int ue = 0;ue<4;ue++){				//ciclo que percorre o array
				if (ajuda0.toLowerCase().equals(rv[ue].toLowerCase())){
					valido = 1;						//so e so se for igual a um dos valores que tao dentro do array
					break;
				}
			}
		}	
					
		
		Random rand = new Random();													//random, numero utilizado para extrair dos array um elemento aleatorio
		int ciclo = 0;
			for (int u = 0;u<lista_ajudas.size();u++){
			if ( (u+1) == Integer.parseInt(ajuda0)){		//converte para inteiro
				System.out.println("\n");
				System.out.println("Escolheu "+lista_ajudas.get(u));	//mostra a ajuda que escolheu
				System.out.println("\n");
				//nesta ajuda, simplesmente devolve a resposta certa + uma resposta aleatoria
				///50/50///
				if (lista_ajudas.get(u).equals("50/50")){
					System.out.println("reduzir para metade: ");
					while (ciclo !=1){			//atraves deste ciclo permite que a resposta aleatoria nao seja igual a resposta certa
						int valor4 = rand.nextInt(4);
						if (!aleatorio[valor4].equals(p.getResposta_certa())){
							System.out.println(aleatorio[valor4]);
							ciclo = 1;				// = 1 quando se verificar a igualdade, termina o ciclo
						}else{
							valor4 = rand.nextInt(4);	//continua a gerar valores aleatorios ate ser diferente do index que e igual a resposta aleatoria no array
						}
					}
					//quando termina remove do array e devolve os dois valores aleatorios
					System.out.println(p.getResposta_certa());
					lista_ajudas.remove(u);
					break;
				}
				///PUBLICO///
				if (lista_ajudas.get(u).equals("publico")){	
					int r1 = rand.nextInt(100+1);	//entre 0-100%
					int r2 = rand.nextInt(100+1);
					int r3 = rand.nextInt(100+1);
					int r4 = rand.nextInt(100+1);
					while((r1+r2+r3+r4) != 100){	//a soma entre os 4 tem de dar 100
						 r1 = rand.nextInt(100+1);
						 r2 = rand.nextInt(100+1);
						 r3 = rand.nextInt(100+1);
						 r4 = rand.nextInt(100+1);
					}
					System.out.println (" A: "+r1+"%"+" ; "+"B: "+r2+"%"+" ; "+"C: "+r3+"%"+" ; "+"D: "+r4+"%");
					
					lista_ajudas.remove(u);
					break;
				}
												//apos ter sido utilizada e removida do array, termina aqui.
				//// TELEFONE /////															
				if (lista_ajudas.get(u).equals("telefone")){								//semelhante ao anterior
					Random telefone = new Random();
					int randoms = telefone.nextInt(3);										//numero aleatorio do array de amigos
					System.out.println("Calling "+amigos[randoms]+".....");
					
					Thread.sleep(5000); //faz um delay de 5 segundos
					//as respostas variam consoante a dificuldade da pergunta, quanto maior for mais aleatoria sera a resposta
					if (current_lvl.equals("1")){
						System.out.println("Epah... nem precisavas de telefonar, tenho 100% certeza que deves escolher a "+p.getResposta_certa());

					}
					if (current_lvl.equals("2")){
						int valor3 = rand.nextInt(7);
						System.out.println("Epah... essa ja' e' mais complicada mas pah... eu diria  "+menorcerteza[valor3]);

					}
					if (current_lvl.equals("3")){
						int valor = rand.nextInt(4);
						System.out.println("Vou ser honesto contigo... nao faço a menor das ideias, mas tenho mais confiança na "+aleatorio[valor]+" era o que eu escolhia");

					}
						//termina aqui, quando e utilizada, e removida do array
					lista_ajudas.remove(u);
					break;
				}
				
			
			}
		}
			
	
	}
	
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//metodo que adiciona pergunta ao ficheiro
	 //por enquanto so queremos adicionar para o ficheiro
	 private static void add_pergunta() throws IOException{ //aqui vamos adicionar umas quantas perguntas ate o ficheiro estar completo!;
		 	System.out.print("nivel: ");
		 	Scanner input0 = new Scanner(System.in);	//input de Nivel
		 	String nivel = input0.nextLine();
			String[] rv = {"1","2","3"};				//respostas de niveis valida
			int valido = 0;								//restricao
			while(valido == 0){							//enquanto for = 0, nao sai do ciclo
				System.out.print("Repita Valor: ");		//este ciclo funciona como restricao de input, ou seja so se pode escrever o que esta dentro do array
				nivel = input0.nextLine();				//como tambem serve de "safety check" que permite ao utilizador uma hipotese de pensar se o que escreveu e' o que realmente pretende.
				for (int ue = 0;ue<3;ue++){				//ciclo que percorre o array
					if (nivel.toLowerCase().equals(rv[ue].toLowerCase())){
						valido = 1;						//so e so se for igual a um dos valores que tao dentro do array
						break;
					}
				}
			}											//as restantes linhas sao iguais, recebem input e guardam o resultado numa variavel
		 	System.out.print("Pergunta: ");
			Scanner input1 = new Scanner(System.in);
			String pergunta = input1.nextLine();
			while (pergunta.length()==0){
				System.out.print("length<1, nova pergunta: ");
				pergunta = input1.nextLine();
			}
			
			System.out.print("resposta A: ");
			//Scanner input2 = new Scanner(System.in);
			String A = input1.nextLine();
			while (A.length()==0){
				System.out.print("length<1, nova pergunta: ");
				A= input1.nextLine();
			}		
			System.out.print("Resposta B: ");
			//Scanner input3 = new Scanner(System.in);
			String B = input1.nextLine();
			while (B.length()==0){
				System.out.print("length<1, nova pergunta: ");
				B = input1.nextLine();
			}
			System.out.print("resposta C: ");
			//Scanner input4 = new Scanner(System.in);
			String C = input1.nextLine();
			while (C.length()==0){
				System.out.print("length<1, nova pergunta: ");
				C = input1.nextLine();
			}
			System.out.print("Resposta D: ");
			//Scanner input5 = new Scanner(System.in);
			String D = input1.nextLine();
			while (D.length()==0){
				System.out.print("length<1, nova pergunta: ");
				D = input1.nextLine();
			}											//ate este ponto e igual
														//este ultimo input, e igual ao input Nivel, a diferenca e' que ele so pode escolher entre A,B,C,D
			System.out.print("Resposta correcta: ");	//o conceito e exactamente o mesmo.
			//Scanner input6 = new Scanner(System.in);
			String rc = input1.nextLine();
			String[] rv2 = {"A","B","C","D"};
			int valido2 = 0;
			while(valido2 == 0){
				System.out.print("Repita Valor: ");
				rc = input1.nextLine();
				for (int ue = 0;ue<4;ue++){
					if (rc.toLowerCase().equals(rv2[ue].toLowerCase())){
						valido2 = 1;
						break;
					}
				}
			}
			rc = rc.toUpperCase();
		 	
		//termina aqui
		//quando termina o input, os valores sao recebidos pelo constructor que vai criar o formato requerido.
			Questao_QQSM questao = new Questao_QQSM(nivel,pergunta,A,B,C,D,rc);
			questao.add_para_ficheiro();
		
			
	 }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//metodo com o proposito de contar o numero de linhas com tamanho >0 no ficheiro
//por outras palavras ele ta a contar o numero de perguntas
//este metodo e utilizado para garantir que ficheiro em uso tem o minimo de perguntas necessario para executar o jogo
	 private static int tamanho_ficheiro() throws IOException{
		 FileInputStream fin = new FileInputStream(finess); 
		 BufferedReader br = new BufferedReader(new InputStreamReader(fin)); //ler ficheiro
		 String strLine;
		 int n_linhas = 0;
		 while((strLine = br.readLine()) !=null){		//percorre um ciclo 
			 if (strLine.length() != 0){
			 n_linhas = n_linhas + 1;				//sempre que a linha for >0 incrementa
			 }
		 }
		 return n_linhas;						//tem de devolver um valor tipo int
	 }
	 
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//metodo que percorre o  ficheiro e adiciona questao ao array
	 private static void add_to_array() throws IOException{
				FileInputStream fin = new FileInputStream(finess); 					//abrir ficheiro para leitura
				BufferedReader br = new BufferedReader(new InputStreamReader(fin)); //ler ficheiro
				Questao_QQSM questao1;		//objecto temporario
				String linha;			//string temporaria
				//adiciona as linhas para o array
				int n = 1;
				while(n<=15) {
				while ((linha=br.readLine()) != null){						//percorre o ficheiro todo
					if ((linha.length() != 0)){ 								//ele adiciona 7 em 7 linhas, ignora as linhas com espaços em branco ou seja ""
						questao1= new Questao_QQSM();
						
						questao1.setNivel(linha);
						linha=br.readLine();
																				//executa substring porque com o formato do toString()
						questao1.setPergunta(linha.substring(3));				//da classe Questao_QQSM os simbolos (P,A,B,C,D,R) sao duplicados
						linha=br.readLine();									//pois ele quando escreve e quando le, trata-se de objectos Questao_QQSM
						questao1.setRespostaA(linha.substring(3));
						linha=br.readLine();
																				//alterar os valores atraves dos setters
						questao1.setRespostaB(linha.substring(3));
						linha=br.readLine();
	
						questao1.setRespostaC(linha.substring(3));
						linha=br.readLine();

						questao1.setRespostaD(linha.substring(3));
						linha=br.readLine();
						
						questao1.setResposta_certa(linha.substring(3));
						jogo.add(questao1);									//e adicionar ao array
						
					}else{
							 continue;										//se o tamanho for igual a 0, ele continua para a proxima iteracao
						 }
				}
				n++;
				}						
		 }
		 
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//metodo com o proposito de saber o nome do concorrente
	 //nome do jogador
	 private static String jogador(){
		 System.out.print("\n"+"nome do jogador: "+"\n");	
		Scanner nome = new Scanner(System.in);
		jogador = nome.nextLine();
		return jogador;
	 }
	 
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//metodo com o unico proposito de verificar qual e o nivel em que o concorrente se encontra 
	 private static void verifica_nivel() {
		 if (i<=5){
			 current_lvl = "1";
		 }
		 if (i>5 && i<=10){
			 current_lvl = "2";
		 }
		 if (i>10 && i<=15){
			 current_lvl ="3";
		 }
	}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	 //metodo que verifica o patamar en que esta atraves do nivel
	 //dependendo do nivel, ira' depender da resposta
	public static void patamar(){	
		if (current_lvl.equals("1")){		//se perder no nivel 1, significa que nao chegou a nenhum patamar de seguranca, este nao ganhou nada
			System.out.println("Nao chegas-te a um patamar de segurança e erras-te a pergunta, nao conseguis-te ganhar nada");
			System.out.println("Obrigado por jogares!");
		}
		if (current_lvl.equals("2")){		//se perder no nivel 2, esta e' a resposta
			System.out.println("\n");
			System.out.println("Perdes-te mas conseguiste assegurar: "+moneypatamar[0]);
			System.out.println("Obrigado por jogares!");
		}
		if (current_lvl.equals("3") && i<15){	//se perder no nivel 3, esta e' a resposta
			System.out.println("\n");
			System.out.println("Perdes-te mas conseguiste assegurar: "+moneypatamar[1]);
			System.out.println("Obrigado por jogares!");
		}
		if ( i>=15){	//se ganhou o jogo, esta e' a resposta
			System.out.println("\n");
			System.out.println("Parabens! ");
			System.out.println("Ganhaste o jogo de Quem quer ser milionario e ganhas-te o grande premio de "+ moneypatamar[2]);
			System.out.println("Obrigado por jogares!");
		}
	}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	public static void play() throws InterruptedException{
		i = 1;				//fazer reset sempre que ha um new game
		j = 15;				//fazer reset sempre que ha um new game
		Random rand= new Random();
		while (i <=15){		//condicao
			verifica_nivel();	//verifica o nivel actual
			int random = rand.nextInt(j) + 1;
			p = jogo.get(random-1);		//indica um numero random qualquer do array
			if (current_lvl.equals(p.getNivel())){ //se o valor aleatorio corresponder ao nivel
				System.out.println("Pergunta "+(i)+" - "+"Nivel "+p.getNivel()+"\n");
				System.out.println("P: "+ p.getPergunta());
				System.out.println("A: "+p.getRespostaA());
				System.out.println("B: "+p.getRespostaB());
				System.out.println("C: "+p.getRespostaC());
				System.out.println("D: "+p.getRespostaD());
				
				if (lista_ajudas.size() != 0){			//comeca por indicar se quer ajudas ou nao
					System.out.println("\n"+"Deseja utilizar ajudas? 1 - Sim,"+"\n"+"Any other key - Nao");
					Scanner pergunta = new Scanner(System.in);
					String pergunta0 = pergunta.next();
					if (pergunta0.equals("1")){		//caso sim, e feito uma chamada ao metodo ajudas();
						ajudas();
					}
				}//caso a resposta seja 4, ele sai do menu
				
				//o jogador pode desistir quando quiser desde que escreva "desistir" no input
				System.out.println("\n");
				System.out.println("Se pretende desistir, insira desistir");
				System.out.print("Decisao: ");
				Scanner rc = new Scanner(System.in);		//input
				String rc0 = rc.nextLine();
				
				String[] rv = {"A","B","C","D","desistir"};				//array de opcoes validas
				int valido = 0;									//condicao
				while(valido == 0){
					System.out.print("Repita Valor: ");
					rc0 = rc.nextLine();
					for (int ue = 0;ue<5;ue++){					//so termina quando rc0 for igual a um dos valores dentro do array
						if (rc0.toLowerCase().equals(rv[ue].toLowerCase())){
							valido = 1;				//caso se verifique altera-se para um
							break;
						}
					}
				}
				
				if (rc0.toLowerCase().equals("desistir")){
					if (i==1){		//caso tenha  desistido na primeira pergunta e lhe dado 0 euros
						System.out.println("Desiste-te!Conseguis-te assegurar: 0 euros");
					}else{//caso contrario da lhe o equivalente a pergunta anterior
						System.out.println("Desiste-te! Mas conseguis-te assegurar:"+ moneygiveup[i-2]+" euros");
					}
					break;
				}
				if (p.getResposta_certa().toLowerCase().equals(rc0.toLowerCase())){	//caso a resposta esteja certa
					System.out.println("\n");
					System.out.println("Correct!");
					System.out.println("\n");
					
					jogo.remove(random-1);					//remove do array
					i++;					//incrementa pergunta
					j--;					//decrementa o numero de perguntas, ira ter menos uma hipotese no numero aleatorio
				}else{
					if (i>1){				//se for superior a 1
						System.out.println("Infelizmente erraste a pergunta!");
						patamar();
						break;
					}else{		//caso contrario ele indica que nao ganhou nada
						System.out.println("Infelizmente nao chegaste ao primeiro patamar de segurança por isso ganhas te 0 euros");
						System.out.println("Obrigado por jogares!");
						break;
						}
					}
				}
				
			}
			if (i>15){			//visto que o programa termina com i = 16
								//se a condicao se verificar, o output e' que ganhou o jogo
				patamar();
			}
			lista_ajudas.clear();	//faz clear a lista de ajudas
		}

	
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//so permite criar ficheiro .txt
//metodo que recebe um ficheiro, caso nao seja encontra na directoria, o metodo cria um novo ficheiro
//para que se possa jogar 
	private static void ficheiro() throws IOException {
		String path;
		System.out.print("Nome do ficheiro, ");
		System.out.print(" se o ficheiro nao existir na directoria, esse ficheiro e' criado: ");
		Scanner fin = new Scanner(System.in);
		path = fin.nextLine();
		
		File fines = new File(path.toLowerCase());
		if (!fines.exists()){
			fines.createNewFile();
		}
		finess = fines;
	}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//aqui e' onde tudo começa
	public static void main(String args[]) throws IOException, InterruptedException{
		
		for(;;){						//ciclo infinito, so termina com input do utilizador
			lista_ajudas.add("50/50");		//nestas 3 linhas adiciona ao array as 3 ajudas disponiveis
			lista_ajudas.add("telefone");
			lista_ajudas.add("publico");
			
			System.out.println("\n");
			jogo = new ArrayList<Questao_QQSM>();			//faz reset ao array jogo caso no jogo anterior tenha havido alguma desistencia ou falha a responder a pergunta
															//isto garante que o programa começe de novo
			System.out.println("Bem vindo ao Quem Quer Ser Milionario! "
				+ "" + "\n" +"\n"+ "1: Começar" +  "\n" +  "2: Adicionar questao" + "\n"+ "3: Sair");

			Scanner case1 = new Scanner(System.in);
			String input = case1.nextLine();
			String[] rv = {"1","2","3"};					//lista de opcoes disponiveis
			int valido = 0;									//restricao
			while(valido == 0){								//so termina quando != 0
				System.out.print("Repita Valor: ");			//funciona como "safety check" para verificar se o utilizador nao se enganou a escrever ou se introduzio input de forma errada
				input= case1.nextLine();	
				for (int ue = 0;ue<3;ue++){
					if (input.toLowerCase().equals(rv[ue].toLowerCase())){ //percorre o array e verifica a igualdade
						valido = 1;							//caso se verifique, o ciclo termina
						break;	
					}
				}
			}
			switch(Integer.parseInt(input)){				//switch case
			case 1:
				ficheiro();
					while (tamanho_ficheiro() <105){		//verifica o tamanho do ficheiro, tem de ter pelo menos 15 perguntas para iniciar
						System.out.println("\n");			//105 = 15*7
						System.out.println("Numero de perguntas no ficheiro: "+ tamanho_ficheiro() / 7);
						System.out.println("perguntas insuficientes (minimo 15)");
						System.out.println("1 - Sair?");			//caso o ficheiro nao tenha tamanho suficiente e apresentado 3 opcoess
						System.out.println("2 - Adicionar");		//carregar outro ficheiro, adicionar outra pergunta ou terminar o programa
						System.out.println("3 - outro ficheiro");
						input = case1.next();
						//de acordo com os inputs...
						if (input.equals("1")){
							System.exit(0);
						}else if (input.equals("2")){
							System.out.println("Adicione questao: ");
							add_pergunta();
						}else if (input.equals("3")){
							ficheiro();
						}
					}
				jogador();							//input do jogador
				add_to_array();						//adiciona o conteodo do ficheiro para array
				play();								//iniciar jogo
				break;
			case 2:									//se se quer adicionar uma pergunta e necessario primeiro ver se  o ficheiro tem as 15 perguntas necessarias
				ficheiro(); //pede o nome do ficheiro para comecar a adicionar
				add_pergunta();						
				break;
			case 3:	
				System.exit(0);	//termina o programa
				break;
			}
		}
	}
	
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//to do list
		//testar
		// testar com 15 perguntas
	