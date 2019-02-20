#include "GTUIterator.h"

namespace CSE241_151044026
{
	template<class T>
	T& GTUIterator<T>::operator*(){		
		return current->getData();
	}	
	template<class T>
	const shared_ptr< GTUNode<T>> GTUIterator<T>::operator->() const{		
		return current;// *(iteratör). ile aynı anlaması gelmesi gerektiği için current i return ediyor
	}
	template<class T>
	const shared_ptr<GTUNode<T>>  GTUIterator<T>::getCurrent() const{
		return current;
	}
	template<class T>
	const GTUIterator<T>& GTUIterator<T>::operator++(){//prefix ++	
		current =current->getNextLink();
		return *this;
	}
	template<class T>
	const GTUIterator<T> GTUIterator<T>::operator++(int){//postfix ++
		GTUIterator starVersion(current);
		current =current->getNextLink();
		return starVersion;
	}
	template<class T>
	const GTUIterator<T>& GTUIterator<T>::operator--(){
		current =current->getPreviousLink();
		return *this;
	}
	template<class T>
	const GTUIterator<T> GTUIterator<T>::operator--(int){
		GTUIterator starVersion(current);
		current =current->getPreviousLink();
		return starVersion;
	}
	template<class T>
	const GTUIterator<T>& GTUIterator<T>::operator=(const GTUIterator<T>& other){		
		current =other.current;
		return *this; 
	}
	template<class T>
	bool GTUIterator<T>::operator==(const GTUIterator<T>& other) const{
		if(current == other.current)
			return true;
		return false;
	}
	template<class T>
	bool GTUIterator<T>::operator!=(const GTUIterator<T>& other) const{
		return !(current == other.current);//== in tersinden yararlanıyorum
	}

	template<class T>// GTUSet.cpp de end(return type shared_ptr< GTUNode<T>>) ile iteratör ü kıyaslarken kullanıyorum
	bool operator!=(const shared_ptr< GTUNode<T>>& x, const GTUIterator<T>& y){
		if(x != y.getCurrent());
	}
}