#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"

#pragma package(smart_init)
#pragma resource "*.dfm"

TForm1 *Form1;

//Режим
int Rezim = 0;
//Найдена ли фигура при удалении
bool Naydeno = false;
//Нажата ли мышь
bool MishNiz = false;

__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner), Figs() { }

//Метод создания формы
void __fastcall TForm1::FormCreate(TObject *Sender)
{
	//Обновить экран
    KeyPreview = true;
	Nach();
}

//Начало отрисовки пикселя
void TForm1::StartTochkaDraw(int X, int Y)
{
	//Рисуем точку в виде линии
    //Это нужно для того, чтобы при быстром движении мыши не получалось разрывов пикселей между собой
    Image1->Canvas->MoveTo(X, Y);
	Image1->Canvas->LineTo(X, Y);
	Cveta->Canvas->MoveTo(X, Y);
	Cveta->Canvas->LineTo(X, Y);
	//Добавляем точку, в которую было совершено нажатие пользователем, в список точек
	Points.push_back(TPoint(X, Y));
}

//Начало отрисовки линии
void TForm1::StartLineDraw(int X, int Y)
{
    //Если нет точек в списке точек(то есть нажатие произведено в первый раз)
    if(Points.empty())
	{
        //Задаем точку начала отрисовки линии
		Image1->Canvas->MoveTo(X, Y);
		Image1->Canvas->LineTo(X, Y);
        //Также делаем отображение на картинке вывода пикселей
		Cveta->Canvas->MoveTo(X, Y);
		Cveta->Canvas->LineTo(X, Y);
		Points.push_back(TPoint(X, Y));
	}
	else
	{
		//Если точка уже есть, то извлекаем первую из списка
		TPoint Point = Points.front();
        //Создаем линию
		auto* L = new Line(Point, {X, Y}, St);
        //Отрисовываем ее в экране вывода
		L->Draw(Image1->Canvas);
        //Добавляем в массив фигур
		Figs.push_back(L);
        //Очищаем список точек, для дальнейшей отрисовки линий
		Points.clear();
	}
}

int PoliN = 0;

