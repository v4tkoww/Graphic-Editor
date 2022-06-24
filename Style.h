//---------------------------------------------------------------------------

#ifndef StyleH
#define StyleH

#include <Graphics.hpp>

struct Style
{
	Style();
	Style(TColor, TColor, TPenStyle, TBrushStyle, int);

	TColor Color1;
	TColor Color2;
	TPenStyle PenStyle;
	TBrushStyle BrushStyle;
    int Lsh;
};

#endif
