//---------------------------------------------------------------------------
#pragma hdrstop

#include "iStruct.h"
#include "SysUtils.hpp"
#include "Dialogs.hpp"
#include "io.h";
#include "DateUtils.hpp";
#include "Math.h";
//---------------------------------------------------------------------------
#pragma package(smart_init)

const char trFieldLength = 13;
const char trDraftLength = 100;

struct transaction {
  char n;
  char date[10];
  char time[8];
  int trType;
  int f1;              // номер ПК
  int f2;              // номер документа
  int f3;              // код кассира
  char f4[20];         // код товара
  char f5[20];         // коды значений разрезов
  double f6;            // цена товара
  double f7;            // количество товара
  double f8;            // сумма с округлением и без скидок
  int f9;              // тип чека ккм
  int f10;             // номер смены
  double f11;           // цена с округлением и скидками
  double f12;           // сумма с окрглением и скидками
  int f13;             // код ККМ
  char f14[20];        // артикул товара
  int f15;             // штрихкод регистрации
  double f16;           // сумма без скидок и округлений
  int f17;             //
  int f18;             // флаг обучающего режима
  int f19;             // код вида документа
  int f20;             // код комментария
};

typedef transaction *TrArray;
typedef double *tSums;

struct SalePos {
  double Code;
  double Quantity;
  double Price;
  double Sum;
};

//typedef SalePos *SalePosArray;

struct Sale {
  TDateTime *Date;
  int Amount;
  int Storno;
  double cSum;
  SalePos *SalePosArr;
};

typedef Sale *SaleArray;
typedef short int word;
void SaleLoad(TrArray T, SaleArray S, int num);


void strchng(char *dest, char a, char b) {
  int s;
  s = strlen(dest);
  for (int i = 0; i<s; i++) {
    if (dest[i] == a) dest[i] = b;
  }
}

void ParseDate(char *Date, word &Day, word &Month, word &Year) {
  char Y[5];
  char M[3];
  char D[3];

  D[0] = Date[0];
  D[1] = Date[1];
  D[2] = 0x0;
  M[0] = Date[3];
  M[1] = Date[4];
  M[2] = 0x0;
  Y[0] = Date[6];
  Y[1] = Date[7];
  Y[2] = Date[8];
  Y[3] = Date[9];
  Y[4] = 0x0;

  Day = atoi(D);
  Month = atoi(M);
  Year = atoi(Y);
}

void ParseTime(char *Time, word &Hour, word &Min, word &Sec) {
  char H[3];
  char M[3];
  char S[3];

  if (Time[1] != ':') {
    H[0] = Time[0];
    H[1] = Time[1];
    H[2] = 0x0;
    M[0] = Time[3];
    M[1] = Time[4];
    M[2] = 0x0;
    S[0] = Time[6];
    S[1] = Time[7];
    S[2] = 0x0;
  } else {
    H[0] = Time[0];
    H[1] = 0x0;
    H[2] = 0x0;
    M[0] = Time[2];
    M[1] = Time[3];
    M[2] = 0x0;
    S[0] = Time[5];
    S[1] = Time[6];
    S[2] = 0x0;
  }
  Hour = atoi(H);
  Min = atoi(M);
  Sec = atoi(S);
}

