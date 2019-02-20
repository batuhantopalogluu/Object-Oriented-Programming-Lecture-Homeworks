/*  
	
	Batuhan TOPALOĞLU 151044026 HW5  

	!!! ROW ve COL değerlerini fonksiyonları tasarlarken ters düşündüğüm için row aslında col, col aslında row değerlerini barındırıyor. !!!
	
*/
//#include "ConnectFourAbstract.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
using namespace std;

class Cell
{			
public:

	Cell();		
	Cell(char ttype,char position,int row);
	
	const bool operator==(const Cell &other)const;
	const bool operator==(char cchar)const;
	const bool operator!=(char cchar)const;
	const Cell& operator=(const Cell & other);
	const Cell& operator=(char type);
	void operator-();
	
	inline void setterType(char setterT){type=setterT;};
	inline void setterPosition(char setterP){position=setterP;};
	inline void setterRow(int setterR){Crow=setterR;};
	inline const int getterRow() const { return Crow;}
	inline const char getterPosition() const { return position;}
	inline const char getterType() const { return type;}	

protected:
	
	char position;//A ,B ,c
	int Crow; //1 , 2 , 3
	char type;/* 'O' || 'X' ||'*' */
	int usr2OrCom =0;// User 2 iken 0 computer iken 1 // Pre and post increment/decrement operatorleri için
};
class ConnectFourAbstract
{
public:

 	ConnectFourAbstract(int rowValue=5,int colValue=5);
	ConnectFourAbstract(const ConnectFourAbstract & copy);
	~ConnectFourAbstract();	

    virtual int playGame();/*This function plays the game by asking the user the board size first then asks the user to play and the computer plays, etc.*/      
   
   	const ConnectFourAbstract& operator=(const ConnectFourAbstract& other);	   
	
protected:
	
    char tochar(int i)const ;

    bool read_file(const string & filename,int &i);//load yapınca sıranın kimde olduğu değişebileceği için i yi referance gönderiyorum
	void write_file(const string & filename,int i)const;

    int map_statu() const; // bitme koşullarının sağlanıp sağlanmadığını kontrol eden fonksiyonlar
    
    int numberCheck(string &size,char rowOrCol);//alınan inputun rakamlar oluşup oluşmadığını kontrol eden fonksiyon //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++ & const kontrolü yapıldı
    virtual int endgame();

    void current_print()const; //displays the current board	   
   
    inline int gettercolPos(int hedef){return colPositions[hedef];}
    inline void settercolPos(int h){colPositions[h]--;}

    int play_user(const char hedef[],int &i);   //position and it plays the user. i fonksiyon içinde değiştiği için reference gönderiyorum
    virtual char play_computer();    //The class will have two functions named play that plays the game for a single time step. First
											//function does not take a parameter and it plays the computer. The second function takes a cell    
    void resize();
    
   	int row;
	int col;
	char gameType;
	int * colPositions;
	Cell ** gameCells;		
};
class ConnectFourPlus:public ConnectFourAbstract
{
protected:
	int endgame()override ;
    char play_computer() override;

