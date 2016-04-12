#include <stdlib.h>
#include <strings.h>
#include <time.h>
#include <stdio.h>
#include <time.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>


void error(char *mensaje)
{
    perror(mensaje);
    exit(1);
}

void waitFor (unsigned int segundos) 
{
  int retraso = time(0) + segundos;    
  while (time(0) < retraso);   
}

int main(int argc, char *argv[])
{
     int i = 0;
     char buffer[256];
     int socketFD;
     int numeroPuerto, clilen;
     int nuevoSocketFileDescriptor;
     int nuevoSocketFileDescriptor2;
     int nuevoSocketFileDescriptor3;
     int nuevoSocketFileDescriptor4;
     struct sockaddr_in direccionServidor, direccionCliente;
     if (argc < 2) {
         fprintf(stderr,"ERROR,No se dio el PUERTO\n");
         exit(1);
     }
     socketFD = socket(AF_INET, SOCK_STREAM, 0);
     if (socketFD < 0) 
        error("ERROR opening socket");
     bzero((char *) &direccionServidor, sizeof(direccionServidor));
     numeroPuerto = atoi(argv[1]);
     direccionServidor.sin_family = AF_INET;
     direccionServidor.sin_addr.s_addr = INADDR_ANY;
     direccionServidor.sin_port = htons(numeroPuerto);

     if (bind(socketFD, (struct sockaddr *) &direccionServidor, sizeof(direccionServidor)) < 0) 
              error("ERROR on binding");
     
     listen(socketFD,5);
     clilen = sizeof(direccionCliente);
     while(i<4){
        if(i==0){
            nuevoSocketFileDescriptor = accept(socketFD, (struct sockaddr *) &direccionCliente, &clilen);
            if (nuevoSocketFileDescriptor < 0){
                error("ERROR on accept");
            }else{i=1;printf("%d\n", i);}
        }
        if(i==1){
            nuevoSocketFileDescriptor2 = accept(socketFD, (struct sockaddr *) &direccionCliente, &clilen);
            if (nuevoSocketFileDescriptor2 < 0){
                error("ERROR on accept");
            }else{i++;printf("%d\n", i);}
        }
        if(i==2){
            nuevoSocketFileDescriptor3 = accept(socketFD, (struct sockaddr *) &direccionCliente, &clilen);
            if (nuevoSocketFileDescriptor3 < 0){
                error("ERROR on accept");
            }else{i++;printf("%d\n", i);}
        }
        if(i==3){
            nuevoSocketFileDescriptor4 = accept(socketFD, (struct sockaddr *) &direccionCliente, &clilen);
            if (nuevoSocketFileDescriptor4 < 0){
                error("ERROR on accept");
            }else{i++;printf("%d\n", i);}
        }
     }
     if (i==4){
     do{
        time_t tiempo;
        struct tm *tm_p;
        tiempo = time( NULL );
        tm_p = localtime( &tiempo );
        int hora = tm_p->tm_hour;
        int min  = tm_p->tm_min;
        int seg  = tm_p->tm_sec;
        char dhora[] = {(hora/10)+48};
        char dmin[] = {(min/10)+48};
        char dseg[]  = {(seg/10)+48};
        char uhora[] = {(hora%10)+48};
        char umin[] = {(min%10)+48};
        char useg[]  = {(seg%10)+48};
        
        int pc = write(nuevoSocketFileDescriptor,dmin,1);
        int pc2 = write(nuevoSocketFileDescriptor2,umin,1);
        int pc3 = write(nuevoSocketFileDescriptor3,dseg,1);
        int pc4 = write(nuevoSocketFileDescriptor4,useg,1);
        waitFor(1);
     }while(0==0);
    }
}