void writefield(transaction &tr, char *field, char n) {
/*  char n;
  char date[10];
  char time[8];
  int trType;
  int f1;              // номер ПК
  int f2;              // номер документа
  int f3;              // код кассира
  char f4[20];         // код товара
  char f5[20];         // коды значений разрезов
  double f6;            // цена товара
  double f7;            // количество товара
  double f8;            // сумма с округлением и без скидок
  int f9;              // тип чека ккм
  int f10;             // номер смены
  double f11;           // цена с округлением и скидками
  double f12;           // сумма с окрглением и скидками
  int f13;             // код ККМ
  char f14[20];        // артикул товара
  int f15;             // штрихкод регистрации
  double f16;           // сумма без скидок и округлений
  int f17;             //
  int f18;             // флаг обучающего режима
  int f19;             // код вида документа
  int f20;             // код комментария
*/
  switch (n) {
    case 1: tr.n = atoi(field); break;
    case 2: memset(tr.date, 0, sizeof(tr.date)); strcpy(tr.date, field); break;
    case 3: memset(tr.time, 0, sizeof(tr.time));strcpy(tr.time, field); break;
    case 4: tr.trType = atoi(field); break;

    case 5: tr.f1 = atoi(field); break;
    case 6: tr.f2 = atoi(field); break;
    case 7: tr.f3 = atoi(field); break;

    case 8: memset(tr.f4, 0, sizeof(tr.f4)); strcpy(tr.f4, field); break;
    case 9: memset(tr.f5, 0, sizeof(tr.f5)); strcpy(tr.f5, field); break;

    case 10: strchng(field, ',', '.'); tr.f6 = atof(field); break;
    case 11: strchng(field, ',', '.'); tr.f7 = atof(field); break;
    case 12: strchng(field, ',', '.'); tr.f8 = atof(field); break;

    case 13: tr.f9 = atoi(field); break;
    case 14: tr.f10 = atoi(field); break;

    case 15: strchng(field, ',', '.'); tr.f11 = atof(field); break;
    case 16: strchng(field, ',', '.'); tr.f12 = atof(field); break;

    case 17: tr.f13 = atoi(field); break;
    case 18: memset(tr.f14, 0, sizeof(tr.f14)); strcpy(tr.f14, field); break;
    case 19: tr.f15 = atoi(field); break;
    case 20: strchng(field, ',', '.'); tr.f16 = atof(field); break;
    case 21: tr.f17 = atoi(field); break;
    case 22: tr.f18 = atoi(field); break;
    case 23: tr.f19 = atoi(field); break;
    case 24: tr.f20 = atoi(field); break;

  }
}

void fLoad(AnsiString fName, TrArray trarr, int &Q) {
  int handle;
  long fSize;
  char *buf;
  long iByteRead;
  int n;     // движение по буферу
  char f;    // номер текущего поля
  char l;    // движение по буферу поля
  long ntr;  // номер текущей транзакции
  char *field;
  transaction tr;


  handle = FileOpen(fName.c_str(), fmOpenReadWrite);
  if (handle == -1) {
    ShowMessage("Unable open file");
    return;
  };
//  fSize = filelength(handle);
  fSize = FileSeek(handle,0,2);
  FileSeek(handle,0,0);

  buf = new char[fSize];
  if (buf == 0) {
    ShowMessage("Unable allocate memory.");
    return;
  }

  iByteRead = FileRead(handle, buf, fSize);
  FileClose(handle);
  if (iByteRead != fSize) {
    ShowMessage("Load file error.");
    return;
  }
  n = 0;
  f = 0;
  l = 0;
  ntr = 0;

  field = new char[trFieldLength];
  setmem(field, trFieldLength, 0);

//  trarr = new transaction[1000];
//  while (buf[n] == '\n') { n++; }
//  while (buf[n] == '\n') { n++; }
//  while (buf[n] == '\n') { n++; }
  for (int i=0; i< fSize; i++) {
    n++;
    if (buf[n] == '\n') break;
  }
  for (int i=n; i< fSize; i++) {
    n++;
    if (buf[n] == '\n') break;
  }
  for (int i=n; i< fSize; i++) {
    n++;
    if (buf[n] == '\n') break;
  }
  n++;

  for (int i = n; i< fSize; i++) {
    switch (buf[n]) {
      case 0xD: f=0;
                trarr[ntr] = tr;
                ntr++;
                break;
      case 0xA: break;
      case ';': l=0; f++;
                writefield(tr, field, f);
                setmem(field, trFieldLength, 0);
                field[0] = '0';
                break;
      default: field[l] = buf[n]; l++;
               if (l > trFieldLength) {
                 ShowMessage("Buffer overflow.\nBuffer: " + AnsiString(field));
                 return;
               }
    }
    n++;
    if (n > fSize) {
      ShowMessage("Offset range error.");
      return;
    }
  }
  Q = ntr;
}

