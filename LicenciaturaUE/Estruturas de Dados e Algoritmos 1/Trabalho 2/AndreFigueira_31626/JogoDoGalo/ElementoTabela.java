package JogoDoGalo;
//31626 - Andre Figueira
public class ElementoTabela{
	JogoDoGalo valor;
	boolean deleted;
	
	public ElementoTabela(JogoDoGalo v){
		valor=v;
		deleted=false;
	}
	 
	void delete(){
		deleted=true;
	}
	
    void setValor(JogoDoGalo v){
  	  valor=v;
  	  deleted=false; 
  
    }
	
	public String toString(){
		if(deleted){
			return "well this is awkward...";
		}
		else{
			return valor.toString();
		}
	}
}
