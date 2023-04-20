
#Author: Kenyon Leblanc

alg:
	gcc ./algorithms.c -o run_algorithms
	$(clean)

clean:
	rm -f *.o
