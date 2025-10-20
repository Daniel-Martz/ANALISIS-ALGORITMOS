set terminal jpeg size 800,600
set output "insert_medio_caso_OBs.jpg"

set title "Tiempo medio en OBs - InsertSort"
set xrange [1:1000]
set yrange [0:*]                     # eje Y desde 0 hasta el máximo automático
set xlabel "Tamaño de la permutación"
set ylabel "Average_OB"
set key top left
set grid
set datafile separator whitespace

# --- Función cuadrática ajustada con los parámetros obtenidos ---
f_insert(x) = -2.93278 - 0.189299*x + 0.240336*x**2

# --- Graficar datos y ajuste ---
plot "insert_1000_1000.dat" using 1:3 with linespoints lt rgb "#0033CC" lw 2 pt 7 title "InsertSort (caso promedio)", \
     f_insert(x) with lines lt rgb "#00CCFF" lw 3 dt 2 title "Ajuste cuadrático"

unset output
