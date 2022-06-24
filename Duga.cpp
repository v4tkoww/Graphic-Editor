//---------------------------------------------------------------------------

#pragma hdrstop

#include "Duga.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

#define DELTA 0.02

Duga::Duga() :
		 D1({0, 0}),
		 D2({0, 0}),
         D3({0, 0}),
         St({clBlue, clWhite, psSolid, bsSolid, 1})
{

}

Duga::Duga(TPoint P1, TPoint P2, TPoint P3, Style S) :
		 D1(P1),
		 D2(P2),
         D3(P3),
		 St(S)
{

}

void Duga::Draw(TCanvas* canvas)
{
	canvas->Pen->Color = St.Color1;
	canvas->Pen->Style = St.PenStyle;
	canvas->Pen->Width = St.Lsh;

	canvas->MoveTo(D1.X, D1.Y);
	for( float i = 0 ; i < 1 ; i += DELTA)
	{
		int X1 = SubLin(D1.X, D2.X, i );
		int Y1 = SubLin(D1.Y, D2.Y, i );
		int X2 = SubLin(D2.X, D3.X, i );
		int Y2 = SubLin(D2.Y, D3.Y, i );

		TPoint P({SubLin( X1 , X2 , i ), SubLin( Y1 , Y2 , i )});

		canvas->LineTo(P.X, P.Y);
	}
}

int SubLin(int P1, int P2, float Mod)
{
	int Delta = P2 - P1;
	return P1 + (Delta * Mod);
}