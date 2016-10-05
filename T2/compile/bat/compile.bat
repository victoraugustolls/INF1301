nmake /F..\comp\TEST_LIS.make 
copy ..\obj\TEST_LIS.exe ..\..\bin\TEST_LIS.EXE
if exist ..\err\TEST_LIS.err notepad ..\err\TEST_LIS.err

nmake /F..\comp\TEST_VMV.make 
copy ..\obj\TEST_VMV.exe ..\..\bin\TEST_VMV.EXE
if exist ..\err\TEST_VMV.err notepad ..\err\TEST_VMV.err