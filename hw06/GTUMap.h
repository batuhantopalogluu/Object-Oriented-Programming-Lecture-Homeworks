#ifndef GTUMAP_H
#define GTUMAP_H

#include "GTUSet.cpp"
#include <utility>

namespace CSE241_151044026
{
	template <class K,class V>
	class GTUMap : public GTUSet<pair<K,V>>
	{
	public:
		V& operator[](const K& k);
		template<class T>
		GTUIterator<T> insert(const T& newN);//GTUSet::insert() den farklı;
		GTUIterator<pair<K,V>> find(const K& wanted)const; //GTUSet::find() den farklı;
	};
}
#endif

