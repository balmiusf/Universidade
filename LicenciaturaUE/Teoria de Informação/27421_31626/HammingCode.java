
public class HammingCode 
{
	// USING HAMMING(7,4)
	String original_code = ""; // this is the original decoded code
	int error_counter = 0; // error counter
	String hammingCode = ""; // hamming code 
	
	// matrix geradora
	int[][] geradora = 	{
						{1,1,0,1},
						{1,0,1,1},
						{1,0,0,0},
						{0,1,1,1},
						{0,1,0,0},
						{0,0,1,0},
						{0,0,0,1}
						};
	
	// matrix verificacao de erro
	int[][] error_check = 	{
							{0,0,0,1,1,1,1},
							{0,1,1,0,0,1,1},
							{1,0,1,0,1,0,1}
							};
	
	// matrix descodificadora
	int[][] decoder = 	{
			{0,   0,   1,   0,   0,   0,   0},
			{0,   0,   0,   0,   1,   0,   0},
			{0,   0,   0,   0,   0,   1,   0},
			{0,   0,   0,   0,   0,   0,   1}
						};
						
	
	
	HammingCode()
	{
	}
	
	// multiply matrix with matrix to give a new matrix
	void multiplica(int rowSize, int colSize, int rowSize2, int colSize2, int matriz[][], int matriz2[][], int mult[][])
	{
		int resultado = 0;
		for(int i = 0; i < rowSize; i++)
		{
			for(int j = 0; j < colSize2; j++)
			{
				for(int l = 0; l < rowSize2; l++)
					resultado += matriz[i][l] * matriz2[l][j];

				mult[i][j] = resultado % 2;
				resultado = 0;	
			}
		}
	}

	// apply hamming to the code
	// after huffman coding apply this function	
	public void generateCode(String code)
	{
		int j = 3;
		int i = 0;
		int[][] converted = new int[4][1];
		int[][] matrix = new int[7][1];
		
		// will go threw the entire code
		for(; i < code.length()-3;)
		{
			// it will go threw the code 4 by 4
			String part = code.substring(i,j+1);
			i += 4;
			j = i+3;
			
			// convert the code into a matrix
			for(int k = 0; k < part.length(); k++)
				converted[k][0] = part.charAt(k);

			// multiple the matrix by the geradora. it will create a 7 bit hamming code
			multiplica(7,4,4,1,geradora,converted, matrix);
			
			// matrix ja tem o codigo gerador.
			for(int c = 0; c < 7; c++)
				for(int l = 0; l < 1; l++)
					this.hammingCode += matrix[c][l] + "";
	
		}
		
		
		
	}
	
	// will detect any errors in the hamming code
	// after passing trough the channel apply this function
	public void error_detection(int[][] code)
	{

		int[][] error = new int[3][1]; // error position matrix

		multiplica(3,7,7,1,this.error_check,code,error); // multiply by the error detection matrix to check error
		
		String n = error[0][0] +""+ error[1][0] +""+ error[2][0]+""; // turn into a value

		int error_bit = Integer.parseInt(n, 2); // turn it into an Integer

		// if its superior to 0 then there is an error at pos bit 
		// else there is no error
		if (error_bit > 0)
		{
			this.error_counter++; // increment error counter
			code[error_bit-1][0] ^= code[error_bit-1][0]; // use NOT to negate the value

		}
		}
	
	// go through the entire code 7 by 7
	public void runCode(String code)
	{
		int converted[][] = new int[7][1];
		String new_code = ""; 

			for(int i = 0; i < code.length()-6; i+=7)
			{
				new_code = code.substring(i,i+7);
				for(int k = 0; k < new_code.length(); k++)				
					converted[k][0] = Integer.parseInt(new_code.charAt(k)+"");
				
				
				error_detection(converted); // detect the error
				
				decode(converted); // after its fixed, decoded using the matrix
				
			}
			
		}


	
	// take the hamming code, and decoded to its original form
	// after passing threw the the channel and error detection function apply this function
	public void decode(int[][] code)
	{
		int[][] decoded = new int[4][1]; // decoded matrix
		
		// multiply it by the decoder matrix
		multiplica(4, 7, 7, 1, decoder, code, decoded); // multiply to get original value ( 4 bits )
		this.original_code += decoded[0][0] +""+ decoded[1][0] +""+ decoded[2][0] +""+ decoded[3][0]; // add it to the String
		
	}
}
