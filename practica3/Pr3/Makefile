#-----------------------
# IMPORTANTE: The values of the parameters for exercise?_test have to be conveniently adjusted.
# It is assumed that the name of the source files is exercise1.c, exercise2.c,...,exercise.h
#-----------------------

CC = gcc -ansi -pedantic -O3
CFLAGS = -Wall
EXE = exercise1 exercise2

all : $(EXE)

.PHONY : clean
clean :
	rm -f *.o core $(EXE)

$(EXE) : % : %.o search.o times.o permutations.o
	@echo "#---------------------------"
	@echo "# Generating $@ "
	@echo "# Depepends on $^"
	@echo "# Has changed $<"
	$(CC) $(CFLAGS) -o $@ $@.o search.o times.o permutations.o

permutations.o : permutations.c permutations.h
	@echo "#---------------------------"
	@echo "# Generating $@ "
	@echo "# Depepends on $^"
	@echo "# Has changed $<"
	$(CC) $(CFLAGS) -c $<

search.o : search.c search.h
	@echo "#---------------------------"
	@echo "# Generating $@ "
	@echo "# Depepends on $^"
	@echo "# Has changed $<"
	$(CC) $(CFLAGS) -c $<

times.o : times.c times.h
	@echo "#---------------------------"
	@echo "# Generating $@ "
	@echo "# Depepends on $^"
	@echo "# Has changed $<"
	$(CC) $(CFLAGS) -c $<

exercise1_test:
	@echo Running exercise1
	@valgrind --leak-check=full ./exercise1 -size 100 -key 67

exercise2_test:
	@echo Running exercise2
	@./exercise2 -num_min 1000 -num_max 10000 -incr 100 -n_times 1 -outputFile Lin_auto_N1.dat


plotLinealvsBinaria_promedioOB:
	@gnuplot -persist -e "set title 'Comparación OBs Promedio: Binaria vs Lineal'; \
	set xlabel 'Tamaño (N)'; \
	set ylabel 'Número Medio de OBs'; \
	set grid; \
	set key top left; \
	plot 'rodrigo_lineal.dat' u 1:3 w lines lc rgb 'red' title 'Lineal', \
	     'rodrigo_binaria.dat' u 1:3 w lines lc rgb 'blue' title 'Binaria'"

plotLinealvsBinaria_promedioTIEMPO:
	@gnuplot -persist -e "set title 'Comparación Tiempo Promedio: Binaria vs Lineal'; \
	set xlabel 'Tamaño (N)'; \
	set ylabel 'Tiempo promedio (s)'; \
	set grid; \
	set key top left; \
	plot 'rodrigo_lineal.dat' u 1:2 w lines lc rgb 'red' title 'Lineal', \
	     'rodrigo_binaria.dat' u 1:2 w lines lc rgb 'blue' title 'Binaria'"

plotBinaria_promedioOB:
	@gnuplot -persist -e "set title 'Comparación OB Promedio: Binaria vs Teorico'; \
	set xlabel 'Tamaño (N)'; \
	set ylabel 'Numero Medio de OBs'; \
	set grid; \
	set key top left; \
	f(x) = log(x)/log(2) - 1; \
	plot 'rodrigo_binaria_1PARTE.dat' u 1:3 w lines lc rgb 'blue' title 'Binario', \
	     f(x) w lines lc rgb 'black' title 'Teórica log(N)'"











plotBinarySearch_test:
	@echo Running $@ 
	@./exercise2 -num_min 1 -num_max 1000 -incr 1 -n_times 10 -outputFile datos.log
	@gnuplot -persist -e "set title 'Binary Search OBs vs Size'; \
	set xlabel 'Size'; \
	set ylabel 'OBs'; \
	plot 'datos.log' u 1:3 w lines title 'Average OB', \
	"

# BINARY SEARCH (MIN OBs - COLUMNA 5)

plot_Bin_N1_MinOB:
	@echo Running $@
	@gnuplot -persist -e " \
	set title 'Bin Search: Min OB (n\_times=1)'; \
	set xlabel 'Tamaño de la Tabla (N)'; \
	set ylabel 'Mínimo de Operaciones Básicas (Min OB)'; \
	set key off; \
	set logscale x; \
	plot 'Bin_N1.dat' u 1:5 w lines title 'Bin Search (Min OB)';"

plot_Bin_N100_MinOB:
	@echo Running $@
	@gnuplot -persist -e " \
	set title 'Bin Search: Min OB (n\_times=100)'; \
	set xlabel 'Tamaño de la Tabla (N)'; \
	set ylabel 'Mínimo de Operaciones Básicas (Min OB)'; \
	set key off; \
	set logscale x; \
	plot 'Bin_N100.dat' u 1:5 w lines title 'Bin Search (Min OB)';"

