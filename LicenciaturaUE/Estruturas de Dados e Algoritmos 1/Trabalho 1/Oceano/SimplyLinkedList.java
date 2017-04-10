package Oceano;

import java.util.Iterator;

public class SimplyLinkedList<T> implements Iterable<T>,Cloneable {
	private SingleNode<T> header;
	public int size;
	
	public SimplyLinkedList(){
		header = new SingleNode<T>(null);
        size = 0;
	}
	
	public java.util.Iterator<T> iterator(){
		return new LinkedListIterator<T>(header.next);
		
	}
	public int size(){
		return size;
	}

	public boolean isEmpty(){
		return size == 0;
	}

	public void add(int i , T x ){
		SingleNode<T> newNode = new SingleNode<T>(x);
		SingleNode<T> p = header();
		
		if (i == 0){
			newNode.setNext(header.getNext());
			header.setNext(newNode);
		}else{
			
			for (int j = 0;j<i;j++){
				p = p.next; //ou usar getNext();
			}
			newNode.setNext(p.getNext());
			p.setNext(newNode);
		}
		size++;

	}
	void add(SingleNode<T> prev, T x){
		 SingleNode<T> newNode= new SingleNode<T>(x,prev.getNext()); 
		 prev.setNext(newNode);
		 size++;
		 }
	
	public void add(T x){
		SingleNode<T> n = new SingleNode<T>(x, null);
		SingleNode<T> p = header();
		while(p.next!=null){
			p = p.next;
		}
			p.next = n;
			size++;
	}
	void remove(SingleNode<T> prev){
		 prev.setNext(prev.getNext().getNext());
		 size--;
		 }
		 
	public void remove(int ind){
		remove(getNode(ind-1));
		}
		 
	public SingleNode<T> findPrevious(T x) {
		SingleNode<T> p=header();
		for(T v:this){
			if (v.equals(x)) return p; else p=p.getNext();
		 	}
		 throw new java.util.NoSuchElementException( );
		 
		 }
		
	public void set(int i, T x){
		getNode(i).setElement(x);
	}
	
	public T get(int i) throws InvalidNodeException{
		if (i >=0 && i<=size()-1){
			return getNode(i).element();
		}else{
			throw new IndexOutOfBoundsException( "getNode index: " + i + "; size: " + size( ) );
		}
	}
	
	public SingleNode<T> header(){
		 return header;
	}
	
	SingleNode<T> getNode(int i){
		 int ind=-1;
		 SingleNode<T> s=header();
		 while(ind++<i)
		 s=s.getNext();
		 return s;
		 
	}
	
	public String toString(){
		 StringBuilder sb = new StringBuilder( "[ " );
		 
		 for( T x : this ){
			sb.append( x + " " );
		 }
		 sb.append( "]" );
		 return new String( sb );
		 }
	
	//31626 - Andre Figueira
}
