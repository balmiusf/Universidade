package JogoDoGalo;

//31626 - Andre Figueira

public class JogoDoGalo{
	private int tabuleiro[][];
	int Xplayer = 1;
	int Oplayer = 2; 
	private int victorias;
	private int derrotas;
	private int empates;
	private SimplyLinkedList<JogoDoGalo> lista;
	private int turnCounter;
	
	
	  public JogoDoGalo(){
		  this.tabuleiro = new int[3][3]; 
		  this.victorias = 0;
		  this.derrotas = 0;
		  this.empates = 0;		  
		  this.turnCounter = 0;
		  this.lista = new SimplyLinkedList<JogoDoGalo>();
		  
		  
		  		  
	  }
	  
	  //diz quem ganhou o jogo
	  public int vencedor(){
		//right collum
		  if (tabuleiro[0][0] == tabuleiro[0][1] && tabuleiro[0][1] == tabuleiro[0][2] && tabuleiro[0][0]!=0){
			  if (tabuleiro[0][0]==Xplayer){
					return Xplayer;
				}else{
					return Oplayer;
				}
		  }
  
		 //mid collum
		  if (tabuleiro[1][0] == tabuleiro[1][1] && tabuleiro[1][1] == tabuleiro[1][2] && tabuleiro[1][0]!=0){
			  if (tabuleiro[1][0]==Xplayer){
					return Xplayer;
				}else{
					return Oplayer;
				}
		  }
		 
		//left col
		  if (tabuleiro[2][0] == tabuleiro[2][1] && tabuleiro[2][1] == tabuleiro[2][2] && tabuleiro[2][0]!=0){
			  if (tabuleiro[2][0]==Xplayer){
					return Xplayer;
				}else{
					return Oplayer;
				}
		  }
 
		  //top row
		  if (tabuleiro[0][0] == tabuleiro[1][0] && tabuleiro[1][0] == tabuleiro[2][0] && tabuleiro[0][0]!=0){
			if (tabuleiro[0][0]==Xplayer){
				return Xplayer;
			}else{
				return Oplayer;
			}
			}
					 
		//mid row
		  if (tabuleiro[0][1] == tabuleiro[1][1] && tabuleiro[1][1] == tabuleiro[2][1] && tabuleiro[0][1]!=0){
			if (tabuleiro[0][1]==Xplayer){
				return Xplayer;
			}else{
				return Oplayer;
			}
		}
		
			
			//bottom row
		  if (tabuleiro[0][2] == tabuleiro[1][2] && tabuleiro[1][2] == tabuleiro[2][2] && tabuleiro[0][2]!=0){
			if (tabuleiro[0][2]==Xplayer){
				return Xplayer;
			}else{
				return Oplayer;
			}
		  }
		
			
			//left diagonal
		  if (tabuleiro[0][0] == tabuleiro[1][1] && tabuleiro[1][1] == tabuleiro[2][2] && tabuleiro[0][0]!=0){
			if (tabuleiro[0][0]==Xplayer){
				return Xplayer;
			}else{
				return Oplayer;
			}
		  }
		
			
			//right diagonal
		  if (tabuleiro[0][2] == tabuleiro[1][1] && tabuleiro[1][1] == tabuleiro[2][0] && tabuleiro[0][2]!=0){
			if (tabuleiro[0][2]==Xplayer){
				return Xplayer;
			}else{
				return Oplayer;
			}
		  }
		
		 
		//se nenhuma condicao se verificar, entao sera um empate
		  return 0; 
		
	  }
	  
	  //retorna o c—digo hash do objecto
	  //representa um codigo unico para cada objecto
	  
	  public int hashcode(){
		int hashcode = 0;
		int m = 0;
		int[] primos = {1,3,5,7,11,13,17,19,23};
		
		for(int i = 0;i<3;i++){
			for (int j = 0; j<3; j++){
				hashcode += tabuleiro[i][j] * primos[m];
				m++;
			}
		}
		
	    return hashcode;
	  }

	  //verifica se o tabuleiro esta cheio
	  public boolean isBoardFull(){
		  for(int i = 0;i<3;i++){
			 for(int j = 0;j<3;j++){
				 if(tabuleiro[i][j]==0){
					 return false;
				 }
			 }
		  }
		  return true;
	  }
	  
	  public boolean acabou(){ 
		//right col
		  if (tabuleiro[0][0] == tabuleiro[0][1] && tabuleiro[0][1] == tabuleiro[0][2] && tabuleiro[0][0]!=0){
			  return true;
		}
		  
		 //mid col 
		  if (tabuleiro[1][0] == tabuleiro[1][1] && tabuleiro[1][1] == tabuleiro[1][2] && tabuleiro[1][0]!=0){
			  return true;
		} 
		//left col
		  if (tabuleiro[2][0] == tabuleiro[2][1] && tabuleiro[2][1] == tabuleiro[2][2] && tabuleiro[2][0]!=0){			  
			  return true;
		}   
		  //top row
		if (tabuleiro[0][0] == tabuleiro[1][0] && tabuleiro[1][0] == tabuleiro[2][0] && tabuleiro[0][0]!=0){			
			return true;
		}
			 
			//mid row
		if (tabuleiro[0][1] == tabuleiro[1][1] && tabuleiro[1][1] == tabuleiro[2][1] && tabuleiro[0][1]!=0){			
			return true;
		}
			
			//bot row
		if (tabuleiro[0][2] == tabuleiro[1][2] && tabuleiro[1][2] == tabuleiro[2][2] && tabuleiro[0][2]!=0){			
			return true;
		}
			
			//left diagonal
		if (tabuleiro[0][0] == tabuleiro[1][1] && tabuleiro[1][1] == tabuleiro[2][2] && tabuleiro[0][0]!=0){			
			return true;
		}
			
			//right diagonal
		if (tabuleiro[0][2] == tabuleiro[1][1] && tabuleiro[1][1] == tabuleiro[2][0] && tabuleiro[0][2]!=0){			 
			return true;
		}
			
		//if board is full
		if(isBoardFull()){
			return true;
		}			
		return false; 
	}
	  
