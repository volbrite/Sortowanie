set terminal eps font ",10" linewidth 3
set output 'Sprawozdanie_SORTOWANIE-gnuplottex-fig2.eps'
set title "Zakres 99 999 | Posortowane 25%"
set datafile separator ';'
set ylabel 'Czas [s]'
set xlabel 'Ilość przypisanych danych'
set logscale x 10
set xtics ('10k' 10000, '50k' 50000, '100k' 100000, '500k' 500000, '1M' 1000000)
unset key
plot 'W/r1_wyniki_1.csv' title "MergeSort" with linespoints lt 1 , 'W/r1_wyniki_2.csv' title "QuickSort" with linespoints lt 2, 'W/r1_wyniki_3.csv' title "IntroSort" with linespoints lt 3
