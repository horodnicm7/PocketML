build: test.cpp
	g++ -o main test.cpp -lpthread -g
linklib: test.cpp
	g++ -L. -lpocketml -o main $^
buildlib: linearreg.o logisticreg.o
	g++ -shared $^ -o libpocketml.so
linearreg.o: models/linearreg.cpp
	g++ -c $^
logisticreg.o: models/logisticreg.cpp
	g++ -c $^
clean:
	rm -f *.o
	rm -f main
