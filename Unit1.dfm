object Form1: TForm1
  Left = 243
  Top = 172
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = 'Parser'
  ClientHeight = 266
  ClientWidth = 498
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poDefaultSizeOnly
  PixelsPerInch = 96
  TextHeight = 13
  object PageControl1: TPageControl
    Left = 0
    Top = 0
    Width = 497
    Height = 265
    ActivePage = TabSheet3
    TabIndex = 2
    TabOrder = 0
    object TabSheet1: TTabSheet
      Caption = 'TabSheet1'
      object Label1: TLabel
        Left = 2
        Top = 184
        Width = 31
        Height = 13
        Caption = #1055#1086#1088#1086#1075
      end
      object Edit1: TEdit
        Left = 0
        Top = 8
        Width = 377
        Height = 21
        TabOrder = 0
      end
      object Memo1: TMemo
        Left = 0
        Top = 32
        Width = 377
        Height = 145
        ReadOnly = True
        TabOrder = 1
      end
      object Edit2: TEdit
        Left = 39
        Top = 184
        Width = 121
        Height = 21
        TabOrder = 2
        Text = '100,0'
      end
      object Button2: TButton
        Left = 200
        Top = 184
        Width = 75
        Height = 25
        Caption = 'Parse'
        TabOrder = 3
        OnClick = Button2Click
      end
      object Button3: TButton
        Left = 280
        Top = 184
        Width = 75
        Height = 25
        Caption = 'Stat'
        Enabled = False
        TabOrder = 4
        OnClick = Button3Click
      end
      object Button4: TButton
        Left = 368
        Top = 184
        Width = 75
        Height = 25
        Caption = 'Exit'
        TabOrder = 5
        OnClick = Button4Click
      end
      object CheckBox1: TCheckBox
        Left = 384
        Top = 40
        Width = 97
        Height = 17
        Caption = 'v3.0'
        TabOrder = 6
      end
      object Button1: TButton
        Left = 384
        Top = 8
        Width = 24
        Height = 22
        Caption = '...'
        TabOrder = 7
        OnClick = Button1Click
      end
    end
    object TabSheet2: TTabSheet
      Caption = 'TabSheet2'
      ImageIndex = 1
      object StringGrid1: TStringGrid
        Left = 0
        Top = 0
        Width = 489
        Height = 233
        Ctl3D = False
        FixedCols = 0
        FixedRows = 0
        ParentCtl3D = False
        PopupMenu = PopupMenu1
        TabOrder = 0
        ColWidths = (
          123
          122
          64
          64
          64)
      end
    end
    object TabSheet3: TTabSheet
      Caption = 'TabSheet3'
      ImageIndex = 2
      object Image1: TImage
        Left = 0
        Top = 0
        Width = 369
        Height = 185
      end
      object Edit3: TEdit
        Left = 376
        Top = 8
        Width = 73
        Height = 21
        ReadOnly = True
        TabOrder = 0
        Text = '5'
      end
      object UpDown1: TUpDown
        Left = 449
        Top = 8
        Width = 15
        Height = 21
        Associate = Edit3
        Min = 1
        Max = 10
        Position = 5
        TabOrder = 1
        Wrap = False
      end
      object Button5: TButton
        Left = 384
        Top = 160
        Width = 75
        Height = 25
        Caption = 'Draw'
        TabOrder = 2
        OnClick = Button5Click
      end
    end
    object TabSheet4: TTabSheet
      Caption = 'TabSheet4'
      ImageIndex = 3
      object Memo2: TMemo
        Left = 0
        Top = 0
        Width = 185
        Height = 89
        TabOrder = 0
      end
    end
  end
  object OpenDialog1: TOpenDialog
    DefaultExt = '*.rep'
    Left = 416
  end
  object PopupMenu1: TPopupMenu
    Left = 448
    object N1: TMenuItem
      Caption = #1050#1086#1087#1080#1088#1086#1074#1072#1090#1100
      OnClick = N1Click
    end
  end
end
