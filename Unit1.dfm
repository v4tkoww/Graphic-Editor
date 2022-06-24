object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Form1'
  ClientHeight = 654
  ClientWidth = 964
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  Menu = MainMenu
  OldCreateOrder = False
  OnCreate = FormCreate
  OnKeyDown = OnKeyDown
  PixelsPerInch = 96
  TextHeight = 13
  object Image1: TImage
    Left = 80
    Top = 8
    Width = 873
    Height = 593
    OnMouseDown = OnMouseDown
    OnMouseMove = OnMouseMove
    OnMouseUp = OnMouseUp
  end
  object Label1: TLabel
    Left = 580
    Top = 631
    Width = 45
    Height = 13
    Caption = #1058#1086#1083#1097#1080#1085#1072
  end
  object Label2: TLabel
    Left = 703
    Top = 631
    Width = 67
    Height = 13
    Caption = #1050#1086#1083'-'#1074#1086' '#1091#1075#1083#1086#1074
  end
  object Label3: TLabel
    Left = 448
    Top = 633
    Width = 75
    Height = 13
    Caption = #1057#1090#1080#1083#1100' '#1079#1072#1083#1080#1074#1082#1080
  end
  object Label4: TLabel
    Left = 80
    Top = 633
    Width = 59
    Height = 13
    Caption = #1062#1074#1077#1090' '#1083#1080#1085#1080#1080
  end
  object Label5: TLabel
    Left = 191
    Top = 633
    Width = 70
    Height = 13
    Caption = #1062#1074#1077#1090' '#1079#1072#1083#1080#1074#1082#1080
  end
  object Label6: TLabel
    Left = 320
    Top = 634
    Width = 64
    Height = 13
    Caption = #1057#1090#1080#1083#1100' '#1083#1080#1085#1080#1080
  end
  object Label7: TLabel
    Left = 8
    Top = 101
    Width = 25
    Height = 13
    Caption = #1044#1091#1075#1072
  end
  object SpinEdit1: TSpinEdit
    Left = 580
    Top = 607
    Width = 85
    Height = 22
    MaxValue = 100
    MinValue = 1
    TabOrder = 0
    Value = 1
    OnChange = SpinEdit1Change
  end
  object CheckBox1: TCheckBox
    Left = 848
    Top = 607
    Width = 105
    Height = 37
    Caption = #1054#1087#1080#1089#1072#1085#1085#1099#1081
    Checked = True
    State = cbChecked
    TabOrder = 1
  end
  object SpinEdit2: TSpinEdit
    Left = 703
    Top = 607
    Width = 121
    Height = 22
    MaxValue = 100
    MinValue = 3
    TabOrder = 2
    Value = 3
    OnChange = SpinEdit1Change
  end
  object ColorBox1: TColorBox
    Left = 80
    Top = 607
    Width = 105
    Height = 22
    DefaultColorColor = clBlue
    NoneColorColor = clBlue
    Selected = clBlue
    TabOrder = 3
    OnChange = ColorBox1Change
  end
  object ColorBox2: TColorBox
    Left = 191
    Top = 607
    Width = 105
    Height = 22
    DefaultColorColor = clWhite
    NoneColorColor = clWhite
    Selected = clWhite
    TabOrder = 4
    OnChange = ColorBox2Change
  end
  object ComboBox1: TComboBox
    Left = 320
    Top = 607
    Width = 113
    Height = 21
    ItemIndex = 0
    TabOrder = 5
    Text = 'Solid'
    OnChange = ComboBox1Change
    Items.Strings = (
      'Solid'
      'Dash'
      'Dot'
      'DashDot'
      'DashDotDot')
  end
  object ComboBox2: TComboBox
    Left = 448
    Top = 607
    Width = 113
    Height = 21
    ItemIndex = 0
    TabOrder = 6
    Text = 'Solid'
    OnChange = ComboBox2Change
    Items.Strings = (
      'Solid'
      'Clear'
      'Horizontal'
      'Vertical'
      'Diagonal'
      'BDiagonal '
      'Cross'
      'DiagCross')
  end
  object Panel1: TPanel
    Left = 680
    Top = 607
    Width = 9
    Height = 41
    TabOrder = 7
  end
  object Button1: TButton
    Left = 8
    Top = 8
    Width = 66
    Height = 25
    Caption = #1058#1086#1095#1082#1072
    TabOrder = 8
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 8
    Top = 39
    Width = 66
    Height = 25
    Caption = #1051#1080#1085#1080#1103
    TabOrder = 9
    OnClick = Button2Click
  end
  object Button3: TButton
    Left = 8
    Top = 70
    Width = 66
    Height = 25
    Caption = #1055#1086#1083#1080#1083#1080#1085#1080#1103
    TabOrder = 10
    OnClick = Button3Click
  end
  object Button4: TButton
    Left = 8
    Top = 120
    Width = 66
    Height = 25
    Caption = #1050#1088#1091#1075
    TabOrder = 11
    OnClick = Button4Click
  end
  object Button5: TButton
    Left = 8
    Top = 151
    Width = 66
    Height = 25
    Caption = #1044#1091#1075#1072
    TabOrder = 12
    OnClick = Button5Click
  end
  object Button6: TButton
    Left = 8
    Top = 182
    Width = 66
    Height = 25
    Caption = #1055#1088#1103#1084#1086#1091#1075#1083'.'
    TabOrder = 13
    OnClick = Button6Click
  end
  object Button7: TButton
    Left = 8
    Top = 213
    Width = 66
    Height = 25
    Caption = #1052#1085#1086#1075#1086#1091#1075#1083'.'
    TabOrder = 14
    OnClick = Button7Click
  end
  object Button8: TButton
    Left = 8
    Top = 270
    Width = 66
    Height = 25
    Caption = #1051#1072#1089#1090#1080#1082
    TabOrder = 15
    OnClick = Button8Click
  end
  object MainMenu: TMainMenu
    Left = 296
    Top = 112
    object File1: TMenuItem
      Caption = #1060#1072#1081#1083
      object Sozd1: TMenuItem
        Caption = #1057#1086#1079#1076#1072#1090#1100
        OnClick = Sozd1Click
      end
      object Open1: TMenuItem
        Caption = #1054#1090#1082#1088#1099#1090#1100
        OnClick = Open1Click
      end
      object Save1: TMenuItem
        Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100
        OnClick = Save1Click
      end
    end
  end
  object ColorDialog1: TColorDialog
    Left = 680
    Top = 336
  end
  object OpenDialog1: TOpenDialog
    Left = 728
    Top = 216
  end
  object SaveDialog1: TSaveDialog
    Left = 728
    Top = 272
  end
end
