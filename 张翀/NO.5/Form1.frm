VERSION 5.00
Begin VB.Form Creeper 
   BackColor       =   &H000080FF&
   Caption         =   "Creeper?"
   ClientHeight    =   6825
   ClientLeft      =   120
   ClientTop       =   465
   ClientWidth     =   12735
   Icon            =   "Form1.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   ScaleHeight     =   6825
   ScaleWidth      =   12735
   StartUpPosition =   3  '窗口缺省
   Begin VB.Frame Frame2 
      BackColor       =   &H00FF00FF&
      Caption         =   "已自鲨"
      Height          =   1575
      Left            =   10680
      TabIndex        =   15
      Top             =   3240
      Visible         =   0   'False
      Width           =   1575
   End
   Begin VB.CommandButton Command2 
      BackColor       =   &H00FFFF00&
      Caption         =   "提示一次"
      Height          =   255
      Left            =   5520
      Style           =   1  'Graphical
      TabIndex        =   14
      Top             =   5160
      Visible         =   0   'False
      Width           =   1215
   End
   Begin VB.TextBox Text3 
      BackColor       =   &H000000FF&
      Height          =   855
      Index           =   2
      Left            =   1080
      TabIndex        =   13
      Top             =   3600
      Visible         =   0   'False
      Width           =   375
   End
   Begin VB.TextBox Text3 
      BackColor       =   &H000000FF&
      Height          =   270
      Index           =   1
      Left            =   480
      TabIndex        =   12
      Top             =   3120
      Visible         =   0   'False
      Width           =   855
   End
   Begin VB.TextBox Text3 
      BackColor       =   &H000000FF&
      Height          =   270
      Index           =   0
      Left            =   240
      TabIndex        =   11
      Top             =   3600
      Visible         =   0   'False
      Width           =   735
   End
   Begin VB.Timer Timer1 
      Interval        =   1
      Left            =   5880
      Top             =   6480
   End
   Begin VB.Frame Frame1 
      BackColor       =   &H0000FF00&
      Caption         =   "生命值："
      Height          =   975
      Index           =   1
      Left            =   10800
      TabIndex        =   7
      Top             =   600
      Width           =   1215
   End
   Begin VB.Frame Frame1 
      BackColor       =   &H0000FF00&
      Caption         =   "生命值："
      Height          =   975
      Index           =   0
      Left            =   360
      TabIndex        =   6
      Top             =   480
      Width           =   1215
   End
   Begin VB.PictureBox Picture3 
      Height          =   1575
      Left            =   10680
      Picture         =   "Form1.frx":1084A
      ScaleHeight     =   1515
      ScaleWidth      =   1515
      TabIndex        =   5
      Top             =   3240
      Width           =   1575
   End
   Begin VB.PictureBox Picture2 
      Height          =   2415
      Left            =   120
      Picture         =   "Form1.frx":11EC5
      ScaleHeight     =   2355
      ScaleWidth      =   1635
      TabIndex        =   4
      Top             =   2640
      Width           =   1695
   End
   Begin VB.TextBox Text2 
      BackColor       =   &H0000FF00&
      ForeColor       =   &H000000FF&
      Height          =   495
      Left            =   2880
      TabIndex        =   2
      Text            =   "Text2"
      Top             =   6000
      Width           =   6615
   End
   Begin VB.CommandButton Command1 
      BackColor       =   &H0000FFFF&
      Caption         =   "Command1"
      Height          =   495
      Left            =   4440
      Style           =   1  'Graphical
      TabIndex        =   1
      Top             =   4440
      Width           =   3495
   End
   Begin VB.TextBox Text1 
      BackColor       =   &H00FFFF00&
      ForeColor       =   &H00FF0000&
      Height          =   615
      Left            =   2760
      TabIndex        =   0
      Text            =   "Text1"
      Top             =   240
      Width           =   6615
   End
   Begin VB.PictureBox Picture1 
      BackColor       =   &H0000FFFF&
      Height          =   4575
      Left            =   2160
      Picture         =   "Form1.frx":145D2
      ScaleHeight     =   4515
      ScaleWidth      =   7995
      TabIndex        =   3
      Top             =   1200
      Width           =   8055
   End
   Begin VB.Label Label1 
      BackColor       =   &H000000FF&
      Height          =   495
      Index           =   2
      Left            =   1320
      TabIndex        =   10
      Top             =   5760
      Width           =   375
   End
   Begin VB.Label Label1 
      BackColor       =   &H000000FF&
      Height          =   495
      Index           =   1
      Left            =   720
      TabIndex        =   9
      Top             =   5760
      Width           =   375
   End
   Begin VB.Label Label1 
      BackColor       =   &H000000FF&
      Height          =   495
      Index           =   0
      Left            =   120
      TabIndex        =   8
      Top             =   5760
      Width           =   375
   End
