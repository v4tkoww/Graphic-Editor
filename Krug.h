//---------------------------------------------------------------------------

#ifndef KrugH
#define KrugH

#include "Fig.h"
#include "Style.h"

class Krug : public Fig
{
public:
	Krug();
	Krug(TPoint, int, Style);

	bool Sel(int X, int Y) override;

	void Draw(TCanvas*) override;

private:
	Style St;

	TPoint D;
	int Rad;
};

#endif
