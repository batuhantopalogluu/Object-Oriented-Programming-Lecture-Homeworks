package pkg151044026;

// Batuhan TOPALOĞLU 151044026 CSE241
import java.security.InvalidParameterException;

public class GTUMap<K, V> extends GTUSet< javafx.util.Pair <K, V> >
{
	public V at(final K k)throws InvalidParameterException{

		for(int i=0;i<lenght;i++){
			if(((javafx.util.Pair)data[i]).getKey()==k){//data[i] nin tipini pair a cast ediyorum çünkü object tipinde
				return (V)((javafx.util.Pair)data[i]).getValue();
			}
		}
		throw new InvalidParameterException("!!! Bu key de bir Pair mecvut değil.");
	}
	
	public void insert(final javafx.util.Pair parametre) throws InvalidParameterException
	{
		if(lenght == 0){
			data[0] = new javafx.util.Pair(parametre.getKey(),parametre.getValue());
			lenght++;
		}
		else{
			for(int i=0;i<lenght;i++){
				if(((javafx.util.Pair)data[i]).getKey()==parametre.getKey()){
					throw new InvalidParameterException("!!! Aynı key'e sahip bir eleman mevcut");//aynı keyde bir eleman önceden varsa
				}										  // exception fırlatıyor
			}
			if(lenght+1<capacity){//end() fonksiyonu lenght'inci elemanı gösterdiği için mape lenght tane elemana 
								 // sahip olunca erişmek istediğim bana ait olmuyor onu önlemek için lenght+1'i kontrol ediyorum
				data[lenght] = new javafx.util.Pair(parametre.getKey(),parametre.getValue());	
				lenght++;
			}
			else{
				// Kapasite ulaşılmışsa bütün eleman temp bir yere atılır ve kapasite +20 lik yeni bir yer alınıp
				// veriler tekrar kopyalanır
				Object [] temp = new Object[lenght+1];
				for (int i=0;i<lenght;i++){
					temp[i]=new javafx.util.Pair(((javafx.util.Pair)data[i]).getKey(),((javafx.util.Pair)data[i]).getValue());
				}
				temp[lenght]= new javafx.util.Pair(parametre.getKey(),parametre.getValue());
				lenght++;
				data = null;
				data = new Object[capacity+20];
				for (int i=0;i<lenght;i++){
					data[i]= new javafx.util.Pair(((javafx.util.Pair)temp[i]).getKey(),((javafx.util.Pair)temp[i]).getValue());
				}
			}

		}
	}
	//@Override
	public GTUMap<K,V> intersection(final GTUSetInt<javafx.util.Pair<K,V>>  parametre){//GTUSetInt<javafx.util.Pair<K,V>> 
		
		//GTUSetInt< javafx.util.Pair <K, V> > temp = /*(GTUSetInt<javafx.util.Pair<K,V>>)*/ new GTUSet<javafx.util.Pair<K,V>>();
		GTUMap<K,V> temp = new GTUMap<K,V>();
		for(int i=0;i<lenght;i++){ // this de elemanları parametre olarak gelen Sette arıyorum eşleşenleri kesişim kümeme ekliyorum
			if(((/*GTUSet<javafx.util.Pair<K,V>>*/GTUMap<K,V>)parametre).findMapElement((javafx.util.Pair)data[i])){//findElement boolean bir fonksiyon 
				temp.insert((javafx.util.Pair)data[i]);												 //gönderilen keyde eleman varsa true return ediyor
			}
		}	
		return ((GTUMap<K,V>)temp);
	}

	private boolean findMapElement(final javafx.util.Pair parametre){// Interseciton için yardımcı fonksiyon
		
		for(int i = 0;i<lenght;i++){// Aranan eleman sette true return ediyor
			if(((((javafx.util.Pair)data[i]).getKey()).equals(parametre.getKey())) 
		    && ((((javafx.util.Pair)data[i]).getValue()).equals(parametre.getValue()))){					
				
				return true;
			}
		}
		return false;
	}

	public int erase(final javafx.util.Pair parametre){
		if(lenght == 0){
			return 0;//silinen eleman sayısını return ediyor .Boş mape te eleman silemeyiz
		}
		for(int i=0;i<lenght;i++){
			if((((javafx.util.Pair)data[i]).getKey()).equals(parametre.getKey())){//siinecek key de eleman varsa onun ardında ki bütün elemanlar bir index öne alınır.
				for(int j= i;j+1<lenght;j++){
					data[j] = new javafx.util.Pair(((javafx.util.Pair)data[j+1]).getKey(),((javafx.util.Pair)data[j+1]).getValue());
				}
				lenght--;
				return 1;//silinen eleman sayısı
			}
		}
		return 0;//o key de eleman sette yok demek		
	}
	public GTUIterator<javafx.util.Pair<K,V>> find(javafx.util.Pair parametre){//gönderilen pair'ı keyi ile arıyor sette arıyorum.
		
		GTUIterator<javafx.util.Pair<K,V>> iter = new GTUIterator<javafx.util.Pair<K,V>>();//return edilecek iteratör oluşturulur
		for(int i = 0;i<lenght;i++){
			if((((javafx.util.Pair)data[i]).getKey()).equals(parametre.getKey())){//aranan key'deki eleman sette koşul sağlanır onun bilgileri iter e aktarılır
				iter.setCurrent((javafx.util.Pair)data[i]);
				iter.setIndex(i);
				return iter;
			}
		}
		iter=(GTUIterator<javafx.util.Pair<K,V>> )this.end();// aranan keyde eleman yoksa c++ standartta end return ettiği burada da öyle yapyorum
		return iter;
	}
}