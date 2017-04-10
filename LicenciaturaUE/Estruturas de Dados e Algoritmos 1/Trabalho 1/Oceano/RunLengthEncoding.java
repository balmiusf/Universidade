package Oceano;


/**
 *  The RunLengthEncoding class defines an object that run-length encodes an
 *  Ocean object.  Descriptions of the methods you must implement appear below.
 *  They include constructors of the form
 *
 *      public RunLengthEncoding(int i, int j, int starveTime);
 *      public RunLengthEncoding(int i, int j, int starveTime,
 *                               int[] runTypes, int[] runLengths) {
 *      public RunLengthEncoding(Ocean ocean) {
 *
 *  that create a run-length encoding of an Ocean having width i and height j,
 *  in which sharks starve after starveTime timesteps.
 *
 *  The first constructor creates a run-length encoding of an Ocean in which
 *  every cell is empty.  The second constructor creates a run-length encoding
 *  for which the runs are provided as parameters.  The third constructor
 *  converts an Ocean object into a run-length encoding of that object.
 *
 *  See the README file accompanying this project for additional details.
 */

public class RunLengthEncoding {
	private SimplyLinkedList<Run> runLenght;
	private int width;
	private int height;
	private int starveTime;
	private int index = 0; //index da lista ligada
	
  /**
   *  Define any variables associated with a RunLengthEncoding object here.
   *  These variables MUST be private.
   */



  /**
   *  The following methods are required for Part II.
   */

  /**
   *  RunLengthEncoding() (with three parameters) is a constructor that creates
   *  a run-length encoding of an empty ocean having width i and height j,
   *  in which sharks starve after starveTime timesteps.
   *  @param i is the width of the ocean.
   *  @param j is the height of the ocean.
   *  @param starveTime is the number of timesteps sharks survive without food.
   */

  public RunLengthEncoding(int i, int j, int starveTime) {
    
	  this.width = i;
	  this.height = j;
	  this.starveTime = starveTime;
	  
	  runLenght = new SimplyLinkedList<Run>();
	  runLenght.add(new Run(".",i*j));
	  
  }

  /**
   *  RunLengthEncoding() (with five parameters) is a constructor that creates
   *  a run-length encoding of an ocean having width i and height j, in which
   *  sharks starve after starveTime timesteps.  The runs of the run-length
   *  encoding are taken from two input arrays.  Run i has length runLengths[i]
   *  and species runTypes[i].
   *  @param i is the width of the ocean.
   *  @param j is the height of the ocean.
   *  @param starveTime is the number of timesteps sharks survive without food.
   *  @param runTypes is an array that represents the species represented by
   *         each run.  Each element of runTypes is Ocean.EMPTY, Ocean.FISH,
   *         or Ocean.SHARK.  Any run of sharks is treated as a run of newborn
   *         sharks (which are equivalent to sharks that have just eaten).
   *  @param runLengths is an array that represents the length of each run.
   *         The sum of all elements of the runLengths array should be i * j.
 * @throws InvalidNodeException 
   */



  public RunLengthEncoding(int i, int j, int starveTime,
                           int[] runTypes, int[] runLengths) throws InvalidNodeException {
	  
	  this.width = i;
	  this.height = j;
	  this.starveTime = starveTime;
	  int count = 0;
	  int l = 0;
	  
	  runLenght = new SimplyLinkedList<Run>();
	  
	  while(count != i*j){ //so termina se o tamanho do runlenght igual ao i*j - alterar para igual
		  
		  if (runTypes[l] == Ocean.EMPTY){
			  runLenght.add(new Run(".",runLengths[l]));
		  }
		  if (runTypes[l] == Ocean.FISH){
			  runLenght.add(new Run("F",runLengths[l]));
		  }
		  if (runTypes[l] == Ocean.SHARK){
			  runLenght.add(new Run("S"+1,runLengths[l]));
		  }

		  if(runTypes[l] != Ocean.SHARK && runTypes[l] != Ocean.FISH && runTypes[l] != Ocean.EMPTY){
			 runLenght.add(new Run(".",runLengths[l]));
		  }
		  count = count + runLengths[l];
		  l++;
		  if (count > i*j){
			  System.out.println("sum of runlengths superior to size of ocean");
			  System.exit(0);
		  }
	  }
	  arrange();
  }

