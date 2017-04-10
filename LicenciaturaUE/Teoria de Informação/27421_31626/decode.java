import java.io.BufferedWriter;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.FileWriter;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;

public class decode {
	
	decode()
	{
		
	}
	
	public static void main(String args[]) throws IOException, ClassNotFoundException
	{
		
		decode decoding = new decode(); 
		Channel canal = new Channel(args[0]); //read bin file
		canal.Import_file();
		String temp = canal.byte__to_string(canal.fileData); 
		
		HammingCode hamming = new HammingCode();
		Huffman decoded_huff = new Huffman();
		
		hamming.runCode(temp); //gets the code back into huffman and corrects it
		FileInputStream fos = new FileInputStream(args[2]); // get the tree from bin file
		ObjectInputStream ois = new ObjectInputStream(fos);
		
		HuffmanNode root = (HuffmanNode) ois.readObject(); // read the tree
		
		String huffman_decode = decoded_huff.decode(hamming.original_code,root);// decode the huffman back to its original symbols
		
		
		// create output file with decoded huffman
		File file = new File(args[1]);
		file.createNewFile();
		FileWriter fw = new FileWriter(file.getAbsoluteFile());
		BufferedWriter bw = new BufferedWriter(fw);
		bw.write(huffman_decode);
		bw.close();
		
	}
	
}
