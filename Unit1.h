//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.Samples.Spin.hpp>
#include <Vcl.Dialogs.hpp>
#include <list>
#include <vector>

#include "Line.h"
#include "Krug.h"
#include "Duga.h"
#include "Rect.h"
#include "Nugl.h"

using namespace std;

//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:
	TImage *Image1;
	TMainMenu *MainMenu;
	TMenuItem *File1;
	TMenuItem *Sozd1;
	TMenuItem *Open1;
	TMenuItem *Save1;
	TSpinEdit *SpinEdit1;
	TLabel *Label1;
	TColorDialog *ColorDialog1;
	TOpenDialog *OpenDialog1;
	TSaveDialog *SaveDialog1;
	TCheckBox *CheckBox1;
	TSpinEdit *SpinEdit2;
	TLabel *Label2;
	TColorBox *ColorBox1;
	TColorBox *ColorBox2;
	TComboBox *ComboBox1;
	TComboBox *ComboBox2;
	TPanel *Panel1;
	TLabel *Label3;
	TLabel *Label4;
	TLabel *Label5;
	TLabel *Label6;
	TButton *Button1;
	TButton *Button2;
	TButton *Button3;
	TButton *Button4;
	TButton *Button5;
	TButton *Button6;
	TButton *Button7;
	TButton *Button8;
	TLabel *Label7;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall Button4Click(TObject *Sender);
	void __fastcall Button5Click(TObject *Sender);
	void __fastcall Button6Click(TObject *Sender);
	void __fastcall Button7Click(TObject *Sender);
	void __fastcall SpinEdit1Change(TObject *Sender);
	void __fastcall OnMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall OnMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall Sozd1Click(TObject *Sender);
	void __fastcall Open1Click(TObject *Sender);
	void __fastcall ColorBox1Change(TObject *Sender);
	void __fastcall ColorBox2Change(TObject *Sender);
	void __fastcall ComboBox1Change(TObject *Sender);
	void __fastcall ComboBox2Change(TObject *Sender);
	void __fastcall Button8Click(TObject *Sender);
	void __fastcall OnMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall Save1Click(TObject *Sender);
	void __fastcall OnKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
private:
	//Стили(Цвета, типы кистей и ширина линии)
	Style St;
    //Картинка для вывода пикселей
	Graphics::TBitmap* Cveta;
    // Динамический массив фигур
	vector<Fig*> Figs;
    // Список введенных точек
	list<TPoint> Points;

	vector<bool> tps;

    bool PoliType;
public:
	__fastcall TForm1(TComponent* Owner);

	void ObnovCveta();

	void UstSt();

	void IzmRezim(int Old, int New);
	void LastikStyle();

	void StartTochkaDraw(int X, int Y);
	void StartLineDraw(int X, int Y);
	void StartPoliDraw(int X, int Y);
	void StartKrugDraw(int X, int Y);
	void StartDugaDraw(int X, int Y);
	void StartRectDraw(int X, int Y);
	void StartPolygonDraw(int X, int Y);
	void StartLastikDraw(int X, int Y);

	void MoveTochkaDraw(int X, int Y);
	void MoveLastikDraw(int X, int Y);

    void Nach();
	void Obnov();
	void Ochist();
    void Draw();

    void Open();
	void Save();
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
