//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Dialogs.hpp>
#include <ComCtrls.hpp>
#include <Grids.hpp>
#include <Menus.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
  TPageControl *PageControl1;
  TTabSheet *TabSheet1;
  TEdit *Edit1;
  TMemo *Memo1;
  TEdit *Edit2;
  TButton *Button2;
  TButton *Button3;
  TButton *Button4;
  TCheckBox *CheckBox1;
  TButton *Button1;
  TOpenDialog *OpenDialog1;
  TLabel *Label1;
  TTabSheet *TabSheet2;
  TStringGrid *StringGrid1;
  TPopupMenu *PopupMenu1;
  TMenuItem *N1;
  TTabSheet *TabSheet3;
  TImage *Image1;
  TEdit *Edit3;
  TUpDown *UpDown1;
  TButton *Button5;
  TTabSheet *TabSheet4;
  TMemo *Memo2;
        void __fastcall Button1Click(TObject *Sender);
  void __fastcall Button2Click(TObject *Sender);
  void __fastcall Button3Click(TObject *Sender);
  void __fastcall Button4Click(TObject *Sender);
  void __fastcall N1Click(TObject *Sender);
  void __fastcall Button5Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
