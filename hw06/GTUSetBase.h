#ifndef GTUSETBASE_H
#define GTUSETBASE_H

#include "GTUIterator.cpp"

namespace CSE241_151044026
{
	template <class T>
	class GTUSetBase
	{ //GTUSet conteynerini türeteceğimiz template abstract base class .Bütün fonksiyonlar pure virtual .
	public:
		virtual bool empty() const =0;
		virtual int size() const =0;
		virtual int max_size() const =0;
		virtual void insert(const T& parametre) =0;
		virtual int erase(const T& parametre) =0;//std::set::erase de parametre olarak silinecek değeri alan erase için return 
		//						" the function returns the number of elements erased." olarak verildiği için int return ediyorum. 
		virtual void clear() =0;
		virtual GTUIterator<T> find(const T& parametre) const =0;
		virtual int count(const T& parametre) const =0;
		virtual GTUIterator<T> begin() const =0;
		virtual GTUIterator<T> end() const =0;
	};	
}

#endif