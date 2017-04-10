import java.io.Serializable;

class HuffmanNode implements Serializable
{
	
	 public String symbol; // composto por 3 caracteres
     private final double frequency; // frequency de cada simbolo
     public HuffmanNode child_ESQ, child_DIR; // filho esquerdo filho direiro do no
     public String code;

     // cada no tem um simbolo, uma frequency e (se tiver) filho esquerdo e direito 
     HuffmanNode(String symbol, double frequency, HuffmanNode child_ESQ, HuffmanNode child_DIR, String code) 
     {
    	 this.code = code;
         this.symbol    = symbol;
         this.frequency  = frequency;
         this.child_ESQ  = child_ESQ;
         this.child_DIR = child_DIR;
     }

     // verifica se o no em questao e' uma folha
     @SuppressWarnings("unused")
	public boolean isLeaf() 
     {
         return (this.child_ESQ == null) && (this.child_DIR == null);
     }

     public double compareTo(HuffmanNode node) 
     {
         return this.frequency - node.frequency;
     }
     
    public double getFreq()
    {
    	return this.frequency;
    }
    
	public String getSymbol() 
	{
		return this.symbol;
	}
	public String getCode()
	{
		return this.code;
	}
	public void setSymbol(String s)
	{
		this.symbol = s;
	}
	public void setCode(String code)
	{
		this.code = code;
	}
 }
