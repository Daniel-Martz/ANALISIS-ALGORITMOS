#-----------------------
# IMPORTANTE: The values of the parameters for exercise?_test have to be conveniently adjusted.
# It is assumed that the name of the source files is exercise1.c, exercise2.c,...,exercise.h
#-----------------------

CC = gcc -ansi -pedantic
CFLAGS = -g -Wall
EXE = exercise1 exercise2 exercise3 exercise4 exercise5

all : $(EXE)

.PHONY : clean
clean :
	rm -f *.o core $(EXE)

$(EXE) : % : %.o sorting.o times.o permutations.o
	@echo "#---------------------------"
	@echo "# Generating $@ "
	@echo "# Depepends on $^"
	@echo "# Has changed $<"
	$(CC) $(CFLAGS) -o $@ $@.o sorting.o times.o permutations.o

permutations.o : permutations.c permutations.h
	@echo "#---------------------------"
	@echo "# Generating $@ "
	@echo "# Depepends on $^"
	@echo "# Has changed $<"
	$(CC) $(CFLAGS) -c $<

sorting.o : sorting.c sorting.h
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
	@./exercise1 -limInf 1 -limSup 5 -numN 10

exercise2_test:
	@echo Running exercise2
	@./exercise2 -size 1 -numP 5

exercise3_test:
	@echo Running exercise3
	@./exercise3 -size 1 -numP 5

exercise4_test:
	@echo Running exercise4
	@./exercise4 -size 20

exercise5_test:
	@echo Running exercise5
	@./exercise5 -num_min 1 -num_max 50 -incr 1 -numP 100000 -outputFile quicksort.txt

exercise1_testv:
	@echo Running exercise1
	@valgrind --leak-check=full ./exercise1 -limInf 1 -limSup 5 -numN 10

exercise2_testv:
	@echo Running exercise2
	@valgrind --leak-check=full ./exercise2 -size 1 -numP 5

exercise3_testv:
	@echo Running exercise3
	@valgrind --leak-check=full ./exercise3 -size 1 -numP 5

exercise4_testv:
	@echo Running exercise4
	@valgrind --leak-check=full ./exercise4 -size 1

exercise5_testv:
	@echo Running exercise5
	@valgrind --leak-check=full ./exercise5 -num_min 1 -num_max 5 -incr 2 -numP 23 -outputFile exercise5.log



#========================================================
# NUEVA SECCIÓN: Generación automática de gráfica de pivotes
#========================================================

# Archivos de entrada de datos
DATA_FILES = median.txt median_avg.txt median_stat.txt

# Archivos auxiliares
GRAPH_SRC = graph_data.c
GRAPH_EXE = graph_data
PLOT_SCRIPT = plot_quick.gnuplot
CSV = quick_comparison.csv
IMG = quick_comparison.png

# Compilar el generador de CSV
$(GRAPH_EXE): $(GRAPH_SRC)
	@echo "#---------------------------"
	@echo "# Compilando el generador de datos"
	$(CC) $(CFLAGS) -o $(GRAPH_EXE) $(GRAPH_SRC)

# Generar el CSV combinando los archivos de resultados
$(CSV): $(GRAPH_EXE) $(DATA_FILES)
	@echo "#---------------------------"
	@echo "# Generando CSV combinado con datos de pivotes"
	./$(GRAPH_EXE)

# Generar la gráfica con Gnuplot
plot: $(CSV) $(PLOT_SCRIPT)
	@echo "#---------------------------"
	@echo "# Generando gráfica comparativa de QuickSort"
	gnuplot -e "set terminal pngcairo size 1000,600; set output '$(IMG)'; load '$(PLOT_SCRIPT)'"
	@echo "✅ Gráfico generado: $(IMG)"

# Limpiar archivos de graficado
clean_plot:
	rm -f $(GRAPH_EXE) $(CSV) $(IMG)