void SaleLoad(TrArray T, SaleArray S, int num, int &chC) {
  Sale ts;
  int chN;
  int l; // текущая позиция.
  int chCount;
  word D;
  word M;
  word Y;

  word H;
  word Mn;
  word Sc;
//  tS.SalePosArr = new SalePosArray[trDraftLength];     // Позиций в чеке
//  tS.Amount = 0;
//  setmem(ts.SalePosArr, sizeof(SalePos)*trDraftLength, 0);
  chN = 0;
  l = 0;
  chCount = 0;
  for (int i=0; i<num; i++ ) {
    if (T[i].trType == 12) {
      l--;
      ts.Amount--;
      ts.Storno++;
      continue;
    }
    if (T[i].trType == 55) {
      if (chN != 0) {
        S[chCount] = ts;
        chCount++;
      }
    }
    if (T[i].trType == 56) {
      chCount--;
    }
    if (T[i].trType == 42) {
      l=0;
      chN = T[i].f2;
      ts.SalePosArr = new SalePos[trDraftLength];     // Позиций в чеке
      ts.Amount = 0;
      ts.Storno = 0;
      setmem(ts.SalePosArr, sizeof(SalePos)*trDraftLength, 0);
      ts.Date = new TDateTime();
      ParseDate(T[i].date, D, M, Y);
      ParseTime(T[i].time, H, Mn, Sc);
      ts.Date->Val = EncodeDateTime(Y, M, D, H, Mn, Sc, 0);
    }
    if (T[i].trType != 11) {
       continue;
    }
    if (T[i].trType == 11) {
      ts.SalePosArr[l].Code     = atoi(T[i].f4);
      ts.SalePosArr[l].Quantity = T[i].f7;
      ts.SalePosArr[l].Price    = T[i].f11;
      ts.SalePosArr[l].Sum      = T[i].f12;

      l++;
      ts.Amount++;
    }
  }
  S[chCount] = ts;  // Последний накопленный чек
  chC = chCount + 1;
}

void Init_cSum(Sale &s) {
  double sm;
  sm = 0.0;
  for (int i=0; i<s.Amount; i++){
    sm += s.SalePosArr[i].Sum;
  }
  s.cSum = sm;
}

void Initalize_cSum(SaleArray S, int num) {
  for (int i=0; i<num; i++){
    Init_cSum(S[i]);
  }
}

double Median(SaleArray S, int num) {
  double sm;
  sm = 0.0;
  for (int i=0; i<num; i++){
    sm += S[i].cSum;
  }
  return sm/num;
}

int UpThan(double pr, SaleArray S, int num) {
  int n;
  n = 0;
  for (int i=0; i<num; i++){
    if (S[i].cSum > pr) {
      n++;
      //ShowMessage(S[i].Date->DateTimeString());
    }
  }
  return n;
}

int qStorno(SaleArray S, int num) {
  int n;
  n = 0;
  for (int i=0; i<num; i++){
    if (S[i].Amount != 0) {
      n += S[i].Storno;
    }
  }
  return n;
}

void Razlog(SaleArray S, int num, tSums Sums, int n, double porog) {
  int tn;

  tn = 0;

  for (int i=0; i<n; i++){
    Sums[i] = 0.0;
  }
  for (int i=0; i<num; i++){
    if (S[i].cSum > 0.0) {
      tn = (int)ceil(S[i].cSum) / (int)porog;
      if (tn > n) {
        tn = n-1;
      }
      Sums[tn]++;
    }
  }
}

