#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"

#pragma package(smart_init)
#pragma resource "*.dfm"

TForm1 *Form1;

//�����
int Rezim = 0;
//������� �� ������ ��� ��������
bool Naydeno = false;
//������ �� ����
bool MishNiz = false;

__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner), Figs() { }

//����� �������� �����
void __fastcall TForm1::FormCreate(TObject *Sender)
{
	//�������� �����
    KeyPreview = true;
	Nach();
}

//������ ��������� �������
void TForm1::StartTochkaDraw(int X, int Y)
{
	//������ ����� � ���� �����
    //��� ����� ��� ����, ����� ��� ������� �������� ���� �� ���������� �������� �������� ����� �����
    Image1->Canvas->MoveTo(X, Y);
	Image1->Canvas->LineTo(X, Y);
	Cveta->Canvas->MoveTo(X, Y);
	Cveta->Canvas->LineTo(X, Y);
	//��������� �����, � ������� ���� ��������� ������� �������������, � ������ �����
	Points.push_back(TPoint(X, Y));
}

//������ ��������� �����
void TForm1::StartLineDraw(int X, int Y)
{
    //���� ��� ����� � ������ �����(�� ���� ������� ����������� � ������ ���)
    if(Points.empty())
	{
        //������ ����� ������ ��������� �����
		Image1->Canvas->MoveTo(X, Y);
		Image1->Canvas->LineTo(X, Y);
        //����� ������ ����������� �� �������� ������ ��������
		Cveta->Canvas->MoveTo(X, Y);
		Cveta->Canvas->LineTo(X, Y);
		Points.push_back(TPoint(X, Y));
	}
	else
	{
		//���� ����� ��� ����, �� ��������� ������ �� ������
		TPoint Point = Points.front();
        //������� �����
		auto* L = new Line(Point, {X, Y}, St);
        //������������ �� � ������ ������
		L->Draw(Image1->Canvas);
        //��������� � ������ �����
		Figs.push_back(L);
        //������� ������ �����, ��� ���������� ��������� �����
		Points.clear();
	}
}

int PoliN = 0;

