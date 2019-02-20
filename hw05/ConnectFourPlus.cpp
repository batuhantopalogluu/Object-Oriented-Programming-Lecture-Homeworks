#include "ConnectFourPlus.h"

namespace CSE241_151044026{

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
}