object ChildForm: TChildForm
  Left = 708
  Top = 147
  Width = 820
  Height = 704
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -10
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  FormStyle = fsMDIChild
  OldCreateOrder = False
  Position = poDefault
  Visible = True
  OnClose = FormClose
  PixelsPerInch = 96
  TextHeight = 13
  object Splitter1: TSplitter
    Left = 0
    Top = 590
    Width = 804
    Height = 3
    Cursor = crVSplit
    Align = alBottom
  end
  object Memo1: TMemo
    Left = 0
    Top = 593
    Width = 804
    Height = 72
    Align = alBottom
    ReadOnly = True
    ScrollBars = ssBoth
    TabOrder = 0
  end
  object ScrollBox1: TScrollBox
    Left = 0
    Top = 0
    Width = 804
    Height = 590
    Align = alClient
    TabOrder = 1
    object Image1: TImage
      Left = 0
      Top = 0
      Width = 657
      Height = 468
      AutoSize = True
    end
  end
end
