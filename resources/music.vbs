Dim oPlayer, strFile, strDir
Set oPlayer = CreateObject("WMPlayer.OCX")

strDir = CreateObject("Scripting.FileSystemObject").GetParentFolderName(WScript.ScriptFullName)
strFile = strDir & "\music\song.mp3"

oPlayer.URL = strFile
oPlayer.controls.play 
While oPlayer.playState <> 1
  WScript.Sleep 100
Wend

oPlayer.close