    void auxiliarXXX_OOO(int &statu,int &statu2,int i,int j,char xo,int &sayi); // user vs computer modunda computer hamleleri için yardımcı fonksiyonlar. play_computer fonksiyonun yardımcı fonksiyonları
	void auxiliarXX_X_OO_O(int &statu,int &statu2,int i,int j,char xo,int &sayi); 
	void auxiliarX_XX_O_OO(int &statu,int &statu2,int i,int j,char xo,int &sayi);
	void auxiliarVertical(int &statu,int &statu2,int i,int j,char xo,int &sayi);
};
class ConnectFourDiag:public ConnectFourAbstract
{
protected:
	int endgame() override;
	char play_computer() override;
};
class ConnectFourPlusUndo:public ConnectFourPlus
{
public:
	int playGame() override;	
protected:
    inline void settercolPosUndo(int h){colPositions[h]++;}      
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------

char ConnectFourAbstract::play_computer(){ // abstractan türetilecek olan class larda içi dolucak
	/**/
}
int ConnectFourAbstract::endgame(){// abstractan türetilecek olan class larda işlevsel hale gelicek
/**/
}

int main(int argc, char const *argv[]){

    cout<<"________________ ConnectFour____________________"<<endl;															
    char gamemode[10];
    int c=1;    
    while(c==1){ // hatalı inputlarda tekrar input alıyorum
       
        cout<<"OYUN MODUNU SEÇİNİZ"<<endl<<"'P'-ConnectFourPlus"<<"\t"<<"'D'-DIAGONAL"<<"\t"<<"'U'-UNDO\n";
        cin>>gamemode;

        if(gamemode[0]=='p' || gamemode[0]=='P'){
            ConnectFourPlus plus;
            plus.playGame();
            c=0;
        }
         
        if(gamemode[0]=='d' || gamemode[0]=='D'){   
			ConnectFourDiag diag;   
			diag.playGame();						
			c=0;  
        }  
  
        if(gamemode[0]=='u' || gamemode[0]=='U'){   
        	ConnectFourPlusUndo undo;
        	undo.playGame();
        	c=0;
        }  
        else{
            cerr<<"!!!FALSE GAME MODE PLEASE TRY AGAIN!!!\n";
        }                 
    }
	return 0;
}

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
Cell::Cell():position('A'),Crow(1),type('.'){} 			

Cell::Cell(char ttype,char tposition,int row):type(ttype),position(tposition),Crow(row){}

void Cell::operator-(){
	type+=32;
}
const bool Cell::operator==(const Cell &other)const{
	if(type==other.getterType() && position==other.getterPosition() && Crow==other.getterRow()){
		return true;
	}
	return false;
}
const bool Cell::operator==(char cchar)const{
	if(type==cchar) return true;
	return false;
}
const bool Cell::operator!=(char cchar)const{
	if(type==cchar) return false;
	return true;
}
const Cell& Cell::operator=(char otype){
	type=otype;
	return *this;
}
const Cell& Cell::operator=(const Cell & other){
	type=other.getterType();
	Crow=other.getterRow();
	position=other.getterPosition();
	return *this;
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
int ConnectFourAbstract::currentWH(){
	/* some code*/
}
int ConnectFourPlusUndo::playGame(){//************************************************************************************************************************************************* UNUTMA UNUTMA UNUTMA
  
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
    char *usedCells; 
    usedCells = new char[col*row];
	int usedCellCount = 0;
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
            if(((adres[0]=='L' && adres[1]=='O' && adres[2]=='A' && adres[3]=='D') || (adres[0]=='S' && adres[1]=='A' && adres[2]=='V' && adres[3]=='E'))&& adres[4]==' '){
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
			    cout<<" cell:"<<usedCells[usedCellCount-1]<<"sayi: "<<sayi<<endl;
			    usedCellCount--;
			    for(int j=0;j<row;j++)cout<<colPositions[j]<<" ";
			    settercolPosUndo(sayi);
				cout<<endl;
			    for(int j=0;j<row;j++)cout<<colPositions[j]<<" ";
			    cout<<endl;
			    gameCells[colPositions[sayi]][sayi].setterType('.');
            	//i-=2;
            	current_print();
            	//i--;
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
	return 0;
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

		//if(i!=1 && i%2==1)cout<<"livingcell:"<<getterLivinCell()<<endl;
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
	        
	        //num_livingCell(); // bitme koşulu sağlanmış mu diye kontrol ediyorum
    		statuVH=endgame();//verticalhorizontal();
    		
    		//statuD=diagonal();
    
    		if((statuVH==1 )&& gameType=='P')cout<<"\n\n--- CONGRULATİONS -P1- Win The Game ---\n";// bitme mesajları
			else if((statuVH==2 )&& gameType=='P')cout<<"\n\n--- CONGRULATİONS -P2- Win The Game ---\n";
			else if((statuVH==2 )&& gameType=='C' && i%2==0)cout<<"\n\n--- COMPUTER- Win The Game ---\n";
			else if((statuVH==2 )&& gameType=='C' && i%2==1)cout<<"\n\n--- CONGRULATİONS -YOU- Win The Game ---\n";																									
	       
	        current_print();
	        //cout<<"vh"<<statuVH<<"d"<<statuD<<endl;if(statuVH==1 || statuD==1)exit(1);
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
		

       // okuma>>num;setterLivingCell(num);
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
        //exit(1);
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
int ConnectFourPlus::endgame(){
    
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

int ConnectFourDiag::endgame(){ //Diag class ı için çapraz bitme koşulunu kontrol ediyor
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

void ConnectFourPlus::auxiliarXXX_OOO(int &statu,int &statu2,int i,int j,char xo,int &sayi){
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
void ConnectFourPlus::auxiliarXX_X_OO_O(int &statu,int &statu2,int i,int j,char xo,int &sayi){
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
void ConnectFourPlus::auxiliarX_XX_O_OO(int &statu,int &statu2,int i,int j,char xo,int &sayi){
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
void ConnectFourPlus::auxiliarVertical(int &statu,int &statu2,int i,int j,char xo,int &sayi){
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
char ConnectFourDiag::play_computer(){
int i,j,sayi= 0;
    int statu=1,statu2=1; // Uygun ihtimaller sağlandığında ve oynan istenen yer legal bir konum ise bu kontrolleri yaparak hamle yapıyorum.
    for(i=0;i<col;i++){
        for(j=0;j<row;j++){            
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
char ConnectFourPlus::play_computer(){
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