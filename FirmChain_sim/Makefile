Firmchain_sim : main.o sha256.o
	gcc -o Firmchain_sim main.o sha256.o -lpthread
	./Firmchain_sim

main.o : 
	gcc -c -o main.o main.c 
	
sha256.o :
	gcc -c -o sha256.o sha256.c

clean :
	rm *.o Firmchain_sim
