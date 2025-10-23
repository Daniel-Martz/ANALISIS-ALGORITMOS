set terminal jpeg size 800,600           # Define el tipo de salida y tamaño
set output "insert_peor_caso_OBs.jpg"     # Archivo de salida

set title "Tiempo peor en OBs"
set xrange [1:1000]
set xlabel "Tamaño de la permutación"
set ylabel "Max_OB"
set key top left
set grid
set datafile separator whitespace      # Asegura la lectura correcta de columnas
set key autotitle columnheader         # Opcional: usa la cabecera para títulos

# Plotea la columna 1 (N) contra la columna 5 (Min_OB). Se asume que Min_OB es la columna 5.
plot "insert_1000_1000.dat" using 1:4 with linespoints lt rgb "#0033CC" lw 2 pt 7 title "InsertSort (peor caso)"

unset output                             # Cierra el fichero