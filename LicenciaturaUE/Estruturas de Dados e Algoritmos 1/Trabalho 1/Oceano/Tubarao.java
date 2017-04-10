package Oceano;

public class Tubarao extends Bestas{
	int food = 1;
	int tubarao = 1;
	
	public Tubarao(){
		super(1);
	}
	
	public Tubarao(int food){
		super(1);
		this.food = food;
	}
	
	public void setFood(int food){
		this.food = food;
	}
	public int getFood(){
		return food;
	}
	
	public int getTubarao(){
		return tubarao;
	}
}
//31626 - Andre Figueira