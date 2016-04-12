all: servidor cliente

servidor:
	gcc -o Servidor ElServidor.c

cliente:
	gcc -o Cliente ElCliente.c

clean:
	rm Servidor Cliente
