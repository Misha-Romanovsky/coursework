object DialogForm: TDialogForm
  Left = 358
  Top = 363
  BorderStyle = bsDialog
  ClientHeight = 210
  ClientWidth = 493
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 120
  TextHeight = 16
  object Panel: TPanel
    Left = 0
    Top = 0
    Width = 493
    Height = 210
    Align = alClient
    TabOrder = 0
    object Bevel1: TBevel
      Left = 1
      Top = 1
      Width = 491
      Height = 208
      Align = alClient
    end
    object BitBtn1: TBitBtn
      Left = 376
      Top = 24
      Width = 105
      Height = 41
      TabOrder = 0
      Kind = bkOK
    end
    object BitBtn2: TBitBtn
      Left = 376
      Top = 72
      Width = 105
      Height = 41
      TabOrder = 1
      Kind = bkCancel
    end
  end
end
