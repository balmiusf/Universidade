package JogoDoGalo;
//31626 - Andre Figueira
public class QuadHashTable extends HashTable {
	
	public QuadHashTable(){
		super();
	}

	public QuadHashTable(int n){
		super(n);
	}
	public int procPos(JogoDoGalo s) {
		int hash=s.hashcode() % tabela.length; 
		int z=0;
		for(int x=0; !(tabela[z]==null || tabela[z].valor.toString().equals(s.toString())) ; x++) {
			z=(hash+(x*x))  % tabela.length;
		}
		
		return z;
	}

}


