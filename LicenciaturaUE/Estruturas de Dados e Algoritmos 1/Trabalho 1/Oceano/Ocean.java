package Oceano;



/* Ocean.java */

/**
 *  The Ocean class defines an object that models an ocean full of sharks and
 *  fish.  Descriptions of the methods you must implement appear below.  They
 *  include a constructor of the form
 *
 *      public Ocean(int i, int j, int starveTime);
 *
 *  that creates an empty ocean having width i and height j, in which sharks
 *  starve after starveTime timesteps.
 *
 *  See the README file accompanying this project for additional details.
 */

public class Ocean {

  /**
   *  Do not rename these constants.  WARNING:  if you change the numbers, you
   *  will need to recompile Test4.java.  Failure to do so will give you a very
   *  hard-to-find bug.
   */
	
  public final static int EMPTY = 0;
  public final static int SHARK = 1;
  public final static int FISH = 2;
  private int width = 0;
  private int height = 0;
  private int starvetime;
  private Bestas[][] oceano;
  
  /**
   *  Define any variables associated with an Ocean object here.  These
   *  variables MUST be private.
   */

  /**
   *  The following methods are required for Part I.
   */

  /**
   *  Ocean() is a constructor that creates an empty ocean having width i and
   *  height j, in which sharks starve after starveTime timesteps.
   *  @param i is the width of the ocean.
   *  @param j is the height of the ocean.
   *  @param starveTime is the number of timesteps sharks survive without food.
   */
  
  public Ocean(int i, int j, int starveTime) { 
	  oceano = new Bestas[i][j];
	  this.starvetime = starveTime;
	  this.width = i;
	  this.height = j;
	  for (int k = 0;k<width;k++){
		  for (int l = 0;l<height;l++){
			  oceano[k][l] =  new Mar();
		  }
	  }

  }

  /**
   *  width() returns the width of an Ocean object.
   *  @return the width of the ocean.
   */

  public int width() {
    return width;
  }

  /**
   *  height() returns the height of an Ocean object.
   *  @return the height of the ocean.
   */

  public int height() {
    return height;
  }

  /**
   *  starveTime() returns the number of timesteps sharks survive without food.
   *  @return the number of timesteps sharks survive without food.
   */

  public int starveTime() {
    return starvetime;
  }

  /**
   *  addFish() places a fish in cell (x, y) if the cell is empty.  If the
   *  cell is already occupied, leave the cell as it is.
   *  @param x is the x-coordinate of the cell to place a fish in.
   *  @param y is the y-coordinate of the cell to place a fish in.
   */

  public void addFish(int x, int y) {
	  x = mod(x,this.width());
	  y = mod(y,this.height());
	
		if (cellContents(x,y)==EMPTY){
	  		oceano[x][y] = new Peixe();}
  }

  /**
   *  addShark() (with two parameters) places a newborn shark in cell (x, y) if
   *  the cell is empty.  A "newborn" shark is equivalent to a shark that has
   *  just eaten.  If the cell is already occupied, leave the cell as it is.
   *  @param x is the x-coordinate of the cell to place a shark in.
   *  @param y is the y-coordinate of the cell to place a shark in.
   */

  public void addShark(int x, int y) {
	  x = mod(x,this.width());
	  y = mod(y,this.height());
	  
		 if (cellContents(x,y)==EMPTY){
			 oceano[x][y] = new Tubarao();}
		
	 }
  
  public Bestas[][] getOceano(){
	  return oceano;
  }
 

  /**
   *  cellContents() returns EMPTY if cell (x, y) is empty, FISH if it contains
   *  a fish, and SHARK if it contains a shark.
   *  @param x is the x-coordinate of the cell whose contents are queried.
   *  @param y is the y-coordinate of the cell whose contents are queried.
   */

  public int cellContents(int x, int y) {
	  x = mod(x,this.width());
	  y = mod(y,this.height());
	  
	  
	  if (oceano[x][y].getBesta()==2){
		  return FISH;
		  
	  }else if (oceano[x][y].getBesta()==1){
		  return SHARK;
		  
	  }else
		  return EMPTY;
	  
  }
  

  public int checkNeighoursFish(int x, int y){
	  int countFish = 0;
		  for (int i = x-1; i<=x+1;i++){
			  for (int j = y-1; j<=y+1;j++){
				 if (cellContents(i,j)==FISH){
					 countFish++;
				 }				
			  }
		  }  
		return countFish;
  	}
  