  /**
   *  restartRuns() and nextRun() are two methods that work together to return
   *  all the runs in the run-length encoding, one by one.  Each time
   *  nextRun() is invoked, it returns a different run (represented as a
   *  TypeAndSize object), until every run has been returned.  The first time
   *  nextRun() is invoked, it returns the first run in the encoding, which
   *  contains cell (0, 0).  After every run has been returned, nextRun()
   *  returns null, which lets the calling program know that there are no more
   *  runs in the encoding.
   *
   *  The restartRuns() method resets the enumeration, so that nextRun() will
   *  once again enumerate all the runs as if nextRun() were being invoked for
   *  the first time.
   *
   *  (Note:  Don't worry about what might happen if nextRun() is interleaved
   *  with addFish() or addShark(); it won't happen.)
   */


  /**
   *  restartRuns() resets the enumeration as described above, so that
   *  nextRun() will enumerate all the runs from the beginning.
   */

  public void restartRuns() {
	  this.index = 0; //reinicia o index para 0, por outras palavras volta para o inicio da lista
  }

  /**
   *  nextRun() returns the next run in the enumeration, as described above.
   *  If the runs have been exhausted, it returns null.  The return value is
   *  a TypeAndSize object, which is nothing more than a way to return two
   *  integers at once.
   *  @return the next run in the enumeration, represented by a TypeAndSize
   *          object.
 * @throws InvalidNodeException 
   */

  public TypeAndSize nextRun() throws InvalidNodeException {
	  if(this.index>=this.runLenght.size()){ //quando nao tem mais runs para devolver retorna null, isto quando o index e' superior ao tamanho da lista
		return null;
	}else{
		String type = this.runLenght.get(index).getRun().substring(0,1); // exemplo: se for Tubarao -> da me so o S e nao S1
			int type2 = 0; //type 2 por default e' Ocean.EMPTY
			
			if (type.equals("S"+"")){
				type2 = Ocean.SHARK;
			}
			if(type.equals("."+"")){
				type2 = Ocean.EMPTY;
			}
			if(type.equals("F"+"")){
				type2 = Ocean.FISH;
			}
	
			int size = this.runLenght.get(index).getSize();
			TypeAndSize nextRun = new TypeAndSize(type2,size);
			this.index++;
			return nextRun;
	}
  }

  /**
   *  toOcean() converts a run-length encoding of an ocean into an Ocean
   *  object.  You will need to implement the three-parameter addShark method
   *  in the Ocean class for this method's use.
   *  @return the Ocean represented by a run-length encoding.
   */

 public Ocean toOcean() throws InvalidNodeException {
    Ocean oceano = new Ocean(width,height,starveTime);
    restartRuns();
    int runSize = 1; //tamanho da run
    int x = 0;
    int y = 0;
    int feeding = 1;
    TypeAndSize temp = nextRun();
	while(temp!=null){ //termina quando nao houver mais runs para devolver
		
				/*	percorre array do objecto de tipo Ocean
				 *	efectua as runs, se uma run for igual a Ocean.EMPTY ou Ocean.FISH ou Ocean.SHARK
				 *	inicia o contador. este contador serve para saber quantas Bestas devera adicionar seguidas
				 *	Enquanto o contador nao for igual ao tamanho da respectiva Run, incrementa o contador, e as coordenadas,
					no caso de ser um canto x==width (nao pode ser width-1 porque x e' incrementado antes) passa para a proxima linha 
				 */
		
				if (temp.getType()==Ocean.EMPTY){
					runSize = 0; 
					while(runSize!=temp.getSize()){						
						x++;
						if(x==width){
							x = 0;
							y++;
						}
						runSize++;
					}
				}
				
				/*
				 * no caso de ser um tubarao, sera necessario retirar da getRun() o valor do feeding, visto que se trata duma String
				 * basta fazer subString e converter para inteiro
				 * obtemos o feeding da lista ligada usando o index que e' usado na nextRun()
				 */
				if(temp.getType()==Ocean.SHARK){;
					runSize = 0;
					while(runSize!=temp.getSize()){
						feeding = Integer.parseInt(runLenght.get(index-1).getRun().substring(1,2));
						oceano.addShark(x, y,feeding);
						x++;						
						if(x==width){
							x = 0;
							y++;
						}
						runSize++;
					}
				}
				
				if(temp.getType()==Ocean.FISH){
					runSize = 0;
					while(runSize!=temp.getSize()){
						oceano.addFish(x, y);
						x++;
						if(x==width){
							x = 0;
							y++;
						}
						runSize++;
					}
				}
				temp = nextRun();
	}
	restartRuns(); //reinicar o index
    return oceano;
  }

  /**
   *  The following method is required for Part III.
   */

