package pkg151044026;

/**
 *
 * @author batuhan
 */
import java.security.InvalidParameterException;

public class GTUSet<E> implements GTUSetInt<E>
{
    protected int lenght = 0;
    protected int capacity;
    public Object [] data;// Verinin tipini E tutunca yer alırken sıkıntı yaşıyordum.Paylaşılan çözümü de sonradan gördüğüm için verimi
                                            // Object tipinde tutuyorum ve kullanacağım zaman (E) ye cast ediyorum.

    public GTUSet(){
            data = new Object[20];// default olarak 20 lik yer kapasite tutuyorum
    }

    @Override
    public boolean empty(){
            return (lenght == 0);
    }

    @Override
    public int size(){
            return lenght;
    }

    @Override
    public int max_size(){
            return 1000;//*******************************
    }

    @Override
    public void insert(final E parametre)throws InvalidParameterException{

            if(lenght == 0){
                    data[0] = parametre;
                    lenght++;
            }
            else{
                    for(int i=0;i<lenght;i++){
                            if(data[i]==parametre){// Set in özelliğinden dolayı aynı eleman birden fazla olamıyor.
                                    throw new InvalidParameterException();//Eklenmek istenilen eleman sette var ise exception fırlatılıyor
                            }				
                    }

                    if(lenght+1<capacity){// Sette kapasite dahilinde yer olması durumu
                                    //end() fonksiyonu lenght'inci elemanı gösterdiği için mape lenght tane elemana 
                                    // sahip olunca erişmek istediğim bana ait olmuyor onu önlemek için lenght+1'i kontrol ediyorum
                            data[lenght]=parametre;
                            lenght++;
                    }
                    else{
                            // Kapasite ulaşılmışsa bütün eleman temp bir yere atılır ve kapasite +20 lik yeni bir yer alınıp
                            // veriler tekrar kopyalanır
                            Object [] temp = new Object[lenght+1];
                            for (int i=0;i<lenght;i++){
                                    temp[i]=data[i];
                            }
                            temp[lenght]=parametre;
                            lenght++;
                            data = new Object[capacity+20];
                            for (int i=0;i<lenght;i++){
                                    data[i]=temp[i];
                            }
                    }
            }
    }

    public GTUSetInt<E> intersection(final GTUSetInt<E> parametre){

            GTUSetInt<E> temp = new GTUSet<E>();
            for(int i=0;i<lenght;i++){ // this de elemanları parametre olarak gelen Sette arıyorum eşleşenleri kesişim kümeme ekliyorum
                    if(((GTUSet)parametre).findElement((E)data[i])){//findElement boolean bir fonksiyon  
                            temp.insert((E)data[i]);
                    }
            }	
            return temp;
    }

    public int erase(E parametre){
            if(lenght == 1){
                    data[0]=0;
                    lenght --;
                    return 1;// silinen eleman sayısı doğru koşullarda her zaman 1 olucağı için 1 return ediyorum
            }
            for(int i=0;i<lenght;i++){
                    if(data[i].equals(parametre)){//silinecek elemanı sette bulma durumu
                            for(int j= i;j+1<lenght;j++){
                                    data[j]=data[j+1];// silinen elemandan sonrasını birer adım öne çekiyorum
                            }
                            lenght--;
                            return 1;
                    }
            }
        return 0;//Sette olmayan bir eleman durumu

    }
    public void clear(){

            if(lenght == 0) System.out.println("!!! Set zaten boş.");//boş set'i clear lama durumu
            //Set in verilerini sıfırlıyoruz
            data = null;
            lenght = 0;
            capacity = 0;
    }

    public int count(final E parametre){
            for(int i = 0;i<lenght;i++){
                    if(data[i].equals(parametre))
                            return 1;//aranan eleman Sette varsa direk bir return ediyorum çünkü birden fazla olamaz.
            }
            return 0;//Sette olmama durumu.			
    }

    public GTUIterator<E> find(final E parametre){

            GTUIterator<E> t= new GTUIterator<E>();
            for(int i = 0;i<lenght;i++){
                    if(data[i].equals(parametre)){//aranan eleman sette varsa bilgileri iteratör e aktarılıp iter return edilir
                            t.setCurrent((E)data[i]);
                            t.setIndex(i);
                            return t;
                    }
            }
            t=this.end();// aranan keyde eleman yoksa c++ standartta end return ettiği burada da öyle yapıyorum
            return t;
    }
    private boolean findElement(final E parametre){// Interseciton için yardımcı fonksiyon

            for(int i = 0;i<lenght;i++){// Aranan eleman sette true return ediyor
                    if(data[i].equals(parametre)){					
                            return true;
                    }
            }
            return false;
    }
    public GTUIterator<E> begin(){//set in ilk elemanın bilgileri iteratör e geçirilip return ediliyor
            GTUIterator<E> t = new GTUIterator<E>();
            t.setCurrent((E)data[0]);
            t.setIndex(0);
            return t;
    }
    public GTUIterator<E> end(){// Set in son elemanından sonraki yani length'inci elemanı return ediyor
            GTUIterator<E> t= new GTUIterator<E>();
            t.setCurrent((E)data[lenght]);
            t.setIndex(lenght);
            return t;
    }

    public class GTUIterator<E> implements GTUIteratorInt<E>{

        private E current;// 
        private int index;// gösterdiği elemanın setteki index ini tutuyor

        public GTUIterator(){
                index = 0;
        }
        public boolean hasNext(){//Returns true if this list iterator has more elements when traversing the list in the forward direction.
                return (index <lenght);	
        }
        public boolean hasPrevious(){//Returns true if this list iterator has more elements when traversing the list in the reverse direction.
                return (index > 0);
        }
        public E next(){//Returns the next element in the list and advances the cursor position.
                index++;
                current = (E)data[index-1]; //kendini return edip index ini sonraki elemana kaydırıyor.
                return current;
        }
        public E previous(){//Returns the previous element in the list and moves the cursor position backwards.
                index--;
                current = (E)data[index]; 
                return current;		
        }
        public E getCurrent(){
                return current;
        }
        public void setCurrent(E newc){
                current = newc;
        }
        public void setIndex(int newIndex){
                index = newIndex;
        }
        public int getIndex(){
                return index;
        }
    }
}