	  //turn for X player
	  //metodo auxiliar que coloca 1 ( = X no toString) na posicao desejada
	  public void Xturn(int row,int col){
		  tabuleiro[row][col] = 1;
	  }
	  
	  //turn for O player
	  //metodo auxiliar que coloca 2 ( = O no toString) na posicao desejada
	  public void Oturn(int row,int col){
		  tabuleiro[row][col] = 2;
	  }
	  
	  //faz uma jogada na cŽlula indicada se est‡ vazia, se n‹o est‡ vazia retorna false
	  
	  boolean joga(int row, int col){
		  
		  if(jogador(row,col)!=0){ //verifica se esta vazio
			  return false;
		  }else{
			  
			  this.turnCounter++; //contador, se for impar joga X caso contrario joga O
			  
			  if(turnCounter % 2 == 0){
				  Oturn(row,col);
			  }else{
				  Xturn(row,col);
			  }
			  
			  return true;
		  }
	  }
	  
	  //verifica se esta vazio
	  boolean isEmpty(int row, int col){
		  if (jogador(row,col)!=0){
			  return false;
		  }else{
			  return true;
		  }
	  }
	 	 
	//metodo que permite saber a evolucao do jogo que esta a decorrer
	public void gamePath(JogoDoGalo currentBoard) throws InvalidNodeException{
		  this.lista.add(currentBoard.clone());	 

	}

	public SimplyLinkedList<JogoDoGalo> getLista() throws InvalidNodeException {	
		return lista;
	}

	
	//retorna o movimento actual na localiza‹o dada, i.e qual o jogador naquela posi‹o
	  int jogador(int row, int col){		  
	    return tabuleiro[row][col];
	  }
	  
	  
	  
	  //incrementa Victorias(V) ou Derrotas (D) ou Empate(E) consoante o "vencedor" que receber
	  public void incrementarVDE(int vencedor){
		  
		  	if( vencedor == 0 ){
				this.empates++;}
			
			if( vencedor == Xplayer ){
				this.derrotas++;}
			
			if( vencedor == Oplayer ){
				this.victorias++;}
			
	  }
	  
	  public int getVictory(){
		 return this.victorias;
	  }
	 
	  
	  public int getDefeat(){
		  return this.derrotas;
	  }
	 
	  
	  public int getTie(){
		  return this.empates;
	  }
	 
	  public int getTotalJogos(){
		  return this.getVictory() + this.getDefeat() + this.getTie();
	  }
	  
	  //permite returnar o valor do win ratio relativo ao jogador inteligente
	  //a primeira condicao serve para impedir que haja problemas relacionados com NaN (Not a Number)
	  public double getWinRatio(){
		  if (this.getTotalJogos()==0){
			  return 0.0;
		  }else{
			  return ((double) this.getVictory()) / ((double)this.getTotalJogos());
		  }
	  }
	  
	  //permite criar um clone do tabuleiro
	  public JogoDoGalo clone(){
		  JogoDoGalo clone = new JogoDoGalo();
		  
		  	for(int i = 0 ; i < 3 ; i++){
		  		for (int j = 0 ; j < 3 ; j++){
		  			clone.tabuleiro[i][j] = this.tabuleiro[i][j];
		  		}
		  	}
			clone.Xplayer = this.Xplayer ;
			clone.Oplayer = this.Oplayer; 
			clone.victorias = this.victorias;
			clone.derrotas = this.derrotas;
			clone.empates = this.empates;
			clone.turnCounter = this.turnCounter;
			
			for(int m = 0 ; m < this.lista.size();m++){
				try {
					clone.lista.add(this.lista.get(m));
					
				} catch (InvalidNodeException e) {
					
					e.printStackTrace();
				}
			}
			
		return clone;
		  
	  }
	  
	  //retorna reperesenta‹o em String do tabuleiro	    
	  public String toString(){
		  StringBuilder sb = new StringBuilder( );
		  
			for (int i=0; i<3; i++) {
			    for (int j=0; j<3; j++){
			    	
				if (tabuleiro[i][j] == 0){
				    sb.append(" _");}
			    
				else if (tabuleiro[i][j] == Xplayer){
				    sb.append(" X");}
			    
				else if (tabuleiro[i][j] == Oplayer){
				    sb.append(" O");}
			    }
			    sb.append('\n');
			    
			}
			return sb+"";
	    }
	  
	}


