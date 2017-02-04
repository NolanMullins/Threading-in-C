OBJQ1 = main.o
FLAGS =-Wall -Iinclude -std=c99 -pthread
EXE = run


all:$(OBJQ1) 
	gcc $(OBJQ1) -o $(EXE) $(FLAGS)
clean:
	rm $(OBJQ1) $(EXE)
run:
	./$(EXE)

main.o: main.c 
	gcc -c main.c $(FLAGS)