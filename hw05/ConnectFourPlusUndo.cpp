#include "ConnectFourPlusUndo.h"


namespace CSE241_151044026{

	int ConnectFourPlusUndo::playGame(){
  
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
	    usedCells = new char[col*row];
		
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
	            if(((adres[0]=='L' && adres[1]=='O' && adres[2]=='A' && adres[3]=='D') || 
	            	(adres[0]=='S' && adres[1]=='A' && adres[2]=='V' && adres[3]=='E'))&& adres[4]==' '){
	            													// load veya save komutu girildiği zaman dosyanın ismini çıkarıp gerekli fonksiyonları çağıran kısım			    
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
	            if(adres[0]=='U' && adres[1]=='N' && adres[2]=='D' && adres[3]=='O' && adres.size()==4){

	            	if(usedCellCount==0){ i--; cerr<<" ! All the cells of the board are already empty"<<endl; continue;}
	            	int sayi;
	            	int k,l,m;
				    for (k=0,l=65,m=97;k<25;k++,l++,m++){
				    	if((usedCells[usedCellCount-1]==(char)l || usedCells[usedCellCount-1]==(char)m)){
				    		sayi=k;
				    	}
				    }
				    usedCellCount--;
				    settercolPosUndo(sayi);
				    gameCells[colPositions[sayi]][sayi].setterType('.');
	            	current_print();
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
	        int statu;
	    	if(play_user(hedef,i)==1){ // Play computer fonksiyonun belilediği hedefe oynama işini de play_user() fonksiyonu gerçekleştiriyor
		        
		        usedCells[usedCellCount]=hedef[0];
		        usedCellCount++; 
	    		statu=endgame();// class tipine göre override edilmiş endgame() fonksiyonu ile bitme durumunun sağlanıp sağlanmadığını kontrol ediyorum
	    		
	    		if((statu==1 )&& gameType=='P')cout<<"\n\n--- CONGRULATİONS -P1- Win The Game ---\n";// bitme mesajları
				else if((statu==2 )&& gameType=='P')cout<<"\n\n--- CONGRULATİONS -P2- Win The Game ---\n";
				else if((statu==2 )&& gameType=='C' && i%2==0)cout<<"\n\n--- COMPUTER- Win The Game ---\n";
				else if((statu==2 )&& gameType=='C' && i%2==1)cout<<"\n\n--- CONGRULATİONS -YOU- Win The Game ---\n";																									
		       
		        current_print();
		        if(map_statu()==1 || statu !=0 ) exit(1);//oyunun bitme durumları	    	
		    }   
		}
		delete [] usedCells;
	return 0;
	}

    bool ConnectFourPlusUndo::read_file(const string & filename,int &i){
		
		ifstream okuma(filename);
	    if(okuma.is_open()){
	        int num;
	        for(int i=0;i<col;i++){ //  hali hazırda kullandığım yerleri free ediyorum
				delete [] gameCells[i];
			}
			delete [] gameCells;
			delete [] colPositions;
			delete [] usedCells;

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
			char tempchar;
			okuma>>usedCellCount;
			usedCells= new char[row*col];
			for(auto a=0;a<usedCellCount;a++){
				okuma>>tempchar;
				usedCells[a]=tempchar;
			}
			current_print();			
	        okuma.close();
	   
	        return true;
	    }
	    else cerr<<"!!!Invalid filename"; // olmayan dosyayı load etmeye çalışma durumu.
     	    return false;
    }
    void ConnectFourPlusUndo::write_file(const string & filename,int i)const{

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
		    yazma<<usedCellCount<<endl;
		    for(auto a=0;a<usedCellCount;a++)yazma<<usedCells[a]<<' ';	    
		}	
    }
}