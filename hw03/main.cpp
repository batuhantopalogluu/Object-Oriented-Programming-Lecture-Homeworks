/*  Batuhan TOPALOĞLU 151044026 HW3  */

#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

class connectFour
{
	public:
        connectFour();
	 	connectFour(int rowValue,int colValue);
		connectFour(int rowValue,int colValue, int gameTypeValue,int gameTodeValue);

		bool read_file(const string filename,int &i);
		void write_file(const string filename,int i);

		int current_wh();  		//current width and height of the board

		void current_print()const; //displays the current board

		void resize();
	    char play_computer();    //The class will have two functions named play that plays the game for a single time step. First
												//function does not take a parameter and it plays the computer. The second function takes a cell
	    int play_user(char hedef[],int &i);   //position and it plays the user.
	    int playGame(char gamemode);/*This function plays the game by asking the user the board size first then asks the user to play and the computer plays, etc.*/

	    int map_statu() const; // bitme koşullarının sağlanıp sağlanmadığını kontrol eden fonksiyonlar
	    int verticalhorizontal(); //
	    int diagonal(); //

	   
		void smal_character(int x,int y); // oyunun bitme koşulunu sağlayan cell i küçük karaktere çeviren fonksiyon.Cell in koordinatlarını parametre alır
		int numberCheck(string size,char rowOrCol);//alınan inputun rakamlar oluşup oluşmadığını kontrol eden fonksiyon

	    int suggestorH(char xo); // yatay dikey veya çapraz olarak aynı tipte cell countları tutan fonksiyonlar .Count u sayılacak tipi parametre olarak alıyor
	    int suggestorV(char xo); // 
	    int suggestorD(char xo); // 

	    char getterGameType(){return gameType;}
		inline int gettercolPos(int hedef){return colPositions[hedef];}
		inline void settercolPo(int h){colPositions[h]--;}
		inline static int num_livingCell(){livingcell++;}     /*returns the number of living cells in all the games. Be careful here because there could be more than one game active at the same time.*/
	    inline static int getterLivinCell(){return livingcell;}
	    inline static int setterLivingCell(int numliv){livingcell=numliv;}
	    inline  int setterGameStatu(int temp){gamestatu=temp;}
	    inline int ggeGameStatu()const{return gamestatu;}
	   
   
		int multigamesize;
	private:
		class Cell
		{
			public:
				Cell();		
				
				inline void setterType(char setterT){type=setterT;};
				inline void setterPosition(char setterP){position=setterP;};
				inline void setterRow(int setterR){Crow=setterR;};
				inline int getterRow() const { return Crow;}
				inline char getterPosition() const { return position;}
				inline char getterType() const { return type;}
				
			private:
				char position;//A ,B ,c
				int Crow; //1 , 2 , 3
				char type;/* 'O' || 'X' ||'.' */

		};
		int row;
		int col;
		char gameType;
		char gameMode;
		
		vector<int> colPositions;

		int gamestatu; // Multi modda playgame fonksiyonu her çağrıldığında yeniden size sormasın diye tuttuğum bir değişken
		static int livingcell;
		vector<vector<Cell>> gameCells;
		
};
int biggerPossib(char xo,vector<connectFour> v,const int t);
/**************************************************************************************************************************/
connectFour::connectFour(): row(4),col(4),gameType('P'),gameMode('M'){}
connectFour::connectFour(int rowValue,int colValue): gameType('P'),gameMode('M'){
	row=rowValue;  col=colValue;
}
connectFour::connectFour(int rowValue,int colValue, int gameTypeValue,int gameTodeValue){
	row=rowValue;  col=colValue;  gameType=gameTypeValue;  gameMode=gameTodeValue;
}
connectFour::Cell::Cell():position('A'),Crow(1),type('.'){} 			
int connectFour::livingcell = 0;


