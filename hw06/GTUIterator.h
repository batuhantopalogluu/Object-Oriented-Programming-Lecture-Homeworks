#ifndef GTUIterator_H
#define GTUIterator_H

#include <memory>
#include "GTUNode.cpp"

namespace CSE241_151044026
{
	template<class T>
	class GTUIterator
	{
	typedef shared_ptr<GTUNode<T>> node_ptr;// okumayı kolaylaştırmak için kullandım
	typedef GTUIterator<T> iter;
	public:
		GTUIterator() : current(nullptr){}
		GTUIterator(node_ptr initial) : current(initial){}
		const node_ptr operator->() const;
		T& operator*();
		const node_ptr getCurrent() const;
		const iter& operator++();//Prefix form
		const iter operator++(int); //Postfix form
		const iter& operator--();
		const iter operator--(int);
		const iter& operator=(const iter& other);
		bool operator==(const iter& other) const;// currentları kıyaslıyor
		bool operator!=(const iter& other) const;
		bool operator!=(const shared_ptr<T> parameter) const;
	private:
		node_ptr current;//iteratör ün geçerli andaki gösterdiği yer.
	};
}

#endif