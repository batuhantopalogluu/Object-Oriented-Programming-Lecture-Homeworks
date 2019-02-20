/*  
	
	Batuhan TOPALOĞLU 151044026 HW4  

	

	
	!!! ROW ve COL değerlerini fonksiyonları tasarlarken ters düşündüğüm için row aslında col, col aslında row değerlerini barındırıyor. !!!
	


*/
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

class connectFour
{
public:

 	connectFour(int rowValue=5,int colValue=5);
	connectFour(const connectFour & copy);
	connectFour(string filename);
	~connectFour();	

	void current_print()const; //displays the current board	   
    int playGame(char gamemode);/*This function plays the game by asking the user the board size first then asks the user to play and the computer plays, etc.*/    
    int numberCheck(string size,char rowOrCol);//alınan inputun rakamlar oluşup oluşmadığını kontrol eden fonksiyon

	friend const bool operator==(const connectFour& me,const connectFour& other);
    friend const bool operator!=(const connectFour& me,const connectFour& other);
    
    char getterGameType(){return gameType;}
	inline int gettercolPos(int hedef){return colPositions[hedef];}
	inline void settercolPo(int h){colPositions[h]--;}
	inline static int num_livingCell(){livingcell++;}     /*returns the number of living cells in all the games. Be careful here because there could be more than one game active at the same time.*/
    inline static int getterLivinCell(){return livingcell;}
    inline static int setterLivingCell(int numliv){livingcell=numliv;}
    inline  int setterGameStatu(int temp){gamestatu=temp;}
    inline int ggeGameStatu()const{return gamestatu;}    

   	const connectFour operator=(const connectFour& other);	   
	int multigamesize;
private:
		class Cell
		{			
		public:

			Cell();		
			Cell(char ttype,char position,int row);
			const bool operator==(const Cell other)const;
			const bool operator==(char cchar)const;
			const bool operator!=(const Cell other)const;
			const bool operator!=(char cchar)const;
			inline void setterType(char setterT){type=setterT;};
			inline void setterPosition(char setterP){position=setterP;};
			inline void setterRow(int setterR){Crow=setterR;};
			inline int getterRow() const { return Crow;}
			inline char getterPosition() const { return position;}
			inline char getterType() const { return type;}				
			const Cell operator=(const Cell & other);
			const Cell operator=(char type);
			Cell operator++(int);
			Cell& operator++();
			Cell operator--(int);
			Cell& operator--();
			friend connectFour;
			void operator-();
		
		private:
			
			char position;//A ,B ,c
			int Crow; //1 , 2 , 3
			char type;/* 'O' || 'X' ||'*' */
			int usr2OrCom =0;// User 2 iken 0 computer iken 1 // Pre and post increment/decrement operatorleri için
		};
	friend ostream& operator<<(ostream & outputstream, const connectFour::Cell & obje);
	friend istream& operator>>(istream& inputstream ,connectFour::Cell & obje);
	
	void auxiliarXXX_OOO(int &statu,int &statu2,int i,int j,char xo,int &sayi); // user vs computer modunda computer hamleleri için yardımcı fonksiyonlar
	void auxiliarXX_X_OO_O(int &statu,int &statu2,int i,int j,char xo,int &sayi); 
	void auxiliarX_XX_O_OO(int &statu,int &statu2,int i,int j,char xo,int &sayi);
	void auxiliarVertical(int &statu,int &statu2,int i,int j,char xo,int &sayi);
    
    char tochar(int i)const ;

    bool read_file(const string filename,int &i);//load yapınca sıranın kimde olduğu değişebileceği için i yi referance gönderiyorum
	void write_file(const string filename,int i);

    int map_statu() const; // bitme koşullarının sağlanıp sağlanmadığını kontrol eden fonksiyonlar
    int verticalhorizontal(); //
    int diagonal(); //

    int play_user(char hedef[],int &i,int *colspace);   //position and it plays the user.
    char play_computer();    //The class will have two functions named play that plays the game for a single time step. First
											//function does not take a parameter and it plays the computer. The second function takes a cell    
    void resize();

	int row;
	int col;
	char gameType;
	char gameMode;
	
