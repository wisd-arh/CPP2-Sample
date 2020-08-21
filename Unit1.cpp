//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "iStruct.cpp"
#include "Clipbrd.hpp"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

SaleArray sa;
SaleArray *dsa;
int chC;

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
  if (OpenDialog1->Execute()) {
    Edit1->Text = OpenDialog1->FileName;
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button2Click(TObject *Sender)
{
  int q;
  TrArray tr;
  int j;
  double **Ss;
  int poss[7];
  double Qs[7];
  int Ts[7][29];
  double TsD[7][29];

  tr = new transaction[1000000]; // Количество транзакций
  if (sa != NULL) delete[] sa;
  sa = new Sale[1000000]; // Количество чеков
  fLoad(Edit1->Text, tr, q);
  SaleLoad(tr, sa, q, chC);
  delete[] tr;
  Initalize_cSum(sa, chC);
  Button3->Enabled = true;

  dsa = new Sale*[7]; // 7 дней недели
  for (int i = 0; i < 7; i++)
    dsa[i] = new Sale[1000000];

  SaleToDay(sa, chC, dsa, poss);

  Ss = new double*[7];

  for (int i = 0; i < 7; i++)
    Ss[i] = new double[chC];


  for (int i = 0; i < 7; i++)
    for (int j = 0; j < poss[i]; j++)
      Ss[i][j] = dsa[i][j].cSum;

  memset(Qs, 0, sizeof(Qs));
  for (int i = 0; i < 7; i++)
    for (int j = 0; j < poss[i]; j++)
      Qs[i]+=Ss[i][j];

  StringGrid1->RowCount = 29;
  StringGrid1->ColCount = 7;
/*  StringGrid1->Cells[0][0] = "День недели";
  StringGrid1->Cells[1][0] = "Сумма";
  StringGrid1->Cells[0][1] = "Понедельник";
  StringGrid1->Cells[0][2] = "Вторник";
  StringGrid1->Cells[0][3] = "Среда";
  StringGrid1->Cells[0][4] = "Четверг";
  StringGrid1->Cells[0][5] = "Пятница";
  StringGrid1->Cells[0][6] = "Суббота";
  StringGrid1->Cells[0][7] = "Воскресенье";
 */
/*  for (int i = 0; i < 7; i++)
    StringGrid1->Cells[1][i+1] = Qs[i];
*/

  SaleToTime(sa, chC, Ts);

  for (int i = 0; i < 7; i++)
    for (int j = 0; j < 29; j++)
      StringGrid1->Cells[i][j] = Ts[i][j];

/*  SaleToTimeD(sa, chC, TsD);

  for (int i = 0; i < 7; i++)
    for (int j = 0; j < 29; j++)
      StringGrid1->Cells[i][j] = TsD[i][j];
*/
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button3Click(TObject *Sender)
{
  int n;
  float sr;
  float pr;
  float m;
  float l;
  float o;
  tSums Sums;
  try {
    pr = StrToFloat(Edit2->Text);
  } catch(...) {
    Edit2->Text="0,0";
    return;
  }

  Memo1->Lines->Clear();
  m = Median(sa, chC);
  l = UpThan(pr, sa, chC);
  o = SimpleRoundTo((l/chC)*100, -3);
  Memo1->Lines->Clear();
  Memo1->Lines->Add("Период: [" + sa[0].Date->DateTimeString() + "      " + sa[chC-1].Date->DateTimeString() + "]");
  Memo1->Lines->Add("Чеков всего: " + IntToStr(chC));
  Memo1->Lines->Add("Средняя сумма чека: " + FloatToStr(m));
  Memo1->Lines->Add("Порог: " + FloatToStr(pr));
  Memo1->Lines->Add("Чеков больше порога: " + FloatToStr(l));
  Memo1->Lines->Add("Чеков больше порога, %: " + FloatToStr(o));
  o = qStorno(sa, chC)/(float)chC * 100;

  Memo1->Lines->Add("Количество чеков со сторно, %: " + FloatToStr(o));

  Sums = new double[1000];
  Razlog(sa, chC, Sums, 21, 30.0);
  Memo1->Lines->Add("");
  for (int i = 0; i < 21; i++) {
    Memo1->Lines->Add(FloatToStr(Sums[i]));
  }
  delete[] Sums;

  for (int i = 0; i < 7; i++)
    delete[] dsa[i];

  delete[] dsa;
  delete[] sa;
  
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button4Click(TObject *Sender)
{
  Close();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N1Click(TObject *Sender)
{
  TClipboard *Cl;
  Cl = Clipboard();
  Cl->Clear();
  AnsiString s;
  s = "";
  for (int j = StringGrid1->Selection.Top; j < StringGrid1->Selection.Bottom+1; j++) {
    for (int i = StringGrid1->Selection.Left; i < StringGrid1->Selection.Right+1; i++)
      s = s + StringGrid1->Cells[i][j] + ";";

    s.SetLength(s.Length() - 1);
    s = s + '\n';
  }
  Cl->SetTextBuf(s.c_str());
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button5Click(TObject *Sender)
{
  Graphics::TBitmap *bm;
  int k, l;
  double **Data;
  double max;
  double step;
  double lod;
  char **AlignData;
  int w, h;
  int cstep;

  bm = new(Graphics::TBitmap);

  k = StringGrid1->RowCount;
  l = StringGrid1->ColCount;

  Data = new double*[k];
  for (int i = 0; i < k; i++)
    Data[i] = new double[l];

  max = -1;
  for (int i = 0; i < k; i++)
    for (int j = 0; j < l; j++) {
      Data[i][j] = StringGrid1->Cells[j][i].ToDouble();
      if (Data[i][j] > max) max = Data[i][j];
    }
  lod = Edit3->Text.ToInt();
  step = max / (float)lod;

  AlignData = new char*[k];
  for (int i = 0; i < k; i++)
    AlignData[i] = new char[l];

  for (int i = 0; i < k; i++)
    for (int j = 0; j < l; j++)
      AlignData[i][j] = Ceil(Data[i][j] / step);

  bm->Width = Image1->Width;
  bm->Height = Image1->Height;
  bm->Canvas->Brush->Color = clBlack; 
  bm->Canvas->Rectangle(0, 0, bm->Width, bm->Height);


  w = Floor((float)bm->Width / (float)k);
  h = Floor((float)bm->Height / (float)l);

  cstep = Floor((float)255 / (float)lod)  - 1;
  for (int i = 0; i < k; i++)
    for (int j = 0; j < l; j++) {
      bm->Canvas->Brush->Color = cstep*AlignData[i][j]; // clRed ^ (clBlue & (cstep*AlignData[i][j] << 16));
      bm->Canvas->Pen->Width = 1;
      bm->Canvas->Rectangle(Rect(i*w, j*h, i*w + w + 1, j*h + h + 1));
    }

  Image1->Picture->Bitmap->Assign(bm);
  bm->Free();

  Memo1->Lines->Add(FloatToStr(max));
  Memo1->Lines->Add(FloatToStr(step));

}
//---------------------------------------------------------------------------


