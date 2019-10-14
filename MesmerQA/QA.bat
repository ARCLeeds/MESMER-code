@echo off
setlocal
set starttime=%time%

:: string begins with a period needs to be quoted
SET directive=
SET otfn=mesmer.test

IF EXIST "../Windows VC16/Mesmer/Mesmer.exe" GOTO VC16
IF EXIST "../Windows VC15/Mesmer/Mesmer.exe" GOTO VC15
IF EXIST "../Windows VC14/Mesmer/Mesmer.exe" GOTO VC14

::For installed version
SET executable= "..\..\Mesmer.exe"
SET version= "..\Mesmer.exe"
GOTO SETTINGS

:VC14
SET executable= "..\..\Windows VC14\Mesmer\Mesmer.exe"
SET version= "..\Windows VC14"
GOTO SETTINGS

:VC15
SET executable= "..\..\Windows VC15\Mesmer\Mesmer.exe"
SET version= "..\Windows VC15"
GOTO SETTINGS

:VC16
SET executable= "..\..\Windows VC16\Mesmer\Mesmer.exe"
SET version= "..\Windows VC16"
GOTO SETTINGS

:SETTINGS
SET tfn=mesmer.test
SET lfn=mesmer.log
SET bline=baselines/Win32/
SET outf=out.xml
SET mpicommand="C:\Program Files\Microsoft MPI\Bin\mpiexec" -n 4 %executable%
:: SET cmdline=%executable%
SET cmdline=%mpicommand%


:: This compares the "double quote" altogether with the content
IF "%1"=="" (
SET directive=-q
SET otfn=test.test
echo.
echo -------------------------------------------------------------------------------------------------------------
echo User QA check mode: output will copy to test.test in the baselines folder. Use your own "diff" program to 
echo check changes between test.test and mesmer.test in baseline folders. Please ensure the original files in 
echo the baseline folders were not previously modified by user.
echo -------------------------------------------------------------------------------------------------------------
echo.
GOTO RUNNING
)
IF "%1"=="-o" (
echo.
echo -------------------------------------------------------------------------------
echo Developer QA check mode: output will overwrite the baselines. Use
echo "SVN check for modifications" to check the changes compared with the baselines.
echo -------------------------------------------------------------------------------
echo.
GOTO RUNNING
)

echo.
echo -------------------------------------------------------------------------------------------------------------
echo This file execute mesmer executable on several quality assessment files. There are two options to execute this file:
echo.
echo 1. user test mode; simply to confirm that if the files (mesmer.test) generated by current machine
echo    is identical to the mesmer baselines.
echo.
echo Syntax:
echo.
echo "\MESMER_PATH\MesmerQA>QA"
echo.
echo 2. developer SVN test mode; it overwrites mesmer.test files in the baseline folders, thus the developer can use
echo    SVN check for modifications from the MesmerQA folder to see what files are changed and the detail of the modifications.
echo    To use it in the developer mode simply give a -o directive after QA command.
echo.
echo Syntax:
echo.
echo "\MESMER_PATH\MesmerQA>QA -o"
echo -------------------------------------------------------------------------------------------------------------
echo.
GOTO END

:RUNNING
@echo --------------------------------------------------------------------
set printversion= %version%"\Mesmer\Mesmer.exe" -V
%printversion%
@echo --------------------------------------------------------------------

@echo on
@cd pentyl
%cmdline% pentyl_isomerization_test.xml -o %outf% %directive%
@copy "./%tfn%" "./%bline%%otfn%"
@IF "%1"=="-o" copy "./%lfn%" "./%bline%%lfn%"
@cd ..
@echo --------------------------------------------------------------------

@cd benzene_oxidation
%cmdline% benzene_oxidation_test.xml -o %outf% %directive%
@copy "./%tfn%" "./%bline%%otfn%"
@IF "%1"=="-o" copy "./%lfn%" "./%bline%%lfn%"
@ cd ..
@echo --------------------------------------------------------------------

@cd HSO2
%cmdline% HSO2_test.xml -o %outf% %directive%
@copy "./%tfn%" "./%bline%%otfn%"
@IF "%1"=="-o" copy "./%lfn%" "./%bline%%lfn%"

@set testName="HSO2"
%cmdline% -N %testName%.xml %directive%
@copy "./%testName%.test" "./%bline%%testName%.test"
@IF "%1"=="-o" copy "./%testName%.log" "./%bline%%testName%.log"
@cd ..
@echo --------------------------------------------------------------------

@cd "cyclopropene isomerization"
%cmdline% Cyclopropene_isomerization_test.xml -o %outf% %directive%
@copy "./%tfn%" "./%bline%%otfn%"
@IF "%1"=="-o" @copy "./%lfn%" "./%bline%%lfn%"
@cd ..
@echo --------------------------------------------------------------------

@cd "cyclopropene isomerization reservoir state"
%cmdline% Cyclopropene_isomerization_reservoir_state_test.xml -o %outf% %directive%
@copy "./%tfn%" "./%bline%%otfn%"
@IF "%1"=="-o" @copy "./%lfn%" "./%bline%%lfn%"
@cd ..
@echo --------------------------------------------------------------------

@cd "OH acetylene association"
%cmdline% OH_acetylene_association_test.xml -o %outf% %directive%
@copy "./%tfn%" "./%bline%%otfn%"
@IF "%1"=="-o" copy "./%lfn%" "./%bline%%lfn%"

@set testName="OH_acetylene_pseudo_isomerization"
%cmdline% -N %testName%.xml %directive%
@copy "./%testName%.test" "./%bline%%testName%.test"
@IF "%1"=="-o" copy "./%testName%.log" "./%bline%%testName%.log"
@cd ..
@echo --------------------------------------------------------------------

@cd "Acetyl O2 association"
%cmdline% Acetyl_O2_association.xml -o %outf% %directive%
@copy "./%tfn%" "./%bline%%otfn%"
@IF "%1"=="-o" copy "./%lfn%" "./%bline%%lfn%"
@cd ..
@echo --------------------------------------------------------------------

@cd "i-propyl"
%cmdline% ipropyl_test.xml -o %outf% %directive%
@copy "./%tfn%" "./%bline%%otfn%"
@IF "%1"=="-o" copy "./%lfn%" "./%bline%%lfn%"

@set testName="ipropyl_reservoir"
%cmdline% -N %testName%.xml %directive%
@copy "./%testName%.test" "./%bline%%testName%.test"
@IF "%1"=="-o" copy "./%testName%.log" "./%bline%%testName%.log"
@cd ..
@echo --------------------------------------------------------------------

@cd "ThermodynamicTable"
%cmdline% ThermodynamicTable.xml -o %outf% %directive%
@copy "./%tfn%" "./%bline%%otfn%"
@IF "%1"=="-o" copy "./%lfn%" "./%bline%%lfn%"

@set testName="ThermodynamicTable_Fourier"
%cmdline% -N %testName%.xml %directive%
@copy "./%testName%.test" "./%bline%%testName%.test"
@IF "%1"=="-o" copy "./%testName%.log" "./%bline%%testName%.log"
@cd ..
@echo --------------------------------------------------------------------

@cd "UnitTests"
%cmdline% UnitTests.xml -o %outf% %directive%
@copy "./%tfn%" "./%bline%%otfn%"
@IF "%1"=="-o" copy "./%lfn%" "./%bline%%lfn%"
@cd ..
@echo --------------------------------------------------------------------
@echo off
@echo Start Time=%starttime% - End Time=%time%

@:: The line below makes DOS beep (err yup)
@echo 
@echo 
@echo 

:END