//�������, ������������� ������ std � ������ C++
TPoint* VMas(std::list<TPoint> Ps)
{
    //������� ������� ������ ������������ ���������� ������ (��������� � ������������ ��������)
	TPoint* mas = new TPoint[Ps.size()];
    //��� ���� ����� ������� ����� ������ ������� �� ������ � ��������� ������
    int i = 0;
	for(auto P : Ps)
	{
		mas[i++] = P;
	}
    // ���������� ��������� �� ������
    return mas;
}
//������� ���� � ������ �������
void TForm1::StartPoliDraw(int X, int Y)
{
	if(PoliN == 0 && PoliType) {
		PoliN = 0;
		Points.push_back(TPoint(X, Y));
		tps.push_back(true);
	}
	else if(PoliN == 1 && PoliType) {
        PoliN = 0;
		tps.push_back(true);
		Points.push_back(TPoint(X, Y));
        tps.push_back(true);
    }
	else if(PoliN == 1 && !PoliType) {
		PoliN = 0;
		Points.push_back(TPoint(X, Y));
		tps.push_back(false);
	}
	else {
		++PoliN;
		Points.push_back(TPoint(X, Y));
	}

	auto it = Points.begin();
	for(bool b : tps) {
		if(b) {
			TPoint p1 = *it++;
			TPoint p2 = *it;
			if(p2.X < Image1->Width)
			{
				Image1->Canvas->LineTo(p2.X, p2.Y);
				Cveta->Canvas->LineTo(p2.X, p2.Y);
            }
		}
		else {
			TPoint p1 = *it++;
			TPoint p2 = *it++;
			TPoint p3 = *it;
			if(p3.X >= 0 && p3.X <= Image1->Width)
			{
				auto duga = new class Duga({p1.x, p1.y}, {p2.x, p2.y}, {p3.x, p3.y}, St);
				duga->Draw(Image1->Canvas);
				duga->Draw(Cveta->Canvas);
			}
		}
	}
}
//������� ���� � ������ �����
void TForm1::StartKrugDraw(int X, int Y)
{
    //���� ����� ���, ���������
	if(Points.empty())
		Points.push_back(TPoint(X, Y));
	else
	{
        //����� ����� ������ ����� � ������� ����
		TPoint PervTochka = Points.front();

		auto* K = new Krug({PervTochka.X, PervTochka.Y}, X - PervTochka.X, St);
		Figs.push_back(K);

		Obnov();
		Points.clear();
	}
}
//������� ���� � ������ ����
void TForm1::StartDugaDraw(int X, int Y)
{
    //�� �� �����, ������ ��� ����
    if(Points.size() < 2)
		Points.push_back(TPoint(X, Y));
	else
	{
		auto it = Points.begin();
		TPoint p1 = *it++;
		TPoint p2 = *it;
		Fig* D = new Duga({p1.x, p1.y}, {p2.x, p2.y}, {X, Y}, St);
		D->Draw(Image1->Canvas);
		Figs.push_back(D);
		Points.clear();
	}
}
//������� ���� � ������ ��������������
void TForm1::StartRectDraw(int X, int Y)
{
    //�� �� �����, ������ ��� ��������������
    if(Points.empty())
        Points.push_back(TPoint(X, Y));
	else
	{
		TPoint PervTochka = Points.front();

		Fig* R = new class Rect({PervTochka.X, PervTochka.Y}, {X, Y}, St);
		R->Draw(Image1->Canvas);
		Figs.push_back(R);

		Points.clear();
	}
}
//������� ���� � ������ ��������������
void TForm1::StartPolygonDraw(int X, int Y)
{
    //�� �� �����, ������ ��� ��������������
    if(Points.empty())
		Points.push_back(TPoint(X, Y));
	else
	{
		TPoint PervTochka = Points.front();
		bool C = CheckBox1->Checked;
		int N = SpinEdit2->Value;

		Fig* NU = new Nugl({X, Y}, X - PervTochka.X, St, N, C);
		NU->Draw(Image1->Canvas);
		Figs.push_back(NU);

		Points.clear();
	}
}
//������� ���� � ������ �������
void TForm1::StartLastikDraw(int X, int Y)
{
    //�� ��������� ������ �� �������
	Naydeno = false;
	//������ ����������� ����� ������� �����
    //����� ������ ����� ������� �� �������, ������� ����� ����
	for(auto fig = Figs.rbegin(); fig != Figs.rend(); fig++)
	{
        //���� ���� ���������
		if((*fig)->Sel(X, Y))
		{
			//����������� ����������� ��������
			std::advance(fig, 1);
            //������� ������ �� ������� ��������
			Figs.erase(fig.base());

            //������ ���������� ������
			Obnov();
            //�������, ��� �����
			Naydeno = true;
			//��������� ����
			break;
		}
	}
    //���� �� �����, �� ������ ������ ����� ����� � ���� ������� (������ �� ��������� - 4)
	if(!Naydeno)
	{
		Image1->Canvas->Pen->Width = 4 + St.Lsh;
		Image1->Canvas->Pen->Color = clWhite;
		Image1->Canvas->Pen->Style = psSolid;
		Image1->Canvas->MoveTo(X, Y);
		Image1->Canvas->LineTo(X, Y);

		Points.push_back(TPoint(X, Y));
	}
}
//�������� ���� � ������ �����
void TForm1::MoveTochkaDraw(int X, int Y)
{
    //������������� ��������� ������
	UstSt();
	//����� ������ ����� � ���������, ������� ����� ���� �����
    //(��� ����������� ������������� ����������� �����������)
	TPoint Point = Points.front();
	Points.pop_front();
	Image1->Canvas->MoveTo(Point.X, Point.Y);
	Image1->Canvas->LineTo(X, Y);
	Cveta->Canvas->MoveTo(Point.X, Point.Y);
	Cveta->Canvas->LineTo(X, Y);
	Points.push_back(TPoint(X, Y));
}

//�������� ���� � ������ �������
void TForm1::MoveLastikDraw(int X, int Y)
{
    //���� ������� �������� � ������ �� �������, �� ������������ ����� �������� ������ �����
	if(!Naydeno)
	{
        LastikStyle();
		TPoint Point = Points.front();
		Points.pop_front();
		Image1->Canvas->MoveTo(Point.X, Point.Y);
		Image1->Canvas->LineTo(X, Y);
		Cveta->Canvas->MoveTo(Point.X, Point.Y);
		Cveta->Canvas->LineTo(X, Y);
		Points.push_back(TPoint(X, Y));
    }
}

//��������� ������ ������
void TForm1::UstSt()
{
	//������������ ����������� ��������� ������ ��� ���� �������� ������
	//(Cveta - ��������, ���� ����������� ��������� �������, Image1 - ���� ������)
	Cveta->Canvas->Pen->Color = St.Color1;
	Cveta->Canvas->Pen->Style = St.PenStyle;
	Cveta->Canvas->Pen->Width = St.Lsh;
	Cveta->Canvas->Brush->Color = St.Color2;
	Cveta->Canvas->Brush->Style = St.BrushStyle;

	Image1->Canvas->Pen->Color = St.Color1;
	Image1->Canvas->Pen->Style = St.PenStyle;
	Image1->Canvas->Pen->Width = St.Lsh;
	Image1->Canvas->Brush->Color = St.Color2;
	Image1->Canvas->Brush->Style = St.BrushStyle;
}

