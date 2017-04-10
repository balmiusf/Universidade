import java.io.DataInputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.BitSet;
import java.util.Random;

public class Channel extends General_Functions {
	
	byte[] fileData;
	byte[] fileData2;

	File file;
	int error_counter = 0;
	String temp = "";
	
	Channel (String nome){
		file = new File(nome);
		fileData = new byte[(int) file.length()];
		fileData2 = new byte[(int) file.length()];

	}
	
	
	Channel (String nome, int size){
		file = new File(nome);
		fileData = new byte[size];
		fileData2 = new byte[size];
	}
   
	public File getFile() {
		return file;
	}


	public void setFile(String nome) {
		file = new File(nome);
	}


	public byte[] getFileData() {
		return fileData;
	}


	public void setFileData(byte[] fileData) {
		this.fileData = fileData;
	}


    public void setFiledatasize(int x){
    	fileData = new byte[x];
    }
    
    public void Import_file() throws IOException{
    	
    	DataInputStream dis = new DataInputStream(new FileInputStream(file));
        dis.readFully(fileData);
        dis.close();

} 
 
    
    
    
    
    public void DoubleFile(){
    	for(int x = 0; x <fileData.length; x++){
    		fileData2[x]=fileData[x];
    		}
    }
   
    
    public byte ProcessByte(byte b){
		for ( int x = 0; x<8 ; x++){
			if((b & x) == 1){
				boolean val = new Random().nextInt(10)==1;
    			if(val){
    				b ^= 1 << x;
    				this.error_counter++; // number of errors in the code
    			}
		}
    	
    	}
		return b;
    	
    }
    
    
    public void CheckErros(){
    	for ( int x = 0; x<fileData.length; x++){
    		
    		if(fileData[x] != fileData2[x]){
    			System.out.println("O byte numero " + x  +" com o valor " + fileData[x] + "passou a" + fileData2[x] );
    		}
    	}
    }
    
    public void channel(){
    	DoubleFile(); 
    	for(int x = 0; x<fileData.length; x++){
    		fileData2[x]=ProcessByte(fileData[x]);
    	}
    	 
    	}
    
    // copy paste the data in filedata to filedata 2
    public void nochannel()
    {
    	DoubleFile(); 
    	for(int x = 0; x<fileData.length; x++){
    		fileData2[x]=fileData[x];
    	}
    }
   
    
    public void write_new(byte[] cenas) throws IOException{
    	FileOutputStream fos = new FileOutputStream(file);
    	fos.write(cenas);
    	fos.close();
    }
    
   public String byte__to_string(byte[] temp){
	   String Siga="";
	  for(int x =0; x<temp.length; x++){
		  Siga +=String.format("%8s", Integer.toBinaryString(temp[x] & 0xFF)).replace(' ', '0');
	  }
	return Siga;
	   
	   
   	}
   
   	String applyHamming(HammingCode hamming, String huffman) throws IOException
	{
		// generate hamming code
		hamming.generateCode(huffman);
		
		return hamming.hammingCode;
	}
    public static void main(String args[]) throws IOException
    {

    	Channel canal = new Channel(args[0]);
    	canal.Import_file();
       	canal.channel();
    	write_new(canal.fileData2, args[1]);
		//canal.setFile("coding_binary_channeled");
    	
    }
    
    
    
}



