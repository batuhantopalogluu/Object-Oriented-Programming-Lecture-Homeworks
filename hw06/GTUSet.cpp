#include "GTUSet.h"
#include <unistd.h>// sistemdeki ram bilgisini öğrenmek için kullanıyorum.
namespace CSE241_151044026
{
	template <class T>
	bool GTUSet<T>::empty() const{
		return (lenght == 0);
	}
	
	template <class T> 
	int GTUSet<T>::size() const{ 
		return lenght; //node sayısını return ediyor
	}
	
	template <class T>
	int GTUSet<T>::max_size() const{ // std de "Returns the maximum number of elements that the set container can hold." 
    // olarak tanımlanmış sistemin çalıştığı makinenin donanımına ve o esnada diğer işlemlere göre değişecek bir değer.
    // Ben fiziksel ram miktarını(bit)i değişken tipine bölerek bir değer return ediyorum.		
		return sysconf(_SC_PHYS_PAGES) * sysconf(_SC_PAGESIZE)/(8*sizeof(T));
	}

	template <class T>
	void GTUSet<T>::insert(const T& newN) throw(ErrorMessage){	

		if(lenght==0){
			head=make_shared<GTUNode<T>>(newN);
			head->setNextLink(nullptr);
			head->setPreviousLink(nullptr);
			lenght++;
		}
		else{
			auto iterator=begin();
			for (;iterator!=end();iterator++){
				if(*iterator==newN){
					throw ErrorMessage("! Bu eleman zaten Set'te var.");
				}
			}
			for (iterator=begin();iterator!=end();iterator++){//
				if(iterator->getNextLink()== nullptr){
					auto toNewN = make_shared<GTUNode<T>>(newN);
					toNewN.get()->setNextLink(nullptr);
					toNewN.get()->setPreviousLink(iterator.getCurrent());
					iterator->setNextLink(toNewN);
					lenght++;
					break;
				}
			}
		}		
		orderSet();
	}

	template <class T>
	void GTUSet<T>::orderSet(){		
		T temp ;
		auto j = begin(); //değişkenin tipini auto ile direk belirtmek için çöp bir atama yapıyorum .
		for (auto i=begin();i!=end();i++){
			for (j=i;j!=end();j++){
				if(j->getNextLink()!= nullptr && (j->getData()>(j->getNextLink())->getData())){
					temp = j->getData();
					j->setData(j->getNextLink()->getData());
					(j->getNextLink())->setData(temp);
				}
			}
		}		
	}

	template <class T>
	int GTUSet<T>::erase(const T& eraseElement){
		int statu=0;
		if(head->getData()==eraseElement){ // head silmek istiyorsak bir sonraki node u head yapmamız yeterli
			head=head->getNextLink();
			lenght--; //eleman sildikçe settin eleman sayısını azaltmayı azaltıyoruz
		}
		else{
			for(auto iterator=begin();iterator!=end();iterator++){
				if(*iterator==eraseElement){ // *iterator data'yı return ettiği için silinecek elemanla kıyaslaya biliyorum
					iterator->getPreviousLink()->setNextLink(iterator->getNextLink());
					statu=1;
					lenght--;
					return 1;//silinen eleman sayısı her doğru koşulda 1 olacağı için 1 return ediyorum.
				}
			}
			if(statu==0){ 
				return 0;//silinen eleman olmadığı için hata durumu olarak 0 return ediyorum.
			}				
		}					
	}
	
	template <class T>
	void GTUSet<T>::clear(){
		for (auto iterator=begin();iterator!=end();iterator++){
			erase(*iterator);//bütünn  nodeları tek tek gezerek siliyorum
		}
	}
		
	template <class T>
	GTUIterator<T> GTUSet<T>::find(const T& wanted) const{
		
		for (auto iterator=begin();iterator!=end();iterator++){
			if(iterator.getCurrent()->getData()==wanted){
				return iterator;
			}
		}
		return end();// std::set te hata durumunda end() return ettiği için bende öyle yapıyorum 
	}

	template <class T>
	int GTUSet<T>::count(const T& parametre) const{
		if(this->find(parametre)==GTUIterator<T>(nullptr))return 0; //Count u aranan eleman set'in üyesi değilse 0 return edilir
		return 1; //Set'in bir üyesi ise her elemandan sadece 1 tane olabileceğinden direk 1 return ediliyor.
	}
	
	template <class T>
	GTUIterator<T> GTUSet<T>::begin() const{
		return head;//ilk node u gösteren iteratör ü return ediyor
	}
	
	template <class T>
	GTUIterator<T> GTUSet<T>::end() const{
		return GTUIterator<T>(nullptr);//std::end() set in son elemanından sonrasını gösteriyor .Linkedlist te son node dan sonrasını
									   // gösteren pointer nullptr olduğu için direk nullptr return etmek zorundayım .
	}
}