/**********************************************************************************************************************/
int main(int argc, char const *argv[]){

    cout<<"________________ ConnectFour ____________________"<<endl;
    char gamemode[10];
    int c=1;    
    connectFour single;
    vector<connectFour> multi;
    vector<int> bitenoyunlar;
    connectFour tempI;
    string arrTempi;//classın içindeki number check fonksiyonuma erişmek için temp bir obje oluşturuyorum
    string Tobjectnumber;
    while(c==1){
       
        cout<<"OYUN MODUNU SEÇİNİZ"<<endl<<"'S'-SINGLE GAME "<<"\t"<<"'M'-MULTI GAME\n" ;
        cin>>gamemode;
        if(gamemode[1]!='\0') gamemode[0]='x';
        
        switch(gamemode[0]){
        
            case 's':
            case 'S': 
                
                single.playGame('S');
                c=0;
                break;
            case 'm':
            case 'M':       
                    /*MULTİ modda single bir oyun load edilirse yüklenen oyun single modda bitene kadar oynanır ardından multi modda devam edilir*/           		
               		int tempi;
               		int condition;
               		condition=1;
               		
               		while(condition==1){  // int beklerken hatalı inputları kontrol ediyorum
				    	cout<<"kaç oyun oynamak istiyorsunuz ?:";
						cin>>arrTempi;
						if(tempI.numberCheck(arrTempi,'T')!=-2) condition=-1;
						else cerr<<"! hatalı giriş"<<endl;
					}
               		tempi=tempI.numberCheck(arrTempi,'T');															
					for (int i = 0; i < tempi;i++){
						multi.push_back(connectFour());
					}
					for(int i=0;i<tempi;i++){
						multi[i].setterGameStatu(0);
						multi[i].multigamesize=tempi;						
					}
					for(int i=0;i<tempi;i++){
						cout<<"obje"<<i+1<<":"<<endl;
						multi[i].playGame('M');	
					}
					int objectnumber;
					int h;
					h=0;
					int a;
					a=0;
					while(h!=tempi){
						int z=0;
						if(a!=0)cout<<"livingcell:"<<multi[0].getterLivinCell()<<endl;
						int suggest=0;
			    		if(a!=0){				    		
				    		suggest=biggerPossib('X',multi,tempi);
				    		cout<<"P1 için önerilen obje :"<<suggest+1<<endl;
					    		
				    		suggest=biggerPossib('O',multi,tempi);
				    		cout<<"P2 için önerilen obje :"<<suggest+1<<endl;
				    	}
			    				    		
						cout<<"Obje seçiniz: ";
						while(z==0 ){
							condition=1;               		
							
							while(condition==1){ //input için tip kontrolü yapıyorum
							   	cin>>Tobjectnumber;	
								if(tempI.numberCheck(Tobjectnumber,'T')!=-2) condition=-1;
								else cerr<<"! hatalı giriş"<<endl;
							}
							objectnumber=tempI.numberCheck(Tobjectnumber,'T');
						
							for(int i=0;i<bitenoyunlar.size();i++){ //multi modda biten objeleri daha sonra onlara ulaşılmak istenildiğinde bunu engellemek için bir vectorde tutuyorum.
								if(bitenoyunlar[i]==objectnumber){
									cerr<<" - "<<objectnumber<<" - numaralı oyun bitmişti."<<endl;
									objectnumber=-1;
								}
							}
							if((objectnumber>tempi) || (objectnumber<=0)){cout<<"! Hatalı obje numarası"<<endl;cout<<"Obje seçiniz: ";}
							else z=1;
						}						
						if(multi[objectnumber-1].playGame('M')==1){
							h++;
							cout<<" - "<<objectnumber<<" - numaralı oyun bitti"<<endl;
							bitenoyunlar.push_back(objectnumber);							
						}
						a++;						
					}										
					c=0;  

                break;
            default:
                cerr<<"!!!FALSE GAME MODE PLEASE TRY AGAIN!!!\n";
                break;
        }   
    }
	return 0;
}

