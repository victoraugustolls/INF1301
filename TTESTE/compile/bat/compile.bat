nmake /F..\comp\TEST_LIS.make 
copy ..\obj\TEST_LIS.exe ..\..\bin\TEST_LIS.EXE
if exist ..\err\TEST_LIS.err notepad ..\err\TEST_LIS.err