	int * colPositions;
	int * colspace; // bir sütundaki yukarıdan aşağıya doğru space karakter sayısını tutuyorum
	int gamestatu; // Multi modda playgame fonksiyonu her çağrıldığında yeniden size sormasın diye tuttuğum bir değişken
	static int livingcell;
	Cell ** gameCells;		
};
int biggerPossib(char xo,connectFour *multi,const int t);

connectFour::connectFour(int rowValue,int colValue):row(rowValue),col(colValue),gameType('P'),gameMode('M'){
	
	resize(); // row col a göre gamecell e yer alıyorum
	for(int i=0;i<col;i++){ // cell lerin içlerine konum bilgilerini atıyorum
		for(int j=0;j<row;j++){
			gameCells[i][j].setterRow(j);
			gameCells[i][j].setterPosition(tochar(i));
		}
	}	
}
connectFour::connectFour(const connectFour & copy){
	row=copy.row;
	col=copy.col;
	colPositions= new int[row];
	colspace= new int[row];
	for(int i=0;i<row;i++)colPositions[i]=copy.colPositions[i];
	for(int i=0;i<row;i++)colspace[i]=copy.colspace[i];		
	resize();
	for(int i=0;i<col;i++){
		for (int j=0;i<row;j++){
			gameCells[i][j]=copy.gameCells[i][j];
		}
	}
}
connectFour::connectFour(string filename){
	cout<<"string";
	ifstream temp_okuma(filename);    // ROW size ını bulmak için dosyayı önceden bir kere okuyorum
	if(!temp_okuma.is_open())
	{
		cout << "ERROR FİLE" << endl;
		exit(1);	
	}
    int colSize =0;
    int rowi=0;
    string temp_dosya;
 
    do{
    	getline(temp_okuma,temp_dosya);
    	if(temp_okuma.eof()) break;  	
    	if(temp_dosya.size()>rowi) rowi=temp_dosya.size();
    	colSize++;
    }while(!temp_okuma.eof());
   
    temp_okuma.close();
    
    row=rowi;
    col=colSize;
    ifstream okuma(filename);
    int i=0;
    resize();
    string satir;
    do{
    	getline(okuma,satir);
    	if(okuma.eof()) break;
    	for(int j=0;j<satir.size();j++){
    		gameCells[i][j]=satir[j];
    		gameCells[i][j].setterRow(j);
			gameCells[i][j].setterPosition(tochar(i));
    	}
    	for(int j=satir.size();j<row;j++){
    		gameCells[i][j]=' ';
    	}
    	i++;
    	if(i==col) break;
    }while(!okuma.eof());
  
    okuma.close();
}
connectFour::~connectFour(){
	
	for(int i=0;i<col;i++){
		delete[] gameCells[i];	
	}	
	delete [] gameCells;
	delete [] colPositions;
	delete [] colspace;
}
connectFour::Cell::Cell():position('A'),Crow(1),type('*'){} 			

connectFour::Cell::Cell(char ttype,char tposition,int row):type(ttype),position(tposition),Crow(row){}

int connectFour::livingcell = 0;