  public int checkNeighoursShark(int x, int y){
	  int countShark = 0;
	  
		  for (int i = x-1; i<=x+1;i++){
			  for (int j = y-1; j<=y+1;j++){
				 if (cellContents(i,j)==SHARK){
					 countShark++;
				 }				
			  }		  
		  }	  
		return countShark;
  }

  /**
   *  timeStep() performs a simulation timestep as described in README.
   *  @return an ocean representing the elapse of one timestep.
   */
 
  public Ocean timeStep() {
	  //criar um novo oceano - novinho em folha
		 
	  Ocean novo_oceano = new Ocean(width(),height(),starveTime());
	 
	  for (int x = 0;x<width();x++){
		  for (int y = 0;y<height();y++){
	
			  if(this.cellContents(x, y)==SHARK){
				if (this.checkNeighoursFish(x,y)==0){ //regra 2
						if (((Tubarao)this.oceano[x][y]).getFood()+1==starveTime()){
							
							}else{ 
							novo_oceano.addShark(x, y);
							((Tubarao)novo_oceano.oceano[x][y]).setFood(((Tubarao)this.oceano[x][y]).getFood()+1);
						}
				}else{						
						//regra 1
						/*	caso esteja rodeado de pelo menos um peixe, 
						 *  o getFood() faz reset 
						 */	
					
						//verifica se tem peixes vizinhos
					
						novo_oceano.addShark(x, y);
						((Tubarao)novo_oceano.oceano[x][y]).setFood(1);
						}
				
			  	}
			if(this.cellContents(x, y)==FISH){
					if (this.checkNeighoursShark(x,y)==1){ //regra 4
					
					
					}
					if(this.checkNeighoursShark(x,y)>=2){ //regra 5
						novo_oceano.addShark(x, y);
					}
					
					if(this.checkNeighoursShark(x,y)==0){ //regra 3	
						novo_oceano.addFish(x, y);
					}
				}
				
				if(this.cellContents(x, y)==EMPTY){

					if( this.checkNeighoursFish(x,y)<2){ //regra 6
							
					}
					if(this.checkNeighoursFish(x,y)>=2 && this.checkNeighoursShark(x, y)<=1){ //regra 7
						novo_oceano.addFish(x, y);
					}

					if( this.checkNeighoursFish(x,y)>=2 && this.checkNeighoursShark(x, y)>=2){ //regra 8
						novo_oceano.addShark(x, y);
					}
				//caso simplesmente seja so mar rodeado de mar, adiciona mar			 			
			}
		  }
	  }

		 return novo_oceano;
	  }
	
  public int mod(int n, int d) {
      if (n >= 0){
          return n % d;}
  	else{
    	  return (n % d + d) % d;}
        
  }
  
  /**
   *  The following method is required for Part II.
   */

  /**
   *  addShark() (with three parameters) places a shark in cell (x, y) if the
   *  cell is empty.  The shark's hunger is represented by the third parameter.
   *  If the cell is already occupied, leave the cell as it is.  You will need
   *  this method to help convert run-length encodings to Oceans.
   *  @param x is the x-coordinate of the cell to place a shark in.
   *  @param y is the y-coordinate of the cell to place a shark in.
   *  @param feeding is an integer that indicates the shark's hunger.  You may
   *         encode it any way you want; for instance, "feeding" may be the
   *         last timestep the shark was fed, or the amount of time that has
   *         passed since the shark was last fed, or the amount of time left
   *         before the shark will starve.  It's up to you, but be consistent.
   */

 
  
  public void addShark(int x, int y, int feeding) {
	  x = mod(x,this.width());
	  y = mod(y,this.height());

		 if (cellContents(x,y)==EMPTY && feeding>0 && feeding<this.starvetime){
			 oceano[x][y] = new Tubarao(feeding);}
		
	 }

  /**
   *  The following method is required for Part III.
   */

  /**
   *  sharkFeeding() returns an integer that indicates the hunger of the shark
   *  in cell (x, y), using the same "feeding" representation as the parameter
   *  to addShark() described above.  If cell (x, y) does not contain a shark,
   *  then its return value is undefined--that is, anything you want.
   *  Normally, this method should not be called if cell (x, y) does not
   *  contain a shark.  You will need this method to help convert Oceans to
   *  run-length encodings.
   *  @param x is the x-coordinate of the cell whose contents are queried.
   *  @param y is the y-coordinate of the cell whose contents are queried.
   */

  public int sharkFeeding(int x, int y) {
	  x = mod(x,this.width());
	  y = mod(y,this.height());
    return ((Tubarao)this.oceano[x][y]).getFood();
  }
  
 }

//31626 - Andre Figueira
