#include "GTUNode.h"

namespace CSE241_151044026
{    
    template<class T> 
    const shared_ptr<GTUNode<T>> GTUNode<T>::getNextLink()const{
    	return next;
    }
	
	template<class T> 
	void GTUNode<T>::setNextLink(shared_ptr<GTUNode<T>> pointer){ 
		next=pointer; //sonraki nodeu gösteren pointer ı değiştiriyoruz
	} 

	template<class T> 
	const shared_ptr<GTUNode<T>> GTUNode<T>::getPreviousLink()const{
		return previous;
	}	
	
	template<class T> 	
	void GTUNode<T>::setPreviousLink(shared_ptr<GTUNode<T>> pointer){ 
		previous=pointer; //önceki nodeu gösteren pointer ı değiştiriyoruz
	}
	
	template<class T>
	T& GTUNode<T>::getData(){
		return data;// node daki veriyi döndürüyor
	}
	
	template<class T>
	void GTUNode<T>::setData(const T& theData){ 
		data = theData; 
	}
}