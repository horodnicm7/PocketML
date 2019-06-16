OPTIONS=-Wall -Werror -g -lm
OPTIMIZATIONS=-O0
COMPILER=g++
EXEC=main
FILES=test.cpp classifiers/linearreg.cpp utils/metrics.cpp

build: test.cpp linearreg.o metrics.o
	$(COMPILER) test.cpp linearreg.o metrics.o -o $(EXEC) $(OPTIONS) $(OPTIMIZATIONS)

linearreg.o: classifiers/linearreg.cpp
	$(COMPILER) $(OPTIONS) $(OPTIMIZATIONS) -c $^ -o $@

metrics.o: utils/metrics.cpp
	$(COMPILER) $(OPTIONS) $(OPTIMIZATIONS) -c $^ -o $@

clean:
	rm -f *.out
	rm -f $(EXEC)
	rm -f *.o
