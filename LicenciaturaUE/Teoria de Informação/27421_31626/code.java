import java.io.BufferedWriter;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.io.Serializable;
import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class code extends General_Functions implements Serializable {
	
	int MATRIX_SIZE = 64;
	String unconverted;
	Scanner scannerFile = null;
	Huffman huffman;
	HammingCode hamming;
	String ficheiro = "";
	String temp="";
	
	
	code(String ficheiro, Huffman huffman, HammingCode hamming) throws FileNotFoundException
	{
		this.hamming = hamming;
		this.ficheiro = ficheiro;
		this.huffman = huffman ;
	}

	
	void applyHuffman() throws FileNotFoundException {
		 huffman.convertFile();
		 
	}
	
	void applyHamming() throws IOException
	{
		// generate hamming code
		this.hamming.generateCode(this.huffman.huffmanGenome);	// generate the hamming code
		temp=this.hamming.hammingCode; // copy it
		
	}

	public static void main(String args[]) throws IOException
	{
		String ficheiro = "coding_binary_huff"+"_"+args[0].substring(0, args[0].length()-4)+".bin";
		HammingCode decoded = new HammingCode();
		Huffman decoded_huff = new Huffman(args[0]); 
		code codes = new code(ficheiro,decoded_huff,decoded); 
		codes.applyHuffman(); // apply huffmann to the code
		String_to_write(codes.huffman.huffmanGenome,ficheiro);
		codes.applyHamming(); // apply hamming to the code
		String_to_write(codes.temp,args[1]);
		System.out.println("Compressed file ( only huffman ) : "+ficheiro+"\n");
		System.out.println("Output file (the one to be used in channel and/or decode ): "+args[1]+"\n");
		System.out.println("HuffmanTree saved to file ( to be used in decode) : Huffman_Tree_"+args[0].substring(0, args[0].length()-4)+".bin\n");
		System.out.println("decode program will require 3 arguments: ");
		System.out.println("	Input file, Output file, Huffman_Tree_"+args[0].substring(0, args[0].length()-4)+".bin\n");
	}
}
