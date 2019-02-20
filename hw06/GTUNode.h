#ifndef GTUNODE_H
#define GTUNODE_H

#include <memory>

using std::shared_ptr;

namespace CSE241_151044026
{	
	template<class T>
	class GTUNode
	{
	typedef shared_ptr<GTUNode<T>> node_ptr;
	public:
		GTUNode(T theData):data(theData),next(nullptr),previous(nullptr){}//önü ve arkası olmayan tek verilik node.
		GTUNode(T theData,node_ptr theNext,node_ptr thePrevious):data(theData),next(theNext),previous(thePrevious){}
		const node_ptr getNextLink() const ;
		const node_ptr getPreviousLink() const ;
		T & getData();
		void setNextLink(node_ptr pointer);
		void setPreviousLink(node_ptr pointer);
		void setData(const T& theData);
	private:
		T data; //node un içinde tuttuğu veri
		node_ptr next;//bir sonraki node u gösteren pointer
		node_ptr previous; // bir önceki node u gösteren pointer
	};
}
#endif