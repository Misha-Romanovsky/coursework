object MainForm: TMainForm
  Left = 664
  Top = 240
  Width = 870
  Height = 629
  Caption = #1050#1091#1088#1089#1086#1074#1072
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -10
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  FormStyle = fsMDIForm
  Menu = MainMenu1
  OldCreateOrder = False
  OnClose = FormClose
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object StatusBar1: TStatusBar
    Left = 0
    Top = 551
    Width = 854
    Height = 19
    Panels = <>
    SimplePanel = False
  end
  object MainMenu1: TMainMenu
    Left = 824
    Top = 520
    object N1: TMenuItem
      Caption = #1060#1072#1081#1083
      object N4: TMenuItem
        Action = LoadImageAction
      end
      object N5: TMenuItem
        Caption = #1047#1072#1082#1088#1080#1090#1080
        OnClick = N5Click
      end
      object N6: TMenuItem
        Caption = #1047#1073#1077#1088#1077#1075#1090#1080' '#1088#1077#1079#1091#1083#1100#1090#1072#1090
        OnClick = N6Click
      end
      object N3: TMenuItem
        Caption = '-'
      end
      object N2: TMenuItem
        Action = ExitAction
      end
    end
    object N7: TMenuItem
      Caption = #1060#1110#1083#1100#1090#1088
      object N8: TMenuItem
        Action = FilterAction
      end
    end
    object N9: TMenuItem
      Caption = #1056#1086#1079#1087#1110#1079#1085#1072#1085#1085#1103
      OnClick = N9Click
    end
  end
  object ActionList1: TActionList
    Left = 792
    Top = 520
    object ExitAction: TAction
      Caption = #1042#1080#1093#1110#1076
      OnExecute = ExitActionExecute
    end
    object LoadImageAction: TAction
      Caption = #1047#1072#1075#1088#1091#1079#1080#1090#1080' '#1079#1086#1073#1088#1072#1078#1077#1085#1085#1103
      OnExecute = LoadImageActionExecute
    end
    object FilterAction: TAction
      Caption = #1059#1089#1077#1088#1077#1076#1085#1102#1102#1095#1080#1081' '#1092#1110#1083#1100#1090#1088
      OnExecute = FilterActionExecute
    end
  end
  object OpenPictureDialog1: TOpenPictureDialog
    Left = 760
    Top = 520
  end
end
