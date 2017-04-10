package Oceano;

import java.util.Iterator;

public class SingleNode<T> {
	T element;
	SingleNode<T> next;
	int size = 0;
	
	public SingleNode(T e){
		element = e ;
		next = null;
	}
	public SingleNode(){
		this(null);
		
	}
	public SingleNode(T e , SingleNode<T> n){
		element = e ;
		next = n;
	}
	
	///////////////////////////
	public T getElement() {
		return element;
	}
	public void setElement(T element) {
		this.element = element;
	}
	public SingleNode<T> getNext() {
		return next;
	}
	public void setNext(SingleNode<T> next) {
		this.next = next;
	}
	public int getSize() {
		return size;
	}
	public void setSize(int size) {
		this.size = size;
	}
	/////////////////////////////
	public T element() throws InvalidNodeException{
		 if (this==null)
		 throw new InvalidNodeException();
		 return element;
	}
}//31626 - Andre Figueira
