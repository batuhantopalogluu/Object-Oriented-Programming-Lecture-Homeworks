#include "ConnectFourPlusUndo.h"// içinde ConnectFourAbstract ve ConnectFourPlus'ı include ettiği için ben tekrardan etmiyorum
#include "ConnectFourDiag.h"


using namespace CSE241_151044026;

int main(int argc, char const *argv[]){

    std::cout<<"________________ ConnectFour____________________"<<std::endl;															
    char gamemode[10];
    int c=1;    
    while(c==1){ // hatalı inputlarda tekrar input alıyorum
       
        std::cout<<"OYUN MODUNU SEÇİNİZ"<<std::endl<<"'P'-ConnectFourPlus"<<"\t"<<"'D'-DIAGONAL"<<"\t"<<"'U'-UNDO\n";
        std::cin>>gamemode;

        if((gamemode[0]=='p' || gamemode[0]=='P') && gamemode[1]=='\0'){
            ConnectFourPlus plus;
            plus.playGame();
            c=0;
        }

        if((gamemode[0]=='d' || gamemode[0]=='D') && gamemode[1]=='\0'){   
			ConnectFourDiag diag;   
			diag.playGame();						
			c=0;  
        }  
  
        if((gamemode[0]=='u' || gamemode[0]=='U') && gamemode[1]=='\0'){   
        	ConnectFourPlusUndo undo;
        	undo.playGame();
        	c=0;
        }  
        else{
            std::cerr<<"!!!FALSE GAME MODE PLEASE TRY AGAIN!!!\n";
        }                 
    }
	return 0;
}
