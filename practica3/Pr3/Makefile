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
	@./exercise2 -num_min 1000 -num_max 10000 -incr 10 -n_times 1 -outputFile rodrigo_binaria.dat

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