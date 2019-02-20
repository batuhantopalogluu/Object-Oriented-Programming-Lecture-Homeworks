#include "ConnectFourDiag.h"

namespace CSE241_151044026
{
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
}