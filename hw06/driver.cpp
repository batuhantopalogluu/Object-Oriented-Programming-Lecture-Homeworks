/***********************************/
/*	Batuhan TOPALOĞLU 151044026    */
/*								   */
/*	CSE 241 HW6					   */
/***********************************/

#include "GTUMap.cpp"
#include <string>

using namespace CSE241_151044026;

template <class T>
shared_ptr<GTUSetBase<T>>setIntersection(const GTUSetBase<T>&, const GTUSetBase<T>&);

int main(int argc, char const *argv[])// make file a map i ekle
{
	try{
		GTUSet<int> Set;
		cout<<"\nBoş küme tanımlandığı andaki durum"<<endl;
		cout<<"Set.empty() : "<<Set.empty()<<endl;
		cout<<"Set.max_size :"<<Set.max_size()<<endl;
		cout<<"Set.size() : "<<Set.size()<<endl;
		
		Set.insert(4);//karmaşık sırayla veriyorum sıralamayı doğru yapabiliyormu diye kontrol etmek için
		Set.insert(2);
		Set.insert(0);
		Set.insert(8);
		Set.insert(1);
		Set.insert(10);
		Set.insert(9);
		Set.insert(3);
		Set.insert(5);
		
		cout<<"Sırasıyla 4 2 0 8 1 10 9 3 5 ekleniyor "<<endl
			<<"Set in elemanlarını iteratörle gezerek yazdırınca : ";
		for (auto iterator=Set.begin();iterator!=Set.end();iterator++){
			cout<<*iterator<<" ";
		}
		
		cout<<"\nŞuanki Set.size() : "<<Set.size()<<endl
	    	<<"Set.begin() : "<<*Set.begin()<<endl;
	    
	    if(*Set.find(5)==5)
	    	cout<<"Set.find(5) : Eleman Sette bulundu"<<endl;
		else cerr<<" ! Set.find(5) : Eleman bulunamadı"<<endl;
		
		cout<<"Set.count(5) : "<<Set.count(5)<<endl;		
		
		Set.erase(5);
		Set.erase(0);
		cout<<"Set.erase(5) Set.erase(0) işlemlerinden sonra Set.size() : "
			<<Set.size()<<endl;
		
		Set.clear();
		cout<<"Set.clear() işleminden sonra Set.size() : "
			<<Set.size()<<endl;
		
		//Set i String ile test ediyorum
		cout<<"\nString tipinde veriler tutan set tanımlaması için : \n";
		GTUSet<string> SSet;
		SSet.insert("batuhan");
		SSet.insert("topaloglu");
		cout<<"SSet.insert('batuhan')"<<endl
			<<"SSet.insert('topaloglu')"<<endl
			<<"işlemleri yapıldıktan sonra ..."<<endl;
		
		cout<<"SSet.size() : "<<SSet.size()<<endl;
		
		cout<<"SSet.find('batuhan') işleminin sonucu : ";
		if(*SSet.find("batuhan")=="batuhan")
			cout<<"Sette bulundu"<<endl;
		else cout<<"Sette bulunamadı"<<endl; 

		cout<<"\nIntersection Fonksiyonu : \n";
		GTUSet<int> Set1;

		Set1.insert(4);
		Set1.insert(2);
		Set1.insert(0);
		Set1.insert(8);
		Set1.insert(6);

		GTUSet<int> Set2;

		Set2.insert(4);
		Set2.insert(12);
		Set2.insert(10);
		Set2.insert(8);
		Set2.insert(6);

		cout<<"Birinci kümenin elemanları: "<<endl;
		for (auto iterator=Set1.begin();iterator!=Set1.end();iterator++){
			cout<<*iterator<<" ";
		}
		cout<<"\nİkinci kümenin elemanları: "<<endl;
		for (auto iterator=Set2.begin();iterator!=Set2.end();iterator++){
			cout<<*iterator<<" ";
		}
		cout<<endl;
		
		auto intersection=setIntersection(Set1,Set2);
		cout<<"Kesişim kümesinin elemanları : "<<endl;
		for(GTUIterator<int> iterator=intersection->begin();iterator!=intersection->end();iterator++){
			cout<<*iterator<<" ";
		}
		cout<<endl;

		cout<<"\nMape :"<<endl;
		
		GTUMap<string,int> mape;
		pair<string,int>pair1("batuhan",1);
		pair<string,int>pair2("topaloglu",2);
		cout<<"\npair1('batuhan',1) ve "<<endl
			<<"pair2('topaloglu',2) "<<endl
			<<"insert ediyorum."<<endl;
		mape.insert(pair1);
		mape.insert(pair2);
		
		cout<<"\nMape['Türkiye'] = 3 Satırını yazınca Türkiye Mapete olmamasına rağmen bu satırdan sonra ekleniyor.\n";
		mape["Türkiye"]=3;
		cout<<"Mape in son hali :"<<endl;

		for(auto iterator=mape.begin();iterator!=mape.end();iterator++){
			cout<<(*iterator).first<<"  "<<(*iterator).second<<endl;
		}
		cout<<"\nTürkiye , 5  Mape e eklenmek istediğinmde : ";		
		pair<string,int>pair3("Türkiye",5);
		mape.insert(pair3);
		//Türkiye key inden bir eleman olduğu için insert Fonksiyonu Exception fırlatıyor 
	}
	catch(ErrorMessage m)
	{
		m.showMessage();
	}
	
	return 0;
}


template <class T>
shared_ptr<GTUSetBase<T>> setIntersection(const GTUSetBase<T>& first, const GTUSetBase<T>& second){

	GTUSet<T> intersectionResult;
	T values1[first.size()];
	T values2[second.size()];
	
	int index=0;
	for(auto iterator=first.begin();iterator!=first.end();iterator++,index++){
		values1[index]=*iterator;
	}
	index=0;
	for(auto iterator=second.begin();iterator!=second.end();iterator++,index++){
		values2[index]=*iterator;
	}

	for(int i = 0;i<first.size();i++){
		for(int j=0;j<second.size();j++){
			if(values1[i] == values2[j]){
				intersectionResult.insert(values1[i]);
			}
		}
	}
	auto result = make_shared<GTUSet<T>>(intersectionResult);
	return result;		
}		

