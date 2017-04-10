import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectOutputStream;
import java.io.Serializable;
import java.util.*;

public class Huffman implements Serializable
{
	
	Triple_Genome TG;
	int MATRIX_SIZE = 64;
	String huffmanGenome = ""; // huffman encoded code
	private double[] probabilities; // matrix of probabilities of symbols
	String[] HuffmanCodes = new String[64];
	Map<String, String> dictionary = new HashMap<String,String>(); // dictionary of Symbols - Code
	HuffmanNode root; // start node of tree

	
	Huffman(String ficheiro) throws IOException
	{
		for(int i = 0; i < MATRIX_SIZE; i++)
			HuffmanCodes[i] = "";
		
		
		TG=new Triple_Genome(ficheiro); // initialize
		
		// get values
		TG.FillMatrix(); 
		TG.create_final();
		TG.GetHuffman();
		
		this.probabilities = TG.from; // copy
		root = makeTree(this.probabilities); // create tree
		makeHuffmanCode(this.HuffmanCodes,root,""); // match the huffman codes with the symbols
		
		// create huffman tree file for the current sequence to be used in decode
		FileOutputStream fos = new FileOutputStream("Huffman_Tree_"+ ficheiro.substring(0, ficheiro.length()-4)+".bin");
		ObjectOutputStream oos = new ObjectOutputStream(fos);
		oos.writeObject(root);
		oos.close();

	}
	
	Huffman()
	{
	}
	
	// reads the genome, and turns codes it to huffman
	public void convertFile() throws FileNotFoundException
	{
		 String huffmanGenome_2 = TG.G.getGenome(); // copy the string
		 
		 // go through the copied code and adds the huffman coding to the huffmanGenome
		 for(int i = 0; i < huffmanGenome_2.length()-2; i+=3) 
		 {
			 this.huffmanGenome += dictionary.get(huffmanGenome_2.substring(i,i+3)); // create huffmand coded code 
		 }
	}

	public void makeHuffmanCode(String codes[], HuffmanNode node, String currentCode)
	{	
		// runs the huffman tree top to bottom, going through all nodes -> makes code
		if (!node.isLeaf())
		{
			makeHuffmanCode(codes, node.child_ESQ, currentCode + "0");
			makeHuffmanCode(codes, node.child_DIR, currentCode + "1");
		}else
		// since its a leaf means there is a symbol and not a '\0', so add it and update the node.
		{
			node.setCode(currentCode); // update symbol
			dictionary.put(node.getSymbol(), currentCode); // correspond code to symbol
		}
	}
		
// remove the minimum element of the list
	public HuffmanNode delMin(ArrayList<HuffmanNode> pq)
	{
		double lowest = pq.get(0).getFreq();
		int  index = 0;
		
		for(int i = 1 ; i < pq.size(); i++)
		{
			if (pq.get(i).getFreq() < lowest)
			{
				lowest = pq.get(i).getFreq();
				index = i;
			}
		}
		return pq.remove(index);
	}
	
	// create huffman tree
	public HuffmanNode makeTree(double[] frequency)
	{
		ArrayList<HuffmanNode> pq = new ArrayList<HuffmanNode>();
		for(int i = 0; i < frequency.length ; i++) // get every symbol into the queue
			if(frequency[i] > 0)
				pq.add(0,new HuffmanNode(TG.symbols[i], frequency[i],null,null,"\0"));
		
		while(pq.size() > 1)
		{
			
			HuffmanNode esq = delMin(pq); // remove min
			HuffmanNode dir = delMin(pq);  // remove min
			pq.add(0,new HuffmanNode("\0",esq.getFreq()+dir.getFreq(), esq,dir,"\0")); // sum them up and add them to queue
		}
		return pq.remove(0); // root node
	}
	
	// decode the hamming code 
	public String decode(String hammingCode, HuffmanNode root)
	{	
		String huffmanDecode = ""; 
		HuffmanNode x = root; // start
		for(int i = 0; i < hammingCode.length(); i++) // go trough the code
		{
			if(!x.isLeaf()) // if its leaf continue 
			{
				if (hammingCode.charAt(i) == '0')				
					x = x.child_ESQ;			
				else			
					x = x.child_DIR;
			}
			else{ // else stop and add the code
				i = i-1;
				huffmanDecode += x.getSymbol();
				
				x = root;
			}
		}
		
		return huffmanDecode;
		
	}
	
}
