package JogoDoGalo;

//31626 - Andre Figueira
public abstract class HashTable{
	ElementoTabela[] tabela;
	int ocupados;
	
	public HashTable(){
		this(23);
		
	}
	
	public HashTable(int n){
		alocarTabela(n);
		ocupados=0;
		tornarVazia();
	}
	 
	private boolean primo(int n){
		for (int x=3; x*x<=n; x+=2){
			if (n%x==0)
				return false;
		}
		return true;
	}

	private int nextPrimo(int n){
		if (n%2==0)
		    n++;
		while(!primo(n)){
			n+=2;
		}
		return n;
	}
	
	public int ocupados(){
		return ocupados;
	}
	
	protected abstract int procPos(JogoDoGalo s);
	
	public void alocarTabela(int dim){
		tabela= new ElementoTabela[nextPrimo(dim)];
	}
	
	public void tornarVazia(){
		ocupados=0;
		
		for(int i=0; i<tabela.length; i++){
		    tabela[i]=null;
		}
	}
	
	
	public boolean procurar(JogoDoGalo x){
		int pos = procPos(x);
		return (tabela[pos] != null && !tabela[pos].deleted);
	}
	
	public void remove(JogoDoGalo x){
		int pos = procPos(x);
		if (tabela[pos] != null) {
			tabela[pos].deleted=false;
		}
	}
	
	public void insere (JogoDoGalo x){
		int pos = procPos(x);
		if (tabela[pos] == null){
			tabela[pos]= new ElementoTabela(x);
			ocupados++;
			if (ocupados*2>=tabela.length){
				rehash();
			}
		} else if(tabela[pos].deleted) {
			tabela[pos]= new ElementoTabela(x);
		}
	}
	
	public void rehash(){
		
		ocupados=0;
		ElementoTabela[] temp=tabela;
		alocarTabela(nextPrimo(2*tabela.length));
		
		for (int i=0; i<temp.length; i++){
		    if (temp[i]!=null && !temp[i].deleted)
			insere( (JogoDoGalo) temp[i].valor);
		}
	}
	
	public JogoDoGalo procurarJogo(JogoDoGalo x){
		
		if (!procurar(x)){			
			return x;
			
		}else{	
			int pos = procPos(x);
			return tabela[pos].valor;
		}
	}
	
	public void print(){
		System.out.println(tabela);
	}
	
	public String toString(){
		String r="[";
		for(int i=0;i<=tabela.length-1;i++){
			r += i+"-";
			r += (i<tabela.length-1) ? tabela[i]+";" : tabela[i];
		}
		return r+"]";
	}
}
