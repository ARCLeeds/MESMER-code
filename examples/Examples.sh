#!/bin/sh

# qashell.sh
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
    echo "    \MESMER_PATH\MesmerQA>./qashell.sh -u"
    echo ""
    echo "2. developer SVN test mode; it overwrites mesmer.test files in the baseline"
    echo "   folders, thus the developer can use SVN check for modifications from the "
    echo "   MesmerQA folder to see what files are changed and the detail of the "
    echo "   modifications. To use it in the developer mode simply give a -o directive"
    echo "   after QA command."
    echo ""
    echo "Syntax:"
    echo ""
    echo "    \MESMER_PATH\MesmerQA>./qashell.sh -o"
    echo "----------------------------------------------------------------------"
    echo ""
    ;;
esac

pwd
$executable -V

cd AcetylO2
$executable Acetyl_O2_associationEx.xml -o $outf $directive
cp ./$tfn ./$bline$otfn
if [ "$1" == "-o" ]; then
  cp ./$lfn ./$bline$lfn 
fi
cd ..

cd benzene_oxidation
$executable benzene_oxidation_test.xml -o $outf $directive
cp ./$tfn ./$bline$otfn
if [ "$1" == "-o" ] ; then
  cp ./$lfn ./$bline$lfn 
fi
cd ..

cd Ethyl_H_to_Ethane
$executable Ethyl_H_to_Ethane.xml -o $outf $directive
cp ./$tfn ./$bline$otfn
if [ "$1" == "-o" ] ; then
  cp ./$lfn ./$bline$lfn 
fi
cd ..

cd i-propyl
$executable ipropyl_LM.xml -o $outf $directive
cp ./$tfn ./$bline$otfn
if [ "$1" == "-o" ] ; then
  cp ./$lfn ./$bline$lfn 
fi
cd ..

cd Methyl_H_to_Methane
$executable Methyl_H_to_Methane.xml -o $outf $directive
cp ./$tfn ./$bline$otfn
if [ "$1" == "-o" ] ; then
  cp ./$lfn ./$bline$lfn 
fi

$executable -N Methyl_H_to_Methane_FTST.xml $directive
cp ./Methyl_H_to_Methane_FTST.test ./$bline/Methyl_H_to_Methane_FTST.test
if [ "$1" == "-o" ] ; then
  cp ./Methyl_H_to_Methane_FTST.log ./$bline/Methyl_H_to_Methane_FTST.log 
fi
cd ..

cd reservoirSink
$executable reservoirSinkAcetylO2.xml -o $outf $directive
cp ./$tfn ./$bline$otfn
if [ "$1" == "-o" ] ; then
  cp ./$lfn ./$bline$lfn 
fi
cd ..

cd spin_forbidden_kinetics
$executable -N HCCH_methylene.xml  $directive
cp ./$tfn ./$bline$otfn
if [ "$1" == "-o" ] ; then
  cp ./$lfn ./$bline$lfn 
fi

$executable -N LZ_test.xml $directive
cp ./$tfn ./$bline$otfn
if [ "$1" == "-o" ] ; then
  cp ./$lfn ./$bline$lfn 
fi

$executable -N WKB_test.xml $directive
cp ./$tfn ./$bline$otfn
if [ "$1" == "-o" ] ; then
  cp ./$lfn ./$bline$lfn 
fi
cd ..

cd OH_NO_to\ HONO
$executable OH_NO_HONO.xml -o $outf $directive
cp ./$tfn ./$bline$otfn
if [ "$1" == "-o" ] ; then
  cp ./$lfn ./$bline$lfn 
fi
cd ..

echo Start Time=$starttime - End Time=`date`

# This line below makes shell to create a system Beep (err yup)
echo -e "\007"
echo -e "\007"
echo -e "\007"



