@ECHO  OFF
REM  Compila todos os exemplos simples 

pushd  .

del *.err
del TRAB1-1.exe

del *.obj
nmake /Ftestelista.make 

copy  *.err  tudo.err

notepad tudo.err

popd
