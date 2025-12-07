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
	@./exercise2 -num_min 1000 -num_max 10000 -incr 100 -n_times 10000 -outputFile Lin_N10000.dat

plotBinarySearch_test:
	@echo Running $@ 
	@./exercise2 -num_min 1 -num_max 1000 -incr 1 -n_times 10 -outputFile datos.log
	@gnuplot -persist -e "set title 'Binary Search OBs vs Size'; \
	set xlabel 'Size'; \
	set ylabel 'OBs'; \
	plot 'datos.log' u 1:3 w lines title 'Average OB', \
	"

plotLin-vs-LinautoSearch_test:
	@echo Running $@ 
	@./exercise2 -num_min 1 -num_max 1000 -incr 1 -n_times 10 -outputFile datos.log
	@gnuplot -persist -e " \
    set title 'Comparación de Máx OBs: Lineal vs Lineal Auto-organizada (según n\_times)'; \
    set xlabel 'Tamaño de la Tabla (N)'; \
    set ylabel 'Máximo de Observaciones (Max OB)'; \
    set key outside right top; \
    set logscale x; \
    \
    plot 'Lin_N1.dat' u 1:4 w lines title 'Lin Search (n\_times=1)', \
         'Lin_auto_N1.dat' u 1:4 w lines title 'Lin Auto Search (n\_times=1)', \
         'Lin_N100.dat' u 1:4 w lines title 'Lin Search (n\_times=100)', \
         'Lin_auto_N100.dat' u 1:4 w lines title 'Lin Auto Search (n\_times=100)', \
         'Lin_N10000.dat' u 1:4 w lines title 'Lin Search (n\_times=10000)', \
         'Lin_auto_N10000.dat' u 1:4 w lines title 'Lin Auto Search (n\_times=10000)';"