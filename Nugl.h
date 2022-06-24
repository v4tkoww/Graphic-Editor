//---------------------------------------------------------------------------

#ifndef NuglH
#define NuglH

#include "Fig.h"
#include "Style.h"

class Nugl : public Fig
{
public:
	Nugl();
	Nugl(TPoint, int, Style, int, bool);

	bool Sel(int, int) override;
	void Draw(TCanvas*) override;

private:
	Style St;

	TPoint D;
	int Rad;
	int NUgs;
	bool Des;

	void DrawNugl(TPoint*, TCanvas*);
    void DrawKrug(TCanvas*);
};

#endif
