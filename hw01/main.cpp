/* 
 * File:   main.cpp
 * Author: batuhan
 *
 * Created on September 18, 2017, 8:07 AM
 */

#include <iostream>                      
#include <cstdlib>
#include<limits>/*rakam beklerken karakter girme durumunu engellemek için kullandým*/

using namespace std;

int mapstatu(char array[][20],int ilkb);/*map'in herhangi bir kazanma durumu olmadan dolmuþ olmasýný kontrol eden fonksiyon*/
void init(char  arr[][20],int yer[],int ilkb,int gametype);/*oyunun akýþýnýn iþlediði fonksiyon*/
void printmaze(char array[][20],int yer[],int ilkb,int gstatu = 0,int gstatu2 = 0,int gstatu3 = 0,int gametype = 0);/*map'i farklý durumlarý kontrol ederek ekrana basan fonksiyon*/
int domaze(int mapsize ,int gametype);/*baþlangýçta istenilen boyutlarda map'i '.' ile doldurur ve oyunun iþleyici fonksiyonlarýný çaðýrýr*/
int verticalhorizontal(char array[][20],int yer[],int ilkb);/*yatay ve dikey bitme durumlarýný kontrol eden fonksiyon*/
int diagonal(char array[][20],int yer[],int ilkb);/*çapraz bitme durumlarýný kontrol eden fonksiyon , bitip bitmeme ve hangi kullanýcýnýn bittiðini return ediyor*/	
char computer(char array[][20],int ilkb); /*single player modunda karþý hamlelere karar veren fonksiyon, hamle yapýlacak yeri return ediyor*/

