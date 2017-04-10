import java.util.ArrayList;

public class Scheduler{
	public ArrayList<PCB> processos;
	public ArrayList<PCB> NEW;
	private ArrayList<PCB> READY;
	private PCB run; // processo que esta a ocupar o processador
	private PCB IO_Blocked; // processo que esta a ocupar o disco
	private ArrayList<PCB> BLOCKED;
	private ArrayList<PCB> EXIT;
	public ArrayList<PCB> ESTADOS; // contem os estados actuais de todos os processos
	private int tempo;	
	private int totalProcessos; // numero de processos a ser executado (default 10)
	private boolean IO_LOCKED; // I/O lock
	private boolean CPU_RUNNING; // se o processador tem algo
	private int paginas_disponiveis; // default = 10;
	int pid; // process identifier
	
	
	public Scheduler(int totalProcessos, int paginas)
	{
		this.pid = 0;
		this.paginas_disponiveis = paginas;
		this.totalProcessos = totalProcessos;
		initialize();
	}

	public void initialize()
	{
		this.tempo = 0;
		this.processos = new ArrayList<PCB>();
		this.IO_LOCKED = false;
		this.CPU_RUNNING = false;
		this.run = null;
		this.IO_Blocked = null;
		
		this.NEW = new ArrayList<PCB>();
		this.READY = new ArrayList<PCB>();
		this.BLOCKED = new ArrayList<PCB>();
		this.EXIT = new ArrayList<PCB>();
		this.ESTADOS = new ArrayList<PCB>();
	}
	
	public int getTempo() {
		return tempo;
	}

	public void setTempo(int tempo) {
		this.tempo = tempo;
	}

	// mudança de estados
	private void newToReady() {
		this.NEW.get(0).setEstado("ready");
		this.READY.add(this.NEW.remove(0));	
	}
	
	private void runToBlock() {
		this.run.setEstado("blocked");    
		this.BLOCKED.add(this.run);
	}
	
	
	private void runToExit(){ //O programa termina e vai para exit
		this.run.setEstado(" exit ");
		this.EXIT.add(this.run);
		this.totalProcessos--;
	}

	private void runToReady() {
		this.run.setEstado("ready");
		this.READY.add(this.run);  
	}
	
	// ultima instrucao relativa ao processo que esta a correr
	private boolean lastInst() {
		return this.run.getInstrucoes().length == this.run.getPC();
	}
	
	private void readyToRun() {
		this.READY.get(0).setEstado(" run ");
		this.run = this.READY.remove(0);
	}
	
	private void newIOBLocked()
	{
		this.IO_Blocked = this.BLOCKED.remove(0); // prox da lista passa a blocked
		this.READY.add(this.IO_Blocked); 
		this.IO_LOCKED = true; // I/0 locked
	}	
	
	// instrucao actual do elemento que esta a frente
	private int current_inst(ArrayList<PCB> queue)
	{		
		return queue.get(0).getInstrucoes()[queue.get(0).getPC()]; 
	}
	
	// duplica o processo passado por argumento (processo que esta no processador)
	private void fork(PCB run)
	{
		int[] inst = new int[run.getInstrucoes().length];
		for(int i = 0; i < run.getInstrucoes().length; i++)
			inst[i] = run.getInstrucoes()[i]; // copia instrucoes
		
		PCB fork = new PCB(pid,"ready",inst);
		fork.setPC(0); // reset ao PC
		this.ESTADOS.add(fork); // envia para ESTADOS
		this.READY.add(fork); // envia pa READY
		this.pid++;	
	}
	
	// imprime o estados actuais ao fim de cada ciclo em Teste
	public String toString()
	{
		String output = tempo+"";
		for(int i = 0; i < ESTADOS.size(); i++)
			output += " | "+ESTADOS.get(i).getEstado();
		
		return output + "\n";
		
	}
	
