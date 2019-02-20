#include "GTUMap.h"
#include <string>

namespace CSE241_151044026
{
	template<class K, class V>
	V& GTUMap<K,V>::operator[](const K& k){
		GTUIterator<pair<K,V>> returnvalue = find(k); 
		if(returnvalue.getCurrent() == nullptr){// mape te eleman yoksa find nullptr return ediceği için burada onun
											     // kontrolünü yapıpyeni eleman ekliyorum 
			pair<K,V> temp = make_pair(k,V());
			returnvalue = insert(temp);
			return (*returnvalue).second; 
		}
		else{
			return (*returnvalue).second;//mape zaten varsa
		}
	}

	template<class K,class V>
	GTUIterator<pair<K,V>> GTUMap<K,V>::find(const K& wanted)const{//mape te keyle arama yaptiğim fonksiyon
		for(auto iterator=this->begin();iterator!=this->end();iterator++){
			if( (*iterator).first==wanted ){
				return iterator; 
			}
		}
		return GTUIterator<pair<K,V>>(nullptr);
	}

	template<class K, class V>
	template<class T> 
	GTUIterator<T> GTUMap<K,V>::insert(const T& value){// key göre eleman eklediğim fonksiyon		
		auto iterator=this->begin();
		for(;iterator!=this->end();iterator++){
			if((*iterator).first==value.first ){
				throw ErrorMessage("Bu key zaten mapte var."); 
			}
		}
		GTUSet<pair<K,V>>::insert(value);
		auto sonuc=find(value.first);
		return sonuc;
	}
}