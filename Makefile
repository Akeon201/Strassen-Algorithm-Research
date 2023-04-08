
#Author: Kenyon Leblanc

ship-shell:
	gcc ./algorithms.c -o run_algorithms
	$(clean)

clean:
	rm -f *.o
