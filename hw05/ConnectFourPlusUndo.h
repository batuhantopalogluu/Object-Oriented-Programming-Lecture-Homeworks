#ifndef CONNECTFOURPLUSUNDO_H
#define CONNECTFOURPLUSUNDO_H
#include <iostream>
#include <fstream>
#include "ConnectFourPlus.h"

using namespace std;
namespace CSE241_151044026{

	class ConnectFourPlusUndo:public ConnectFourPlus
	{
	public:
		
		int playGame() override;	
	protected:
	    
	    inline void settercolPosUndo(int h){colPositions[h]++;} 
        bool read_file(const string & filename,int &i)override;//load yapınca sıranın kimde olduğu değişebileceği için i yi referance gönderiyorum
    	void write_file(const string & filename,int i)const override;
	    char *usedCells;
	    int usedCellCount = 0;       
	};
}
#endif