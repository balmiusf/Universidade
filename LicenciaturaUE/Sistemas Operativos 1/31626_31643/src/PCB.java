
public class PCB {

	private int id;
	private String estado;
	private int instante;
	private int[] instrucoes;
	private int paginas_ocupadas;
	private int pc;
	
	public PCB(int id, String estado, int[] instrucoes) {
		this.pc = 0;
		this.id = id;
		this.estado = estado;
		this.setInstrucoes(instrucoes);
		this.instante = 0;
	}
	
	//Construtor para um PCB vazio
	public void setPC(int pc)
	{
		this.pc = pc;
	}
	public int getPaginas_ocupadas() {
		return paginas_ocupadas;
	}

	public void setPaginas_ocupadas(int paginas_ocupadas) {
		this.paginas_ocupadas = paginas_ocupadas;
	}
	
	public int getId() {
		return id;
	}

	public void setId(int id) {
		this.id = id;
	}

	public String getEstado() {
		return estado;
	}

	public void setEstado(String estado) {
		this.estado = estado;
	}

	public int getPC()
	{
		return this.pc;
	}
	public int[] getInstrucoes() {
		return instrucoes;
	}

	public void setInstrucoes(int[] instrucoes) {
		this.instrucoes = instrucoes;
	}

	public int getInstante() {
		return instante;
	}

	public void setInstante(int instante) {
		this.instante = instante;
	}
	
}