//---------------------------------------------------------------------------

#pragma hdrstop

#include "Krug.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

Krug::Krug() : D({0, 0}), Rad(0), St({clBlue, clWhite, psSolid, bsSolid, 1}) { }
Krug::Krug(TPoint P, int R, Style S) : D(P), Rad(R), St(S) { }

int Pow(int I1) { return I1 * I1; }

bool Krug::Sel(int X, int Y)
{
    return Pow(X - D.X) + Pow(Y - D.Y) <= Pow(Rad);
}

void Krug::Draw(TCanvas* Canva)
{
	Canva->Pen->Color = St.Color1;
	Canva->Brush->Color = St.Color2;
	Canva->Pen->Style = St.PenStyle;
	Canva->Brush->Style = St.BrushStyle;
	Canva->Pen->Width = St.Lsh;

	Canva->Ellipse(D.X - Rad, D.Y - Rad, D.X + Rad, D.Y + Rad);
}
