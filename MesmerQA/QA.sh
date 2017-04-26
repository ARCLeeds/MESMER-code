#!/bin/sh

# QA.sh
# mesmer
#
# Created by Chi-Hsiu Liang on 13/05/2010.

starttime=`date`
directive=
otfn=mesmer.test

# To execute the 
if [ -f "../bin/mesmer" ]; then
  executable="../../bin/mesmer"
else
  echo "----------------------------------------------------------------------"
  echo "The executable mesmer cannot be found, the QA test stopped."
  echo "Please make sure the executable mesmer is located in the \"bin\" folder."
  if [ "$TERM_PROGRAM" == "Apple_Terminal" ]; then 
    echo "If you use XCode to compile mesmer, make sure you set the \"Copy Files\""
    echo "build phase of target mesmer to have Destination \"Absolute Path\", copying the full"
    echo "path of mesmer\bin to the \"Full Path\" box. This will make sure you get a fresh executable"
    echo "each time you compile mesmer."
    echo "----------------------------------------------------------------------"
    exit
  fi
fi

tfn=mesmer.test
lfn=mesmer.log
bline=baselines/Linux64/
outf=out.xml

case $1 in
  -u)
    directive=-q
    otfn=test.test
    echo "----------------------------------------------------------------------"
    echo "User QA check mode: output will copy to test.test in the baselines folder."
    echo "Use your own \"diff\" program to check changes between test.test and "
    echo "mesmer.test in baseline folders. Please ensure the original files in "
    echo "the baseline folders were not previously modified by user."
    echo "----------------------------------------------------------------------"
    ;;
  -o)
    echo "----------------------------------------------------------------------"
    echo "Developer QA check mode: output will overwrite the baselines. Use"
    echo "\"SVN check for modifications\" to check the changes compared with the baselines."
    echo "----------------------------------------------------------------------"
    ;;
  "")
    echo ""
    echo "----------------------------------------------------------------------"
    echo "This file execute mesmer executable on several quality assessment files."
    echo "There are two options to execute this file:"
    echo ""
    echo "1. user test mode; simply to confirm that if the files (mesmer.test) "
    echo "generated by current machine is identical to the mesmer baselines."
    echo ""
    echo "Syntax:"
    echo ""
    echo "    \MESMER_PATH\MesmerQA>./QA.sh -u"
    echo ""
    echo "2. developer SVN test mode; it overwrites mesmer.test files in the baseline"
    echo "   folders, thus the developer can use SVN check for modifications from the "
    echo "   MesmerQA folder to see what files are changed and the detail of the "
    echo "   modifications. To use it in the developer mode simply give a -o directive"
    echo "   after QA command."
    echo ""
    echo "Syntax:"
    echo ""
    echo "    \MESMER_PATH\MesmerQA>./QA.sh -o"
    echo "----------------------------------------------------------------------"
    echo ""
    ;;
esac

cd pentyl
pwd
$executable -V
mpicommand="mpirun -n 2 $executable" 
cmdline=$executable

cmdline pentyl_isomerization_test.xml -o $outf $directive
cp ./$tfn ./$bline$otfn
if [ "$1" == "-o" ]; then
  cp ./$lfn ./$bline$lfn 
fi
cd ..
echo "--------------------------------------------------------------------"

cd benzene_oxidation
$cmdline benzene_oxidation_test.xml -o $outf $directive
cp ./$tfn ./$bline$otfn
if [ "$1" == "-o" ] ; then
  cp ./$lfn ./$bline$lfn 
fi
cd ..
echo "--------------------------------------------------------------------"

cd HSO2
$cmdline HSO2_test.xml -o $outf $directive
cp ./$tfn ./$bline$otfn
if [ "$1" == "-o" ] ; then
  cp ./$lfn ./$bline$lfn 
fi

testName=HSO2
$cmdline -N $testName.xml
cp ./$testName.test ./$bline$testName.test
if [ "$1" == "-o" ] ; then
  cp ./$testName.log ./$bline$testName.log 
fi
cd ..
echo "--------------------------------------------------------------------"

cd "cyclopropene isomerization"
$cmdline Cyclopropene_isomerization_test.xml -o $outf $directive
cp ./$tfn ./$bline$otfn
if [ "$1" == "-o" ] ; then
  cp ./$lfn ./$bline$lfn 
fi
cd ..
echo "--------------------------------------------------------------------"

cd "cyclopropene isomerization reservoir state"
$cmdline Cyclopropene_isomerization_reservoir_state_test.xml -o $outf $directive
cp ./$tfn ./$bline$otfn
if [ "$1" == "-o" ] ; then
  cp ./$lfn ./$bline$lfn 
fi
cd ..
echo "--------------------------------------------------------------------"

cd "OH acetylene association"
$cmdline OH_acetylene_association_test.xml -o $outf $directive
cp ./$tfn ./$bline$otfn
if [ "$1" == "-o" ] ; then
  cp ./$lfn ./$bline$lfn 
fi

testName=OH_acetylene_pseudo_isomerization
$cmdline -N $testName.xml
cp ./$testName.test ./$bline$testName.test
if [ "$1" == "-o" ] ; then
  cp ./$testName.log ./$bline$testName.log 
fi
cd ..
echo "--------------------------------------------------------------------"

cd "Acetyl O2 association"
$cmdline Acetyl_O2_association.xml -o $outf $directive
cp ./$tfn ./$bline$otfn
if [ "$1" == "-o" ] ; then
  cp ./$lfn ./$bline$lfn 
fi
cd ..
echo "--------------------------------------------------------------------"

cd "i-propyl"
$cmdline ipropyl_test.xml -o $outf $directive
cp ./$tfn ./$bline$otfn
if [ "$1" == "-o" ] ; then
  cp ./$lfn ./$bline$lfn 
fi

testName=ipropyl_reservoir
$cmdline -N $testName.xml
cp ./$testName.test ./$bline$testName.test
if [ "$1" == "-o" ] ; then
  cp ./$testName.log ./$bline$testName.log 
fi
cd ..
echo "--------------------------------------------------------------------"

cd "ThermodynamicTable"
$cmdline ThermodynamicTable.xml -o $outf $directive
cp ./$tfn ./$bline$otfn
if [ "$1" == "-o" ] ; then
  cp ./$lfn ./$bline$lfn 
fi

testName=ThermodynamicTable_Fourier
$cmdline -N $testName.xml
cp ./$testName.test ./$bline$testName.test
if [ "$1" == "-o" ] ; then
  cp ./$testName.log ./$bline$testName.log 
fi
cd ..
echo "--------------------------------------------------------------------"

cd "UnitTests"
$cmdline UnitTests.xml -o $outf $directive
cp ./$tfn ./$bline$otfn
if [ "$1" == "-o" ] ; then
  cp ./$lfn ./$bline$lfn 
fi
cd ..
echo "--------------------------------------------------------------------"

echo Start Time=$starttime - End Time=`date`

# This line below makes shell to create a system Beep (err yup)
echo -e "\007"
echo -e "\007"
echo -e "\007"



