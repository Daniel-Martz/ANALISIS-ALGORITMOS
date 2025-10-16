set terminal jpeg size 800,600           # tipo de salida y tamaño
set output "comparacion_OBs.jpg"         # archivo de salida

set title "Comparación del tiempo medio de OBs"
set xrange [1:1000]
set xlabel "Tamaño de la permutación"
set ylabel "Tiempo medio (s)"
set key top left
set grid

# --- Funciones cuadráticas ---
# InsertSort cuadrática:
c1 = 0.0024115
d1 = 1.69078e-06
e1 = 3.75933e-07
f_insert(x) = c1 + d1*x + e1*x**2

# BubbleSort cuadrática:
c2 = 0.00226202
d2 = 7.44039e-05
e2 = 1.05902e-06
f_bubble(x) = c2 + d2*x + e2*x**2

# --- Datos experimentales y ajustes ---
plot "insert_1000_1000.dat" using 1:2 with linespoints lt rgb "#0033CC" lw 2 pt 7 title "InsertSort (datos)", \
     "bubble_1000_1000.dat" using 1:2 with linespoints lt rgb "#CC0000" lw 2 pt 5 title "BubbleSort (datos)", \
     f_insert(x) with lines lt rgb "#00CC99" lw 3 dt 2 title "InsertSort (ajuste cuadrático)", \
     f_bubble(x) with lines lt rgb "#FFA500" lw 3 dt 2 title "BubbleSort (ajuste cuadrático)"

unset output                            # cierra el fichero
