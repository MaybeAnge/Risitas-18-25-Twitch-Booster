Dim oPlayer, strFile, strDir, delay
Set oPlayer = CreateObject("WMPlayer.OCX")

strDir = CreateObject("Scripting.FileSystemObject").GetParentFolderName(WScript.ScriptFullName)
strFile = strDir & "\music\error.mp3"

Randomize
delay = Int((10000 - 700 + 1) * Rnd + 500)
WScript.Sleep delay

oPlayer.URL = strFile
oPlayer.controls.play 

While oPlayer.playState <> 1
  WScript.Sleep 100
Wend

oPlayer.close