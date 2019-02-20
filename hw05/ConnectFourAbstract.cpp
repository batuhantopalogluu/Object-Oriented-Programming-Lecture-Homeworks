#include <iostream>
#include <fstream>

#include "ConnectFourAbstract.h"

using namespace std;

namespace CSE241_151044026
{
	
	ConnectFourAbstract::ConnectFourAbstract(int rowValue,int colValue):row(rowValue),col(colValue),gameType('P'){
	
		resize(); // row col a göre gamecell e yer alıyorum
		for(int i=0;i<col;i++){ // cell lerin içlerine konum bilgilerini atıyorum
			for(int j=0;j<row;j++){
				gameCells[i][j].setterRow(j);
				gameCells[i][j].setterPosition(tochar(i));
			}
		}	
	}
	ConnectFourAbstract::ConnectFourAbstract(const ConnectFourAbstract & copy){
		row=copy.row;
		col=copy.col;
		colPositions= new int[row];
		
		for(int i=0;i<row;i++)colPositions[i]=copy.colPositions[i];
			
		resize();
		for(int i=0;i<col;i++){
			for (int j=0;i<row;j++){
				gameCells[i][j]=copy.gameCells[i][j];
			}
		}
	}

	ConnectFourAbstract::~ConnectFourAbstract(){
		
		for(int i=0;i<col;i++){
			delete[] gameCells[i];	
		}	
		delete [] gameCells;
		delete [] colPositions;
		
	}