//Функция, преобразующая список std в массив C++
TPoint* VMas(std::list<TPoint> Ps)
{
    //Создаем обычный массив динамическим выделением памяти (очищается в деструкторах объектов)
	TPoint* mas = new TPoint[Ps.size()];
    //Для всех точек массива точек делаем перенос из списка в созданный массив
    int i = 0;
	for(auto P : Ps)
	{
		mas[i++] = P;
	}
    // Возвращаем указатель на массив
    return mas;
}
//Нажатие мыши в режиме полинии
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
//Нажатие мыши в режиме круга
void TForm1::StartKrugDraw(int X, int Y)
{
    //Если точек нет, добавляем
	if(Points.empty())
		Points.push_back(TPoint(X, Y));
	else
	{
        //Иначе берем первую точку и создаем круг
		TPoint PervTochka = Points.front();

		auto* K = new Krug({PervTochka.X, PervTochka.Y}, X - PervTochka.X, St);
		Figs.push_back(K);

		Obnov();
		Points.clear();
	}
}
//Нажатие мыши в режиме дуги
void TForm1::StartDugaDraw(int X, int Y)
{
    //То же самое, только для дуги
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
//Нажатие мыши в режиме прямоугольника
void TForm1::StartRectDraw(int X, int Y)
{
    //То же самое, только для прямоугольника
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
//Нажатие мыши в режиме многоугольника
void TForm1::StartPolygonDraw(int X, int Y)
{
    //То же самое, только для многоугоьлника
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
//Нажатие мыши в режиме ластика
void TForm1::StartLastikDraw(int X, int Y)
{
    //По умолчанию ничего не найдено
	Naydeno = false;
	//Делаем реверсивный обход массива фигур
    //Чтобы первым делом удалить те объекты, которые лежат выше
	for(auto fig = Figs.rbegin(); fig != Figs.rend(); fig++)
	{
        //Если есть попадание
		if((*fig)->Sel(X, Y))
		{
			//Реверсируем реверсивный итератор
			std::advance(fig, 1);
            //Удаляем объект из массива объектов
			Figs.erase(fig.base());

            //Делаем обновление экрана
			Obnov();
            //Говорим, что нашли
			Naydeno = true;
			//Прерываем цикл
			break;
		}
	}
    //Если не нашли, то просто рисуем белую линию в виде пикселя (размер по умолчанию - 4)
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
//Движение мыши в режиме точки
void TForm1::MoveTochkaDraw(int X, int Y)
{
    //Устанавливаем настройки кистей
	UstSt();
	//Берем первую точку и следующую, проводя между ними линию
    //(Для обеспечения непрерывности пиксельного инструмента)
	TPoint Point = Points.front();
	Points.pop_front();
	Image1->Canvas->MoveTo(Point.X, Point.Y);
	Image1->Canvas->LineTo(X, Y);
	Cveta->Canvas->MoveTo(Point.X, Point.Y);
	Cveta->Canvas->LineTo(X, Y);
	Points.push_back(TPoint(X, Y));
}

//Движение мыши в режиме ластика
void TForm1::MoveLastikDraw(int X, int Y)
{
    //Если двигаем ластиком в режиме не найдено, то отрисовываем белым пискелем поверх всего
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

//Установка стилей кистей
void TForm1::UstSt()
{
	//Устанавливем сохраненные настройки кистей для двух областей вывода
	//(Cveta - картинка, куда сохраняются введенные пиксели, Image1 - окно вывода)
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

//Изменение режима отрисовки (старый режим и новый)
void TForm1::IzmRezim(int Old, int New)
{
    //Если прежний режим был режимом полилинии, то сохраняем полилинию в массив фигур
	if(Old == 2)
	{
		PoliN = 0;
        tps.clear();
		Points.clear();
		Obnov();
	}
    //Удаляем точки полилинии
    Points.clear();
}
//Установка режима ластика
void TForm1::LastikStyle()
{
    //Задаем для вывода параметры белой толстой кисти
	Cveta->Canvas->Pen->Color = clWhite;
	Cveta->Canvas->Pen->Style = psSolid;
	Cveta->Canvas->Pen->Width = 4 + St.Lsh;
	Image1->Canvas->Pen->Color = clWhite;
	Image1->Canvas->Pen->Style = psSolid;
	Image1->Canvas->Pen->Width = 4 + St.Lsh;
}
//Метод изменения цвета линии
void __fastcall TForm1::ColorBox1Change(TObject *Sender)
{
    //Извлекаем информацию в переменную, если произошло изменения значения в меню выбора цвета
	St.Color1 = ColorBox1->Selected;
}
//Метод изменения цвета заливки
void __fastcall TForm1::ColorBox2Change(TObject *Sender)
{
	St.Color2 = ColorBox2->Selected;
}

//Метод изменения ширины линии
void __fastcall TForm1::SpinEdit1Change(TObject *Sender)
{
	St.Lsh = SpinEdit1->Value;
}
//Метод измения типа линии (в меню формы)
void __fastcall TForm1::ComboBox1Change(TObject *Sender)
{
    //Меняем тип линии в соответствии с выбранным элементом
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
//Метод измения типа заливки (в меню формы)
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
//Метод нажатия кнопки "точка"
void __fastcall TForm1::Button1Click(TObject *Sender)
{
    IzmRezim(Rezim, 0);
	Rezim = 0;
}
//Метод нажатия кнопки "линия"
void __fastcall TForm1::Button2Click(TObject *Sender)
{
	IzmRezim(Rezim, 1);
	Rezim = 1;
}
//Метод нажатия кнопки "полилиния"
void __fastcall TForm1::Button3Click(TObject *Sender)
{
	IzmRezim(Rezim, 2);
	Rezim = 2;
}
//Метод нажатия кнопки "круг"
void __fastcall TForm1::Button4Click(TObject *Sender)
{
	IzmRezim(Rezim, 3);
	Rezim = 3;
}
//Метод нажатия кнопки "Дуга"
void __fastcall TForm1::Button5Click(TObject *Sender)
{
	IzmRezim(Rezim, 4);
	Rezim = 4;
}
//Метод нажатия кнопки "Прямоугольник"
void __fastcall TForm1::Button6Click(TObject *Sender)
{
	IzmRezim(Rezim, 5);
	Rezim = 5;
}
//Метод нажатия кнопки "Многоугольник"
void __fastcall TForm1::Button7Click(TObject *Sender)
{
	IzmRezim(Rezim, 6);
	Rezim = 6;
}
//Метод нажатия кнопки "Ластик"
void __fastcall TForm1::Button8Click(TObject *Sender)
{
    IzmRezim(Rezim, 7);
	Rezim = 7;
}
//Нажатие Создать в верхнем меню
void __fastcall TForm1::Sozd1Click(TObject *Sender)
{
	Nach();
}
//Нажатие Открыть в верхнем меню
void __fastcall TForm1::Open1Click(TObject *Sender)
{
	Nach();
    Open();
}
//Нажатие Сохранить в верхнем меню
void __fastcall TForm1::Save1Click(TObject *Sender)
{
    Save();
}
//Метод обновления всего приложения
void TForm1::Nach()
{
	//Обновляем цвета и типы линий
	St.Color1 = ColorBox1->Selected;
	St.Color2 = ColorBox2->Selected;
	St.PenStyle = psSolid;
	St.BrushStyle = bsSolid;

    //Очищаем все массивы
	Figs.clear();
    Points.clear();
	Ochist();
    //Обновляем картинку вывода пикселей
	ObnovCveta();
}
//Метод обновления фигур на экране
void TForm1::Obnov()
{
    Draw();
	for(auto Fig : Figs)
		Fig->Draw(Image1->Canvas);
}
//Метод вывода нарисованных пикселей на экран
void TForm1::ObnovCveta()
{
	if(Cveta != nullptr)
		delete Cveta;
	Cveta = new TBitmap();

	Cveta->Width = Image1->Width;
	Cveta->Height = Image1->Height;
}
//Метод очистки окна вывода
void TForm1::Ochist()
{
	Image1->Canvas->Brush->Color = clWhite;
	Image1->Canvas->FillRect(TRect(0, 0, Image1->Width, Image1->Height));
}
//Метод переноса сохраненных пикселей в окно вывода
void TForm1::Draw()
{
	Ochist();
	TRect rect(0, 0, Image1->Width, Image1->Height);
	Image1->Canvas->CopyRect(rect, Cveta->Canvas, rect);
}
//Метод открытия картинки через верхнее меню
void TForm1::Open()
{
    //Задаем фильтры для окна выбора файла
    OpenDialog1->DefaultExt=".jpg";
	OpenDialog1->Filter="JPEG (*.jpg)|*.jpg";
    //Открываем это окно и извлекаем эту картинку из файла
	if(OpenDialog1->Execute()) {
		Cveta->LoadFromFile(OpenDialog1->FileName);
		Image1->Picture->Bitmap->LoadFromFile(OpenDialog1->FileName);
	}
}
//Метод сохранения картинки через верхнее меню
void TForm1::Save()
{
    // То же самое, что и выше
    SaveDialog1->DefaultExt=".jpg";
	SaveDialog1->Filter="JPEG (*.jpg)|*.jpg";
	if(SaveDialog1->Execute()) {
		Image1->Picture->Bitmap->SaveToFile(SaveDialog1->FileName);
	}
}
//Метод нажатия мыши по окну вывода картинки
void __fastcall TForm1::OnMouseDown(TObject *Sender,
									TMouseButton Button,
									TShiftState Shift,
									int X, int Y)
{
	if(Button == mbLeft)
	{
        //Говорим, что мышь нажата
		MishNiz = true;
        //Устанавливаем параметры кистей
		UstSt();

        //В соответствии с выбранным режимом начинаем отрисовку
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
//Метод движения мыши по окну вывода картинки
void __fastcall TForm1::OnMouseMove(TObject *Sender, TShiftState Shift, int X, int Y)

{
    //Если левая кнопка мыши зажата
	if(MishNiz)
	{
		//Делаем непрерывную отрисовку для пикселя или ластика
		if(Rezim == 0) MoveTochkaDraw(X, Y);
		else if(Rezim == 7) MoveLastikDraw(X, Y);
	}
}
//Метод отпускания зажатой кнопки мыши
void __fastcall TForm1::OnMouseUp(TObject *Sender,
								  TMouseButton Button,
								  TShiftState Shift,
								  int X, int Y)
{
	//Если мышь отпущеная левая
	if(Button == mbLeft)
	{
		//Говорим, что левая кнопка мыши больше не зажата
		MishNiz = false;
		//Если рисовали пиксели или стирали ластиком, то обнуляем массив точек
		if(Rezim == 0 || Rezim == 7)
			Points.clear();
	}
}


void __fastcall TForm1::OnKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	if(Key == VK_CONTROL && Rezim == 2) {
		PoliType = !PoliType;
		if(PoliType)
			Label7->Caption = "Линия";
		else
			Label7->Caption = "Дуга";
	}
}
//---------------------------------------------------------------------------

