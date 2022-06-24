//---------------------------------------------------------------------------

#ifndef RectH
#define RectH

#include "Fig.h"
#include "Style.h"

class Rect : public Fig
{
public:
	Rect();
	Rect(TPoint, TPoint, Style);

    bool Sel(int, int) override;
	void Draw(TCanvas*) override;

private:
	Style St;

	TPoint D;
	TPoint Razm;
};

#endif
