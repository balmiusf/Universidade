package JogoDoGalo;
//31626 - Andre Figueira
import java.awt.Point;
import java.util.Random;

public class JogInteli{
	HashTable hashtable;
	Random random;
		 
	public JogInteli(){
		this.hashtable = new QuadHashTable();
		this.random = new Random();
	  }
	  
	  //prepara-se para um novo jogo, i.e. prepara-se para registar os tabuleirod do jogo que se vai iniciar
	  //deve ser chamado quando um novo jogo vai comear
	  //deve registar qual o jogador que JogInteli Ž (X ou O)
	
	  public void novoJogo(int jogador){
		  
		  //jogador inteligente é sempre o O
	  }
	  
	  //faz uma jogada baseada na experincia passada, devendo ser escolhido o movimento com maior % de ganhos
	  //#ganhou/(#ganhou+#perdeu+#empatou), em caso de empate decida-se alet—riamnte
	  
	  public void joga(JogoDoGalo t) throws InvalidNodeException{
		   
		  Point point;
		  int row = 0;
		  int col = 0;
		  
		  if(hashtable.ocupados()==0){ 
			  point = randomPosition(t);
			  
			 row = (int) point.getX();
			 col = (int) point.getY();
			 
			 t.joga(row, col);
		  	  
		  }else{	

			point = findBestPosition(t); //metodo auxiliar
			
			row = (int) point.getX();
			col = (int) point.getY();

			t.joga(row, col);
		  }
	}
	   
	  /*
	   * encontra a melhor posicao possivel para o jogador inteligente
	   */
	  
	  public Point findBestPosition(JogoDoGalo actual) throws InvalidNodeException{
		  double maxWinRatio = 0.0; //raccio para comparar inicialmente
		  JogoDoGalo temp;
		  int row = -1;
		  int col = -1;
		  
		  for(int i = 0 ; i < 3 ; i++){
			  for (int j = 0 ; j < 3 ; j++){	
				  
					temp = actual.clone();		//clona para nao alterar o objecto original, e para fazer reset para o estado inicial apos cada iteracao
					  	
					  if(temp.joga(i, j)){ //joga numa posicao
						  	  
						  //procura a configuracao na hash table, se nao esta presente passa para a proxima iteracao
						  //se no fim de todas as iteracoes nao encontrar nenhuma configuracao entao da se as variaveis row e col valores aleatorios
						  if (hashtable.procurar(temp)){
							  
							  temp = hashtable.procurarJogo(temp); //se existe copia
							
							  if (temp.getWinRatio() == maxWinRatio){ //compara o seu win ratio com o max
								 
								  /*
								   * caso seja igual ao maxWinRatio (implica dizer que existe pelo menos uma outra configuracao com a mesma percentagem
								   * entao e escolhido aleatoriamente entre os dois a posicao
								   * 
								   */
								  
								  if(random.nextBoolean()){ 
									  row = i;
									  col = j;
								  }						  
							  }
							  
							  //se o winratio for maior que o maxWinRatio entao substitui-se o valor do maxWinRatio por esse valor
							  //e guarda-se os valores do row e col 
							  if (temp.getWinRatio()>maxWinRatio){ 
								  
								maxWinRatio = temp.getWinRatio();
							 	row = i;
							 	col = j;
							 	
							  }					  
						  }
					  }
			  	 }				  					  
			  }
		  
		  /*
		   * esta condicao permite que seja atribuido a row e col valores aleatorios caso nao estejam
		   * presentes na hashtable. ou seja apos todas as iteracoes, se nunca se verificar que aquela configuracao
		   * nao esta presente na hashtable entao esta condicao em baixo atribui valores aleatorios.
		   */
		  if (row == -1 && col == -1){
			  
			  Point point = randomPosition(actual);
			  row = (int) point.getX();
			  col = (int) point.getY();
		  }
		  
		  return new Point(row,col);
	  }
	  
	  //atribui valores aleatorios
	  public Point randomPosition(JogoDoGalo t){

		  
		  int randRow = random.nextInt(3);
		  int randCol = random.nextInt(3);
		  
		  boolean joga = t.isEmpty(randRow, randCol);
		  
		  while(!joga){
			  randRow = random.nextInt(3);
			  
			  randCol = random.nextInt(3);
			  
			  joga = t.isEmpty(randRow, randCol);
		  }
		  
		  return new Point(randRow,randCol);
		  
	  }
	  