void connectFour::Cell::operator-(){
	type+=32;
}
const bool connectFour::Cell::operator==(const Cell other)const{
	if(type==other.getterType() && position==other.getterPosition() && Crow==other.getterRow()){
		return true;
	}
	return false;
}
const bool connectFour::Cell::operator!=(const Cell other)const{
	if(*this==other){
		return false;
	}
	return true;
}
const bool connectFour::Cell::operator==(char cchar)const{
	if(type==cchar) return true;
	return false;
}
const bool connectFour::Cell::operator!=(char cchar)const{
	if(type==cchar) return false;
	return true;
}
const connectFour::Cell connectFour::Cell::operator=(char otype){
	type=otype;
	return *this;
}
const connectFour::Cell connectFour::Cell::operator=(const connectFour::Cell & other){
	type=other.getterType();
	Crow=other.getterRow();
	position=other.getterPosition();
	return *this;
}
const connectFour connectFour::operator=(const connectFour& other){
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
const bool operator==(const connectFour& me,const connectFour& other){

	if(me.row!=other.row || me.col!=other.col) return false;

	for(auto a = 0;a<me.col;a++){
		for(auto b=0;b<me.row;b++){
			if(me.gameCells[a][b]!=other.gameCells[a][b]) return false;		
		}
	}	
	return true;
}
const bool operator!=(const connectFour& me,const connectFour& other){
	if(me==other) return false;

	return true;
}
connectFour::Cell connectFour::Cell::operator++(int){//postfix
	Cell temp; 
	temp=*this;	
	
	if(type=='*') type='X';
	else if(type=='X') type='O';
	else if(type=='O' && usr2OrCom==0)usr2OrCom=1;
	else if(type=='O' && usr2OrCom==1)type='*';

	return temp;//Cell(temptype,position,Crow);
}
connectFour::Cell& connectFour::Cell::operator++(){//prefix 
	
	if(type=='*') type='X';
	else if(type=='X') type='O';
	else if(type=='O' && usr2OrCom==0)usr2OrCom=1;
	else if(type=='O' && usr2OrCom==1)type='*';
	
	return *this;
}
connectFour::Cell connectFour::Cell::operator--(int){ // unary artı nın tam tersi yönde değişim yapıyorlar
	Cell temp; 
	temp=*this;	
	
	if(type=='*'){type='O'; usr2OrCom=1;}
	else if(type=='O' && usr2OrCom==1)usr2OrCom=0;
	else if(type=='O' && usr2OrCom==0)type='X';
	else if(type=='X') type='*';

	return temp;
}
connectFour::Cell& connectFour::Cell::operator--(){
	
	if(type=='*'){type='O'; usr2OrCom=1;}
	else if(type=='O' && usr2OrCom==1)usr2OrCom=0;
	else if(type=='O' && usr2OrCom==0)type='X';
	else if(type=='X') type='*';
	
	return *this;
}
ostream& operator<<(ostream & outputstream, const connectFour::Cell & obje){

	outputstream<<"CELL TYPE : "<<obje.getterType()<<endl
				<<"CELL Position : "<<obje.getterPosition()<<endl
				<<"CELL Row : "<<obje.getterRow();
 	return outputstream;
}
istream& operator>>(istream& inputstream ,connectFour::Cell & obje){

	cout<<"Row of CELL :";
	int trow;
	inputstream>>trow;
	obje.setterRow(trow);
	cout<<"Position of CELL";
	char tposition;
	inputstream>>tposition;
	obje.setterPosition(tposition);
	char a;
	inputstream>>a;
	obje.setterType(a);

	return inputstream;
}

int main(int argc, char const *argv[]){

    cout<<"________________ ConnectFour ____________________"<<endl;															
    char gamemode[10];
    int c=1;    
    connectFour single;
    connectFour* multi;
    int * bitenoyunlar;
    int bitenoyunlarsize=0;
  	int multisize=5;
  	int tempi;
  	bool bol;
  	tempi=multisize;
    multi = new connectFour[multisize];
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
               	    int condition;
               		condition=1;
					for(int i=0;i<multisize;i++){
						multi[i].setterGameStatu(0);
						multi[i].multigamesize=multisize;						
					}
					for(int i=0;i<multisize;i++){
						cout<<"\nobje"<<i+1<<":"<<endl;
						multi[i].playGame('M');
					}
					int objectnumber;
					int h;
					h=0;
					int a;
					a=0;
			
					while(h!=multisize){
						int z=0;
						if(a!=0)cout<<"livingcell:"<<multi[0].getterLivinCell()<<endl;
						int suggest=0;
			    		
			    		cout<<"Obje seçiniz: ";
						while(z==0 ){
							condition=1;               		
							
							while(condition==1){ //input için tip kontrolü yapıyorum
							   	cin>>Tobjectnumber;	
								if(tempI.numberCheck(Tobjectnumber,'T')!=-2) condition=-1;
								else cerr<<"! hatalı giriş"<<endl;
							}
							objectnumber=tempI.numberCheck(Tobjectnumber,'T');
						
							for(int i=0;i<bitenoyunlarsize;i++){ //multi modda biten objeleri daha sonra onlara ulaşılmak istenildiğinde bunu engellemek için bir vectorde tutuyorum.
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
							
							int * tempbitenoyunlar = new int[bitenoyunlarsize+1];
							for(int i=0;i<bitenoyunlarsize;i++){
								tempbitenoyunlar[i]=bitenoyunlar[i];
							}
							tempbitenoyunlar[bitenoyunlarsize]=objectnumber;
							bitenoyunlarsize++;
							bitenoyunlar=tempbitenoyunlar;
									
						}
						cout<<"obje1 == obje2 durumu : ";
				   	 	bol=multi[0]==multi[1];
						cout<<bol<<endl;
						cout<<"obje1 != obje2 durumu : ";
						bol=multi[0]!=multi[1];
						cout<<bol<<endl;
						a++;						
					}
					delete [] bitenoyunlar;										
					c=0;  
                break;
          
            default:
                cerr<<"!!!FALSE GAME MODE PLEASE TRY AGAIN!!!\n";
                break;
        }   
    }
	return 0;
}

