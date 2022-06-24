//---------------------------------------------------------------------------

#ifndef LineH
#define LineH

#include "Fig.h"
#include "Style.h"

class Line : public Fig
{
public:
	Line();
	Line(TPoint, TPoint, Style);

	void Draw(TCanvas*) override;

private:
	Style St;

	TPoint D1;
	TPoint D2;
};

#endif