//��������� ������ ��������� (������ ����� � �����)
void TForm1::IzmRezim(int Old, int New)
{
    //���� ������� ����� ��� ������� ���������, �� ��������� ��������� � ������ �����
	if(Old == 2)
	{
		PoliN = 0;
        tps.clear();
		Points.clear();
		Obnov();
	}
    //������� ����� ���������
    Points.clear();
}
//��������� ������ �������
void TForm1::LastikStyle()
{
    //������ ��� ������ ��������� ����� ������� �����
	Cveta->Canvas->Pen->Color = clWhite;
	Cveta->Canvas->Pen->Style = psSolid;
	Cveta->Canvas->Pen->Width = 4 + St.Lsh;
	Image1->Canvas->Pen->Color = clWhite;
	Image1->Canvas->Pen->Style = psSolid;
	Image1->Canvas->Pen->Width = 4 + St.Lsh;
}
//����� ��������� ����� �����
void __fastcall TForm1::ColorBox1Change(TObject *Sender)
{
    //��������� ���������� � ����������, ���� ��������� ��������� �������� � ���� ������ �����
	St.Color1 = ColorBox1->Selected;
}
//����� ��������� ����� �������
void __fastcall TForm1::ColorBox2Change(TObject *Sender)
{
	St.Color2 = ColorBox2->Selected;
}

