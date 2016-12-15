nmake /F..\comp\TEST_TAB_DEBUG.make 
copy ..\obj\TEST_TAB_DEBUG.exe ..\..\bin\TEST_TAB_DEBUG.EXE
if exist ..\err\TEST_TAB_DEBUG.err notepad ..\err\TEST_TAB_DEBUG.err
