import java.io.FileOutputStream;
import java.io.IOException;

public class General_Functions {
	static int NUMBER_OF_UNIQUE_SYMBOLS=4;
	
	int Locate(String A){
		int place = 0;  
		int multiplier = (int) Math.pow(NUMBER_OF_UNIQUE_SYMBOLS, A.length()-1);
	//	System.out.println(multiplier);
			for ( int i=0; i<A.length(); i++){
			if (A.charAt(i) == 'A'){
				place+= multiplier * 0;
			}
			if (A.charAt(i) == 'C'){
				place+= multiplier * 1;
			}
			if (A.charAt(i) == 'G'){
				place+= multiplier * 2;
			}
			
			if (A.charAt(i) == 'T'){
				place+= multiplier * 3;
			}
		
			multiplier = multiplier / NUMBER_OF_UNIQUE_SYMBOLS;
			
		}
		return place;
	}
	
	
	
	public double Average(double[] cenas){
		double counter=0;
		for (int i = 0; i<cenas.length; i++){
			counter+=cenas[i];
		}
		
		return counter/cenas.length;
	}
	 public static int String_to_byte_size(String cenas) throws IOException{
	    	byte[] temp = new byte[cenas.length()/8];
	    	for(int x=0; x<cenas.length()-8; x+=8){
	    		temp[x/8]=(byte) Integer.parseInt(cenas.substring(x,x+8),2);
	    	}
	    	return temp.length;
	    }
	
	
	 public static void String_to_write(String cenas,String nome) throws IOException{
	    	byte[] temp = new byte[cenas.length()/8];
	    	for(int x=0; x<cenas.length()-8; x+=8){
	    		temp[x/8]=(byte) Integer.parseInt(cenas.substring(x,x+8),2);
	    	}
	    	write_new(temp,nome);
	    }
	    
	    
	    
	    public static void write_new(byte[] cenas,String name) throws IOException{
	    	FileOutputStream fos = new FileOutputStream(name);
	    	fos.write(cenas);
	    	fos.close();
	    }
	
	
/*
	
	public double Line_total(double[]Line){
		double total=0;
		for (int i=0; i<Line.length; i++) {
			total+=Line[i];
		}
		return total;
	}
	
	public double invert (double c){
		return 1/c;
	}
	
	public double[] Average_Line(double[] Line){
		for (int i=0; i<Line.length; i++) {
			  Line[i] = Line[i]/Line_total(Line);
			}

		return Line;
		
	}
	
	
	public boolean[] Below_Average(double[][] cenas){
		boolean[] below = new boolean[cenas.length];
		double[] Line_average = new double[cenas.length];
		for (int i = 0; i<cenas.length; i++){
			for (int j =0; j<cenas.length; j++){
				Line_average[i]+=cenas[j][i];	
			}
		}
		double[]Line2=Average_Line(Line_average);
		for (int z = 0; z<cenas.length; z++){
			if (Line[])
		}

		
	}
	
	*/
}