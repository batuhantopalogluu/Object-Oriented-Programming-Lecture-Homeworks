#ifndef CELL_H
#define CELL_H

namespace CSE241_151044026
{
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
}
#endif
