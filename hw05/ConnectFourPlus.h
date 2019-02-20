#ifndef CONNECTFOURPLUS_H
#define CONNECTFOURPLUS_H

#include "ConnectFourAbstract.h"	

namespace CSE241_151044026
{
	class ConnectFourPlus:public ConnectFourAbstract
	{
	protected:
		int endgame()override ;
	    char play_computer() override;
	    //  computer hamleleri için yardımcı fonksiyonlar. play_computer fonksiyonun yardımcı fonksiyonları
	    void auxiliarXXX_OOO(int &statu,int &statu2,int i,int j,char xo,int &sayi); 
		void auxiliarXX_X_OO_O(int &statu,int &statu2,int i,int j,char xo,int &sayi); 
		void auxiliarX_XX_O_OO(int &statu,int &statu2,int i,int j,char xo,int &sayi);
		void auxiliarVertical(int &statu,int &statu2,int i,int j,char xo,int &sayi);
	};
}
#endif