	  //dado que terminal Ž uma configura‹o em que o jogo acabou as configura›es que constituem todas as
	  //jogadas do jogo devem ser registadas como respondentes a voit—ria, empate ou derrota
	  public void acabou(JogoDoGalo terminal) throws InvalidNodeException{
		  	  
			  for(int i = 0 ; i < terminal.getLista().size();i++){
				  
				  //verifica se a configuracao esta presente na hash table
				  //se nao esta presente entao incrementa o numero de victorias ou derrotas ou empates para 1 em todas as configuracoes presentes na lista
				  //e insere na hash table
				  
				  if(!hashtable.procurar(terminal.getLista().get(i))){
					  
					  terminal.getLista().get(i).incrementarVDE(terminal.vencedor());					  
					  hashtable.insere(terminal.getLista().get(i));
					  
				  //caso contrario procura o jogo, e incrementa o numero de victorias ou derrotas ou empates
				 // em todas as configuracoes que se sao iguais
				  }else{
					 			  
					 hashtable.procurarJogo(terminal.getLista().get(i)).incrementarVDE(terminal.vencedor());
					
					  					  
				  	}
				  
			  }
			  
		  }
	  
	  /*
	   * escolhe o primeiro movimento com mais victorias
	   * cria um tabuleiro vazio, e insere um X numa posicao aleatoria
	   * utiliza o metodo sucessores() para saber tabuleiros com as configuracoes seguintes que existem na hashtable
	   */
	  
	  public JogoDoGalo movimentoFavorito() throws InvalidNodeException{
		  JogoDoGalo temp;
		  JogoDoGalo temp2 = new JogoDoGalo();
		  JogoDoGalo[] arrayTemp;
		  int maxWins = 0;
		  
		  
		  for(int i = 0; i < 3 ; i++){
			  for(int j = 0; j < 3 ; j++){
				  temp = new JogoDoGalo(); //inicializa
				  
				  temp.joga(i, j); //joga numa posicao (1)
				  
				  arrayTemp = sucessores(temp); //chama sucessores para saber quais as configuracoes seguintes a (1) que existem na hashtable
				  for(int x = 0 ; x < arrayTemp.length ; x++ ){
					  if(arrayTemp[x] == null){
						  break;
					  }
					  
					  if (arrayTemp[x].getVictory() > maxWins ){
						  temp2 = new JogoDoGalo();
						  maxWins = arrayTemp[x].getVictory();
						  temp2 = arrayTemp[x];
					  }
					  
					  if (arrayTemp[x].getVictory()== maxWins){
						  if(random.nextBoolean()){
							  temp2 = arrayTemp[x];
						  }
					  }
				  }
			  }
			  
		  }
		  
		  return temp2;
	  }
	  
	  // numero de vezes que a configura‹o t foi vista
	  public int numeroDeVezesVisto(JogoDoGalo t){
		  
		if (!hashtable.procurar(t)){
			return 0;
			
		}else{
			
			JogoDoGalo temp = hashtable.procurarJogo(t);
			
			return temp.getTotalJogos(); //o numero de vezes que foi visto e' o numero de jogos que tem
		}
	  }
	  
	  // retorna todas as configura›es que foram jogadas ap—s a configura‹o t
	  public JogoDoGalo[] sucessores(JogoDoGalo t){
		  
		 JogoDoGalo temp;
		 JogoDoGalo[] sucessores = new JogoDoGalo[hashtable.ocupados()]; //garante que ha espaço suficiente ao usar o numero de ocupados na hashtable
		 int index = 0;
		 
		 for(int i = 0 ; i < 3 ; i++){
			 for(int j = 0; j < 3 ; j++){
				 
				temp = t.clone(); //clona para nao fazer modificacoes desnecessarias ao original, e fazer reset ao estado inicial em cada iteracao
						
				temp.joga(i, j); //joga numa posicao
					 
				//e procura na hashtable
					 if(hashtable.procurar(temp)){
						 sucessores[index] = (JogoDoGalo) hashtable.procurarJogo(temp); //e adiciona
						 index++;
				 	}				 
			 }
		 }
	    return sucessores;
	  }
	  
	  
	}
