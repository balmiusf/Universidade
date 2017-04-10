package JogoDoGalo;
//31626 - Andre Figueira
public class ProjectGalo {
	private int numJogos;
	private double victoryO;
	private double victoryX;
	
	public ProjectGalo(int numJogos){
		this.numJogos = numJogos;		
	}
	
	
	public void play(JogAcaso playerX, JogInteli playerO, int numJogos) throws InvalidNodeException{
		
		JogoDoGalo tb;
		
		for(int i = 0 ; i < numJogos ; i++ ){
			tb = new JogoDoGalo();
			
			while(!tb.acabou()){
				
				playerX.joga(tb);
				
				if(!tb.acabou()){
					
					playerO.joga(tb);				
					tb.gamePath(tb); //este metodo permite guardar todas as jogadas do playerO numa lista ligada
				}
			}
			playerO.acabou(tb);
			if (tb.vencedor()==2){
				victoryO++;
			}
			if(tb.vencedor()==1){
				victoryX++;
			}
		}
		
			JogoDoGalo bestBoard = playerO.movimentoFavorito();
			
			//END REPORT
			
			System.out.println("Numero de Slots: "+playerO.hashtable.tabela.length);
			System.out.println("Numero de entradas: "+playerO.hashtable.ocupados());
			System.out.println("Factor de Carga: "+ (double) playerO.hashtable.ocupados() / (double) playerO.hashtable.tabela.length);
			System.out.println("JogInteli ganhou: "+this.victoryO + "("+this.getPlayerOWinRatio()*100+"%)");
			System.out.println("JogAcaso ganhou: "+this.victoryX + "("+this.getPlayerXwinRatio()*100+"%)");		
			System.out.println("a minha 1ª jogada preferida (o que tem mais victorias): ");
			System.out.println(bestBoard.toString());
			System.out.println("Ganhou "+bestBoard.getVictory()+" vezes em "+bestBoard.getTotalJogos()+" que e' "+bestBoard.getWinRatio()*100+"%");
							
	}
	
	public double getPlayerOWinRatio(){
		return victoryO / (victoryX + victoryO + (numJogos-victoryX-victoryO));
	}
	
	public double getPlayerXwinRatio(){
		return victoryX / (victoryX + victoryO + (numJogos-victoryX-victoryO));
	}
	
	public int getNumJogos() {
		return numJogos;
	}
	
	public static void main(String args[]) throws InvalidNodeException{
		
		JogAcaso playerX = new JogAcaso();
		JogInteli playerO = new JogInteli();		
		ProjectGalo jogoDoGalo = new ProjectGalo(100);
		
		jogoDoGalo.play(playerX, playerO, jogoDoGalo.getNumJogos());

		
		
		
	}


	
}