	public void scheduler()
	{
		// verificar se ha algum processo que esta usar o disco
		// se ja terminou o uso do disco
		// e enviado para a ready queue
		if(!this.IO_LOCKED && !BLOCKED.isEmpty())
		{
			// deixou de aceder ao disco
				this.IO_LOCKED = false; // liberta o lock
				newIOBLocked(); // novo processo a ocupar o disco
		}
		
			int temp = 0;
			if(this.run != null) // se estiver algum processo a ocupar
				temp++;
			if(this.IO_Blocked != null) // se estiver algum processo a ocupar
				temp++;
			
			if((BLOCKED.size() + READY.size() + temp) < this.totalProcessos && !this.NEW.isEmpty())
			{

				if (paginas_disponiveis > 0) // se houver paginas disponiveis
				{
					// caso ocupe uma pagina
					if(NEW.get(0).getInstrucoes().length <= 10){
						NEW.get(0).setPaginas_ocupadas(1);
						newToReady();
						paginas_disponiveis--; // ocupa uma pagina
						this.totalProcessos++;
					}
					else
					{
						// caso ocupe multiplas paginas
						int paginas = NEW.get(0).getInstrucoes().length / 10;
						if( paginas == 1) // length < 20
							paginas = 2;
						if(paginas_disponiveis >= paginas){
							NEW.get(0).setPaginas_ocupadas(paginas); 
							paginas_disponiveis -= paginas; // decrementa as paginas
							newToReady(); // passa para outro estado
							this.totalProcessos++; //incrementa o numero de processos a correr
						}
					}			
				}
			}

			/* verificar se o processo que esta no processador terminou
			   caso contrario e interrompido e enviado para a ready queue */
			
			if(this.CPU_RUNNING)
			{
				if (lastInst()) // se e a ultima instrucao do programa
				{
					// se o PID for igual
					if(this.run.getId() == this.IO_Blocked.getId())
						if(!this.BLOCKED.isEmpty())
							newIOBLocked(); // novo processo IO_BLOCKED 
						runToExit(); // termina
						this.paginas_disponiveis += run.getPaginas_ocupadas(); // liberta pagina ocupada 
				}
				else
				{ // caso contrario como passou o quantum = 1 e' interrompido
					runToReady();
				}
				this.CPU_RUNNING = false; // processador vazio
				
			}
			
			/*
			 * mete um processo a correr
			 * se a instrucao actual for uma no operation entao nesse caso nao faz nada
			 */
			if(!READY.isEmpty())
			{
				// nao ha necessidade de trazer pa processador
				while(current_inst(READY) == 3) // se for um NO OPERATION, 
				{		
					READY.get(0).setPC(READY.get(0).getPC()+1); // incrementa o program counter
					if(READY.get(0).getPC() == READY.get(0).getInstrucoes().length){
						READY.get(0).setEstado(" Exit ");
						
						EXIT.add(READY.remove(0));
					}else
						READY.add(READY.remove(0)); // passa para o fim da queue
				}	
				// caso haja multiplos processos que terminaram durante o ciclo devido a instrucao 3
				if(!READY.isEmpty()){
					this.CPU_RUNNING = true; // processador ocupado
					readyToRun(); // mete um processo a correr
					
				}
			}
			
			// se houver um processo a correr
			// se o processo RUN for igual ao processo que esta a bloquear o disco
			// e a instrucao que está a fazer for diferente de 2, entao liberta o lock
			if(this.CPU_RUNNING)
			{
				if(run.getInstrucoes()[run.getPC()] == 0){// EXIT
					if(this.IO_Blocked != null && this.run.getId() == this.IO_Blocked.getId())
						this.IO_LOCKED = false;
					run.setPC(run.getInstrucoes().length);
				}else if(run.getInstrucoes()[run.getPC()] == 1){ // USE CPU
					if(this.IO_Blocked != null && this.run.getId() == this.IO_Blocked.getId()){
						this.IO_LOCKED = false;
					}
					run.setPC(run.getPC()+1);					
				}
				else if(run.getInstrucoes()[run.getPC()] == 2) // USE DISK
				{
					run.setPC(run.getPC()+1);
					if (!this.IO_LOCKED)
					{
						this.IO_Blocked = this.run;					
						this.IO_LOCKED = true; // IO LOCK
					}
					else{ // se o IO ainda estiver locked 
						// se o processo a correr nao for o processo que esta a bloquear o disco
						if(this.run.getId() != this.IO_Blocked.getId()){
							runToBlock(); //bloqueia o processo
							this.CPU_RUNNING = false; 
						}
					}
				}
				else if (run.getInstrucoes()[run.getPC()] == 4){// GO TO BEGIN
					if(this.IO_Blocked != null && this.run.getId() == this.IO_Blocked.getId())
						this.IO_LOCKED = false;
					run.setPC(0);
				}
				else if (run.getInstrucoes()[run.getPC()] == 5) // FORK 
				{
					if(this.IO_Blocked != null && this.run.getId() == this.IO_Blocked.getId())
						this.IO_LOCKED = false;
					run.setPC(run.getPC()+1);
					fork(this.run);
				}
			}
			tempo++; // incrementa o tempo
		}
		
// verifica se todos os processos se encontram no estado EXIT
	public boolean terminate() { 
		if(this.ESTADOS.size() == this.EXIT.size())
			return true;
		return false;
	}
}