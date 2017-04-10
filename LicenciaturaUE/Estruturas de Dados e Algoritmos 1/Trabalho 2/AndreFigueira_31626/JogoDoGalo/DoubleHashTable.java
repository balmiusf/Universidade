package JogoDoGalo;
//31626 - Andre Figueira

public class DoubleHashTable extends HashTable {
	public DoubleHashTable(){
		super();
	}

	public DoubleHashTable(int n){
		super(n);
	}
 
	public int myhash2(JogoDoGalo s) {

		return 13-(s.hashcode() % 13);
	}

	public int procPos(JogoDoGalo s) {
		int hash=s.hashcode() % tabela.length;
		int hash2=myhash2(s);
		int z=0;
		for(int x=0; !(tabela[z]==null || tabela[z].valor.toString().equals(s.toString())); x++) {
			z=(hash+x*hash2)  % tabela.length;
		}
		return z;
	}

}

