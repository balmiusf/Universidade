import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.io.FileWriter;
import java.util.Scanner;
import java.util.concurrent.*;


public class Main extends Thread{
	
	final Semaphore semaphore = new Semaphore(1); 
	public Scheduler scheduler; // inicializado com valores default
	String ficheiro; // ficheiro
	boolean got_input; // flag que verifica se tem input
	boolean cycle; // ciclo while na main;
	FileWriter fw;

	// command prompt
	Thread command_prompt = new Thread() {
		public void run() {
			try 
			{
				Scanner input = new Scanner(System.in);
				while(cycle) {

					semaphore.acquire();										
					System.out.println("Insere Processo: ");
					ficheiro = input.nextLine(); // pede processo
					ficheiro = ficheiro +".txt";
					File f = new File(ficheiro); // verifica a existencia
					// caso nao exista escreve no ficheiro
			    	if (!ficheiro.equals("stop.txt") && !f.exists()) 
			    	{
			    		fw = new FileWriter("scheduler.out",true);
			    		fw.write("\nPROGRAM "+ficheiro+" NOT FOUND\n\n");
			    		fw.close(); 
			    	}
			    	else // caso exista
			    	{
			    		got_input = true; // altera a flag
			    		if(ficheiro.equals("stop.txt")) // terminar programa
			    		{
			    			got_input = false; // altera flag
			    			cycle = false; // altera flag
						}
			    	}
					semaphore.release();
					Thread.sleep(500);
				}
				
			} 
			catch (Exception e) 
			{
				e.printStackTrace();
			}
		}
	};

	private void read_input(String ficheiro) 
	{
		String line;
		try 
		{
			BufferedReader f = new BufferedReader(new FileReader(ficheiro));
			while ((line = f.readLine()) != null) 
			{
				int[] inst;
				boolean containsExit = false; // verificar se contem a instrucao 0
				String[] aux = line.split(" "); 
				for(int i = 0;i < aux.length; i++)
					if(aux[i].equals("0")) //procurar o 0
						containsExit = true; // altera a flag
				if(!containsExit){ // se nao contem 
					inst = new int[aux.length+1]; // mais uma posicao
					inst[aux.length] = 0;
				}
				else
					inst = new int[aux.length];
				
					
				for (int i = 0; i < aux.length; i++)
					inst[i] = Integer.parseInt(aux[i]); // copiar instrucoes
				
				// adicionar processo a lista new
				this.scheduler.NEW.add(new PCB(this.scheduler.pid, "new", inst));
				this.scheduler.NEW.get(this.scheduler.NEW.size()-1).setInstante(this.scheduler.getTempo());
				
				this.scheduler.pid++; // incrementa process identifier
			}
			// adicionar a lista de estados actuais
				this.scheduler.ESTADOS.add(this.scheduler.NEW.get(this.scheduler.NEW.size()-1)); 
			
		f.close();
	}
		catch (IOException e) 
		{
			e.printStackTrace();
		}
	}
	
	
	public static void main(String[] args) throws InterruptedException, IOException {
		Main teste = new Main();
		teste.got_input = false; // inicializar flag
		teste.cycle = true;  // inicializar flag
		Scanner input = new Scanner(System.in);
		
		System.out.println(" ** Inserir -1 implica valores defaults ** ");
		System.out.println("Numero maximo processos a correr: ");
		String n_processos = input.next(); // pede o numero de processos
		if(n_processos.equals("-1"))
			n_processos = "10"; // valor default
		System.out.println("Numero maximo de paginas disponiveis: ");
		String n_paginas = input.next(); // pede o numero de paginas
		if(n_paginas.equals("-1"))
			n_paginas = "10"; // valor default
		//inicializar scheduler
		teste.scheduler = new Scheduler(Integer.parseInt(n_processos),Integer.parseInt(n_paginas));
		System.out.println(" ** Inserir stop para terminar programa ** ");
		System.out.println(" ** ( Basta inserir nome do programa ) ** ");
		
		teste.command_prompt.start(); // thread comeca

		while(teste.cycle) 
		{	
			while(teste.got_input) // flag activada pela thread
			{
				teste.read_input(teste.ficheiro); // le ficheiro
				// altera flag, impede que o mesmo ficheiro esteja sempre a 
				// ser lido quando esta a espera de input
				teste.got_input = false; 
				Thread.sleep(1000);
			}
			if (teste.ficheiro != null) // caso tenha sido alterado
			{ 
				teste.fw = new FileWriter("scheduler.out",true);
				teste.fw.write(teste.scheduler.toString()); // escreve
				teste.scheduler.scheduler(); // corre o escalonador
				teste.fw.close(); // fecha
				
				if(teste.scheduler.terminate()){ // todos os processos terminaram
					teste.cycle = false; // altera a flag
					teste.fw = new FileWriter("scheduler.out",true);
					teste.fw.write(teste.scheduler.toString()); // escreve
					teste.fw.close(); // fecha
				}
			}
			Thread.sleep(1000);	
		}
		teste.command_prompt.join(); // espera pa terminar
		System.exit(0); // programa termina
	}
}
