//---------------------------------------------------------------------------

#pragma hdrstop

#include "Line.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

Line::Line() : D1({0, 0}), D2({0, 0}), St(clBlue, clWhite, psSolid, bsSolid, 1) { }
Line::Line(TPoint d1, TPoint d2, Style style) : D1(d1), D2(d2), St(style) { }

void Line::Draw(TCanvas* Canva)
{
	Canva->Pen->Color = St.Color1;
	Canva->Pen->Width = St.Lsh;
	Canva->Pen->Style = St.PenStyle;

	Canva->MoveTo(D1.X, D1.Y);
    Canva->LineTo(D2.X, D2.Y);
}