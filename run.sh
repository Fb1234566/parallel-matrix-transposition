cd $HOME/Documenti/Prog_avanzata/parallel-matrix-transposition/bin/run/

for i in {4..12} ; do
    ./a.out -s $[2**$i]
done