void SaleToDay(SaleArray S, int chC, SaleArray *dsa, int pos[7]){
  char dn;
  memset(pos, 0, sizeof(pos)*7);

  for (int i = 0; i < chC; i++) {
    // Распихиваем i-й чек в день недели
    dn = DayOfTheWeek(*S[i].Date);
    dn--;
    // 1-й день недели - понедельник
    dsa[dn][pos[dn]] = S[i];
    pos[dn]++;

  }
}

void SaleToTime(SaleArray S, int chC, int Ts[7][29]) {
  char dn;
  int j;
  TDateTime StartTime;
  int delta;
  memset(Ts, 0, sizeof(int)*7*29);

  StartTime = StrToTime("08:00:00");
  for (int i = 0; i < chC; i++) {
    dn = DayOfTheWeek(*S[i].Date);
    dn--;

    delta = MinutesBetween(TimeOf(*S[i].Date), TimeOf(StartTime));
    if (delta < 30) j = 0;
    else if (delta < 2*30) j = 1;
    else if (delta < 3*30) j = 2;
    else if (delta < 4*30) j = 3;
    else if (delta < 5*30) j = 4;
    else if (delta < 6*30) j = 5;
    else if (delta < 7*30) j = 6;
    else if (delta < 8*30) j = 7;
    else if (delta < 9*30) j = 8;
    else if (delta < 10*30) j = 9;
    else if (delta < 11*30) j = 10;
    else if (delta < 12*30) j = 11;
    else if (delta < 13*30) j = 12;
    else if (delta < 14*30) j = 13;
    else if (delta < 15*30) j = 14;
    else if (delta < 16*30) j = 15;
    else if (delta < 17*30) j = 16;
    else if (delta < 18*30) j = 17;
    else if (delta < 19*30) j = 18;
    else if (delta < 20*30) j = 19;
    else if (delta < 21*30) j = 20;
    else if (delta < 22*30) j = 21;
    else if (delta < 23*30) j = 22;
    else if (delta < 24*30) j = 23;
    else if (delta < 25*30) j = 24;
    else if (delta < 26*30) j = 25;
    else if (delta < 27*30) j = 26;
    else if (delta < 28*30) j = 27;
    else j = 28;

    Ts[dn][j]++;
  }
}

void SaleToTimeD(SaleArray S, int chC, double Ts[7][29]) {
  char dn;
  int j;
  TDateTime StartTime;
  int delta;
  memset(Ts, 0, sizeof(double)*7*29);

  StartTime = StrToTime("08:00:00");
  for (int i = 0; i < chC; i++) {
    dn = DayOfTheWeek(*S[i].Date);
    dn--;

    delta = MinutesBetween(TimeOf(*S[i].Date), TimeOf(StartTime));
    if (delta < 30) j = 0;
    else if (delta < 2*30) j = 1;
    else if (delta < 3*30) j = 2;
    else if (delta < 4*30) j = 3;
    else if (delta < 5*30) j = 4;
    else if (delta < 6*30) j = 5;
    else if (delta < 7*30) j = 6;
    else if (delta < 8*30) j = 7;
    else if (delta < 9*30) j = 8;
    else if (delta < 10*30) j = 9;
    else if (delta < 11*30) j = 10;
    else if (delta < 12*30) j = 11;
    else if (delta < 13*30) j = 12;
    else if (delta < 14*30) j = 13;
    else if (delta < 15*30) j = 14;
    else if (delta < 16*30) j = 15;
    else if (delta < 17*30) j = 16;
    else if (delta < 18*30) j = 17;
    else if (delta < 19*30) j = 18;
    else if (delta < 20*30) j = 19;
    else if (delta < 21*30) j = 20;
    else if (delta < 22*30) j = 21;
    else if (delta < 23*30) j = 22;
    else if (delta < 24*30) j = 23;
    else if (delta < 25*30) j = 24;
    else if (delta < 26*30) j = 25;
    else if (delta < 27*30) j = 26;
    else if (delta < 28*30) j = 27;
    else j = 28;

    Ts[dn][j]+=S[i].cSum;
  }
}
