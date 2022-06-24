//---------------------------------------------------------------------------

#pragma hdrstop

#include "Rect.h"

#pragma package(smart_init)

Rect::Rect() : D({0, 0}), Razm({0, 0}), St({clBlue, clWhite, psSolid, bsSolid, 1}) { }

Rect::Rect(TPoint P, TPoint R, Style S) : D(P), Razm(R), St(S) { }


bool Rect::Sel(int X, int Y)
{
	return X > D.X && Y > D.Y && X < Razm.X && Y < Razm.Y;
}

void Rect::Draw(TCanvas* Canva)
{
	Canva->Pen->Color = St.Color1;
	Canva->Brush->Color = St.Color2;
	Canva->Pen->Style = St.PenStyle;
	Canva->Brush->Style = St.BrushStyle;
	Canva->Pen->Width = St.Lsh;

	Canva->Rectangle(D.X, D.Y, Razm.X, Razm.Y);
}
