Dim choice
Dim oShell
Dim fso
Set oShell = CreateObject("WScript.Shell")
Set fso = CreateObject("Scripting.FileSystemObject")

choice = MsgBox("Bienvenue dans l'installateur du Twitch Booster pour OBS et XSplit. Souhaitez-vous proc" & Chr(233) & "der " & _
               Chr(224) & " l'installation ?", vbYesNo, "Twitch Booster")

If choice = vbYes Then
    Call WriteFlag("Yes")
    WScript.Sleep 5000
    MsgBox "Installation termin" & Chr(233) & "e, vous pouvez maintenant streamer sur Twitch sans aucun probl" & Chr(232) & _
           "me de connexion ou autre !", vbOKOnly, "Twitch Booster"
Else
    Call WriteFlag("No")
    MsgBox "Vous avez annul" & Chr(233) & " l'installation de Twitch Booster", vbOKOnly, "Twitch Booster"
End If

Sub WriteFlag(status)
    Dim filePath
    filePath = CreateObject("Scripting.FileSystemObject").GetParentFolderName(WScript.ScriptFullName) & "\flag.txt"
    Set file = fso.CreateTextFile(filePath, True)
    file.WriteLine(status)
    file.Close
End Sub