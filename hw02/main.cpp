/* /
 * File:   main.cpp
 * Author: batuhan
 *
 * Created November 2, 2017, 8:07 AM
 */

#include <iostream>                      
#include <cstdlib>
#include <string>
#include <fstream>

using namespace std;

int mapstatu(char array[][20],int ilkb);/*map'in herhangi bir kazanma durumu olmadan dolmu� olmas�n� kontrol eden fonksiyon*/
void init(char  arr[][20],int yer[],int ilkb,int gametype);/*oyunun ak���n�n i�ledi�i fonksiyon*/
void printmaze(char array[][20],int yer[],int ilkb,int gstatu = 0,int gstatu2 = 0,int gstatu3 = 0,int gametype = 0);/*map'i farkl� durumlar� kontrol ederek ekrana basan fonksiyon*/
int domaze(int mapsize ,int gametype);/*ba�lang��ta istenilen boyutlarda map'i '.' ile doldurur ve oyunun i�leyici fonksiyonlar�n� �a��r�r*/
int verticalhorizontal(char array[][20],int yer[],const int & ilkb);/*yatay ve dikey bitme durumlar�n� kontrol eden fonksiyon*/
int diagonal(char array[][20],int yer[],const int & ilkb);/*�apraz bitme durumlar�n� kontrol eden fonksiyon , bitip bitmeme ve hangi kullan�c�n�n bitti�ini return ediyor*/	
char computer(char array[][20],int count[],const int  & ilkb); /*single player modunda kar�� hamlelere karar veren fonksiyon, hamle yap�lacak yeri return ediyor*/

