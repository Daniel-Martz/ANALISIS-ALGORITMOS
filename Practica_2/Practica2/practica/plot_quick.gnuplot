# ============================
# plot_quick.gnuplot
# Gráfica comparativa de QuickSort con distintos pivotes
# ============================

set datafile separator ","
set title "Comparación de Tiempo Medio: QuickSort por tipo de pivote"
set xlabel "N (Número de elementos)"
set ylabel "Tiempo (segundos)"
set key left top
set grid

# Estilo visual refinado
set style line 1 lc rgb "#1f77b4" lw 1.2 pt 7 ps 0.8
set style line 2 lc rgb "#ff7f0e" lw 1.2 pt 5 ps 0.8
set style line 3 lc rgb "#2ca02c" lw 1.2 pt 9 ps 0.8

# Líneas suaves y más ligeras
set term pngcairo size 1000,600 enhanced font 'Arial,12'
set output "quick_comparison.png"

# Dibuja las tres curvas desde el CSV combinado
plot "quick_comparison.csv" using 1:2 with linespoints ls 1 title "QuickSort (median)", \
     "quick_comparison.csv" using 1:3 with linespoints ls 2 title "QuickSort (median_avg)", \
     "quick_comparison.csv" using 1:4 with linespoints ls 3 title "QuickSort (median_stat)"
