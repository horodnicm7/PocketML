build:
	g++ test.cpp linearreg.cpp metrics.cpp -o main
clean:
	rm -f main
	rm -f *.o