int main() {
    int a;
    int b;
    b=0;
    while(b==0){
        cout<<"Enter map size maximum 20 and it must be even number...\n";
        /*hatalý giriþleri burada kontrol ediyorum*/
        while(!(cin >> a)){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input.  Try again:\n";
        }
        if(a<=2){
            cout<<"!!! please enter a number bigger or equal than 4\n";
        }
        else if(a%2==1){ 
            cout<<"!!! please enter a even number !!!\n";
        }
        else if(a>20){
            cout<<"!!! You can enter a maximum of 20 !!! \n";
        }
        else b=1;//legal boyut girince döngüyü kýrýp devam ediyorum
    }
    
    system("clear"); // ekraný temiz tutup oyunun daha güzel gözükmesi için ekraný temizliyorum
    char gameType;
    int c=1;
    while(c==1){//dahalý oyun tipinde tekrar tekrar input almak için burayý bir loop a soktum
        cout<<"CHOOSE YOUR GAME TYPE"<<endl<<"'C'-SINGLE PLAYER "<<"\t"<<"'P'-MULTIPLAYER\n" ;
        cin>>gameType;
        switch(gameType){
            /*oyun tipine göre diðer fonksiyonlarý çaðýrýyorum*/
            case 'c':
            case 'C': cout<<"******SINGLE PLAYER*******\n";
            int i;
                for(i=0;i<26;i++)cout<<"*";cout<<endl;
                c=0;
                domaze(a,1);
                break;
            case 'p':
            case 'P': cout<<"******MULTIPLAYER********\n";

                for(i=0;i<25;i++)cout<<"*";cout<<endl;
                c=0;
                domaze(a,2);
                break;

            default:
                cout<<"!!!FALSE GAME TYPE PLEASE SELECT AGAIN!!!\n";
                break;
        }
    
    }
    return 0;
}
///////maxsize 20 boyutunda array oluþturuyorum ancak bunun istenilen kadarýnda iþlem yapýyorum//////////////////////
int domaze(int a, int gametype){
    
    char arr[20][20];
    int yer[8];  
    int i,j;
    for(i=0;i<a;i++){
        for(j=0;j<a;j++){
            arr[i][j]='.';//alýnan boyuta göre hücrelere '.' atamasý yapýp o boyutlara göre ana fonksiyonlarý çaðýrýyorum
        } 
    } 
    for(i=0;i<8;i++)
        yer[i]=-1;
    printmaze(arr,yer,a);
    init(arr,yer,a,gametype);
    
    return 0;
}
/// Map'i  ve kazanma durumlarý mesajlarýný ekrana basan fonksiyon
void printmaze(char array[][20],int yer[],int ilkb,int gstatu ,int gstatu2,int gstatu3,int gametype){
    
    system("clear"); /*her hamlede ekraný daha temiz durmasý için temizliyorum*/
    int user=gstatu%10; /*return deðerin birler basamaðý user bilgisini taþýdýðý böyle bir þey yapýyorum*/
    if(user==0) user=gstatu3%10;
    if((gstatu>10 || gstatu3>10)&& gametype == 2) cout<<"\n\n--- CONGRULATÝONS user "<<user<<" Win The Game ---\n\n";
    if((gstatu>10 || gstatu3>10)&& gametype == 1){
        if(user==1) cout<<"\n\n--- CONGRULATÝONS YOU Win The Game ---\n\n";
        if(user==2) cout<<"\n\n--- CONGRULATÝONS COMPUTER Win The Game ---\n\n";
    } 
    if(gstatu2==1) cout<<"\n\n--- MAPE  FULL GAME FINISHED ---\n\n";
    char harfler[41]={"a b c d e f g h i j k l m n o p q r s t"};
    int i;
    for(i=0;i<2*ilkb;i++)
        cout<<harfler[i];
    
    cout<<endl;
     if(gstatu>10 || gstatu3>10){  /*oyunu bir kazanan olduðunda kazanma durmunu saðlayan hücleri küçük harfe çevirdiðim yer*/
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
///// programýn ana oynayýcý fonksiyonu 
void init(char  arr[][20],int yer[],int ilkb,int gametype){
    
    int c;
    int count[ilkb]; // her sütün için en son hangi saturýný atama yaptýðým bilgisini tutmak için bir array kullanýyorum
    for(c=0;c<ilkb;c++) // ve ilk olarak bütün elemanlar map boyutuna göre en son satýrý göstermesi için dolduruluyor
        count[c]=ilkb-1;
    ////////////////////////////////////////////////////////////////////////////
    char hedef;
    
    for(int i=1;i!=-1;i++){
        if(i%2==1 && gametype == 2) cout<<"It's Your Turn USER 1...";
        if(i%2==0 && gametype == 2) cout<<"It's Your Turn USER 2...";
        if(i%2==1 && gametype == 1) cout<<"It's Your Turn"; //single player modu için
        
        if (gametype == 2 || (gametype ==1 && i%2==1))cin>>hedef; // oynanmak istenilem hedef sutunu burada alýyorum
        else if (gametype ==1 && i%2==0){
            hedef=computer(arr,ilkb); // single modunda bilgisayarýn hamlelerini yardýmcý fonksiyondan alýyorum
        }
        char atanacak;
        if(i%2==1)
                atanacak='X';
        if(i%2==0)
                atanacak='O';
        /////////////////// HEDEFÝ DEÐÝÞTÝRME KISMI/////////////////////////////
        int sayi;
        // harfe göre sütün  seçiyorum
        if(hedef=='a'||hedef=='A')sayi = 0;
        else if((hedef=='b'||hedef=='B')&& ilkb>1) sayi = 1;
        else if((hedef=='c'||hedef=='C')&& ilkb>2) sayi = 2;
        else if((hedef=='d' || hedef=='D')&& ilkb>3) sayi = 3;
        else if((hedef=='e' || hedef=='E')&& ilkb>4) sayi = 4;
        else if((hedef=='f' || hedef=='F')&& ilkb>5) sayi = 5;          
        else if((hedef=='g' || hedef=='G')&& ilkb>6) sayi = 6;
        else if((hedef=='h' || hedef=='H')&& ilkb>7) sayi = 7;
        else if((hedef=='i' || hedef=='I')&& ilkb>8) sayi = 8;
        else if((hedef=='j' || hedef=='J')&& ilkb>9) sayi = 9;
        else if((hedef=='k' || hedef=='K')&& ilkb>10) sayi = 10;
        else if((hedef=='l' || hedef=='L')&& ilkb>11) sayi = 11;
        else if((hedef=='m' || hedef=='M')&& ilkb>12) sayi = 12;    
        else if((hedef=='n' || hedef=='N')&& ilkb>13) sayi = 13;
        else if((hedef=='o' || hedef=='O')&& ilkb>14) sayi = 14;        
        else if((hedef=='p' || hedef=='P')&& ilkb>15) sayi = 15;
        else if((hedef=='q' || hedef=='Q')&& ilkb>16) sayi = 16;
        else if((hedef=='r' || hedef=='R')&& ilkb>17) sayi = 17;
        else if((hedef=='s' || hedef=='S')&& ilkb>18) sayi = 18;
        else if((hedef=='t' || hedef=='T')&& ilkb>19) sayi = 19;
        else if((hedef=='u' || hedef=='U')&& ilkb>20) sayi = 20;        
        
        else { // hatalý hedef durumunda dögüyü bir tur geri alýyorum ki user deðiþtirmeden ayný kiþiden tekrar hedef alsýn
            i--;
            cout<<"!!! Illegal target Please try again\n";
            continue;
        }
        if(count[sayi]==-1){ //dolmuþ sütuna eriþmek istenildiðinde çalýþan kýsým
            i--; 
            continue;
        }
        arr[count[sayi]][sayi]=atanacak; //hedef sütundaki geçerli yeri deðiþtiriyorum
        count[sayi]--;  // sütuna atama yapýldýðý için son lokasyonu bir üste çekiyorum
        int statu,statu2,statu3;
        statu=verticalhorizontal(arr,yer,ilkb); // bitme durumlarýný yardýmcý fonksiyonlarla kontrol edip duruma göre oyunu bitiriyorum
        statu2=mapstatu(arr,ilkb);
        statu3=diagonal(arr,yer,ilkb);
        printmaze(arr,yer,ilkb,statu,statu2,statu3,gametype);
        if(statu>10 || statu2 == 1 || statu3 >10) break;
    }
}
//////mapi gezerek yatay veya dikey yönde kazanma durumunu kontrol eder/////////
int verticalhorizontal(char arr[][20],int yer[],int ilkb){
    
    int i,j;
    for(i=0;i<ilkb;i++){// yatayý tarayan kýsým
        for(j=0;j<ilkb;j++){
            if(arr[i][j]=='X'){
                if(arr[i][j+1]=='X' && arr[i][j+2]=='X' && arr[i][j+3]=='X'){
                    yer[1]=j,yer[3]=j+1,yer[5]=j+2,yer[7]=j+3;
                    yer[0]=i,yer[2]=i,yer[4]=i,yer[6]=i;
                    return 11;
                }
            }
            else if(arr[i][j]=='O' && arr[i][j+1]=='O' && arr[i][j+2]=='O' && arr[i][j+3]=='O'){
                yer[1]=j,yer[3]=j+1,yer[5]=j+2,yer[7]=j+3;
                yer[0]=i,yer[2]=i,yer[4]=i,yer[6]=i;
                return 12;
            }
            /// dikey taramayý yapan kýsým
            else if(arr[i][j]=='X' && arr[i+1][j]=='X' && arr[i+2][j]=='X' && arr[i+3][j]=='X'){
                    yer[1]=j,yer[3]=j,yer[5]=j,yer[7]=j;
                    yer[0]=i,yer[2]=i+1,yer[4]=i+2,yer[6]=i+3;
                    return 11;
            }
            else if(arr[i][j]=='O' && arr[i+1][j]=='O' && arr[i+2][j]=='O' && arr[i+3][j]=='O'){
                yer[1]=j,yer[3]=j,yer[5]=j,yer[7]=j;
                yer[0]=i,yer[2]=i+1,yer[4]=i+2,yer[6]=i+3;
                return 12;
            }
        }
    }
    return 0;
}
//////////çapraz bitme durumunu kontrol eder return deðeri 11 user 1 / 12 user 2 kazanma durumlarý /////////////////////
int diagonal(char arr[][20],int yer[], int ilkb){
    int i,j;
    for(i=0;i<ilkb;i++){
        for(j=0;j<ilkb;j++){
            if(arr[i][j]=='X' && arr[i+1][j+1]=='X' && arr[i+2][j+2]=='X' && arr[i+3][j+3]=='X'){ // sað üsten sað alta tarama yapan kýsým
                yer[0]=i,yer[1]=j,yer[2]=i+1,yer[3]=j+1,yer[4]=i+2,yer[5]=j+2,yer[6]=i+3,yer[7]=j+3;
                return 11;
            }
            if(arr[i][j]=='O' && arr[i+1][j+1]=='O' && arr[i+2][j+2]=='O' && arr[i+3][j+3]=='O'){ 
                 yer[0]=i,yer[1]=j,yer[2]=i+1,yer[3]=j+1,yer[4]=i+2,yer[5]=j+2,yer[6]=i+3,yer[7]=j+3;
                return 12;
            }
            if(arr[i][j]=='X' && arr[i+1][j-1]=='X' && arr[i+2][j-2]=='X' && arr[i+3][j-3]=='X'){// sað üstten  sol alta tarama yapan kýsým 
                yer[0]=i,yer[1]=j,yer[2]=i+1,yer[3]=j-1,yer[4]=i+2,yer[5]=j-2,yer[6]=i+3,yer[7]=j-3;
                return 11;
            }
            if(arr[i][j]=='O' && arr[i+1][j-1]=='O' && arr[i+2][j-2]=='O' && arr[i+3][j-3]=='O'){ 
                yer[0]=i,yer[1]=j,yer[2]=i+1,yer[3]=j-1,yer[4]=i+2,yer[5]=j-2,yer[6]=i+3,yer[7]=j-3;
                return 12;
            }
        }
    }
    return 0;
}
////// Tüm map'in kazanan user olmaksýzýn dolma durumunu kontrol eden fonksiyon ////////////////////////
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
//////// single player modunda bilgisayarýn hedeflerine karar veren fonksiyon
char computer(char arr[][20],int ilkb){

    int i,j,sayi= 0;
    int statu=1,statu2=1;
    
    for(i=0;i<ilkb;i++){
        for(j=0;j<ilkb;j++){
            /// XXX. / OOO. / .OOO / .XXX  DURUMLARINDA OYNAMA
            if(statu==1 && arr[i][j]=='X' && arr[i][j+1]=='X' && arr[i][j+2]=='X' &&(arr[i+1][j+3]=='X' || arr[i+1][j+3]=='O' || i+1== ilkb)){
                if((arr[i][j+3]=='X' || arr[i][j+3]=='O' ) && j > 0){
                    sayi= j-1;
                    statu=0;
                }
                else{
                    sayi=j+3;
                    statu=0;
                }
            }
            else if(statu==1 && arr[i][j]=='O' && arr[i][j+1]=='O' && arr[i][j+2]=='O' &&(arr[i+1][j+3]=='X' || arr[i+1][j+3]=='O' || i+1==ilkb)){
                if((arr[i][j+3]=='X' || arr[i][j+3]=='O' ) && j > 0){
                    sayi= j-1;
                    statu=0;
                }
                else {
                    sayi=j+3;
                    statu=0;
                }
            }
            //// XX.X / OO.O DURUMLARINDA OYNAMA
            else if(statu==1 && arr[i][j]=='X' && arr[i][j+1]=='X' && arr[i][j+3]=='X' &&(arr[i+1][j+2]=='X' || arr[i+1][j+2]=='O' || i+1== ilkb)){
                if((arr[i][j+2]=='X' || arr[i][j+2]=='O' ) && j > 0){ 
                    sayi= j-1;
                    statu2=0;
                }    
                else 
                {
                    sayi=j+2;
                    statu=0;
                }
            }
            else if(statu==1 && arr[i][j]=='O' && arr[i][j+1]=='O' && arr[i][j+3]=='O' &&(arr[i+1][j+2]=='X' || arr[i+1][j+2]=='O' || i+1== ilkb)){
                if((arr[i][j+2]=='X' || arr[i][j+2]=='O' ) && j > 0){ 
                    sayi= j-1;
                    statu2=0;
                }    
                else 
                {
                    sayi=j+2;
                    statu=0;
                }    
            }
            //X.XX / O.OO DURUMLARINDA OYNAMA ///
            else if(statu==1 && arr[i][j]=='X' && arr[i][j+2]=='X' && arr[i][j+3]=='X' &&(arr[i+1][j+1]=='X' || arr[i+1][j+1]=='O' || i+1== ilkb)){
                if((arr[i][j+1]=='X' || arr[i][j+1]=='O' ) && j > 0){ 
                    sayi= j-1;
                    statu2=0;
                }    
                else 
                {
                    sayi=j+1;
                    statu=0;
                }
            }
            else if(statu==1 && arr[i][j]=='O' && arr[i][j+2]=='O' && arr[i][j+3]=='O' &&(arr[i+1][j+1]=='X' || arr[i+1][j+1]=='O' || i+1== ilkb)){
                if((arr[i][j+1]=='X' || arr[i][j+1]=='O' ) && j > 0){ 
                    sayi= j-1;
                    statu2=0;
                }    
                else 
                {
                    sayi=j+1;
                    statu=0;
                }
            }
            ////////////////// ÇAPRAZ DURUMLAR ÝÇÝN OYNAMA
            else if(statu==1 && arr[i][j]=='X' && arr[i+1][j+1]=='X' && arr[i+2][j+2]=='X' && (arr[i+4][j+3]=='X' || arr[i+4][j+3]=='O' || i+4==ilkb)){ 
                if((arr[i+3][j+3]=='X' || arr[i+3][j+3]=='O')&&(arr[i][j-1]=='X' || arr[i][j-1]=='O') && i>0 && j>0 ){
                    sayi=j-1;
                    statu=0;         //    .         |   X
                }                    //      X       |    X
                else{                //       X      |     X
                    sayi=j+3;        //        X     |      .
                    statu=0;         
                }
            }
            else if(statu==1 && arr[i][j]=='O' && arr[i+1][j+1]=='O' && arr[i+2][j+2]=='O' && (arr[i+4][j+3]=='X' || arr[i+4][j+3]=='O' || i+4==ilkb)){ 
                if((arr[i+3][j+3]=='X' || arr[i+3][j+3]=='O')&&(arr[i][j-1]=='X' || arr[i][j-1]=='O')&& i>0 && j>0){
                    sayi=j-1;   
                    statu=0;        //     .         |   O
                }                   //      O        |    O
                else{               //       O       |     O
                    sayi=j+3;       //        O      |      .
                    statu=0;        
                }
            }
            else if(statu==1 && arr[i][j]=='X' && arr[i+1][j-1]=='X' && arr[i+2][j-2]=='X' && (arr[i+4][j-3]=='X' || arr[i+4][j-3]=='O' || i+4==ilkb)){ 
                if((arr[i+3][j-3]=='X' || arr[i+3][j-3]=='O')&&(arr[i][j+1]=='X' || arr[i][j+1]=='O')&& j+1<=ilkb && i>0){ 
                    sayi=j+1;
                    statu=0;        //        .    |    X
                }                   //       X     |     X
                else{               //      X      |      X
                    sayi=j-3;       //     X       |       .
                    statu=0;        
                }
            }
            else if(statu==1 && arr[i][j]=='O' && arr[i+1][j-1]=='O' && arr[i+2][j-2]=='O' && (arr[i+4][j-3]=='X' || arr[i+4][j-3]=='O' || i+4==ilkb)){ 
                if((arr[i+3][j-3]=='X' || arr[i+3][j-3]=='O')&&(arr[i][j+1]=='X' || arr[i][j+1]=='O') && j+1<=ilkb && i>0){
                    sayi=j+1;
                    statu=0;        //        .     |     O
                }                   //       O      |      O
                else{               //      O       |       O
                    sayi=j-3;       //     O        |        .
                    statu=0;
                }
            }
            else if(statu==1 && arr[i][j]=='X' && arr[i+1][j+1]=='X' && arr[i+3][j+3]=='X' && (arr[i+3][j+2]=='X' || arr[i+3][j+2]=='O')){ 
                if(arr[i+2][j+2]=='X' || arr[i+2][j+2]=='O'){
                    sayi=j+3;
                    statu=0;        //     X    
                }                   //      X
                else{               //       .
                    sayi=j+2;       //        X
                    statu=0;
                }
            }
            else if(statu==1 && arr[i][j]=='O' && arr[i+1][j+1]=='O' && arr[i+3][j+3]=='O' && (arr[i+3][j+2]=='X' || arr[i+3][j+2]=='O')){ 
                if(arr[i+2][j+2]=='X' || arr[i+2][j+2]=='O'){
                    sayi=j+3;
                    statu=0;        //     O   
                }                   //      O
                else{               //       .
                    sayi=j+2;       //        O
                    statu=0;
                }
            }
            else if(statu==1 && arr[i][j]=='X' && arr[i+1][j-1]=='X' && arr[i+3][j-3]=='X' && (arr[i+3][j-2]=='X' || arr[i+3][j-2]=='O')){ 
                if(arr[i+2][j-2]=='X' || arr[i+2][j-2]=='O'){
                    sayi=j-3;
                    statu=0;        //          X    
                }                   //         X
                else{               //        .
                    sayi=j-2;       //       X
                    statu=0;
                }
            }
            else if(statu==1 && arr[i][j]=='O' && arr[i+1][j-1]=='O' && arr[i+3][j-3]=='O' && (arr[i+3][j-2]=='X' || arr[i+3][j-2]=='O')){ 
                if(arr[i+2][j-2]=='X' || arr[i+2][j-2]=='O'){
                    sayi=j-3;
                    statu=0;        //          O    
                }                   //         O
                else{               //        .
                    sayi=j-2;       //       O
                    statu=0;
                }
            }
            //// BÝRKAÇ DURUMU BÝLEREK AÇIK BIRAKIYORUM BÝLGÝSAYARA ÞANSIMIZ OLSUN///
            ////////////////DÝKEY OYNAMA ///////////
            else if(statu==1 && arr[i][j]=='X' && arr[i+1][j]=='X' && arr[i+2][j]=='X' && /*(arr[i-1][j]!='X' && arr[i-1][j]!='O' ) && */(i > 0 )){
                if(arr[i-1][j]=='X' || arr[i-1][j]=='O'){  
                     sayi=j+1;
                     statu2=0;
                }
                else {
                    sayi=j;
                    statu=0;
                }
            }
            else if(statu==1 && arr[i][j]=='O' && arr[i+1][j]=='O' && arr[i+2][j]=='O' && /*(arr[i-1][j]!='X' && arr[i-1][j]!='O' ) && */(i > 0 )){
                if(arr[i-1][j]=='X' || arr[i-1][j]=='O'){  
                    sayi=j+1;
                    statu2=0;
                }
                else {
                    sayi=j;
                    statu=0;
                }
            }
        }
    }
    ///// YENME DURUMUNU SAÐLAYACAK ÝHTÝMALLER OLMADIÐINDA OYNAYACAK KISIM
    if(statu==1){
        for(i=0;i<ilkb;i++){
            for(j=0;j<ilkb;j++){
               
                if(arr[i][j]=='X'){
                    int a=rand()%3;
                    if(i==0) sayi=j+1;
                    else if(a==0 && i>0 && statu2==1) sayi = j;
                    else if(a==1 && j+1 < ilkb) sayi= j+1; 
                    else if(a==2 && j>0) sayi=j-1;
                    
                }
            }
        }
    }
    char temp;///seçilen ekseni diðer fonksiyonun anlamasý için karakter hedefe çeviriyorum ve o þekilde return ediyorum
    for(temp=97,i=0;i<ilkb;temp++,i++){
        if(sayi==i) return temp;
    }
}
