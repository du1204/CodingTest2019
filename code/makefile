CC = g++
CFLAGS = -g -O3
OBJS = BigInteger.o fileReader.o

all : clean main run

main : $(OBJS) 
	@echo 'Building target: $@'
	$(CC) main.cpp -o output $(CFLAGS) $(OBJS)
	@echo 'Finished building target: $@'
	@echo ' '
	
.cpp.o :
	@echo 'Building target: $@'
	g++ -c $< $(CFLAGS)
	@echo 'Finished building target: $@'
	@echo ' '

clean : 
	rm -rf *.o output

run :
	./output