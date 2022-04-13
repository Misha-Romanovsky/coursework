inherited AverageFilterDialogForm: TAverageFilterDialogForm
  Left = 342
  Top = 365
  Caption = #1059#1089#1077#1088#1077#1076#1085#1102#1102#1095#1080#1081' '#1092#1110#1083#1100#1090#1088
  ClientHeight = 106
  ClientWidth = 403
  OldCreateOrder = True
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  inherited Panel: TPanel
    Width = 403
    Height = 106
    inherited Bevel1: TBevel
      Width = 401
      Height = 104
    end
    object Label1: TLabel [1]
      Left = 33
      Top = 26
      Width = 150
      Height = 13
      Caption = #1055#1086#1088#1110#1075' '#1091#1089#1077#1088#1077#1076#1085#1102#1102#1095#1086#1075#1086' '#1092#1110#1083#1100#1090#1088#1091
    end
    object Edit1: TEdit
      Left = 33
      Top = 46
      Width = 247
      Height = 21
      TabOrder = 2
      Text = '1'
      OnKeyPress = Edit1KeyPress
    end
  end
end
