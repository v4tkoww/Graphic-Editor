//---------------------------------------------------------------------------

#pragma hdrstop

#include "Style.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

Style::Style() : Color1(clBlue), Color2(clWhite), PenStyle(psSolid), BrushStyle(bsSolid), Lsh(1) { }

Style::Style(TColor C1, TColor C2, TPenStyle Ps, TBrushStyle Bs, int L) : Color1(C1), Color2(C2), PenStyle(Ps), BrushStyle(Bs), Lsh(L) { }
