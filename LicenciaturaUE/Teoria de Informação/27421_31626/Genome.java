
import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;


//Class for Reading information and saving it on a string. Also contains single 4x4 transition matrix.
public class Genome extends General_Functions {

	//int SIZE = 0; For array implementation
	// String[] Genome; For array implementation
	String Genome;
	int symbol_count = 0;
	Scanner scannerFile = null;
	String ficheiro = "";
	
	
	
	
	
	public Genome() {
		// TODO Auto-generated constructor stub
	}
	
	public void setFile(String nome){
		ficheiro = nome;
	}


	// Counters for overall number of transition 
	double from[] = new double [MATRIX_SIZE];
	public double[][] getTM() {
		return TM;
	}

	public void setTM(double[][] tM) {
		TM = tM;
	}
	// For simplicity proposes, The genome is ordered by columns. 
	// Being columns start and rows destination, in such a away that 
	// TM[n][n+1] Describes the number of transitions from the symbol start n to the symbol destination n+1
	// Altough symbols are strings, we are giving them a number for implementation sake.
	// Therefore:
	// A=0
	// C=1
	// G=2
	// T=3
	// So for example, TM[2][3] Would describe the number of transitions from G to T.
	static int MATRIX_SIZE = 4; //size for pairs
	double[][] TM = new double [MATRIX_SIZE][MATRIX_SIZE]; // Pairs
	double[][] TM_Final = new double [MATRIX_SIZE][MATRIX_SIZE]; // Pairs
	//Reads file and passes it into a string.
	
	void readfile() throws FileNotFoundException{
		scannerFile = new Scanner(new File(this.ficheiro));
		Genome = scannerFile.next();
	}
	
	void FillMatrix() throws FileNotFoundException{
		readfile();
		for (int i = 0, n = Genome.length()-1; i < n; i++) {
			TM[Locate(Genome.substring(i,i+1))][Locate(Genome.substring(i+1,i+2))]++;
			from[Locate(Genome.substring(i, i+1))]++;
	}
		
		from[Locate(Genome.charAt(Genome.length()-1)+"")]++;
		
		GetHuffman();
        
	}
	
	 void GetHuffman(){
	       // from[Locate(G.getGenome().substring(G.getGenome().length()-5, G.getGenome().length()-5+3))]++;


		 
	    	GetHuffmanHelper();
	        for ( int j = 0; j<MATRIX_SIZE; j++){
	            from[j]=from[j]/symbol_count;
	        }
	   	
	        
	       // System.out.println("last 3: "+G.getGenome().substring(G.getGenome().length()-5, G.getGenome().length()-5+3));
	      
	      
	        double entropy = 0.0;
	        for(int i = 0; i < from.length; i++)
	        	entropy += from[i]*(Math.log(from[i])/Math.log(2));
	   
	 }
	    void GetHuffmanHelper(){
	        symbol_count=0;
	        for ( int i = 0; i<MATRIX_SIZE; i++){
	            symbol_count+=from[i];
	        }
	    }

	
	
	
	

	public String getGenome() {
		return Genome;
	}


	public void setGenome(String genome) {
		Genome = genome;
	}


	// Creates a new matrix, which is TM diving by the total of each respective transmition
	void create_final(){
		//Count_individual();
		
		for (int i = 0; i < MATRIX_SIZE; i++) {
		    for (int j = 0; j < MATRIX_SIZE; j++) {
		    	TM_Final[i][j]=TM[i][j]/from[i];
		    }
		}

	}
	
	
	// GeneralPrints
	void Print_TM(){
		for (int i = 0; i < MATRIX_SIZE; i++) {
		    for (int j = 0; j < MATRIX_SIZE; j++) {
		        System.out.print(TM[i][j] + " ");
		    }
		    System.out.print("\n");
		
	}
	}
	
		
		void Print_TM_FINAL(){
			for (int i = 0; i < MATRIX_SIZE; i++) {
			    for (int j = 0; j < MATRIX_SIZE; j++) {
			        System.out.print(TM_Final[i][j] + " ");
			    }
			    System.out.print("\n");
			
		}
	
	
		}
	}
	
	
	