End
Attribute VB_Name = "Creeper"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Dim flag, start As Boolean
Dim life1, life2, p, h, w As Integer
Dim s(101) As String

Function Check(words As String) As Boolean
    Dim tmp As String
    Dim res As Boolean
    Dim p As Integer
    res = True
    tmp = UCase(words)
    ans = UCase(Text2.Text)
    p = 1
    If Len(ans) = 0 Then
        res = False
        GoTo Last
    End If
    For i = 1 To Len(tmp)
        If Asc(Mid(tmp, i, 1)) >= 65 And Asc(Mid(tmp, i, 1)) <= 90 Then
            Do While p <= Len(ans) And (Asc(Mid(ans, p, 1)) < 65 Or Asc(Mid(ans, p, 1)) > 90)
                p = p + 1
            Loop
            If p > Len(ans) Or Mid(tmp, i, 1) <> Mid(ans, p, 1) Then
                res = False
                GoTo Last
            End If
            p = p + 1
        End If
    Next
Last:
    Check = res
End Function

Private Sub Command1_Click()
    If Command1.Caption = "我赢了！" Then
        Command1.Caption = "重新开始"
    End If
    If Command1.Caption = "确认" Then
        If Check(s(p)) Then
            MsgBox ("Well done! You do one damage to Creeper!")
            life2 = life2 - 1
            p = p + 1
            If p >= 49 Then
                Exit Sub
            End If
            Text1.Text = s(p)
            Text2.Text = ""
            p = p + 1
        Else
            MsgBox ("Creeper!")
            flag = True
        End If
    End If
    If Command1.Caption = "开始" Or Command1.Caption = "重新开始" Then
        Command1.Caption = "确认"
        Command2.Visible = True
        Frame2.Visible = False
        start = True
        Randomize
        p = Int(Rnd * 29)
        Text1.Text = s(p)
        Text2.Text = ""
        For i = 0 To 2
            Label1(i).Visible = True
            Text3(i).Visible = False
        Next
        life1 = 2
        life2 = 10
        p = p + 1
    End If
End Sub

Private Sub Command2_Click()
    If start = False Then
        Exit Sub
    End If
    Text2.Text = s(p)
    Command2.Visible = False
End Sub

