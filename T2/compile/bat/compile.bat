nmake /F..\comp\TEST_LIS.make 
copy ..\obj\TEST_LIS.exe ..\..\bin\TEST_LIS.EXE
if exist ..\err\TEST_LIS.err notepad ..\err\TEST_LIS.err

nmake /F..\comp\TEST_VMV.make 
copy ..\obj\TEST_VMV.exe ..\..\bin\TEST_VMV.EXE
if exist ..\err\TEST_VMV.err notepad ..\err\TEST_VMV.err

nmake /F..\comp\TEST_PCA.make 
copy ..\obj\TEST_PCA.exe ..\..\bin\TEST_PCA.EXE
if exist ..\err\TEST_PCA.err notepad ..\err\TEST_PCA.err

nmake /F..\comp\TEST_TAB.make 
copy ..\obj\TEST_TAB.exe ..\..\bin\TEST_TAB.EXE
if exist ..\err\TEST_TAB.err notepad ..\err\TEST_TAB.err