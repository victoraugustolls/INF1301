del /S /Q entregavel\*

echo d | xcopy /S /V /Y /E bat entregavel\bat
echo d | xcopy /S /V /Y /E bin entregavel\bin
echo d | xcopy /S /V /Y /E include entregavel\include
echo d | xcopy /S /V /Y /E lib entregavel\lib
echo d | xcopy /S /V /Y /T /E log entregavel\log
echo d | xcopy /S /V /Y /E pecas entregavel\pecas
echo d | xcopy /S /V /Y /E relatorios entregavel\relatorios
echo d | xcopy /S /V /Y /E script entregavel\script
echo d | xcopy /S /V /Y /E src entregavel\src

copy LEIAME.TXT entregavel\LEIAME.TXT
copy COMO_ADD_NOVA_PECA.TXT entregavel\COMO_ADD_NOVA_PECA.TXT
copy RENOMEIA_BAT_EXE_LIB.BAT entregavel\RENOMEIA_BAT_EXE_LIB.BAT.TXT

ren entregavel\bat\*.BAT *.BAT.TXT
ren entregavel\bin\*.EXE *.EXE.TXT
ren entregavel\lib\*.lib *.lib.TXT
