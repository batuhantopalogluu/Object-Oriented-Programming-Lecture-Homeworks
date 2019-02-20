#include "Cell.h"

namespace CSE241_151044026
{
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
}