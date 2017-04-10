import java.io.FileNotFoundException;

import javax.swing.Spring;

public class Double_Genome extends General_Functions {

	
	Genome G = new Genome();
	static int MATRIX_SIZE=16;
	float from[] = new float [MATRIX_SIZE];
	double TM[][] = new double [MATRIX_SIZE][MATRIX_SIZE];
	double TM_Final[][] = new double [MATRIX_SIZE][MATRIX_SIZE];
	static int NUMBER_OF_UNIQUE_SYMBOLS=4;
	int symbol_count = 0;
	
	
	
	public double[][] getTM() {
		return TM;
	}




	public void setTM(double[][] tM) {
		TM = tM;
	}

	Double_Genome(String ficheiro) throws FileNotFoundException{
		G.setFile(ficheiro);
		G.FillMatrix();
	}
	
	
	

	void FillMatrix() throws FileNotFoundException{
		G.readfile();
		for (int i = 0, n = G.getGenome().length()-3; i < n; i++) {
			TM[Locate(G.getGenome().substring(i, i+2))][Locate(G.getGenome().substring(i+2, i+4))]++;
			from[Locate(G.getGenome().substring(i, i+2))]++;
	}
		
		from[Locate(G.getGenome().charAt(G.getGenome().length()-3)+"")]++;
		GetHuffman();
	
}
	void GetHuffman(){
	       // from[Locate(G.getGenome().substring(G.getGenome().length()-5, G.getGenome().length()-5+3))]++;


		 
	    	GetHuffmanHelper();
	        for ( int j = 0; j<MATRIX_SIZE; j++){
	            from[j]=from[j]/symbol_count;
	        }
	   	
	        
	       
	      
	        double entropy = 0.0;
	        for(int i = 0; i < from.length; i++){
	        	entropy += from[i]*(Math.log(from[i])/Math.log(2));
	        	System.out.println("from : "+entropy+ " - "+from[i]);
	        }
	        System.out.println("entropia: "+ -1*entropy);
	    }
	   
	   
	    void GetHuffmanHelper(){
	        symbol_count=0;
	        for ( int i = 0; i<MATRIX_SIZE; i++){
	            symbol_count+=from[i];
	        }
	    }

	
	void Print_TM(){
		for (int i = 0; i < MATRIX_SIZE; i++) {
		    for (int j = 0; j < MATRIX_SIZE; j++) {
		        System.out.print(TM[i][j] + " ");
		    }
		    System.out.print("\n");
		}
	}
	
	
	void Print_TM_Final(){
		for (int i = 0; i < MATRIX_SIZE; i++) {
		    for (int j = 0; j < MATRIX_SIZE; j++) {
		        System.out.print(TM_Final[i][j] + " ");
		    }
		    System.out.print("\n");
		}
	}
	
		void create_final(){
			//Count_individual();
			
			for (int i = 0; i < MATRIX_SIZE; i++) {
			    for (int j = 0; j < MATRIX_SIZE; j++) {
			    	TM_Final[i][j]=TM[i][j]/from[i];
			   
	}
	
}
		}
}
