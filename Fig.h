//---------------------------------------------------------------------------

#ifndef FigH
#define FigH

#include <Graphics.hpp>

class Fig
{
public:
	virtual bool Sel(int, int);

	virtual void Draw(TCanvas*) = 0;
};

#endif
