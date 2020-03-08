BANDERAS = -g -lm --std=c11
SALIDA = pass

all:
	gcc $(BANDERAS) *.c -o $(SALIDA) -lcrypto -lssl
	
run:
	./$(SALIDA)
	
.PHONY clean:
	rm *.o $(SALIDA)
