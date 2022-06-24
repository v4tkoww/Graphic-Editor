//---------------------------------------------------------------------------

#ifndef DugaH
#define DugaH

#include "Fig.h"
#include "Style.h"

class Duga : public Fig
{
public:
	Duga();
	Duga(TPoint, TPoint, TPoint, Style);

	void Draw(TCanvas*) override;

private:
    Style St;

    TPoint D1;
	TPoint D2;
	TPoint D3;
};

int SubLin(int, int, float);

#endif