  /**
   *  RunLengthEncoding() (with one parameter) is a constructor that creates
   *  a run-length encoding of an input Ocean.  You will need to implement
   *  the sharkFeeding method in the Ocean class for this constructor's use.
   *  @param sea is the ocean to encode.
 * @throws InterruptedException 
 * @throws InvalidNodeException 
   */

  public RunLengthEncoding(Ocean sea) throws InvalidNodeException, InterruptedException {
	this.width = sea.width();
	this.height = sea.height();
	this.starveTime = sea.starveTime();
	
	int runSize = 1;   //variavel que soma o numero de Bestas diferentes seguidas quando percorre o array
	runLenght = new SimplyLinkedList<Run>(); //reinicar a lista
    for(int y = 0;y<sea.height();y++){
    	for(int x = 0;x<sea.width();x++){
    		
    		if(x != width-1){ //enquanto nao for um canto
    			//verifica se o conteudo da celula e igual ao da seguinte, se sim incrementa o runSize
    			if(sea.cellContents(x, y)==sea.cellContents(x+1, y)){
    				runSize++;
    				
    				//caso seja um tubarao
    				if(sea.cellContents(x, y)==Ocean.SHARK){
    					//verifica se os feedings sao diferentes
    					if(sea.sharkFeeding(x, y)!=sea.sharkFeeding(x+1, y)){
    						//se sim, entao sao tubaroes sao diferentes e cria uma nova run
    						runLenght.add(new Run("S"+sea.sharkFeeding(x, y),runSize-1));
    						runSize = 1; //e reiniciar o contador de volta a 1
    					}
    				}
    			}else{
    				//caso as celulas nao serem iguais, cria uma nova Run e reinicia o runSize
    				
    				if (sea.cellContents(x, y)==Ocean.EMPTY){
    					runLenght.add(new Run(".",runSize));   					
    					runSize = 1;
    				}
    				if(sea.cellContents(x, y)==Ocean.FISH){
    					runLenght.add(new Run("F",runSize));
    					runSize = 1;
    				}
    				
    				if(sea.cellContents(x, y)==Ocean.SHARK){
    					
    					runLenght.add(new Run("S"+sea.sharkFeeding(x, y),runSize));
    					runSize = 1;
    				}
    			}
    		}else{
    			/*
    			 * exactamente o mesmo procedimento da situaçao anterior mas com a diferença que se for um canto a celula seguinta estara 
    			 * na primeira casa da linha seguinte
    			 */
    			
    			if(sea.cellContents(x, y)==sea.cellContents(x+1, y+1)){
    		
    				runSize++;
    			
    				if(sea.cellContents(x, y)==Ocean.SHARK){
  
    					if(sea.sharkFeeding(x, y)!=sea.sharkFeeding(x+1, y+1)){
    
    						runLenght.add(new Run("S"+sea.sharkFeeding(x, y),runSize-1));
    						runSize = 1;
    					}
    				}
    			}else{
    				if (sea.cellContents(x, y)==Ocean.EMPTY){
    					runLenght.add(new Run(".",runSize));
    					
    					runSize = 1;

    				}
    				if(sea.cellContents(x, y)==Ocean.FISH){
    					runLenght.add(new Run("F",runSize));
    					
    					runSize = 1;

    				}
    				if(sea.cellContents(x, y)==Ocean.SHARK){
    				
    					runLenght.add(new Run("S"+sea.sharkFeeding(x, y),runSize));
    					runSize = 1;

    				}
    			}
    		}
    					
    	}
    }
    /*
     * esta condiçao que se segue refere-se que se a ultima posicao do array for igual a primeira, nesse caso 
     *  a situacao e' ignorada e e' efectuado o mesmo processo como se fossem diferentes
     */
    
    if(sea.cellContents(this.width-1, this.height-1)==sea.cellContents(0, 0)){
    	if(sea.cellContents(0, 0)==Ocean.SHARK){
    		if(sea.sharkFeeding(0, 0)!=sea.sharkFeeding(this.width-1, this.height-1)){
    			
    		}else{
    			runLenght.add(new Run("S"+sea.sharkFeeding(this.width-1, this.height-1),runSize-1));
    		}
    		
    	}
    	if(sea.cellContents(0, 0)==Ocean.FISH){
    		runLenght.add(new Run("F",runSize-1));
    	}
    	if(sea.cellContents(0, 0)==Ocean.EMPTY){
    		runLenght.add(new Run(".",runSize-1));
    	}
    }
   
    check();
  }

