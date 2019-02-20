#ifndef CONNECTFOURDIAG_H
#define CONNECTFOURDIAG_H

#include "ConnectFourAbstract.h"

namespace CSE241_151044026
{
	class ConnectFourDiag:public ConnectFourAbstract
	{
	protected:
		int endgame() override;
		char play_computer() override;
	};
}
#endif