Private Sub Form_Load()
    Creeper.Caption = "Creeper?"
    Text1.Text = "这是Creeper的回答框"
    Text2.Text = "这是你的答题框"
    Command1.Caption = "开始"
    flag = False
    start = False
    Randomize
    p = Int(Rnd * 29)
    h = Creeper.Height
    w = Creeper.Width
    life1 = 2
    life2 = 10
    s(0) = "Creeper?"
    s(1) = "Awww man!"
    s(2) = "So we back in the mine"
    s(3) = "Got our pickaxe swinging from side to side"
    s(4) = "Side,side to side..."
    s(5) = "This task's a grueling one , hope to find some diamonds tonight,night,night Diamonds tonight..."
    s(6) = "Heads up"
    s(7) = "You hear a sound , turn around and look up"
    s(8) = "Total shock fills your body"
    s(9) = "Oh no it's you again , I could never forget those eyes,eyes,eyes"
    s(10) = "Eyes,eyes,eyes..."
    s(11) = "Cause baby tonight , the creeper's trying to steal all our stuff again"
    s(12) = "Cause baby tonight , you grab your pick , shovel and bolt again , bolt again"
    s(13) = "And run,run until it's done,done , until the sun comes up in the morn"
    s(14) = "Cause baby tonight , the creeper's trying to steal all our stuff again , stuff again"
    s(15) = "Just when you think you're safe , overhear some hissing from , right behind"
    s(16) = "Right,right behind..."
    s(17) = "That's a nice life you have ,shame it's gotta end at this time,time,time"
    s(18) = "Time,time,time , time..."
    s(19) = "Blows up , then your health bar drops and you could use a 1-up"
    s(20) = "Get inside , don't be tardy"
    s(21) = "So now you are stuck in there , half a heart is left but don't die,die,die"
    s(22) = "Die,die,die..."
    s(23) = "Cause baby tonight , the creeper's trying to steal all our stuff again"
    s(24) = "Cause baby tonight , you grab your pick , shovel and bolt again,bolt again"
    s(25) = "And run,run until it's done,done , until the sun comes up in the morn'"
    s(26) = "Cause baby tonight , the creeper's trying to steal all our stuff again"
    s(27) = "Creepers , you're mine , haha"
    s(28) = "Dig up diamonds , and craft those diamonds and make some armour , get it baby"
    s(29) = "Go and forge that like you so , MLG pro , the sword's made of diamonds , so come at me bro"
    s(30) = "Huh"
    s(31) = "Training in your room under the torchlight , hone that form to get you ready for the big fight"
    s(32) = "Every single day and the whole night , Creeper's out prowlin' , hmm - alright"
    s(33) = "Look at me , look at you , take my revenge that's what I'm gonna do"
    s(34) = "I'm a - warrior baby , what else is new ? And my blade's gonna tearthrough you , bring it"
    s(35) = "The creeper's trying to steal our stuff again"
    s(36) = "Yeah , let's take back the world"
    s(37) = "Hahhah"
    s(38) = "Grab your sword , armour and go"
    s(39) = "It's on"
    s(40) = "Take your revenge"
    s(41) = "Ahhoahh"
    s(42) = "So fight,fight like it's the last,last night of your life,life show them your bite"
    s(43) = "Wooo"
    s(44) = "Cause baby tonight ,the creeper's trying to steal all our stuff again"
    s(45) = "Cause baby tonight , you grab your pick , shovel and bolt again,bolt again"
    s(46) = "And run,run until it's done,done , until the sun comes up in the morn'"
    s(47) = "Cause baby tonight , the creeper's trying to steal all our stuff again"
    s(48) = "Woooo"
    MsgBox ("Creeper? Awww man! 按下开始键开始接龙!")
End Sub

Private Sub Timer1_Timer()
    Frame1(0).Caption = "生命值" + Str(life1 + 1)
    Frame1(1).Caption = "生命值" + Str(life2)
    Creeper.Height = h
    Creeper.Width = w
    If start = False Then
        Exit Sub
    End If
    If p >= 49 Or life2 <= 0 Then
        start = False
        life2 = 0
        Frame2.Visible = True
        Command2.Visible = False
        Command1.Caption = ("我赢了！")
        MsgBox ("Creeper不堪受辱，自鲨了！")
    End If
    If flag = True And life1 >= 0 Then
        Label1(life1).Visible = False
        Text3(2 - life1).Visible = True
        life1 = life1 - 1
        flag = False
    End If
    If life1 < 0 Then
        If Command1.Caption = "确认" Then
            MsgBox ("你输了")
        End If
        Command2.Visible = False
        Command1.Caption = "重新开始"
    End If
End Sub
