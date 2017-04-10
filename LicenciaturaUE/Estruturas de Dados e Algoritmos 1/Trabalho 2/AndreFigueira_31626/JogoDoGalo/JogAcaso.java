package JogoDoGalo;
//31626 - Andre Figueira
import java.util.Random;

public class JogAcaso{
	private Random random;
	
	   public JogAcaso(){
		   random = new Random();
		   
	   }
	   
	  //faz uma jogada aleat—rio sobre o tabuleiro t
	  public void joga(JogoDoGalo t){
		  
		  int randRow = random.nextInt(3);
		  int randCol = random.nextInt(3);
		  
		  boolean joga2 = t.joga(randRow, randCol);
		  		  
		  while(!joga2){
			  randRow = random.nextInt(3);
			  
			  randCol = random.nextInt(3);
			  
			  joga2 = t.joga(randRow, randCol);
		  }
	  }
	}
