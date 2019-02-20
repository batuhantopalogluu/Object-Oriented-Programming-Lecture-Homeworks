package pkg151044026;

// Batuhan TOPALOĞLU 151044026 CSE241
import javafx.util.Pair;
import java.security.InvalidParameterException;
public class driver
{
	public static void main(String[] args) 
	{
		try
		{
		System.out.println("\n---SET---");
		GTUSet<Integer> a = new GTUSet<Integer>();		
		System.out.printf("\nInteger bir Set oluşturuyorum şuan empty() durumu : %s \n",a.empty());
		System.out.println("Integer bir Set oluşturup '1','2','3','4' elemanlarını ekliyorum");
		
		a.insert(1);
		a.insert(2);
		a.insert(3);
		a.insert(4);

		GTUSet<Integer>.GTUIterator<Integer> iterS1 = a.begin();
		System.out.printf("Sondan başa doğru iteratörle elemanları bastırıyorum   ");
		while(iterS1.hasNext()){
			System.out.printf("//  %s  //",iterS1.next());			
		}
		System.out.println("");
		iterS1=a.find(4);
		System.out.printf("a.find(4) yaparak onu gösteren iteratör oluşturuyorum : %s",iterS1.next());
		System.out.printf("\na.size() : %d \n",a.size());

		a.erase(4);
		a.erase(1);

		System.out.printf("'1've'4' ü siliyorum yeni ");
		System.out.printf("size : %d \n",a.size());
		System.out.printf(" a.count(4) = %d  // a.count(2) = %d \n",a.count(4),a.count(2));

		a.clear();
		System.out.printf("a.clear() çağrıldıktan sonraki size : %d \n",a.size());
		
		//******************************************************************************INTERSECTION
		System.out.println("\n--intersection--\n");
		GTUSet<Integer> b = new GTUSet<Integer>();
		GTUSet<Integer> c = new GTUSet<Integer>();
		GTUSet<Integer> d = new GTUSet<Integer>();
		
		b.insert(2);
		b.insert(4);
		b.insert(6);
		b.insert(8);

		iterS1=b.begin();
		System.out.printf("'b' Set'inin elemanları : ");
		while(iterS1.hasNext()){
			System.out.printf("//  %s  //",iterS1.next());			
		}
		c.insert(6);
		c.insert(8);
		c.insert(10);
		c.insert(12);
		
		System.out.println("");
		iterS1=c.begin();
		System.out.printf("'c' Set'inin elemanları : ");
		while(iterS1.hasNext()){
			System.out.printf("//  %s  //",iterS1.next());			
		}
		d=(GTUSet)b.intersection(c);
		System.out.printf("\n\nd = (GTUSet)b.intersection(c) işleminin sonucu 'd' : ");

		iterS1=d.begin();
		while(iterS1.hasNext()){
			System.out.printf("//  %s  //",iterS1.next());			
		}
		System.out.printf("\nd.size() : %d \n\n",d.size());
		//*******************************************************************************MAPE
		System.out.println("---Map---\n");
		
		GTUMap<Integer, Integer> map1 = new GTUMap<Integer, Integer>();
		Pair p = new Pair<Integer, Integer>(1,18);
		Pair m = new Pair<Integer, Integer>(2,4);
		Pair l = new Pair<Integer, Integer>(3,97);
		Pair i = new Pair<Integer, Integer>(4,23);
		map1.insert(p);
		map1.insert(m);
		map1.insert(l);
		map1.insert(i);
		System.out.printf("Pair p = new Pair<Integer, Integer>(1,18)\n"
						   +"Pair m = new Pair<Integer, Integer>(2,04)\n"
						   +"Pair l = new Pair<Integer, Integer>(3,97)\n"
						   +"Pair i = new Pair<Integer, Integer>(4,23)\n"
						   +"map1.insert(p)\n"
						   +"map1.insert(m)\n"
						   +"map1.insert(l)\n"
						   +"map1.insert(i)\n"
						   +"İşlemlerinin sonucu Map'i iteratörler yazdıralım : ");
		GTUMap<Integer,Integer>.GTUIterator<javafx.util.Pair<Integer,Integer>> iter0 = map1.begin();
		while(iter0.hasNext()){
			System.out.printf("//  %s  //",iter0.next());	
		}
		System.out.printf("\nmap1.size() : %d\n",map1.size());
		map1.erase(p);
		map1.erase(i);
		System.out.printf("\nmap1.erase(p)\n"
						  +"map1.erase(i)\n"
						  +"İşlemlerinin sonucu Map'in yeni hali : ");
		iter0 = map1.begin();
		while(iter0.hasNext()){
			System.out.printf("//  %s  //",iter0.next());	
		}
		System.out.printf("\nmap1.size() : %d\n",map1.size());
		System.out.printf("map1.find(l) : %s\n",(map1.find(l)).next());
		System.out.printf("map1.count(m) : %d\n"
						 +"map1.count(p) : %d\n",map1.count(m),map1.count(p));
		
		System.out.printf("map1.at(2) : %s\n",map1.at(2));

		map1.clear();
		System.out.printf("map1.clear() sonrası map1.size() : %d\n",map1.size());
		
		GTUMap<Integer, Integer> map2 = new GTUMap<Integer, Integer>();

		Pair mapp11 = new Pair<Integer, Integer>(1,1048);
		Pair mapp12 = new Pair<Integer, Integer>(2,1071);
		Pair mapp13 = new Pair<Integer, Integer>(3,1923);
		Pair mapp14 = new Pair<Integer, Integer>(4,2023);

		map2.insert(mapp11);
		map2.insert(mapp12);
		map2.insert(mapp13);
		map2.insert(mapp14);

		System.out.printf("\nPair mapp11 = new Pair<Integer, Integer>(1,1048)\n"
						 +"Pair mapp12 = new Pair<Integer, Integer>(2,1071)\n"
						 +"Pair mapp13 = new Pair<Integer, Integer>(3,1923)\n"
						 +"Pair mapp14 = new Pair<Integer, Integer>(4,2023)\n"

						 +"map2.insert(mapp11)\n"
					     +"map2.insert(mapp12)\n"
						 +"map2.insert(mapp13)\n"
						 +"map2.insert(mapp14)\n"
						 +"İşlemlerinin ardından map2 : ");
		
		iter0 = map2.begin();
		while(iter0.hasNext()){
			System.out.printf("//  %s  //",iter0.next());	
		}
		System.out.println("");

		GTUMap<Integer, Integer> map3 = new GTUMap<Integer, Integer>();

		Pair mapp21 = new Pair<Integer, Integer>(1,1000);
		Pair mapp22 = new Pair<Integer, Integer>(2,1001);
		Pair mapp23 = new Pair<Integer, Integer>(3,1923);
		Pair mapp24 = new Pair<Integer, Integer>(4,2023);

		map3.insert(mapp21);
		map3.insert(mapp22);
		map3.insert(mapp23);
		map3.insert(mapp24);

		System.out.printf("\nPair mapp21 = new Pair<Integer, Integer>(1,1000)\n"
						 +"Pair mapp22 = new Pair<Integer, Integer>(2,1001)\n"
						 +"Pair mapp23 = new Pair<Integer, Integer>(3,1923)\n"
						 +"Pair mapp24 = new Pair<Integer, Integer>(4,2023)\n"

						 +"map3.insert(mapp21)\n"
                                                 +"map3.insert(mapp22)\n"
						 +"map3.insert(mapp23)\n"
						 +"map3.insert(mapp24)\n"
						 +"İşlemlerinin ardından map3 : ");
		iter0 = map3.begin();
		while(iter0.hasNext()){
			System.out.printf("//  %s  //",iter0.next());	
		}
		System.out.println("");
                
		GTUMap<Integer, Integer> map4 = new GTUMap<Integer, Integer>();

		map4 = map2.intersection(map3);
		System.out.printf("map4 = map2.intersection(map3) işleminin ardından map4 : ");
		iter0 = map4.begin();
		while(iter0.hasNext()){
			System.out.printf("//  %s  //",iter0.next());	
		}
                System.out.println("");
		}
		catch(InvalidParameterException e)
		{
			System.out.printf("%s\n",e.getMessage());
		}
	}
}