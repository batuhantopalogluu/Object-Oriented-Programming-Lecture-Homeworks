/*                  BATUHAN TOPALOĞLU 151044026               */
/*                            HW 5                            */

/*   Fonksiyonlarda ki bütün Row ve Col değerleri normal ters kurgulanmış vaziyett    */      
#ifndef CONNECTFOURABSTRACT_H
#define CONNECTFOURABSTRACT_H

#include <string>
#include "Cell.h"
using std::string;


namespace CSE241_151044026
{
    struct WH //current width and height of the board
    {
        int Srow;
        int Scol;  
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

        virtual bool read_file(const string & filename,int &i);//load yapınca sıranın kimde olduğu değişebileceği için i yi referance gönderiyorum
    	virtual void write_file(const string & filename,int i)const;

        int map_statu() const; // bitme koşullarının sağlanıp sağlanmadığını kontrol eden fonksiyonlar
        
        int numberCheck(string &size,char rowOrCol);//alınan inputun rakamlar oluşup oluşmadığını kontrol eden fonksiyon //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++ & const kontrolü yapıldı
        virtual int endgame() = 0;

        void current_print()const; //displays the current board	   
       
        inline int gettercolPos(int hedef){return colPositions[hedef];}
        inline void settercolPos(int h){colPositions[h]--;}

        int play_user(const char hedef[],int &i);   //position and it plays the user. i fonksiyon içinde değiştiği için reference gönderiyorum
        virtual char play_computer() = 0;    //The class will have two functions named play that plays the game for a single time step. First
    											//function does not take a parameter and it plays the computer. The second function takes a cell    
        void resize();
        WH currentWH();//       
    	int row;
    	int col;
    	char gameType;
    	int * colPositions;
    	Cell ** gameCells;		
    };
}

#endif