	int ConnectFourAbstract::play_user(const char hedef[],int & i){

		char atanacak;
		if(i%2==1)
	        atanacak='X';
	    if(i%2==0)
	        atanacak='O';
		int sayi;
	    // harfe göre sütün  seçiyorum
	    int k,l,m,n=1;
	    for (k=0,l=65,m=97;k<25;k++,l++,m++){
	    	if((hedef[0]==(char)l || hedef[0]==(char)m) && row>k){
	    		sayi=k;
	    		n=0;
	    	}
	    }
	    if(n==1){ // hatalı hedef durumunda dögüyü bir tur geri alıyorum ki user değiştirmeden aynı kişiden tekrar hedef alsın
	        i--;
	        cerr<<"!!! Illegal target Please try again\n";
	        return 0;
	    }
	    if(gettercolPos(sayi)==-1){ //dolmuş sütuna erişmek istenildiğinde çalışan kısım
	        i--; 
	        cerr<<"This Column is FUll"<<endl;
	        return 0;
	    }
	    gameCells[colPositions[sayi]][sayi].setterType(atanacak); // mape üzerinde ki doğru konuma user a göre atama yapıyorum          	
	    settercolPos(sayi); // sutünlardaki konumu tutan arrayde atama yaptığım sütun için konumumu bir üst cell e kaydırıyorum
	    return 1;
	}
	int ConnectFourAbstract::playGame(){       // biraz uzun bir fonksiyon ancak içeride yapılması gereken işlemler sabit olduğu daha fazla kısaltamadım         

		string arrRow,arrCol;
		int condition=1;   /// int beklerken girilen hatalı tipleri kontrol ediyorum. ROW veya COL değerlirinin 4 ten küçük olmasını HATALI durum olarak saydım
	    while(condition==1){
	    	cout<<"En giriniz: ";
			cin>>arrRow;
			if(numberCheck(arrRow,'R')==-1) condition=-1;
			else cerr<<"hatalı Row girişi"<<endl;
		}
		condition=1;
		while(condition==1){
	    	cout<<"Boy giriniz: ";
			cin>>arrCol;
			if(numberCheck(arrCol,'C')==-1) condition=-1;
			else cerr<<"hatalı Col girişi"<<endl;
		}	
		resize();
		colPositions = new int[row];
	 
	    for(auto a = 0;a<row;a++){
			colPositions[a]=col-1;
		}
			  
		cout<<"P-player | C-computer: ";
	    char gametype[10];

	    int c=1;    // rakam veya birden fazla harf rakam konbinasyonun hatalı olarak girilmesi durumlarunı kontrol ediyorum
	    while(c==1){// hatalı oyun tipinde tekrar tekrar input almak için burayı bir loop a soktum
	        cin>>gametype;
	        switch(gametype[0]){	                     
	            case 'c':/*oyun tipine göre diğer fonksiyonları çağırıyorum*/
	            case 'C':
	                c=0;
	                gameType='C';
	                break;
	            case 'p':
	            case 'P':
	                c=0;
	                gameType='P';
	                break;

	            default:
	                cerr<<"!!!FALSE GAME TYPE PLEASE TRY AGAIN!!!\n";
	                break;
	        }
	    }	

	    current_print();
	    char hedef[50];
		string adres;
	    char filename[50];
	    int firstcheck=0;

		for(int i=1;i!=-1;i++){
			
			int size=0;
			int statu4 =1;
	        for(auto h=0;h<50;h++)filename[h]='\0';{}
			for(auto h=0;h<50;h++)hedef[h]='\0';{}

			if(i%2==1 && gameType == 'P') cout<<"P1: ";
	        if(i%2==0 && gameType == 'P') cout<<"P2: ";
	        if(i%2==1 && gameType == 'C') cout<<"It's Your Turn\n";		
			
			if (i == 1 && firstcheck==0){
	            getline(cin, adres);
	            firstcheck=1;
	        }
	        if (gameType == 'P' || (gameType =='C' && i%2==1)){        	
	        	
	        	getline(cin, adres);            
	            cout<<adres<<endl;
	            if(adres.size()==0){ // inputları dosyadan alırken oyun bitme koşuluna ulaşmadan inputlar biterse direk programdan çıktığımız için hafızayı boşaltma işini kendim yapıyorum
	            	for(int i=0;i<col;i++){
						delete[] gameCells[i];	
					}	
					delete [] gameCells;
					delete [] colPositions;
					
				   	exit(1);
	            }
	            
	            hedef[0]=adres[0];           
	            if(((adres[0]=='L' && adres[1]=='O' && adres[2]=='A' && adres[3]=='D') || (adres[0]=='S' && adres[1]=='A' && adres[2]=='V' && adres[3]=='E'))&& adres[4]==' '){ // load veya save yapılmak istenilme durumu
				    for (auto a =4 ;a<50;a++){
	            	    if(adres[a]==' ') {
							for(auto b=a+1;adres[b]!='\0';b++){
	                            filename[size]=adres[b];
	                            size++;
	                        }
	                        break;
	                    }  
	                }
	                if(adres[0]=='L') read_file(filename,i); //load
	                
	                if(adres[0]=='S') write_file(filename,i); //save
	             
	                for(auto h=0;h<50;h++)hedef[h]='\0';
	                i--; // load veya save yapınca kullanıcının hamlesi geçmemesi için
	                continue;
	            }

	            if(adres[1]!='\0'){
	                i--;
	                cerr<<"!!! false target try again\n";
	                continue;
	      		}
	        }
			else if (gameType =='C' && i%2==0){
	         	hedef[0]=play_computer();
	        }
	        int statuVH;
	    	if(play_user(hedef,i)==1){
		        
	    		statuVH=endgame();
	    	
	    		if((statuVH==1 )&& gameType=='P')cout<<"\n\n--- CONGRULATİONS -P1- Win The Game ---\n";// bitme mesajları
				else if((statuVH==2 )&& gameType=='P')cout<<"\n\n--- CONGRULATİONS -P2- Win The Game ---\n";
				else if((statuVH==2 )&& gameType=='C' && i%2==0)cout<<"\n\n--- COMPUTER- Win The Game ---\n";
				else if((statuVH==2 )&& gameType=='C' && i%2==1)cout<<"\n\n--- CONGRULATİONS -YOU- Win The Game ---\n";																									
		       
		        current_print();
	       
		        if(map_statu()==1 || statuVH !=0 ) exit(1);//oyunun bitme durumları
		    }   
		}
		return 0;
	}
	bool ConnectFourAbstract::read_file(const string & filename,int &i){

		ifstream okuma(filename);
	    
	    if(okuma.is_open()){
	        int num;
	        for(int i=0;i<col;i++){ //  hali hazırda kullandığım yerleri free ediyorum
				delete [] gameCells[i];
			}
			delete [] gameCells;
			delete [] colPositions;
		
	        okuma>>gameType;
			okuma>>row;
			okuma>>col;
			okuma>>i; // sıranın kimde olduğunu tutan değişken
			string rubbish;
			
			getline(okuma,rubbish);// bir satir boşluk oluyor okurken onu engellemek için çöp bir line okuyorum
			resize(); // load edilen dosyanın boyutlarına göre gamecell e yer alıyorum
		    string satir;
		    int a=0;
		    do{
		    	getline(okuma,satir);
		    	if(a==col) break;

		    	for(int j=0;j<satir.size();j++){
		    		gameCells[a][j]=satir[j];
		    		gameCells[a][j].setterRow(j);
					gameCells[a][j].setterPosition(tochar(a));
		    	}
		    	a++;
		    }while(a<col);
		    int tempint;
			
			colPositions = new int[row]; // bir mape te ki sütunlarda yıldızlara göre konumumu tutan dizi
			for(auto a=0;a<row;a++){
				okuma>>tempint;
				colPositions[a]=tempint;
			}
			cout<<endl;
			
			current_print();			
	        okuma.close();
	   
	        return true;
	    }
	    else cerr<<"!!!Invalid filename"; // olmayan dosyayı load etmeye çalışma durumu.
		    return false;
	}
	void ConnectFourAbstract::write_file(const string  & filename,int i)const{

		ofstream yazma(filename);
	    if(yazma.is_open()){
		    yazma<<gameType<<endl;	    
		    yazma<<row<<endl;
		    yazma<<col<<endl;
		    yazma<<i<<endl;
		    for(auto a=0;a<col;a++){
				for(auto b=0;b<row;b++){
					yazma<<gameCells[a][b].getterType();
				}
				yazma<<'\n';
			}
		    for(auto a=0;a<row;a++)yazma<<colPositions[a]<<' ';	    
		}	
	}
	void ConnectFourAbstract::current_print() const{

		int k,l;
		cout<<endl;
		for (k=0,l=65;k<row;k++,l++) cout<<(char)l;
		cout<<endl;
		for(auto a = 0;a<col;a++){
			for(auto b=0;b<row;b++){
				cout<<gameCells[a][b].getterType();		
			}
			cout<<endl;
		}	
	}
	WH ConnectFourAbstract::currentWH(){
		WH rowcol;

		rowcol.Srow=row;
		rowcol.Scol=col;

		return rowcol;
	}
	char ConnectFourAbstract::tochar(int a)const { // int sütün değerini karakter hedef e çeviriyorum
		int i;
		char temp;
	    for(temp=97,i=0;i<row;temp++,i++){
	        if(a==i) return temp;
	    }
	    return '\0';	
	}
	void ConnectFourAbstract::resize(){

		gameCells = new Cell*[col];
		for(int i=0;i<col;i++){
			gameCells[i]=new Cell[row];
		}
		for(int i=0;i<col;i++){
			for(int j=0;j<row;j++){
				gameCells[i][j].setterRow(j);
				gameCells[i][j].setterPosition(tochar(i));
			}
		}	
	}

