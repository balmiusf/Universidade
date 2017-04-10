import java.io.FileNotFoundException;

public class Triple_Genome extends General_Functions {
	
	
    Genome G = new Genome();
    static int MATRIX_SIZE=64;
    double from[] = new double [MATRIX_SIZE];
    double TM[][] = new double [MATRIX_SIZE][MATRIX_SIZE];
    double TM_Final[][] = new double [MATRIX_SIZE][MATRIX_SIZE];
    double Huffman[] = new double [MATRIX_SIZE];
    static int NUMBER_OF_UNIQUE_SYMBOLS=4;
    double symbol_count=0;
    String symbols[] = new String[64];
   
    public double[][] getTM() {
        return TM;
    }
 
 
    
 
    public void setTM(double[][] tM) {
        TM = tM;
    }
 
    Triple_Genome(String nome) throws FileNotFoundException{
    	G.setFile(nome);
    	G.FillMatrix();
    }
     
    void GetHuffman(){
       // from[Locate(G.getGenome().substring(G.getGenome().length()-5, G.getGenome().length()-5+3))]++;

    	
        GetHuffmanHelper();
        for ( int i = 0; i<MATRIX_SIZE; i++){
            from[i]=from[i]/symbol_count;
            
        }
        
        double entropy = 0.0;
        for(int i = 0; i < from.length; i++)
        	entropy += from[i]*(Math.log(from[i])/Math.log(2));
    }
   
   
    void GetHuffmanHelper(){
        symbol_count=0;
        for ( int i = 0; i<MATRIX_SIZE; i++){
            symbol_count+=from[i];
        }
        //symbol_count++;
    }
   
   
    void FillMatrix() throws FileNotFoundException{
        G.readfile();
        int index = 0;
        for (int i = 0, n = G.getGenome().length()-5; i < n; i+=3) {
            TM[Locate(G.getGenome().substring(i, i+3))][Locate(G.getGenome().substring(i+3, i+6))]++;
            from[Locate(G.getGenome().substring(i, i+3))]++;
            
            if (from[Locate(G.getGenome().substring(i, i+3))] == 1){
            	symbols[index] = G.getGenome().substring(i, i+3);
            	index++;
            }
          
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