nmake /F..\comp\TEST_LIS.make 
copy ..\obj\TEST_LIS.exe ..\..\bin\TEST_LIS.EXE
if exist ..\err\TEST_LIS.err notepad ..\err\TEST_LIS.err

nmake /F..\comp\TEST_VMV.make 
copy ..\obj\TEST_VMV.exe ..\..\bin\TEST_VMV.EXE
if exist ..\err\TEST_VMV.err notepad ..\err\TEST_VMV.err

nmake /F..\comp\TEST_PCA.make 
copy ..\obj\TEST_PCA.exe ..\..\bin\TEST_PCA.EXE
if exist ..\err\TEST_PCA.err notepad ..\err\TEST_PCA.err

nmake /F..\comp\TEST_TAB_DEBUG.make 
copy ..\obj\TEST_TAB_DEBUG.exe ..\..\bin\TEST_TAB_DEBUG.EXE
if exist ..\err\TEST_TAB_DEBUG.err notepad ..\err\TEST_TAB_DEBUG.err

nmake /F..\comp\TEST_CSA.make 
copy ..\obj\TEST_CSA.exe ..\..\bin\TEST_CSA.EXE
if exist ..\err\TEST_CSA.err notepad ..\err\TEST_CSA.err

nmake /F..\comp\TEST_JGO.make 
copy ..\obj\TEST_JGO.exe ..\..\bin\TEST_JGO.EXE
if exist ..\err\TEST_JGO.err notepad ..\err\TEST_JGO.err

nmake /F..\comp\PRINCIPAL.make 
copy ..\obj\PRINCIPAL.exe ..\..\bin\PRINCIPAL.EXE
if exist ..\err\PRINCIPAL.err notepad ..\err\PRINCIPAL.err