	int ConnectFourAbstract::map_statu()const{

		int Count=0,i,j;
		for(i=0;i<col;i++){
	        for(j=0;j<row;j++){
	            if(gameCells[i][j].getterType()=='X'|| gameCells[i][j].getterType()=='O'){     
	            	Count++;      
	            }
	        }
	    }
	    
	    if(Count==row*col){cerr<<"--- MAPE IS FULL GAME FINISHED ---\n";return 1;}  // mape in dolma durumu
		return 0;
	}

	int ConnectFourAbstract::numberCheck(string & size,char rowOrCol){
		int j;
		int olacak=0;
		int basamak=1;
		for(j=0;size[j]!='\0';j++){}
		
		for(int i=j-1;i>=0;i--){
			if(size[i]>=48 && size[i]<=57){
				size[i]-='0';
				olacak+=(int)size[i]*basamak;
				basamak*=10;
			}
			else return -2;
		}
		if((rowOrCol=='R' || rowOrCol=='C') && olacak<4) return -2;
		if(rowOrCol=='R')col=olacak;
		if(rowOrCol=='C')row=olacak;
		if(rowOrCol=='T') return olacak;
	 	return -1;
	}

	const ConnectFourAbstract& ConnectFourAbstract::operator=(const ConnectFourAbstract& other){
		for(int i=0;i<col;i++){
			delete [] gameCells[i];
		}
		delete [] gameCells;
		
		row =other.row;
		col=other.col;
		
		gameCells = new Cell*[col];

		for(int i=0;i<col;i++){
			gameCells[i]= new Cell[row];
			for(int j=0;j<row;j++){
				gameCells[i][j]=other.gameCells[i][j];
			}
		}
		return *this;
	}

}