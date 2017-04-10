package Oceano;


public class LinkedListIterator<T> implements java.util.Iterator<T>{
	private SingleNode<T> current;
	
	public LinkedListIterator(SingleNode<T> e){
		current = e;
	}
	
	public boolean hasNext(){
		return (current != null);
	}
	
	public T next(){
		if (!hasNext()){
			throw new java.util.NoSuchElementException();
		}
		T nextx = null;
		try {
			nextx = current.element();
		} catch (InvalidNodeException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		current = current.getNext();
		return nextx;
	}
	
	public void remove(){
		throw new UnsupportedOperationException();
	}
}
//31626 - Andre Figueira