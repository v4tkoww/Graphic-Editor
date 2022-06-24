//---------------------------------------------------------------------------

#pragma hdrstop

#include "Nugl.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

Nugl::Nugl() : St({clBlue, clWhite, psSolid, bsSolid, 1}), D({0, 0}), Rad(0), NUgs(0), Des(true) { }
Nugl::Nugl(TPoint P, int R, Style S, int N, bool Ds) : D(P), Rad(R), St(S), NUgs(N), Des(Ds) { }

int Pow(int I1)
{
    return I1 * I1;
}

bool Nugl::Sel(int X, int Y)
{
	return Pow(X - D.X) + Pow(Y - D.Y) <= Pow(Rad);
}

void Nugl::Draw(TCanvas* Canva)
{
	TPoint* Ps = new TPoint[NUgs];
	double Alpha = 0.0;
	int R = Des ? (Rad / cos (M_PI / NUgs)) : Rad;

	for(int i = 0; i < NUgs; ++i)
	{
		Alpha = 2 * M_PI * i / NUgs;
		Ps[i].X = R * cos(Alpha) + D.X;
		Ps[i].Y = R * sin(Alpha) + D.Y;
	}

	DrawNugl(Ps, Canva);
    DrawKrug(Canva);

	delete[] Ps;
}

void Nugl::DrawNugl(TPoint* Ps, TCanvas* Canva)
{
	Canva->Pen->Color = St.Color1;
	Canva->Brush->Color = St.Color2;
	Canva->Pen->Style = St.PenStyle;
	Canva->Brush->Style = St.BrushStyle;
	Canva->Pen->Width = St.Lsh;

	Canva->Polygon(Ps, NUgs - 1);
}

void Nugl::DrawKrug(TCanvas* Canva)
{
	Canva->Pen->Color = clGray;
	Canva->Brush->Color = clWhite;
	Canva->Pen->Style = psDot;
	Canva->Brush->Style = bsClear;
	Canva->Pen->Width = 1;

	Canva->Ellipse(D.X - Rad, D.Y - Rad, D.X + Rad, D.Y + Rad);
}