plot_Bin_N10000_MinOB:
	@echo Running $@
	@gnuplot -persist -e " \
	set title 'Bin Search: Min OB (n\_times=10000)'; \
	set xlabel 'Tamaño de la Tabla (N)'; \
	set ylabel 'Mínimo de Operaciones Básicas (Min OB)'; \
	set key off; \
	set logscale x; \
	plot 'Bin_N10000.dat' u 1:5 w lines title 'Bin Search (Min OB)';"

# LINEAR AUTO-ORGANIZED SEARCH (MIN OBs - COLUMNA 5)

plot_LinAuto_N1_MinOB:
	@echo Running $@
	@gnuplot -persist -e " \
	set title 'Lin Auto Search: Min OB (n\_times=1)'; \
	set xlabel 'Tamaño de la Tabla (N)'; \
	set ylabel 'Mínimo de Operaciones Básicas (Min OB)'; \
	set key off; \
	set logscale x; \
	plot 'Lin_auto_N1.dat' u 1:5 w lines title 'Lin Auto Search (Min OB)';"

plot_LinAuto_N100_MinOB:
	@echo Running $@
	@gnuplot -persist -e " \
	set title 'Lin Auto Search: Min OB (n\_times=100)'; \
	set xlabel 'Tamaño de la Tabla (N)'; \
	set ylabel 'Mínimo de Operaciones Básicas (Min OB)'; \
	set key off; \
	set logscale x; \
	plot 'Lin_auto_N100.dat' u 1:5 w lines title 'Lin Auto Search (Min OB)';"

plot_LinAuto_N10000_MinOB:
	@echo Running $@
	@gnuplot -persist -e " \
	set title 'Lin Auto Search: Min OB (n\_times=10000)'; \
	set xlabel 'Tamaño de la Tabla (N)'; \
	set ylabel 'Mínimo de Operaciones Básicas (Min OB)'; \
	set key off; \
	set logscale x; \
	plot 'Lin_auto_N10000.dat' u 1:4 w lines title 'Lin Auto Search (Min OB)';"


# BINARY SEARCH (MAX OBs - COLUMNA 4)

plot_Bin_N1_MaxOB:
	@echo Running $@
	@gnuplot -persist -e " \
	set title 'Bin Search: Máx OB (n\_times=1)'; \
	set xlabel 'Tamaño de la Tabla (N)'; \
	set ylabel 'Máximo de Operaciones Básicas (Max OB)'; \
	set key off; \
	set logscale x; \
	plot 'Bin_N1.dat' u 1:4 w lines title 'Bin Search (Max OB)';"

plot_Bin_N100_MaxOB:
	@echo Running $@
	@gnuplot -persist -e " \
	set title 'Bin Search: Máx OB (n\_times=100)'; \
	set xlabel 'Tamaño de la Tabla (N)'; \
	set ylabel 'Máximo de Operaciones Básicas (Max OB)'; \
	set key off; \
	set logscale x; \
	plot 'Bin_N100.dat' u 1:4 w lines title 'Bin Search (Max OB)';"

plot_Bin_N10000_MaxOB:
	@echo Running $@
	@gnuplot -persist -e " \
	set title 'Bin Search: Máx OB (n\_times=10000)'; \
	set xlabel 'Tamaño de la Tabla (N)'; \
	set ylabel 'Máximo de Operaciones Básicas (Max OB)'; \
	set key off; \
	set logscale x; \
	plot 'Bin_N10000.dat' u 1:4 w lines title 'Bin Search (Max OB)';"


# LINEAR AUTO-ORGANIZED SEARCH (MAX OBs - COLUMNA 4)

plot_LinAuto_N1_MaxOB:
	@echo Running $@
	@gnuplot -persist -e " \
	set title 'Lin Auto Search: Máx OB (n\_times=1)'; \
	set xlabel 'Tamaño de la Tabla (N)'; \
	set ylabel 'Máximo de Operaciones Básicas (Max OB)'; \
	set key off; \
	set logscale x; \
	plot 'Lin_auto_N1.dat' u 1:4 w lines title 'Lin Auto Search (Max OB)';"

plot_LinAuto_N100_MaxOB:
	@echo Running $@
	@gnuplot -persist -e " \
	set title 'Lin Auto Search: Máx OB (n\_times=100)'; \
	set xlabel 'Tamaño de la Tabla (N)'; \
	set ylabel 'Máximo de Operaciones Básicas (Max OB)'; \
	set key off; \
	set logscale x; \
	plot 'Lin_auto_N100.dat' u 1:4 w lines title 'Lin Auto Search (Max OB)';"

plot_LinAuto_N10000_MaxOB:
	@echo Running $@
	@gnuplot -persist -e " \
	set title 'Lin Auto Search: Máx OB (n\_times=10000)'; \
	set xlabel 'Tamaño de la Tabla (N)'; \
	set ylabel 'Máximo de Operaciones Básicas (Max OB)'; \
	set key off; \
	set logscale x; \
	plot 'Lin_auto_N10000.dat' u 1:4 w lines title 'Lin Auto Search (Max OB)';"