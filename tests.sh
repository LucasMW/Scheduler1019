echo -e "running tests"
./shell -interpreter >logRR.txt
echo -e "1/3"
./shell -interpreter entrada3.txt >logSJF.txt
echo -e "2/3"
./shell -interpreter entrada2.txt>logPL.txt
echo -e "3/3"
echo -e "Procure por logRR.txt, logSJF.txt e logPL.txt"