int main() {
    int a=99;
    string p;
    decltype(a) b;
    b=0;
    while(b==0){       // 20 den b�y�k, tek say� , 4 den k���k ve harf veya rakamla beraber harf girilmesi durumlar�n� kontrol ediyorum
        decltype(a) statu=0;
        cout<<"Enter map size maximum 20 and it must be even number...\n";
        getline(cin,p);                                                                                                  
        if(p.length()==1){
            char c=p[0];
            int e=c-'0';
            if(e>=4 && e<=9){
                statu=1;
                a=e;
            }
        }
        else if(p.length()==2){
            char c=p[0];
            char d=p[1];
            int e=c-'0';
            int f=d-'0';
            if((e>=0 && e<=9) && (f>=0 && f<=9)){
                statu=1;
                a=e*10+f;
            }
        }                                                                                                      
        if(statu==1){                                                                                                 
            if(a<=2){
                cerr<<"!!! please enter a number bigger or equal than 4\n";
            }
            else if(a%2==1){ 
                cerr<<"!!! please enter a even number !!!\n";
            }
            else if(a>20){
                cerr<<"!!! You can enter a maximum of 20 !!! \n";
            }
            else if(a<=20)b=1;//legal boyut girince d�ng�y� k�r�p devam ediyorum
        }
    }
    //cin.ignore(1500,'\n');
    char gameType[10];
    int c=1;    // rakam veya birden fazla harf rakam konbinasyonun hatal� olarak girilmesi durumlarun� kontrol ediyorum
    while(c==1){//dahal� oyun tipinde tekrar tekrar input almak i�in buray� bir loop a soktum
       
        cout<<"CHOOSE YOUR GAME TYPE"<<endl<<"'C'-SINGLE PLAYER "<<"\t"<<"'P'-MULTIPLAYER\n" ;
        cin>>gameType;
        if(gameType[1]!='\0') gameType[0]='x';
        switch(gameType[0]){
            /*oyun tipine g�re di�er fonksiyonlar� �a��r�yorum*/
            case 'c':
            case 'C': cout<<"******SINGLE PLAYER*******\n";
            int i;
                for(i=0;i<26;i++)cout<<"*";
                cout<<endl;
                c=0;
                domaze(a,1);
                break;
            case 'p':
            case 'P': cout<<"******MULTIPLAYER********\n";

                for(i=0;i<25;i++)cout<<"*";
                cout<<endl;
                c=0;
                domaze(a,2);
                break;

            default:
                cerr<<"!!!FALSE GAME TYPE PLEASE SELECT AGAIN!!!\n";
                break;
        }
    
    }
    return 0;
}
///////maxsize 20 boyutunda array olu�turuyorum ancak bunun istenilen kadar�nda i�lem yap�yorum//////////////////////
int domaze(int a, int gametype){
    
    char arr[20][20];
    int yer[8];  
    int i,j;
    for(i=0;i<20;i++){
        for(j=0;j<20;j++){
            arr[i][j]='.';//al�nan boyuta g�re h�crelere '.' atamas� yap�p o boyutlara g�re ana fonksiyonlar� �a��r�yorum
        } 
    } 
    for(i=0;i<8;i++)
        yer[i]=-1;
    printmaze(arr,yer,a);
    init(arr,yer,a,gametype);
    
    return 0;
}
/// Map'i  ve kazanma durumlar� mesajlar�n� ekrana basan fonksiyon
void printmaze(char array[][20],int yer[],int ilkb,int gstatu ,int gstatu2,int gstatu3,int gametype){
    
    system("clear"); /*her hamlede ekran� daha temiz durmas� i�in temizliyorum*/
    int user=gstatu%10; /*return de�erin birler basama�� user bilgisini ta��d��� b�yle bir �ey yap�yorum*/
    if(user==0) user=gstatu3%10;
    if((gstatu>10 || gstatu3>10)&& gametype == 2) cout<<"\n\n--- CONGRULAT�ONS user "<<user<<" Win The Game ---\n\n";
    if((gstatu>10 || gstatu3>10)&& gametype == 1){
        if(user==1) cout<<"\n\n--- CONGRULAT�ONS YOU Win The Game ---\n\n";
        if(user==2) cout<<"\n\n--- CONGRULAT�ONS COMPUTER Win The Game ---\n\n";
    } 
    if(gstatu2==1) cout<<"\n\n--- MAPE  FULL GAME FINISHED ---\n\n";
    char harfler[41]={"a b c d e f g h i j k l m n o p q r s t"};
    int i;
    for(i=0;i<2*ilkb;i++)
        cout<<harfler[i];
    
    cout<<endl;
    if(gstatu>10 || gstatu3>10){  /*oyunu bir kazanan oldu�unda kazanma durmunu sa�layan h�cleri k���k harfe �evirdi�im yer*/
        for(i=0;i<8;i+=2){
            array[yer[i]][yer[i+1]]+=32;
        }
     }
    int j;
    int a=0,b=1;
      for(i=0;i<ilkb;i++){
        for(j=0;j<ilkb;j++){
            cout<<array[i][j]<<" ";
        }
        cout<<endl;
    }
}
///// program�n ana oynay�c� fonksiyonu 
void init(char  arr[][20],int yer[],int ilkb,int gametype){

    int c;
    int count[60]; // her s�t�n i�in en son hangi satur�n� atama yapt���m bilgisini tutmak i�in bir array kullan�yorum
    for(c=0;c<ilkb;c++) // ve ilk olarak b�t�n elemanlar map boyutuna g�re en son sat�r� g�stermesi i�in dolduruluyor
        count[c]=ilkb-1;
    string adres;
    char hedef[50];
    int firstcheck=0;
    char filename[50]; 
    decltype(firstcheck) size=0;
    for(int i=1;i!=-1;i++){

        size=0;        
	    int statu4 =1;
        for(auto h=0;h<50;h++)filename[h]='\0';
	    for(auto h=0;h<50;h++)hedef[h]='\0';	
        if(i%2==1 && gametype == 2) cout<<"It's Your Turn USER 1...\n";
        if(i%2==0 && gametype == 2) cout<<"It's Your Turn USER 2...\n";
        if(i%2==1 && gametype == 1) cout<<"It's Your Turn\n"; //single player modu i�in
        ////////***********************************************************************************************************************************************************************************
        if (i == 1 && firstcheck==0){
            getline(cin, adres);
            firstcheck=1;
        }
        if (gametype == 2 || (gametype ==1 && i%2==1)){    // B�y�k harflerle LOAD yazd�ktan sonra 1 bo�luk ve dosya ad� bekliyor, sadece LOAD yazmas� hatal� giri�. Olmayan dosyay� load etmeyi �al��ma durumunu kontrol ettim.
            getline(cin, adres);
            hedef[0]=adres[0];
            /////////////////// LOAD /////////////////////////////////////
            if(adres[0]=='L' && adres[1]=='O' && adres[2]=='A' && adres[3]=='D'){
			    for (auto a =4 ;a<50;a++){
            	    if(adres[a]==' ') {
						for(auto b=a+1;adres[b]!='\0';b++){
                            filename[size]=adres[b];
                            size++;
                        }
                        break;
                    }  
                }
                ifstream okuma(filename);
                if(okuma.is_open()){
	                okuma>>gametype;
	        		okuma>>ilkb;
	        		okuma>>i;
	        		for(auto a=0;a<ilkb;a++){
						for(auto b=0;b<ilkb;b++){
							okuma>>arr[a][b];
	        			}
	    			}
	    			for(auto a=0;a<ilkb;a++)okuma>>count[a];
            		printmaze(arr,yer,ilkb);	
	                okuma.close();
	            }
	            else cerr<<"!!!Invalid filename"; // olmayan dosyay� load etmeye �al��ma durumu.
                //for(int h=0;h<50;h++)adres[h]='\0';
                for(auto h=0;h<50;h++)hedef[h]='\0';
                statu4=0;
                i--;
                continue;
            }

            else if(adres[0]=='S' && adres[1]=='A' && adres[2]=='V' && adres[3]=='E'){ //b�y�k harflerle SAVE yazd�ktan bir bo�luk b�rakarak dosya ad�n� yazarsak o dosyay� a��yor. bir �ey girmeme durumu kontrol edildi
			    for (auto a =4 ;a<50;a++){
           			if(adres[a]==' ') {
						for(auto b=a+1;adres[b]!='\0';b++){
                            filename[size]=adres[b];
                            size++;
                        }
                    break;
                	}
                }
                //////////////////////////// SAVE //////////////////////////
                ofstream yazma(filename);
                if(yazma.is_open());
                yazma<<gametype<<endl;
                yazma<<ilkb<<endl;
                yazma<<i<<endl;
                for(auto a=0;a<ilkb;a++){
					for(auto b=0;b<ilkb;b++){
						yazma<<arr[a][b]<<' ';
        			}
        			yazma<<'\n';
    			}

    			for(auto a=0;a<ilkb;a++)yazma<<count[a]<<' ';
                yazma.close(); 
                statu4=0;
                i--;
                continue;
		
            }
            else if(adres[1]!='\0'){
                i--;
                cerr<<"!!! false target try again\n";
                continue;
            }
//*****************************************************************************************************************************************************************************************************
        }
 
       else if (gametype ==1 && i%2==0){
            hedef[0]=computer(arr,count,ilkb); // single modunda bilgisayar�n hamlelerini yard�mc� fonksiyondan al�yorum
        }
        char atanacak;
        if(i%2==1)
                atanacak='X';
        if(i%2==0)
                atanacak='O';
        /////////////////// HEDEF� DE���T�RME KISMI/////////////////////////////
        int sayi;
        // harfe g�re s�t�n  se�iyorum
        if(hedef[0]=='a'||hedef[0]=='A')sayi = 0;
        else if((hedef[0]=='b' || hedef[0]=='B')&& ilkb>1) sayi = 1;
        else if((hedef[0]=='c' || hedef[0]=='C')&& ilkb>2) sayi = 2;
        else if((hedef[0]=='d' || hedef[0]=='D')&& ilkb>3) sayi = 3;
        else if((hedef[0]=='e' || hedef[0]=='E')&& ilkb>4) sayi = 4;
        else if((hedef[0]=='f' || hedef[0]=='F')&& ilkb>5) sayi = 5;          
        else if((hedef[0]=='g' || hedef[0]=='G')&& ilkb>6) sayi = 6;
        else if((hedef[0]=='h' || hedef[0]=='H')&& ilkb>7) sayi = 7;
        else if((hedef[0]=='i' || hedef[0]=='I')&& ilkb>8) sayi = 8;
        else if((hedef[0]=='j' || hedef[0]=='J')&& ilkb>9) sayi = 9;
        else if((hedef[0]=='k' || hedef[0]=='K')&& ilkb>10) sayi = 10;
        else if((hedef[0]=='l' || hedef[0]=='L')&& ilkb>11) sayi = 11;
        else if((hedef[0]=='m' || hedef[0]=='M')&& ilkb>12) sayi = 12;    
        else if((hedef[0]=='n' || hedef[0]=='N')&& ilkb>13) sayi = 13;
        else if((hedef[0]=='o' || hedef[0]=='O')&& ilkb>14) sayi = 14;        
        else if((hedef[0]=='p' || hedef[0]=='P')&& ilkb>15) sayi = 15;
        else if((hedef[0]=='q' || hedef[0]=='Q')&& ilkb>16) sayi = 16;
        else if((hedef[0]=='r' || hedef[0]=='R')&& ilkb>17) sayi = 17;
        else if((hedef[0]=='s' || hedef[0]=='S')&& ilkb>18) sayi = 18;
        else if((hedef[0]=='t' || hedef[0]=='T')&& ilkb>19) sayi = 19;
        else if((hedef[0]=='u' || hedef[0]=='U')&& ilkb>20) sayi = 20;        
        
        else if(statu4==1) { // hatal� hedef durumunda d�g�y� bir tur geri al�yorum ki user de�i�tirmeden ayn� ki�iden tekrar hedef als�n
            i--;
            cerr<<"!!! Illegal target Please try again\n";
            continue;
        }
        
        if(count[sayi]==-1){ //dolmu� s�tuna eri�mek istenildi�inde �al��an k�s�m
            i--; 
            continue;
        }
        arr[count[sayi]][sayi]=atanacak; //hedef s�tundaki ge�erli yeri de�i�tiriyorum
        count[sayi]--;  // s�tuna atama yap�ld��� i�in son lokasyonu bir �ste �ekiyorum
        int statu,statu2,statu3;
        statu=verticalhorizontal(arr,yer,ilkb); // bitme durumlar�n� yard�mc� fonksiyonlarla kontrol edip duruma g�re oyunu bitiriyorum
        statu2=mapstatu(arr,ilkb);
        statu3=diagonal(arr,yer,ilkb);
        printmaze(arr,yer,ilkb,statu,statu2,statu3,gametype);
        if(statu>10 || statu2 == 1 || statu3 >10) break;
    }
}
//////mapi gezerek yatay veya dikey y�nde kazanma durumunu kontrol eder/////////
int verticalhorizontal(char arr[][20],int yer[],const int & ilkb){
    
    int i,j;
    for(i=0;i<ilkb;i++){// yatay� tarayan k�s�m
        for(j=0;j<ilkb;j++){
            if(j+3<ilkb && arr[i][j]=='X'&& arr[i][j+1]=='X' && arr[i][j+2]=='X' && arr[i][j+3]=='X'){
                    yer[1]=j,yer[3]=j+1,yer[5]=j+2,yer[7]=j+3;
                    yer[0]=i,yer[2]=i,yer[4]=i,yer[6]=i;
                    return 11;
            }
            if(j+3<ilkb && arr[i][j]=='O' && arr[i][j+1]=='O' && arr[i][j+2]=='O' && arr[i][j+3]=='O'){
                yer[1]=j,yer[3]=j+1,yer[5]=j+2,yer[7]=j+3;
                yer[0]=i,yer[2]=i,yer[4]=i,yer[6]=i;
                    return 12;
            }
            /// dikey taramay� yapan k�s�m
            if(i+3<ilkb && arr[i][j]=='X' && arr[i+1][j]=='X' && arr[i+2][j]=='X' && arr[i+3][j]=='X'){
                    yer[1]=j,yer[3]=j,yer[5]=j,yer[7]=j;
                    yer[0]=i,yer[2]=i+1,yer[4]=i+2,yer[6]=i+3;
                    return 11;
            }
            if(i+3<ilkb && arr[i][j]=='O' && arr[i+1][j]=='O' && arr[i+2][j]=='O' && arr[i+3][j]=='O'){
                yer[1]=j,yer[3]=j,yer[5]=j,yer[7]=j;
                yer[0]=i,yer[2]=i+1,yer[4]=i+2,yer[6]=i+3;
                return 12;
            }
        }
    }
    return 0;
}
//////////�apraz bitme durumunu kontrol eder return de�eri 11 user 1 / 12 user 2 kazanma durumlar� /////////////////////
int diagonal(char arr[][20],int yer[],const int & ilkb){
    int i,j;
    for(i=0;i<ilkb;i++){
        for(j=0;j<ilkb;j++){
            if(i+3<ilkb && j+3<ilkb && arr[i][j]=='X' && arr[i+1][j+1]=='X' && arr[i+2][j+2]=='X' && arr[i+3][j+3]=='X'){ // sa� �sten sa� alta tarama yapan k�s�m
                yer[0]=i,yer[1]=j,yer[2]=i+1,yer[3]=j+1,yer[4]=i+2,yer[5]=j+2,yer[6]=i+3,yer[7]=j+3;
                return 11;
            }
            if(i+3<ilkb && j+3<ilkb && arr[i][j]=='O' && arr[i+1][j+1]=='O' && arr[i+2][j+2]=='O' && arr[i+3][j+3]=='O'){ 
                 yer[0]=i,yer[1]=j,yer[2]=i+1,yer[3]=j+1,yer[4]=i+2,yer[5]=j+2,yer[6]=i+3,yer[7]=j+3;
                return 12;
            }
            if(i+3<ilkb && j-3>=0 && arr[i][j]=='X' && arr[i+1][j-1]=='X' && arr[i+2][j-2]=='X' && arr[i+3][j-3]=='X'){// sa� �stten  sol alta tarama yapan k�s�m 
                yer[0]=i,yer[1]=j,yer[2]=i+1,yer[3]=j-1,yer[4]=i+2,yer[5]=j-2,yer[6]=i+3,yer[7]=j-3;
                return 11;
            }
            if(i+3<ilkb && j-3>=0 && arr[i][j]=='O' && arr[i+1][j-1]=='O' && arr[i+2][j-2]=='O' && arr[i+3][j-3]=='O'){ 
                yer[0]=i,yer[1]=j,yer[2]=i+1,yer[3]=j-1,yer[4]=i+2,yer[5]=j-2,yer[6]=i+3,yer[7]=j-3;
                return 12;
            }
        }
    }
    return 0;
}
////// T�m map'in kazanan user olmaks�z�n dolma durumunu kontrol eden fonksiyon ////////////////////////
int mapstatu(char array[][20], int ilkb){
    
    int i,j,counter=0;
    for(i=0;i<ilkb;i++){
        for(j=0;j<ilkb;j++){
            if(array[i][j]=='X' || array[i][j]=='O'){
                counter++;
                if(counter==ilkb*ilkb){
                    return 1;
                }
            }
        }
    }
    return 0;
}
//////// single player modunda bilgisayar�n hedeflerine karar veren fonksiyon
char computer(char arr[][20],int count[],const int & ilkb){

    int i,j,sayi= 0;
    int statu=1,statu2=1; // Uygun ihtimaller sa�land���nda ve oynan istenen yer legal bir konum ise bu kontrolleri yaparak hamle yap�yorum.
    for(i=0;i<ilkb;i++){
        for(j=0;j<ilkb;j++){
            /// XXX. / OOO. / .OOO / .XXX  DURUMLARINDA OYNAMA
            if(statu==1 && arr[i][j]=='X' && arr[i][j+1]=='X' && arr[i][j+2]=='X' &&(arr[i+1][j+3]=='X' || arr[i+1][j+3]=='O' || i+1== ilkb)){
                
                if((arr[i][j+3]=='X' || arr[i][j+3]=='O' ) && j > 0 && count[j-1]!=-1){
                    sayi= j-1;
                    statu=0;
                }
                else if (j+3<ilkb && count[j+3]!=-1){
                    sayi=j+3;
                    statu=0;
                }
            }
            else if(statu==1 && arr[i][j]=='O' && arr[i][j+1]=='O' && arr[i][j+2]=='O' &&(arr[i+1][j+3]=='X' || arr[i+1][j+3]=='O' || i+1==ilkb)){
                if((arr[i][j+3]=='X' || arr[i][j+3]=='O' ) && j > 0 && count[j-1]!=-1){
                    sayi= j-1;
                    statu=0;
                }
                else if (j+3<ilkb && count[j+3]!=-1){
                    sayi=j+3;
                    statu=0;
                }
            }
            //// XX.X / OO.O DURUMLARINDA OYNAMA
            else if(statu==1 && arr[i][j]=='X' && arr[i][j+1]=='X' && arr[i][j+3]=='X' &&(arr[i+1][j+2]=='X' || arr[i+1][j+2]=='O' || i+1== ilkb)){
                if((arr[i][j+2]=='X' || arr[i][j+2]=='O' ) && j > 0 && count[j-1]!=-1){ 
                    sayi= j-1;
                    statu2=0;
                    statu=0;
                }    
                else if (j+2<ilkb && count[j+2]!=-1){
                    sayi=j+2;
                    statu=0;
                }
            }
            else if(statu==1 && arr[i][j]=='O' && arr[i][j+1]=='O' && arr[i][j+3]=='O' &&(arr[i+1][j+2]=='X' || arr[i+1][j+2]=='O' || i+1== ilkb)){
                if((arr[i][j+2]=='X' || arr[i][j+2]=='O' ) && j > 0 && count[j-1]!=-1){ 
                    sayi= j-1;
                    statu2=0;
                    statu=0;
                }    
                else if(j+2<ilkb && count[j+2]!=-1){
                    sayi=j+2;
                    statu=0;
                }    
            }
            //X.XX / O.OO DURUMLARINDA OYNAMA ///
            else if(statu==1 && arr[i][j]=='X' && arr[i][j+2]=='X' && arr[i][j+3]=='X' &&(arr[i+1][j+1]=='X' || arr[i+1][j+1]=='O' || i+1== ilkb)){
                if((arr[i][j+1]=='X' || arr[i][j+1]=='O' ) && j > 0 && count[j-1]!=-1){ 
                    sayi= j-1;
                    statu2=0;
                    statu=0;
                }    
                else if(j+1<ilkb && count[j+1]!=-1){
                    sayi=j+1;
                    statu=0;
                }
            }
            else if(statu==1 && arr[i][j]=='O' && arr[i][j+2]=='O' && arr[i][j+3]=='O' &&(arr[i+1][j+1]=='X' || arr[i+1][j+1]=='O' || i+1== ilkb)){
                if((arr[i][j+1]=='X' || arr[i][j+1]=='O' ) && j > 0 && count[j-1]!=-1){ 
                    sayi= j-1;
                    statu2=0;
                    statu=0;
                }    
                else if(j+1<ilkb && count[j+1]!=-1){
                    sayi=j+1;
                    statu=0;
                }
            }
            ////////////////// �APRAZ DURUMLAR ���N OYNAMA
            else if(statu==1 && arr[i][j]=='X' && arr[i+1][j+1]=='X' && arr[i+2][j+2]=='X' && (arr[i+4][j+3]=='X' || arr[i+4][j+3]=='O' || i+4==ilkb)){ 
                if((arr[i+3][j+3]=='X' || arr[i+3][j+3]=='O')&&(arr[i][j-1]=='X' || arr[i][j-1]=='O') && i>0 && j>0 && count[j-1]!=-1){
                    sayi=j-1;
                    statu=0;                                //    .         |   X
                }                                           //      X       |    X
                else if(j+3<ilkb && count[j+3]!=-1){        //       X      |     X
                    sayi=j+3;                               //        X     |      .
                    statu=0;         
                }
            }
            else if(statu==1 && arr[i][j]=='O' && arr[i+1][j+1]=='O' && arr[i+2][j+2]=='O' && (arr[i+4][j+3]=='X' || arr[i+4][j+3]=='O' || i+4==ilkb)){ 
                if((arr[i+3][j+3]=='X' || arr[i+3][j+3]=='O')&&(arr[i][j-1]=='X' || arr[i][j-1]=='O')&& i>0 && j>0 && count[j-1]!=-1){
                    sayi=j-1;   
                    statu=0;                                //     .         |   O
                }                                           //      O        |    O
                else if(j+3<ilkb && count[j+3]!=-1){        //       O       |     O
                    sayi=j+3;                               //        O      |      .
                    statu=0;        
                }
            }
            else if(statu==1 && arr[i][j]=='X' && arr[i+1][j-1]=='X' && arr[i+2][j-2]=='X' && (arr[i+4][j-3]=='X' || arr[i+4][j-3]=='O' || i+4==ilkb)){ 
                if((arr[i+3][j-3]=='X' || arr[i+3][j-3]=='O')&&(arr[i][j+1]=='X' || arr[i][j+1]=='O')&& j+1<ilkb && i>0 && count[j+1]!=-1){ 
                    sayi=j+1;
                    statu=0;                                 //        .    |         X
                }                                            //       X     |        X
                else if (j-3>=0 && count[j-3]!=-1){          //      X      |       X
                    sayi=j-3;                                //     X       |      .
                    statu=0;        
                }
            }
            else if(statu==1 && arr[i][j]=='O' && arr[i+1][j-1]=='O' && arr[i+2][j-2]=='O' && (arr[i+4][j-3]=='X' || arr[i+4][j-3]=='O' || i+4==ilkb)){ 
                if((arr[i+3][j-3]=='X' || arr[i+3][j-3]=='O')&&(arr[i][j+1]=='X' || arr[i][j+1]=='O') && j+1<ilkb && i>0 && count[j+1]!=-1){
                    cout<<"M1"<<endl;
                    sayi=j+1;
                    statu=0;        //        .     |         O
                }                   //       O      |        O
                else if(j-3>=0 && count[j-3]!=-1){
                cout<<"M2"<<endl;               //      O       |       O
                    sayi=j-3;       //     O        |      .
                    statu=0;
                }
            }
            else if(statu==1 && arr[i][j]=='X' && arr[i+1][j+1]=='X' && arr[i+3][j+3]=='X' && (arr[i+3][j+2]=='X' || arr[i+3][j+2]=='O')){ 
                if((arr[i+2][j+2]=='X' || arr[i+2][j+2]=='O')&& j+3<ilkb && count[j+3]!=-1){
                    sayi=j+3;
                    statu=0;                            //     X    
                }                                       //      X
                else if (j+2<ilkb && count[j+2]!=-1){   //       .
                    sayi=j+2;                           //        X
                    statu=0;
                }
            }
            else if(statu==1 &&  arr[i][j]=='O' && arr[i+1][j+1]=='O' && arr[i+3][j+3]=='O' && (arr[i+3][j+2]=='X' || arr[i+3][j+2]=='O')){ 
               if((arr[i+2][j+2]=='X' || arr[i+2][j+2]=='O')&& j+3<ilkb && count[j+3]!=-1){
                    
                    cout<<"P1"<<endl;
                    sayi=j+3;
                    statu=0;                                //     O   
                }                                           //      O
                else if (j+2<ilkb && count[j+2]!=-1 ){      //       .
                     sayi=j+2;                              //        O
                    statu=0;
                }
            }
            else if(statu==1 &&  arr[i][j]=='X' && arr[i+1][j-1]=='X' && arr[i+3][j-3]=='X' && (arr[i+3][j-2]=='X' || arr[i+3][j-2]=='O')){ 
                if((arr[i+2][j-2]=='X' || arr[i+2][j-2]=='O') && j-3>=0 && count[j-3]!=-1){
                    sayi=j-3;
                    statu=0;                                      //          X    
                }                                                 //         X
                else if (j-2>=0 && count[j-2]!=-1){               //        .
                    sayi=j-2;                                     //       X
                    statu=0;
                }
            }
            else if(statu==1 && arr[i][j]=='O' && arr[i+1][j-1]=='O' && arr[i+3][j-3]=='O' && (arr[i+3][j-2]=='X' || arr[i+3][j-2]=='O')){ 
                if((arr[i+2][j-2]=='X' || arr[i+2][j-2]=='O') && j-3>=0 && count[j-3]!=-1){
                    sayi=j-3;
                    statu=0;                              //          O    
                }                                         //         O
                else if (j-2>=0 && count[j-2]!=-1){       //        .
                    sayi=j-2;                             //       O
                    statu=0;                                 
                }
            }
            ////////////////D�KEY OYNAMA ///////////
            else if(statu==1 && arr[i][j]=='X' && arr[i+1][j]=='X' && arr[i+2][j]=='X' && (i > 0 )){
                if((arr[i-1][j]=='X' || arr[i-1][j]=='O') && j+1<ilkb && count[j+1]!=-1){  
                    sayi=j+1;
                    statu2=0;
                    statu=0;
                }
                else if(count[j]!=-1){
                    sayi=j;
                    statu=0;
                }
            }
            else if(statu==1 && i+2<ilkb && arr[i][j]=='O' && arr[i+1][j]=='O' && arr[i+2][j]=='O' && (i > 0 )){
               if((arr[i-1][j]=='X' || arr[i-1][j]=='O') && j+1<ilkb && count[j+1]!=-1){  
                    sayi=j+1;
                    statu2=0;
                    statu=0;
                }
                else if(count[j]!=-1){
                    sayi=j;
                    statu=0;
                }
            }
        }
    }
    ///// YENME DURUMUNU SA�LAYACAK �HT�MALLER OLMADI�INDA OYNAYACAK KISIM
    
    if(statu==1){
        for(i=0;i<ilkb;i++){
            for(j=0;j<ilkb;j++){
               
                if(arr[i][j]=='X' || arr[i][j]=='O'){
                    //int a=rand()%3;
                    if(i==0) sayi=j+1;
                    else if(/*a==0 &&*/ i>0 && statu2==1 && count[j]!=-1) sayi = j;
                    else if(/*a==1 &&*/ j+1 < ilkb && count[j+1]!=-1) sayi= j+1; 
                    else if(/*a==2 &&*/ j>0 && count[j-1]!=-1) sayi=j-1;
                    else if(arr[i][j]=='.') sayi=j;
                }
            }
        }
    }
 
    char temp;///se�ilen ekseni di�er fonksiyonun anlamas� i�in karakter hedefe �eviriyorum ve o �ekilde return ediyorum
    for(temp=97,i=0;i<ilkb;temp++,i++){
        if(sayi==i) return temp;
    }
}