  /**
   *  The following methods are required for Part IV.
   */

  /**
   *  addFish() places a fish in cell (x, y) if the cell is empty.  If the
   *  cell is already occupied, leave the cell as it is.  The final run-length
   *  encoding should be compressed as much as possible; there should not be
   *  two consecutive runs of sharks with the same degree of hunger.
   *  @param x is the x-coordinate of the cell to place a fish in.
   *  @param y is the y-coordinate of the cell to place a fish in.
 * @throws InterruptedException 
 * @throws InvalidNodeException 
   */
  
  /*
   * metodo auxiliar que verifica as runs e as agrupa correctamente
   * por exemplo: F12 seguido de um F3, ao percorrer este metodo passa a ser F15
   */
  
  public void arrange() throws InvalidNodeException{
	  int size = 0;
	  int i = 0;
	  while(i!=runLenght.size()-1){	  
		  if(runLenght.get(i).getRun().equals(runLenght.get(i+1).getRun())){
			  	size = runLenght.get(i+1).getSize();
				runLenght.get(i).setSize(size+runLenght.get(i).getSize());
				runLenght.remove(i+1);	
				i = 0;
		  }else{
			  i++;
		  }		  
	  }	  
  }
  
  public int mod(int n, int d) {
      if (n >= 0){
          return n % d;}
  	else{
    	  return (n % d + d) % d;}
        
  }
  
  public void addFish(int x, int y) throws InvalidNodeException, InterruptedException {
	  x = mod(x,this.width);
	  y = mod(y,this.height);
	  
	int count = -1;	 //referencia da posicao
	int distance = 0;	//indica qual a distancia desde o (0,0) ate (x,y) (percorrendo o array)
	loop:
		for(int y2 = 0;y2<this.height;y2++){
			for(int x2 = 0;x2<this.width;x2++){
				distance++;
				if(x2==x && y2==y){			
					break loop;}
			}
		}

	int runSizeSum = 0;
	for(int index2 = 0;index2<runLenght.size();index2++){ 
		runSizeSum += runLenght.get(index2).getSize(); //soma os tamanhos da runs da lista ligada
		count++; 
		
		if(runSizeSum>=distance){ //de acordo com a distancia em Distance, nao pode ser maior ate uma certa soma das runs
			break;
		}
	}
	
	int distance_2 = runSizeSum-distance; //permite saber a partir do fim da run a distancia do fim ate a posicao desejada, ou seja permitindo localizar a posicao que se quer como se fosse para introduzir algo num array 
	if(distance_2<0){
		distance_2 = 0-distance_2; //sempre positiva
	}
	
	if(runLenght.get(count).getRun()!="."){ //so se pode adicionar numa casa vazia
		System.out.println("CELL IS NOT EMPTY");
	}else{
		if(distance_2==0){ //se for 0 significa que se encontra na ultima "celula" da run, ou seja se a distance e' igual a runSizeSum. exemplo:
			// a primeira run sendo de tamanho 3, entao se for convertido em oceano seria: (0,0), (1,0) e (2,0) entao distance_2=0 significa que runSizeSum-Distance = 0; logo (2,0)
			if(runLenght.get(count).getSize()!=1){ //esta condicao acontece se o tamanho for 1
				runLenght.add(count,new Run(".",runLenght.get(count).getSize()-1)); //crio uma nova run igual a seguinte so que decremento -1
				runLenght.remove(count+1); //retiro a run que ta a frente
				runLenght.add(count+1,new Run("F",1)); //para adicionar um peixe
			}else{//caso contrario basta substituir por um peixe
				runLenght.remove(count);
				runLenght.add(count,new Run("F",1));
			}
			
		}else{ //caso o distance_2 nao seja 0 significa que pode ser numa posicao alteatoria num espaco vazio qualquer excepto na condicao apresentada em cima
			if(distance_2!=runLenght.get(count).getSize()-1){ 
				/*
				 * nesta condicao, vem o problema de espacos vazios antes e depois quando se adiciona a o peixe, implica usar o distance_2 que indica a distancia da 
				 * posicao desejada ao "fim" da Run. Para resolver este problema, cria se outra run com runLenght menos distance_2 menos 1 
				 * subtitui se a run por um peixe e adiciona-se uma run depois desta com o distance_2
				 */
				runLenght.add(count,new Run(".",runLenght.get(count).getSize()-distance_2-1)); 
				runLenght.remove(count+1);
				runLenght.add(count+1,new Run("F",1));
				runLenght.add(count+2,new Run(".",distance_2));
			}else{ //referente a primeira celula da run ou seja tomando o exemplo apresentado em cima refere-se a (0,0)
				runLenght.add(count,new Run("F",1));
				runLenght.add(count+1,new Run(".",runLenght.get(count+1).getSize()-1));
				runLenght.remove(count+2);
			}
		}
	}
	/*
	 * addFish(x,y) e addShark(x,y) adiciona mas nao agrupa, essa funcao cabe ao metodo a seguir de agrupar
	 */
	arrange(); 
    check();
  }

