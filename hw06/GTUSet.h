#ifndef GTUSET_H
#define GTUSET_H

#include <iostream>
#include "GTUSetBase.h"

using namespace std;

namespace CSE241_151044026
{
	class ErrorMessage{
	public://Exception fırlatırken Hata durumları mesajlarınıda yanlarında göndermek için exception classımı yaptım.
		ErrorMessage(string message) : errorMessage(message){}
		void showMessage(){cout<<errorMessage;}
		string errorMessage;
	};
	
	template <class T>
	class GTUSet : public GTUSetBase<T>
	{
	public:
		GTUSet(){ head = nullptr; } //Boş küme tanımlaması 
		virtual bool empty() const override;
		virtual int size() const override;
		virtual int max_size() const override;// tutulan node verisinin boyutuna göre sistemde olabileceği max set boyutu.
		virtual void insert(const T& newN) throw(ErrorMessage) override;//eklenecek eleman zaten sette varsa exception fırlatıyor.
		virtual int erase(const T& eraseElement) override;//silinecek eleman sette yoksa 0 return ediyor, aksi halde 1.
		virtual void clear() override;
		virtual GTUIterator<T> find(const T& wanted)const override;// arana eleman sette yoksa end()'i return ediyor.
		virtual int count(const T& parametre) const override;
		virtual GTUIterator<T> begin() const override;
		virtual GTUIterator<T> end() const override;//set'in son elemanından sonraki yeri gösterdiği için linkedlistte nullptr return ediyor.		
	protected:
		void orderSet();//set e her eleman eklendiğinde set tekrar sıralamak için kullanıyorum.
		int lenght = 0;
		shared_ptr<GTUNode<T>> head;
	};	
}
#endif