int connectFour::playGame(char gamemode){                

	gameMode=gamemode;
	string arrRow,arrCol;
	int condition=1;   /// int beklerken girilen hatalı tipleri kontrol ediyorum. ROW veya COL değerlirinin 4 ten küçük olmasını HATALI durum olarak saydım
	if(gameMode=='S' || (gameMode=='M' && ggeGameStatu()==0)){ 
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
		cout<<"P-player | C-computer: ";
	    char gametype[10];
	   
	    int c=1;    // rakam veya birden fazla harf rakam konbinasyonun hatalı olarak girilmesi durumlarunı kontrol ediyorum
	    while(c==1){// hatalı oyun tipinde tekrar tekrar input almak için burayı bir loop a soktum
	        cin>>gametype;
	        if(gametype[1]!='\0') gametype[0]='x';
	        switch(gametype[0]){
	            /*oyun tipine göre diğer fonksiyonları çağırıyorum*/
	            case 'c':
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
		resize();//GİRİLEN boyutlara göre vectöre yer açıyorum
	    current_wh();
	    if (gameMode=='M' && ggeGameStatu()==0){
	    	setterGameStatu(1);
	    	return 0;
		}
	}
    current_print();
    
    for(auto i=0;i<row;i++){
		colPositions.push_back(col-1);
	}
	char hedef[50];
	string adres;
    char filename[50];
    int firstcheck=0;

	for(int i=1;((gameMode=='S' && i!=-1) || (gameMode=='M' && i<3));i++){
		
		int size=0;
		int statu4 =1;
        for(auto h=0;h<50;h++)filename[h]='\0';{}
		for(auto h=0;h<50;h++)hedef[h]='\0';{}

		if(i!=1 && i%2==1)cout<<"livingcell:"<<getterLivinCell()<<endl;
		if(i%2==1 && gameType == 'P') cout<<"P1: ";
        if(i%2==0 && gameType == 'P') cout<<"P2: ";
        if(i%2==1 && gameType == 'C') cout<<"It's Your Turn\n";
		
		if (i == 1 && firstcheck==0){
            getline(cin, adres);
            firstcheck=1;
        }
        if (gameType == 'P' || (gameType =='C' && i%2==1)){
        	
        	getline(cin, adres);
            hedef[0]=adres[0];

            if((adres[0]=='L' && adres[1]=='O' && adres[2]=='A' && adres[3]=='D') || (adres[0]=='S' && adres[1]=='A' && adres[2]=='V' && adres[3]=='E')){
			    for (auto a =4 ;a<50;a++){
            	    if(adres[a]==' ') {
						for(auto b=a+1;adres[b]!='\0';b++){
                            filename[size]=adres[b];
                            size++;
                        }
                        break;
                    }  
                }
                if(adres[0]=='L'){
                   	 read_file(filename,i);
                }
                if(adres[0]=='S'){
             	   	write_file(filename,i);
                }
                for(auto h=0;h<50;h++)hedef[h]='\0';{}
                i--;
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
        
        int statuVH,statuD;
    	if(play_user(hedef,i)==1){
	        num_livingCell();
    		statuVH=verticalhorizontal();
    		statuD=diagonal();
    		
    		if((statuVH==1 || statuD ==1)&& gameType=='P')cout<<"\n\n--- CONGRULATİONS -P1- Win The Game ---\n";
			else if((statuVH==2 || statuD ==2)&& gameType=='P')cout<<"\n\n--- CONGRULATİONS -P2- Win The Game ---\n";
			else if((statuVH==2 || statuD ==2)&& gameType=='C' && i%2==0)cout<<"\n\n--- COMPUTER- Win The Game ---\n";
			else if((statuVH==2 || statuD ==2)&& gameType=='C' && i%2==1)cout<<"\n\n--- CONGRULATİONS -YOU- Win The Game ---\n";																									
	        
	        current_print();
	        if(map_statu()==1 || statuVH !=0 || statuD !=0){//oyunun bitme durumları
	        	
	        	return 1;
	        }
	    }
	    else continue;   
	 }
	 return 0;
}


int connectFour::play_user(char hedef[],int & i){

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
    gameCells[colPositions[sayi]][sayi].setterType(atanacak);
    settercolPo(sayi);
 	cout<<"\n\n";
    return 1;
}

void connectFour::current_print()const{

	int k,l;
	for (k=0,l=65;k<row;k++,l++) cout<<(char)l;
	cout<<endl;
	for(auto a = 0;a<col;a++){
		for(auto b=0;b<row;b++){
			cout<<gameCells[a][b].getterType();		
		}
		cout<<endl;
	}
}

void connectFour::resize(){

	for(int a = 0;a<col;a++){
		vector<Cell> temp;
		for (int i = 0; i < row;i++){
			temp.push_back(Cell());
		}
		gameCells.push_back(temp);
	}
}

int connectFour::map_statu()const{

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

bool connectFour::read_file(string filename,int &i){

	ifstream okuma(filename);
    
    if(okuma.is_open()){
        int num;
        okuma>>num;setterLivingCell(num);
        okuma>>gameMode;
        okuma>>gameType;
		okuma>>row;
		okuma>>col;
		okuma>>i;
		vector<vector<Cell>> TempGameCells;/*dosyadan çekilen mape in boyutları mevcut olana oranla büyük olunca sıkıntı çıkmaması için önce bir temp e okuyup onu ana mape'e kopyalıyorum*/
		for(int a = 0;a<col;a++){
			vector<Cell> tempR;
			for (int i = 0; i < row;i++){
				tempR.push_back(Cell());
			}
			TempGameCells.push_back(tempR);
		}
		char temp;
		for(auto a=0;a<col;a++){
			for(auto b=0;b<row;b++){
			  	okuma>>temp;
				TempGameCells[a][b].setterType(temp);
			}
		}
		gameCells=TempGameCells;
		vector<int> tempcolPositions;
		int tempint;
		for(auto a=0;a<row;a++){
			okuma>>tempint;
			tempcolPositions.push_back(tempint);
		}
		colPositions=tempcolPositions;
		current_print();
        okuma.close();
        return true;
    }
    else cerr<<"!!!Invalid filename"; // olmayan dosyayı load etmeye çalışma durumu.
    	return false;
}

void connectFour::write_file(string filename,int i){

	ofstream yazma(filename);
    if(yazma.is_open()){
    	yazma<<livingcell<<endl;
    	yazma<<gameMode<<endl;
	    yazma<<gameType<<endl;	    
	    yazma<<row<<endl;
	    yazma<<col<<endl;
	    yazma<<i<<endl;
	    for(auto a=0;a<col;a++){
			for(auto b=0;b<row;b++){
				yazma<<gameCells[a][b].getterType()<<' ';
			}
			yazma<<'\n';
		}
		for(auto a=0;a<row;a++)yazma<<colPositions[a]<<' ';
	}
}
int connectFour::current_wh(){

	col=gameCells.size();
	row=gameCells[0].size();

return 1;
}
int connectFour::numberCheck(string size,char rowOrCol){
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
	if(rowOrCol=='R')row=olacak;
	if(rowOrCol=='C')col=olacak;
	if(rowOrCol=='T') return olacak;
 	return -1;
}
int connectFour::suggestorD(char xo){
	int i,j,k;
	int counter=0,counter2=0,tempcounter=0;
    for(i=0;i<col;i++){
        for(j=0,k=i;j<row && k<col;j++,k++){
            if(gameCells[k][j].getterType()==xo){
                 tempcounter++;
            }
            else{
            	if(tempcounter>=counter)counter=tempcounter;
            	tempcounter=0;
            }
        }
    }
    tempcounter=0;

    for(j=row-1;j>=0;j--){
    	for(i=0,k=j;i<col && k>=0;i++,k--){
    		if(gameCells[i][k].getterType()==xo){
                 tempcounter++;
            }
            else{
            	if(tempcounter>=counter2)counter2=tempcounter;
            	tempcounter=0;
            }
    	}
    }
    if(counter2>=counter) return counter2;
    else return counter;
}
int connectFour::suggestorH(char xo){

	int i,j;
	int counter=0,tempcounter=0;
    for(i=0;i<col;i++){
        for(j=0;j<row;j++){
            if(gameCells[i][j].getterType()==xo){
                 tempcounter++;
            }
            else{
            	if(tempcounter>=counter)counter=tempcounter;

            	tempcounter=0;
            }
        }
    }
    return counter;
}
int connectFour::suggestorV(char xo){

	int i,j;
	int counter=0,tempcounter=0;
    for(j=0;j<row;j++){
        for(i=0;i<col;i++){
            if(gameCells[i][j].getterType()==xo){
                 tempcounter++;
            }
            else{
            	if(tempcounter>counter) counter=tempcounter;

            	tempcounter=0;
            }
        }
    }
    return counter;
}
int biggerPossib(char xo,vector<connectFour> multi,const int tempi){
	int vx=0,hx=0,dx=0;
	int max=0,tempmax=0;
	int suggestionnumber=-1;
	
	for(int i=0;i<tempi;i++){
		hx=multi[i].suggestorH(xo);
		vx=multi[i].suggestorV(xo);
		dx=multi[i].suggestorD(xo);

		if(hx>=vx){
			if(hx>=dx){										
				tempmax=hx;
			}
			else{					  					
				tempmax=dx;
			}
		}
		else{
			if(vx>=dx){
				tempmax=vx;					    			
			}
			else{
				tempmax=dx;			    		
			}
		}
		if(tempmax>=max){
			max=tempmax;
			suggestionnumber=i;
		}
	}
	return suggestionnumber;
}
int connectFour::verticalhorizontal(){
    
    int i,j;
    for(i=0;i<col;i++){// yatayı tarayan kısım
        for(j=0;j<row;j++){
            if(j+3<row && gameCells[i][j].getterType()=='X'&& gameCells[i][j+1].getterType()=='X' && gameCells[i][j+2].getterType()=='X' && gameCells[i][j+3].getterType()=='X'){     
            	smal_character(i,j);smal_character(i,j+1);smal_character(i,j+2);smal_character(i,j+3);
            	return 1;         
            }
            if(j+3<row && gameCells[i][j].getterType()=='O'&& gameCells[i][j+1].getterType()=='O' && gameCells[i][j+2].getterType()=='O' && gameCells[i][j+3].getterType()=='O'){
            	smal_character(i,j);smal_character(i,j+1);smal_character(i,j+2);smal_character(i,j+3);
            	return 2;
            }
  			//dikey arama
            if(i+3<col && gameCells[i][j].getterType()=='X'&& gameCells[i+1][j].getterType()=='X' && gameCells[i+2][j].getterType()=='X' && gameCells[i+3][j].getterType()=='X'){
                smal_character(i,j);smal_character(i+1,j);smal_character(i+2,j);smal_character(i+3,j);
            	return 1;            	
            }
            if(i+3<col && gameCells[i][j].getterType()=='O'&& gameCells[i+1][j].getterType()=='O' && gameCells[i+2][j].getterType()=='O' && gameCells[i+3][j].getterType()=='O'){
            	smal_character(i,j);smal_character(i+1,j);smal_character(i+2,j);smal_character(i+3,j);
            	return 2;
            }
        }
    }
    return 0;
}

int connectFour::diagonal(){
    int i,j;
    for(i=0;i<col;i++){
        for(j=0;j<row;j++){
            if(i+3<col && j+3<row && gameCells[i][j].getterType()=='X' && gameCells[i+1][j+1].getterType()=='X' && gameCells[i+2][j+2].getterType()=='X' && gameCells[i+3][j+3].getterType()=='X'){ // sağ üsten sağ alta tarama yapan kısım
                smal_character(i,j);smal_character(i+1,j+1);smal_character(i+2,j+2);smal_character(i+3,j+3);
                 return 1;            
            }
            if(i+3<col && j+3<row && gameCells[i][j].getterType()=='O' && gameCells[i+1][j+1].getterType()=='O' && gameCells[i+2][j+2].getterType()=='O' && gameCells[i+3][j+3].getterType()=='O'){
            	smal_character(i,j);smal_character(i+1,j+1);smal_character(i+2,j+2);smal_character(i+3,j+3);
            	return 2;
            }
            if(i+3<col && j-3>=0 && gameCells[i][j].getterType()=='X' && gameCells[i+1][j-1].getterType()=='X' && gameCells[i+2][j-2].getterType()=='X' && gameCells[i+3][j-3].getterType()=='X'){// sağ üstten  sol alta tarama yapan kısım 
                smal_character(i,j);smal_character(i+1,j-1);smal_character(i+2,j-2);smal_character(i+3,j-3);
                return 1;            	
            }
            if(i+3<col && j-3>=0 && gameCells[i][j].getterType()=='O' && gameCells[i+1][j-1].getterType()=='O' && gameCells[i+2][j-2].getterType()=='O' && gameCells[i+3][j-3].getterType()=='O'){
            	smal_character(i,j);smal_character(i+1,j-1);smal_character(i+2,j-2);smal_character(i+3,j-3);
                return 2;
            }
        }
    }
    return 0;
}

void connectFour::smal_character(int x,int y){

    int a=gameCells[x][y].getterType();
	gameCells[x][y].setterType(a+32);

}

char connectFour::play_computer(){
	int i,j,sayi= 0;
    int statu=1,statu2=1; // Uygun ihtimaller sağlandığında ve oynan istenen yer legal bir konum ise bu kontrolleri yaparak hamle yapıyorum.
    for(i=0;i<col;i++){
        for(j=0;j<row;j++){
            /// XXX. / OOO. / .OOO / .XXX  DURUMLARINDA OYNAMA
            if(statu==1 && gameCells[i][j].getterType()=='X' && gameCells[i][j+1].getterType()=='X' && gameCells[i][j+2].getterType()=='X' &&
            	(i+1==col || gameCells[i+1][j+3].getterType()=='X'||gameCells[i+1][j+3].getterType()=='O')){
     
                if(j > 0 && colPositions[j-1]!=-1 && gameCells[i][j+3].getterType()!='.'){ 
                    sayi= j-1;
                    statu=0;
                    statu2=0;
                }
                else if (j+3<row && colPositions[j+3]!=-1){
                    sayi=j+3;
                    statu=0;
                    statu2=0;
                }
            }
            else if(statu==1 && gameCells[i][j].getterType()=='O' && gameCells[i][j+1].getterType()=='O' && gameCells[i][j+2].getterType()=='O' &&
            	(i+1==col || gameCells[i+1][j+3].getterType()=='X'||gameCells[i+1][j+3].getterType()=='O')){
               
                if(gameCells[i][j+3].getterType()!='.' && j > 0 && colPositions[j-1]!=-1){
                    sayi= j-1;
                    statu=0;
                    statu2=0;
                }
                else if (j+3<row && colPositions[j+3]!=-1){
                    sayi=j+3;
                    statu=0;
                    statu2=0;
                }
            }
            //// XX.X / OO.O DURUMLARINDA OYNAMA
            else if(statu==1 && gameCells[i][j].getterType()=='X' && gameCells[i][j+1].getterType()=='X' && gameCells[i][j+3].getterType()=='X' &&
            	(i+1==col || gameCells[i+1][j+2].getterType()=='X'||gameCells[i+1][j+2].getterType()=='O')){
                
                if(j>0 && gameCells[i][j+2].getterType()!='.' && colPositions[j-1]!=-1){
                    sayi= j-1;
                    statu2=0;
                    statu=0;
                }    
                else if (j+2<row && colPositions[j+2]!=-1){
                    sayi=j+2;
                    statu=0;
                    statu2=0;
                }
            }
             else if(statu==1 && gameCells[i][j].getterType()=='O' && gameCells[i][j+1].getterType()=='O'&& gameCells[i][j+3].getterType()=='O'&&
             	(i+1==col || gameCells[i+1][j+2].getterType()=='X'|| gameCells[i+1][j+2].getterType()=='O')){
                
                if(j > 0 && gameCells[i][j+2].getterType()!='.' && colPositions[j-1]!=-1){ 
                    sayi= j-1;
                    statu2=0;
                    statu=0;
                }    
                else if(j+2<row && colPositions[j+2]!=-1){
                    sayi=j+2;
                    statu=0;
                    statu2=0;
                }    
            }
            //X.XX / O.OO DURUMLARINDA OYNAMA ///
            else if(statu==1 && j+1<row && gameCells[i][j].getterType()=='X' && gameCells[i][j+2].getterType()=='X' && gameCells[i][j+3].getterType()=='X' &&
            	(i+1==col || gameCells[i+1][j+1].getterType()=='X'|| gameCells[i+1][j+1].getterType()=='O')){
            
                if(gameCells[i][j+1].getterType()=='.' && colPositions[j+1]!=-1){
                    sayi= j+1;
                    statu2=0;
                    statu=0;
                }        
                else if(j-1>0 && colPositions[j-1]!=-1){
                    sayi=j-1;
                    statu=0;
                }
            }
             else if(statu==1 && j+1<row && gameCells[i][j].getterType()=='O' && gameCells[i][j+2].getterType()=='O' && gameCells[i][j+3].getterType()=='O' &&
            	(i+1==col || gameCells[i+1][j+1].getterType()=='X'|| gameCells[i+1][j+1].getterType()=='O')){
                
                if(gameCells[i][j+1].getterType()=='.' && colPositions[j+1]!=-1){
                    sayi= j+1;
                    statu2=0;
                    statu=0;
                }        
                else if(j-1>0 && colPositions[j-1]!=-1){
                    sayi=j-1;
                    statu=0;
                }
            }
            ////////////////// ÇAPRAZ DURUMLAR İÇİN OYNAMA
            else if(statu==1 && j+3<row && i+4 <= col&& gameCells[i][j].getterType()=='X' && gameCells[i+1][j+1].getterType()=='X' && gameCells[i+2][j+2].getterType()=='X' 
            	&& (i+4==col || gameCells[i+4][j+3].getterType()=='X'|| gameCells[i+4][j+3].getterType()=='O')){
            	
                if(i>0 && j>0 && gameCells[i+3][j+3].getterType()!='.' &&  colPositions[j-1]!=-1){
                    sayi=j-1;
                    statu=0;                                //    .         |   X
                }                                           //      X       |    X
                else if(j+3<row && colPositions[j+3]!=-1){  //       X      |     X        
                    sayi=j+3;                               //        X     |      .
                    statu=0;         
                }
            }
            else if(statu==1 && j+3<row && i+4 <= col&& gameCells[i][j].getterType()=='O' && gameCells[i+1][j+1].getterType()=='O' && gameCells[i+2][j+2].getterType()=='O' 
            	&& (i+4==col || gameCells[i+4][j+3].getterType()=='X'|| gameCells[i+4][j+3].getterType()=='O')){
            	
                if(i>0 && j>0 && gameCells[i+3][j+3].getterType()!='.' &&  colPositions[j-1]!=-1){
                    sayi=j-1;
                    statu=0;                                //    .         |   O
                }                                           //      O       |    O
                else if(j+3<row && colPositions[j+3]!=-1){  //       O      |     O        
                    sayi=j+3;                               //        O     |      .
                    statu=0;         
                }
            } 
            else if(statu==1 &&  j-3>=0 && i+4 <= col && gameCells[i][j].getterType()=='X' && gameCells[i+1][j-1].getterType()=='X' && gameCells[i+2][j-2].getterType()=='X' 
            	&& (i+4==col ||gameCells[i+4][j-3].getterType()=='X' ||gameCells[i+4][j-3].getterType()=='O')){ 
                
                if(i-1>=0 && j+1 < row && gameCells[i-1][j+1].getterType()=='.' && colPositions[j+1]!=-1){
                    sayi=j+1;
                    statu=0;                                 //        .    |         X
                }                                            //       X     |        X
                else if (j-3>=0 && colPositions[j-3]!=-1){   //      X      |       X             
                    sayi=j-3;                                //     X       |      .
                    statu=0;        
                }
            }
          	else if(statu==1 &&  j-3>=0 && i+4 <= col && gameCells[i][j].getterType()=='O' && gameCells[i+1][j-1].getterType()=='O' && gameCells[i+2][j-2].getterType()=='O' 
            	&& (i+4==col ||gameCells[i+4][j-3].getterType()=='X' ||gameCells[i+4][j-3].getterType()=='O')){ 
                
                if(i-1>=0 && j+1 < row && gameCells[i-1][j+1].getterType()=='.' && colPositions[j+1]!=-1){
                    sayi=j+1;
                    statu=0;                                 //        .    |         O
                }                                            //       O     |        O
                else if (j-3>=0 && colPositions[j-3]!=-1){   //      O      |       O             
                    sayi=j-3;                                //     O       |      .
                    statu=0;        
                }
            }
            else if(statu==1 && j+3<row && i+3 <col && gameCells[i][j].getterType()=='X' && gameCells[i+1][j+1].getterType()=='X' && gameCells[i+3][j+3].getterType()=='X' 
            	&& (gameCells[i+3][j+2].getterType()=='X' ||gameCells[i+3][j+2].getterType()=='O')){ 
                
                if(gameCells[i+2][j+2].getterType()!='.' && colPositions[j+3]!=-1){
                    sayi=j+3;
                    statu=0;                            		//     X    
                }                                       		//      X
                else if(colPositions[j+2]!=-1){    				//       .     
                    sayi=j+2;                           	    //        X
                    statu=0;
                }
            }
            else if(statu==1 && j+3<row && i+3 <col && gameCells[i][j].getterType()=='O' && gameCells[i+1][j+1].getterType()=='O' && gameCells[i+3][j+3].getterType()=='O' 
            	&& (gameCells[i+3][j+2].getterType()=='X' ||gameCells[i+3][j+2].getterType()=='O')){ 
                
                if(gameCells[i+2][j+2].getterType()!='.' && colPositions[j+3]!=-1){
                    sayi=j+3;
                    statu=0;                            		//     O    
                }                                       		//      O
                else if(colPositions[j+2]!=-1){    				//       .     
                    sayi=j+2;                           	    //        O
                    statu=0;
                }
            }
            
            else if(statu==1 && j-3>=0 && i+3<col &&gameCells[i][j].getterType()=='X' && gameCells[i+1][j-1].getterType()=='X' && gameCells[i+3][j-3].getterType()=='X' 
            	&& (gameCells[i+3][j-2].getterType()=='X' || gameCells[i+3][j-2].getterType()=='O')){ 
                
                if(gameCells[i+2][j-2].getterType()!='.' && colPositions[j-3]!=-1){
                    sayi=j-3;
                    statu=0;                                      //          X    
                }                                                 //         X
                else if (colPositions[j-2]!=-1){       			  //        .
                    sayi=j-2;                                     //       X
                    statu=0;
                }
            }
            else if(statu==1 && j-3>=0 && i+3<col &&gameCells[i][j].getterType()=='O' && gameCells[i+1][j-1].getterType()=='O' && gameCells[i+3][j-3].getterType()=='O' 
            	&& (gameCells[i+3][j-2].getterType()=='X' || gameCells[i+3][j-2].getterType()=='O')){ 
                
                if(gameCells[i+2][j-2].getterType()!='.' && colPositions[j-3]!=-1){
                    sayi=j-3;
                    statu=0;                                      //          O    
                }                                                 //         O
                else if (colPositions[j-2]!=-1){       			  //        .
                    sayi=j-2;                                     //       O
                    statu=0;
                }
            }
            ////////////////DİKEY OYNAMA ///////////
            else if(statu==1 && i+2<col && gameCells[i][j].getterType()=='X'&& gameCells[i+1][j].getterType()=='X' && gameCells[i+2][j].getterType()=='X' && i > 0 ){
                if(j+1<row &&(gameCells[i-1][j].getterType()=='X' ||gameCells[i-1][j].getterType()=='O') && colPositions[j+1]!=-1){ 
                    sayi=j+1;
                    statu2=0;
                    statu=0;
                }
                else if(colPositions[j]!=-1){
                    sayi=j;
                    statu=0;
                }
            }
            else if(statu==1 && i+2<col && gameCells[i][j].getterType()=='O'&& gameCells[i+1][j].getterType()=='O' && gameCells[i+2][j].getterType()=='O' && i > 0 ){
                if(j+1<row &&(gameCells[i-1][j].getterType()=='X' ||gameCells[i-1][j].getterType()=='O') && colPositions[j+1]!=-1){ 
                    sayi=j+1;
                    statu2=0;
                    statu=0;
                }
                else if(colPositions[j]!=-1){
                    sayi=j;
                    statu=0;
                }
            }         
        }
    }
    ///// YENME DURUMUNU SAĞLAYACAK İHTİMALLER OLMADIĞINDA OYNAYACAK KISIM
    
    if(statu==1){
        for(i=0;i<col;i++){
            for(j=0;j<row;j++){
               
                if(gameCells[i][j].getterType()=='X' || gameCells[i][j].getterType()=='O'){
                    if(i==0) sayi=j+1;
                    else if(i>0 && statu2==1 && colPositions[j]!=-1) sayi = j;
                    else if(j+1 < row && colPositions[j+1]!=-1) sayi= j+1; 
                    else if(j>0 && colPositions[j-1]!=-1) sayi=j-1;
                    else if(gameCells[i][j].getterType()=='.') sayi=j;
               }
            }
        }
   }
 
    char temp;///seçilen ekseni diğer fonksiyonun anlaması için karakter hedefe çeviriyorum ve o şekilde return ediyorum
    for(temp=97,i=0;i<row;temp++,i++){
        if(sayi==i) return temp;
    }
}