int connectFour::playGame(char gamemode){       // biraz uzun bir fonksiyon ancak içeride yapılması gereken işlemler sabit olduğu daha fazla kısaltamadım         

	gameMode=gamemode;
	string arrRow,arrCol;
	int condition=1;   /// int beklerken girilen hatalı tipleri kontrol ediyorum. ROW veya COL değerlirinin 4 ten küçük olmasını HATALI durum olarak saydım

	if(gameMode=='S' || (gameMode=='M' && ggeGameStatu()==0)){ 
		string filename;
		cout<<"\nmape için dosya ismi giriniz...";
		cin>>filename;		
		ifstream temp_okuma(filename);    // ROW size ını bulmak için dosyayı önceden bir kere okuyorum
		if(!temp_okuma.is_open())
		{
			cout << "ERROR FİLE" << endl;
			exit(1);	
		}
	    int colSize =0;
	    int rowi=0;
	    string temp_dosya;
	    colPositions=new int[row];
	    do{
	    	getline(temp_okuma,temp_dosya);
	    	if(temp_okuma.eof()) break;  	
	    	if(temp_dosya.size()>rowi) rowi=temp_dosya.size();  // en uzun satır uzunluğumu row olarak alıyorum
	    	colSize++;  										// kaç satırı sayarak col u bulmuş oluyorum
	    }while(!temp_okuma.eof());
	    temp_okuma.close();
	    
	    row=rowi;
	    col=colSize;
	    ifstream okuma(filename); // mape i doldurmak için yapılan dosyadan okuma
	    int i=0;
	    gameCells = new Cell*[col];
	    string satir;
	    do{
	    	getline(okuma,satir);
	    	if(okuma.eof()) break;
	    	
	    	gameCells[i]= new Cell[row];
	    	for(int j=0;j<satir.size();j++){
	    		gameCells[i][j]=satir[j];
	    		gameCells[i][j].setterRow(j);
				gameCells[i][j].setterPosition(tochar(i));
	    	}
	    	for(int j=satir.size();j<row;j++){

	    		gameCells[i][j]=' ';  //yıldızlar sonrasındaki boş yerler 
	    	}
	    	i++;
	    	if(i==col) break;
	    }while(!okuma.eof());
	    okuma.close();

     	colspace= new int[row];
		colPositions = new int[row];
	    int count=0;
	    for(auto a = 0;a<row;a++){
			for(auto b=0;b<col;b++){
				if(gameCells[b][a]=='*') count ++;					
			}
			colPositions[a]=count-1;
			colspace[a]=col-count;
			count=0;
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
		if (gameMode=='M' && ggeGameStatu()==0){
	    	setterGameStatu(1);
	    	return 0;
		}
	}
    current_print();
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
            cout<<adres<<endl;
            if(adres.size()==0){ // inputları dosyadan alırken oyun bitme koşuluna ulaşmadan inputlar biterse direk programdan çıktığımız için hafızayı boşaltma işini kendim yapıyorum
            	for(int i=0;i<col;i++){
					delete[] gameCells[i];	
				}	
				delete [] gameCells;
				delete [] colPositions;
				delete [] colspace;
			   	exit(1);
            }
            
            hedef[0]=adres[0];           
            if((adres[0]=='L' && adres[1]=='O' && adres[2]=='A' && adres[3]=='D') || (adres[0]=='S' && adres[1]=='A' && adres[2]=='V' && adres[3]=='E')){ // load veya save yapılmak istenilme durumu
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
        int statuVH,statuD;
    	if(play_user(hedef,i,colspace)==1){
	        
	        num_livingCell(); // bitme koşulu sağlanmış mu diye kontrol ediyorum
    		statuVH=verticalhorizontal();
    		statuD=diagonal();
    		
    		if((statuVH==1 || statuD ==1)&& gameType=='P')cout<<"\n\n--- CONGRULATİONS -P1- Win The Game ---\n";// bitme mesajları
			else if((statuVH==2 || statuD ==2)&& gameType=='P')cout<<"\n\n--- CONGRULATİONS -P2- Win The Game ---\n";
			else if((statuVH==2 || statuD ==2)&& gameType=='C' && i%2==0)cout<<"\n\n--- COMPUTER- Win The Game ---\n";
			else if((statuVH==2 || statuD ==2)&& gameType=='C' && i%2==1)cout<<"\n\n--- CONGRULATİONS -YOU- Win The Game ---\n";																									
	        
	        current_print();
	        if(map_statu()==1 || statuVH !=0 || statuD !=0) return 1;//oyunun bitme durumları
	    }   
	}
	return 0;
}

int connectFour::play_user(char hedef[],int & i,int * colspace){

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
    gameCells[colPositions[sayi]+colspace[sayi]][sayi].setterType(atanacak); // mape üzerinde ki doğru konuma user a göre atama yapıyorum          	
    settercolPo(sayi); // sutünlardaki konumu tutan arrayde atama yaptığım sütun için konumumu bir üst cell e kaydırıyorum
    return 1;
}
bool connectFour::read_file(string filename,int &i){

	ifstream okuma(filename);
    
    if(okuma.is_open()){
        int num;
        for(int i=0;i<col;i++){ //  hali hazırda kullandığım yerleri free ediyorum
			delete [] gameCells[i];
		}
		delete [] gameCells;
		delete [] colPositions;
		delete [] colspace;

        okuma>>num;setterLivingCell(num);
        okuma>>gameMode;
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
	    	for(int j=satir.size();j<row;j++){
	    		gameCells[a][j]=' ';  //yıldızlar sonrasındaki boş yerler 
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
		colspace = new int[row];// bir mape her sütunda yukarıdan kaç boşluk olduğunu tutan dizi
		for(auto a=0;a<row;a++){
			okuma>>tempint;
			colspace[a]=tempint;
		}
		cout<<endl;
		current_print();			
        okuma.close();
        //exit(1);
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
				yazma<<gameCells[a][b].getterType();
			}
			yazma<<'\n';
		}
	    for(auto a=0;a<row;a++)yazma<<colPositions[a]<<' ';
	    yazma<<endl;
	    for(auto a=0;a<row;a++)yazma<<colspace[a]<<' ';
	}	
}
void connectFour::current_print() const{

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
char connectFour::tochar(int a)const { // int sütün değerini karakter hedef e çeviriyorum
	int i;
	char temp;
    for(temp=97,i=0;i<row;temp++,i++){
        if(a==i) return temp;
    }
    return '\0';	
}
void connectFour::resize(){

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

int connectFour::map_statu()const{

	int Count=0,countspace=0,i,j;
	for(i=0;i<col;i++){
        for(j=0;j<row;j++){
            if(gameCells[i][j].getterType()=='X'|| gameCells[i][j].getterType()=='O'){     
            	Count++;      
            }
        }
    }
    for(int k=0;k<row;k++){
    	countspace+=colspace[k];
    }
    if(Count+countspace==row*col){cerr<<"--- MAPE IS FULL GAME FINISHED ---\n";return 1;}  // mape in dolma durumu
	return 0;
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
	if(rowOrCol=='R')col=olacak;
	if(rowOrCol=='C')row=olacak;
	if(rowOrCol=='T') return olacak;
 	return -1;
}
int connectFour::verticalhorizontal(){
    
    int i,j;
    for(i=0;i<col;i++){// yatayı tarayan kısım
        for(j=0;j<row;j++){
            if(j+3<row && gameCells[i][j]=='X'&& gameCells[i][j+1]=='X' && gameCells[i][j+2]=='X' && gameCells[i][j+3]=='X'){     
            	-gameCells[i][j];-gameCells[i][j+1];-gameCells[i][j+2];-gameCells[i][j+3];
            	return 1;         
            }
            if(j+3<row && gameCells[i][j]=='O'&& gameCells[i][j+1]=='O' && gameCells[i][j+2]=='O' && gameCells[i][j+3]=='O'){
            	-gameCells[i][j];-gameCells[i][j+1];-gameCells[i][j+2];-gameCells[i][j+3];
            	return 2;
            }
  			//dikey arama
            if(i+3<col && gameCells[i][j]=='X'&& gameCells[i+1][j]=='X' && gameCells[i+2][j]=='X' && gameCells[i+3][j]=='X'){
                -gameCells[i][j];-gameCells[i+1][j];-gameCells[i+2][j];-gameCells[i+3][j];
            	return 1;            	
            }
            if(i+3<col && gameCells[i][j]=='O'&& gameCells[i+1][j]=='O' && gameCells[i+2][j]=='O' && gameCells[i+3][j]=='O'){
            	-gameCells[i][j];-gameCells[i+1][j];-gameCells[i+2][j];-gameCells[i+3][j];
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
            if(i+3<col && j+3<row && gameCells[i][j]=='X' && gameCells[i+1][j+1]=='X' && gameCells[i+2][j+2]=='X' && gameCells[i+3][j+3]=='X'){ // sağ üsten sağ alta tarama yapan kısım
                -gameCells[i][j];-gameCells[i+1][j+1];-gameCells[i+2][j+2];-gameCells[i+3][j+3];
                 return 1;            
            }
            if(i+3<col && j+3<row && gameCells[i][j]=='O' && gameCells[i+1][j+1]=='O' && gameCells[i+2][j+2]=='O' && gameCells[i+3][j+3]=='O'){
            	-gameCells[i][j];-gameCells[i+1][j+1];-gameCells[i+2][j+2];-gameCells[i+3][j+3];
            	return 2;
            }
            if(i+3<col && j-3>=0 && gameCells[i][j]=='X' && gameCells[i+1][j-1]=='X' && gameCells[i+2][j-2]=='X' && gameCells[i+3][j-3]=='X'){// sağ üstten  sol alta tarama yapan kısım 
                -gameCells[i][j];-gameCells[i+1][j-1];-gameCells[i+2][j-2];-gameCells[i+3][j-3];
                return 1;            	
            }
            if(i+3<col && j-3>=0 && gameCells[i][j]=='O' && gameCells[i+1][j-1]=='O' && gameCells[i+2][j-2]=='O' && gameCells[i+3][j-3]=='O'){
            	-gameCells[i][j];-gameCells[i+1][j-1];-gameCells[i+2][j-2];-gameCells[i+3][j-3];
                return 2;
            }
        }
    }
    return 0;
}

void connectFour::auxiliarXXX_OOO(int &statu,int &statu2,int i,int j,char xo,int &sayi){
	if(gameCells[i][j]==xo && gameCells[i][j+1]==xo && gameCells[i][j+2]==xo &&
    	(i+1==col || gameCells[i+1][j+3]=='X'||gameCells[i+1][j+3]=='O')){

        if(j > 0 && colPositions[j-1]!=-1 && gameCells[i][j+3]!='.'){ 
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
}
void connectFour::auxiliarXX_X_OO_O(int &statu,int &statu2,int i,int j,char xo,int &sayi){
	if(gameCells[i][j]==xo && gameCells[i][j+1]==xo && gameCells[i][j+3]==xo &&
    	(i+1==col || gameCells[i+1][j+2]=='X'||gameCells[i+1][j+2]=='O')){
        
        if(j>0 && gameCells[i][j+2]!='.' && colPositions[j-1]!=-1){
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
}
void connectFour::auxiliarX_XX_O_OO(int &statu,int &statu2,int i,int j,char xo,int &sayi){
	if(j+1<row && gameCells[i][j]==xo && gameCells[i][j+2]==xo && gameCells[i][j+3]==xo &&            	
		(i+1==col || gameCells[i+1][j+1]=='X'|| gameCells[i+1][j+1]=='O')){

	    if(gameCells[i][j+1]=='.' && colPositions[j+1]!=-1){
	        sayi= j+1;
	        statu2=0;
	        statu=0;
	    }        
	    else if(j-1>0 && colPositions[j-1]!=-1){
	        sayi=j-1;
	        statu=0;
	    }
	}
}
void connectFour::auxiliarVertical(int &statu,int &statu2,int i,int j,char xo,int &sayi){
	if(i+2<col && gameCells[i][j]==xo && gameCells[i+1][j]==xo && gameCells[i+2][j]==xo && i > 0 ){
	    if(j+1<row &&(gameCells[i-1][j]=='X' ||gameCells[i-1][j]=='O') && colPositions[j+1]!=-1){ 
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
char connectFour::play_computer(){
	int i,j,sayi= 0;
    int statu=1,statu2=1; // Uygun ihtimaller sağlandığında ve oynan istenen yer legal bir konum ise bu kontrolleri yaparak hamle yapıyorum.
    for(i=0;i<col;i++){
        for(j=0;j<row;j++){            
            /// XXX. / OOO. / .OOO / .XXX  DURUMLARINDA OYNAMA
            if(statu==1) auxiliarXXX_OOO(statu,statu2,i,j,'X',sayi);                        
            if(statu==1) auxiliarXXX_OOO(statu,statu2,i,j,'O',sayi);

			//// XX.X / OO.O DURUMLARINDA OYNAMA
            if(statu==1) auxiliarXX_X_OO_O(statu,statu2,i,j,'X',sayi);            
            if(statu==1) auxiliarXX_X_OO_O(statu,statu2,i,j,'O',sayi);

            //X.XX / O.OO DURUMLARINDA OYNAMA ///
            if(statu==1) auxiliarX_XX_O_OO(statu,statu2,i,j,'X',sayi);            
            if(statu==1) auxiliarX_XX_O_OO(statu,statu2,i,j,'O',sayi);

            ////////////////// ÇAPRAZ DURUMLAR İÇİN OYNAMA
            if(statu==1 && j+3<row && i+4 <= col&& gameCells[i][j]=='X' && gameCells[i+1][j+1]=='X' && gameCells[i+2][j+2]=='X' 
            	&& (i+4==col || gameCells[i+4][j+3]=='X'|| gameCells[i+4][j+3]=='O')){
            	
                if(i>0 && j>0 && gameCells[i+3][j+3]!='.' &&  colPositions[j-1]!=-1){
                    sayi=j-1;
                    statu=0;                                //    .         |   X
                }                                           //      X       |    X
                else if(j+3<row && colPositions[j+3]!=-1){  //       X      |     X        
                    sayi=j+3;                               //        X     |      .
                    statu=0;         
                }
            }
            if(statu==1 && j+3<row && i+4 <= col&& gameCells[i][j]=='O' && gameCells[i+1][j+1]=='O' && gameCells[i+2][j+2]=='O' 
            	&& (i+4==col || gameCells[i+4][j+3]=='X'|| gameCells[i+4][j+3]=='O')){
            	
                if(i>0 && j>0 && gameCells[i+3][j+3]!='.' &&  colPositions[j-1]!=-1){
                    sayi=j-1;
                    statu=0;                                //    .         |   O
                }                                           //      O       |    O
                else if(j+3<row && colPositions[j+3]!=-1){  //       O      |     O        
                    sayi=j+3;                               //        O     |      .
                    statu=0;         
                }
            } 
            if(statu==1 &&  j-3>=0 && i+4 <= col && gameCells[i][j]=='X' && gameCells[i+1][j-1]=='X' && gameCells[i+2][j-2]=='X' 
            	&& (i+4==col ||gameCells[i+4][j-3]=='X' ||gameCells[i+4][j-3]=='O')){ 
                
                if(i-1>=0 && j+1 < row && gameCells[i-1][j+1]=='.' && colPositions[j+1]!=-1){
                    sayi=j+1;
                    statu=0;                                 //        .    |         X
                }                                            //       X     |        X
                else if (j-3>=0 && colPositions[j-3]!=-1){   //      X      |       X             
                    sayi=j-3;                                //     X       |      .
                    statu=0;        
                }
            }
          	if(statu==1 &&  j-3>=0 && i+4 <= col && gameCells[i][j]=='O' && gameCells[i+1][j-1]=='O' && gameCells[i+2][j-2]=='O' 
            	&& (i+4==col ||gameCells[i+4][j-3]=='X' ||gameCells[i+4][j-3]=='O')){ 
                
                if(i-1>=0 && j+1 < row && gameCells[i-1][j+1]=='.' && colPositions[j+1]!=-1){
                    sayi=j+1;
                    statu=0;                                 //        .    |         O
                }                                            //       O     |        O
                else if (j-3>=0 && colPositions[j-3]!=-1){   //      O      |       O             
                    sayi=j-3;                                //     O       |      .
                    statu=0;        
                }
            }
            if(statu==1 && j+3<row && i+3 <col && gameCells[i][j]=='X' && gameCells[i+1][j+1]=='X' && gameCells[i+3][j+3]=='X' 
            	&& (gameCells[i+3][j+2]=='X' ||gameCells[i+3][j+2]=='O')){ 
                
                if(gameCells[i+2][j+2]!='.' && colPositions[j+3]!=-1){
                    sayi=j+3;
                    statu=0;                            		//     X    
                }                                       		//      X
                else if(colPositions[j+2]!=-1){    				//       .     
                    sayi=j+2;                           	    //        X
                    statu=0;
                }
            }
            if(statu==1 && j+3<row && i+3 <col && gameCells[i][j]=='O' && gameCells[i+1][j+1]=='O' && gameCells[i+3][j+3]=='O' 
            	&& (gameCells[i+3][j+2]=='X' ||gameCells[i+3][j+2]=='O')){ 
                
                if(gameCells[i+2][j+2]!='.' && colPositions[j+3]!=-1){
                    sayi=j+3;
                    statu=0;                            		//     O    
                }                                       		//      O
                else if(colPositions[j+2]!=-1){    				//       .     
                    sayi=j+2;                           	    //        O
                    statu=0;
                }
            }
            
            if(statu==1 && j-3>=0 && i+3<col &&gameCells[i][j]=='X' && gameCells[i+1][j-1]=='X' && gameCells[i+3][j-3]=='X' 
            	&& (gameCells[i+3][j-2]=='X' || gameCells[i+3][j-2]=='O')){ 
                
                if(gameCells[i+2][j-2]!='.' && colPositions[j-3]!=-1){
                    sayi=j-3;
                    statu=0;                                      //          X    
                }                                                 //         X
                else if (colPositions[j-2]!=-1){       			  //        .
                    sayi=j-2;                                     //       X
                    statu=0;
                }
            }
            if(statu==1 && j-3>=0 && i+3<col &&gameCells[i][j]=='O' && gameCells[i+1][j-1]=='O' && gameCells[i+3][j-3]=='O' 
            	&& (gameCells[i+3][j-2]=='X' || gameCells[i+3][j-2]=='O')){ 
                
                if(gameCells[i+2][j-2]!='.' && colPositions[j-3]!=-1){
                    sayi=j-3;
                    statu=0;                                      //          O    
                }                                                 //         O
                else if (colPositions[j-2]!=-1){       			  //        .
                    sayi=j-2;                                     //       O
                    statu=0;
                }
            }
            ////////////////DİKEY OYNAMA ///////////
            if(statu==1) auxiliarVertical(statu,statu2,i,j,'X',sayi);
            if(statu==1) auxiliarVertical(statu,statu2,i,j,'O',sayi);
        }
    }
    ///// YENME DURUMUNU SAĞLAYACAK İHTİMALLER OLMADIĞINDA OYNAYACAK KISIM    
    if(statu==1 || gettercolPos(sayi)==-1){
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