  /**
   *  addShark() (with two parameters) places a newborn shark in cell (x, y) if
   *  the cell is empty.  A "newborn" shark is equivalent to a shark that has
   *  just eaten.  If the cell is already occupied, leave the cell as it is.
   *  The final run-length encoding should be compressed as much as possible;
   *  there should not be two consecutive runs of sharks with the same degree
   *  of hunger.
   *  @param x is the x-coordinate of the cell to place a shark in.
   *  @param y is the y-coordinate of the cell to place a shark in.
 * @throws InterruptedException 
 * @throws InvalidNodeException 
   */
/*
 * este metodo e igual ao anterior so que em vez de adicionar um peixe adiciona um tubarao  com feeding a 1
 */
  public void addShark(int x, int y) throws InvalidNodeException, InterruptedException {
	  x = mod(x,this.width);
	  y = mod(y,this.height);
	  
	  int count = -1;		
		int distance = 0;	
		loop:
			for(int y2 = 0;y2<this.height;y2++){
				for(int x2 = 0;x2<this.width;x2++){
					distance++;
					if(x2==x && y2==y){			
						break loop;}
				}
			}
		int runSizeSum = 0;
		for(int index2 = 0;index2<runLenght.size();index2++){
			runSizeSum += runLenght.get(index2).getSize();
			count++;
			
			if(runSizeSum>=distance){
				break;
			}
		}
		
		int distance_2 = runSizeSum-distance;
		if(distance_2<0){
			distance_2 = 0-distance_2;
		}
		if(runLenght.get(count).getRun()!="."){
			System.out.println("CELL IS NOT EMPTY");
			
		}else{
			if(distance_2==0){
				if(runLenght.get(count).getSize()!=1){
					runLenght.add(count,new Run(".",runLenght.get(count).getSize()-1)); 
					runLenght.remove(count+1);
					runLenght.add(count+1,new Run("S"+1,1));
				}else{
					runLenght.remove(count);
					runLenght.add(count,new Run("S"+1,1));
				}
			}else{
				if(distance_2!=runLenght.get(count).getSize()-1){
					runLenght.add(count,new Run(".",runLenght.get(count).getSize()-distance_2-1));
					runLenght.remove(count+1);
					runLenght.add(count+1,new Run("S"+1,1));
					runLenght.add(count+2,new Run(".",distance_2));
				}else{
					runLenght.add(count,new Run("S"+1,1));
					runLenght.add(count+1,new Run(".",runLenght.get(count+1).getSize()-1));
					runLenght.remove(count+2);
				}
			}
		}
	arrange(); //efectua o agrupamento
    check();
  }

  /**
   *  check() walks through the run-length encoding and prints an error message
   *  if two consecutive runs have the same contentsx, or if the sum of all run
   *  lengths does not equal the number of cells in the ocean.
 * @throws InvalidNodeException 
 * @throws InterruptedException 
   */

  public void check() throws InvalidNodeException, InterruptedException {
	  int soma = 0;
	  for(int i = 0;i<runLenght.size()-1;i++){
		  soma = soma + runLenght.get(i).getSize();
		  if(runLenght.get(i).getRun().equals(runLenght.get(i+1).getRun())){
			  			 
			  System.out.println("SEQUENCE IS WRONG\n");
				  
		  }
	  }
		 	soma = soma + runLenght.get(runLenght.size()-1).getSize(); //verifica se o tamanho da runLenght esta correcto
			 if(soma!=this.width*this.height){
				 System.out.println("SUM OF VALUES DIFFERENT FROM SIZE OF OCEAN\n");
			 }
			
  }
  
  public String toString(){
	  String result = "";
	  for(int i = 0;i<runLenght.size();i++){
		  try {
			result = result + " ["+ runLenght.get(i).getRun() + " | " + runLenght.get(i).getSize() + " ] ";
		
		  } catch (InvalidNodeException e) {
			e.printStackTrace();
		}
		  
	  }
	  return result;
  }
  
  
  }

//31626 - Andre Figueira