//����� ��������� ������ �����
void __fastcall TForm1::SpinEdit1Change(TObject *Sender)
{
	St.Lsh = SpinEdit1->Value;
}
//����� ������� ���� ����� (� ���� �����)
void __fastcall TForm1::ComboBox1Change(TObject *Sender)
{
    //������ ��� ����� � ������������ � ��������� ���������
	switch(ComboBox1->ItemIndex)
	{
		case 0:
			St.PenStyle = psSolid;
		break;
		case 1:
			St.PenStyle = psDash;
		break;
		case 2:
			St.PenStyle = psDot;
		break;
		case 3:
			St.PenStyle = psDashDot;
		break;
		case 4:
			St.PenStyle = psDashDotDot;
		break;
	}
}
//����� ������� ���� ������� (� ���� �����)
void __fastcall TForm1::ComboBox2Change(TObject *Sender)
{
	switch(ComboBox2->ItemIndex)
	{
		case 0:
			St.BrushStyle = bsSolid;
		break;
		case 1:
			St.BrushStyle = bsClear;
		break;
		case 2:
			St.BrushStyle = bsHorizontal;
		break;
		case 3:
			St.BrushStyle = bsVertical;
		break;
		case 4:
			St.BrushStyle = bsFDiagonal;
		break;
		case 5:
			St.BrushStyle = bsBDiagonal;
		break;
		case 6:
			St.BrushStyle = bsCross;
		break;
        case 7:
			St.BrushStyle = bsDiagCross;
		break;
	}
}
//����� ������� ������ "�����"
void __fastcall TForm1::Button1Click(TObject *Sender)
{
    IzmRezim(Rezim, 0);
	Rezim = 0;
}
//����� ������� ������ "�����"
void __fastcall TForm1::Button2Click(TObject *Sender)
{
	IzmRezim(Rezim, 1);
	Rezim = 1;
}
//����� ������� ������ "���������"
void __fastcall TForm1::Button3Click(TObject *Sender)
{
	IzmRezim(Rezim, 2);
	Rezim = 2;
}
//����� ������� ������ "����"
void __fastcall TForm1::Button4Click(TObject *Sender)
{
	IzmRezim(Rezim, 3);
	Rezim = 3;
}
//����� ������� ������ "����"
void __fastcall TForm1::Button5Click(TObject *Sender)
{
	IzmRezim(Rezim, 4);
	Rezim = 4;
}
//����� ������� ������ "�������������"
void __fastcall TForm1::Button6Click(TObject *Sender)
{
	IzmRezim(Rezim, 5);
	Rezim = 5;
}
//����� ������� ������ "�������������"
void __fastcall TForm1::Button7Click(TObject *Sender)
{
	IzmRezim(Rezim, 6);
	Rezim = 6;
}
//����� ������� ������ "������"
void __fastcall TForm1::Button8Click(TObject *Sender)
{
    IzmRezim(Rezim, 7);
	Rezim = 7;
}
//������� ������� � ������� ����
void __fastcall TForm1::Sozd1Click(TObject *Sender)
{
	Nach();
}
//������� ������� � ������� ����
void __fastcall TForm1::Open1Click(TObject *Sender)
{
	Nach();
    Open();
}
//������� ��������� � ������� ����
void __fastcall TForm1::Save1Click(TObject *Sender)
{
    Save();
}
//����� ���������� ����� ����������
void TForm1::Nach()
{
	//��������� ����� � ���� �����
	St.Color1 = ColorBox1->Selected;
	St.Color2 = ColorBox2->Selected;
	St.PenStyle = psSolid;
	St.BrushStyle = bsSolid;

    //������� ��� �������
	Figs.clear();
    Points.clear();
	Ochist();
    //��������� �������� ������ ��������
	ObnovCveta();
}
//����� ���������� ����� �� ������
void TForm1::Obnov()
{
    Draw();
	for(auto Fig : Figs)
		Fig->Draw(Image1->Canvas);
}
//����� ������ ������������ �������� �� �����
void TForm1::ObnovCveta()
{
	if(Cveta != nullptr)
		delete Cveta;
	Cveta = new TBitmap();

	Cveta->Width = Image1->Width;
	Cveta->Height = Image1->Height;
}
//����� ������� ���� ������
void TForm1::Ochist()
{
	Image1->Canvas->Brush->Color = clWhite;
	Image1->Canvas->FillRect(TRect(0, 0, Image1->Width, Image1->Height));
}
//����� �������� ����������� �������� � ���� ������
void TForm1::Draw()
{
	Ochist();
	TRect rect(0, 0, Image1->Width, Image1->Height);
	Image1->Canvas->CopyRect(rect, Cveta->Canvas, rect);
}
//����� �������� �������� ����� ������� ����
void TForm1::Open()
{
    //������ ������� ��� ���� ������ �����
    OpenDialog1->DefaultExt=".jpg";
	OpenDialog1->Filter="JPEG (*.jpg)|*.jpg";
    //��������� ��� ���� � ��������� ��� �������� �� �����
	if(OpenDialog1->Execute()) {
		Cveta->LoadFromFile(OpenDialog1->FileName);
		Image1->Picture->Bitmap->LoadFromFile(OpenDialog1->FileName);
	}
}
//����� ���������� �������� ����� ������� ����
void TForm1::Save()
{
    // �� �� �����, ��� � ����
    SaveDialog1->DefaultExt=".jpg";
	SaveDialog1->Filter="JPEG (*.jpg)|*.jpg";
	if(SaveDialog1->Execute()) {
		Image1->Picture->Bitmap->SaveToFile(SaveDialog1->FileName);
	}
}
//����� ������� ���� �� ���� ������ ��������
void __fastcall TForm1::OnMouseDown(TObject *Sender,
									TMouseButton Button,
									TShiftState Shift,
									int X, int Y)
{
	if(Button == mbLeft)
	{
        //�������, ��� ���� ������
		MishNiz = true;
        //������������� ��������� ������
		UstSt();

        //� ������������ � ��������� ������� �������� ���������
		if(Rezim == 0) StartTochkaDraw(X, Y);
		else if(Rezim == 1) StartLineDraw(X, Y);
		else if(Rezim == 2) StartPoliDraw(X, Y);
		else if(Rezim == 3) StartKrugDraw(X, Y);
		else if(Rezim == 4) StartDugaDraw(X, Y);
		else if(Rezim == 5) StartRectDraw(X, Y);
		else if(Rezim == 6) StartPolygonDraw(X, Y);
		if(Rezim == 7) StartLastikDraw(X, Y);
	}
	else if(Button == mbRight && Rezim == 2)
	{
		IzmRezim(2, 2);
	}
}
//����� �������� ���� �� ���� ������ ��������
void __fastcall TForm1::OnMouseMove(TObject *Sender, TShiftState Shift, int X, int Y)

{
    //���� ����� ������ ���� ������
	if(MishNiz)
	{
		//������ ����������� ��������� ��� ������� ��� �������
		if(Rezim == 0) MoveTochkaDraw(X, Y);
		else if(Rezim == 7) MoveLastikDraw(X, Y);
	}
}
//����� ���������� ������� ������ ����
void __fastcall TForm1::OnMouseUp(TObject *Sender,
								  TMouseButton Button,
								  TShiftState Shift,
								  int X, int Y)
{
	//���� ���� ��������� �����
	if(Button == mbLeft)
	{
		//�������, ��� ����� ������ ���� ������ �� ������
		MishNiz = false;
		//���� �������� ������� ��� ������� ��������, �� �������� ������ �����
		if(Rezim == 0 || Rezim == 7)
			Points.clear();
	}
}


void __fastcall TForm1::OnKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	if(Key == VK_CONTROL && Rezim == 2) {
		PoliType = !PoliType;
		if(PoliType)
			Label7->Caption = "�����";
		else
			Label7->Caption = "����";
	}
}
//---------------------------------------------------------------------------

