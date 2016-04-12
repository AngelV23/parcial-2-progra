 #include <stdlib.h>
 #include <strings.h>
 #include <stdio.h>
 #include <fcntl.h>
 #include <sys/types.h>
 #include <sys/socket.h>
 #include <sys/stat.h>
 #include <netinet/in.h>
 #include <netdb.h> 
 #include <unistd.h>
 #include <signal.h>

int socketOpenFD;
int bandera1=1;
int bandera2=1;

void error(char *mensaje)
{
    perror(mensaje);
    exit(1);
}

void senial(int miSenial)
{
  if (miSenial == SIGINT)
  {
    printf("Recibio un comando SIGINT\n");
    close(socketOpenFD);
    exit(1);
    bandera1++;bandera2++;
  }
}

 
 int main(int argc, char *argv[])
 {
     int FileDescriptor;
     char buf[1024];
     int numeroPuerto, n;
 
     struct sockaddr_in direccionServidor;
     struct hostent *Servidor;
 
     char buffer[256];
     if (argc < 3)
     {
        fprintf(stderr,"usage %s hostname port\n", argv[0]);
        exit(0);
     }
    char *pipe = "fifo";
    mkfifo(pipe, 0666);

     numeroPuerto = atoi(argv[2]);
     socketOpenFD = socket(AF_INET, SOCK_STREAM, 0);
     if (socketOpenFD < 0) 
         error("ERROR opening socket");
     Servidor = gethostbyname(argv[1]);

     if (Servidor == NULL) 
     {
         fprintf(stderr,"ERROR, no such host\n");
         exit(0);
     }

     bzero((char *) &direccionServidor, sizeof(direccionServidor));
     direccionServidor.sin_family = AF_INET;
     bcopy((char *)Servidor->h_addr, (char *)&direccionServidor.sin_addr.s_addr, Servidor->h_length);
     direccionServidor.sin_port = htons(numeroPuerto);
     if (connect(socketOpenFD,(struct sockaddr *)&direccionServidor,sizeof(direccionServidor)) < 0) 
         error("ERROR connecting");


    char* lista[] = 
    {
    	"display",
    	"0.jpg",
    	NULL
    };
     
     pid_t idChild;
     idChild = fork ();
     int a = (int) getpid ();
    if (idChild == 0)
    { 
     	int b = (int) getpid ();
     	execvp("display", lista); 
    }
    else
    {
         int c = (int) getpid ();
         idChild = fork ();
        if(idChild==0)
        {
         	int d = (int) getpid ();
            	int i =0;
                do
                { 
                    bzero(buffer,256);
                    n = read(socketOpenFD,buffer,255);
                    FileDescriptor = open(pipe, O_WRONLY);
                    
                    switch(buffer[0])
                    {
                        case '0':
                        	if(i>1)
                        	{
                            	write(FileDescriptor, "0", sizeof("0"));
                        	}
                        	else
                        	{
                        		i++;
                        	}
                        break;
                        case '1':
                        	if(i>1)
                        	{
                            	write(FileDescriptor, "1", sizeof("1"));
                            }
                            else
                            {
                            	i++;
                            }
                        break;
                        case '2':
                        	if(i>1)
                        	{
                            	write(FileDescriptor, "2", sizeof("2"));
                            }
                            else
                            {
                            	i++;
                            }
                        break;
                        case '3':
                        	if(i>1)
                        	{
                            	write(FileDescriptor, "3", sizeof("3"));
                            }
                            else
                            {
                            	i++;
                            }
                        break;
                        case '4':
                        	if(i>1)
                        	{
                            	write(FileDescriptor, "4", sizeof("4"));
                            }
                            else
                            {
                            	i++;
                            }
                        break;
                        case '5':
                        	if(i>1)
                        	{
                            	write(FileDescriptor, "5", sizeof("5"));
                            }
                            else
                            {
                            	i++;
                            }
                        break;
                        case '6':
                        	if(i>1)
                        	{
                            	write(FileDescriptor, "6", sizeof("6"));
                            }
                            else
                            {
                            	i++;
                            }
                        break;
                        case '7':
                        	if(i>1){
                            	write(FileDescriptor, "7", sizeof("7"));
                            }else{i++;}
                        break;
                        case '8':
                        	if(i>1){
                            	write(FileDescriptor, "8", sizeof("8"));
                            }else{i++;}
                        break;
                        case '9':
                        	if(i>1){
                            write(FileDescriptor, "9", sizeof("9"));
                            }else{i++;}
                        break;
                    }
                    close(FileDescriptor);
                    if (signal(SIGINT, senial) == SIG_ERR)
                    {
	  					printf("\nCan't catch signal\n");
                    }
                }while (bandera1==1);   
        }
        else{
           	int e = (int) getpid ();
           	int j=0;
           	do
           	{ 
                FileDescriptor = open(pipe, O_RDONLY);
                read(FileDescriptor, buf, 1024);
                char a = buf[0];
                switch(a)
                {
                    case '0':
                      	if(j>1)
                       	{
                           	system("display -remote 0.jpg");
      	                }
                        else
                        {
                          	j++;
                        }
                            break;
                    case '1':
                       	if(j>1)
                       	{
                           	system("display -remote 1.jpg");
                        }
                        else
                        {
                           	j++;
                        }
                            break;
                        case '2':
                        	if(j>1)
                        	{
	                            system("display -remote 2.jpg");
                            }
                            else
                            {
                            	j++;
                            }
                            break;
                        case '3':
                        	if(j>1)
                        	{
                            	system("display -remote 3.jpg");
                            }
                            else
                            {
                            	j++;
                            }
                            break;
                        case '4':
                        	if(j>1)
                        	{
                            	system("display -remote 4.jpg");
                            }
                            else
                            {
                            	j++;
                            }
                            break;
                        case '5':
                        	if(j>1)
                        	{
                            	system("display -remote 5.jpg");
                            }
                            else
                            {
                            	j++;
                            }
                            break;
                        case '6':
                        	if(j>1)
                        	{
                            	system("display -remote 6.jpg");
                            }
                            else
                            {
                            	j++;
                            }
                            break;
                        case '7':
                        	if(j>1)
                        	{
                            	system("display -remote 7.jpg");
                            }
                            else
                            {
                            	j++;
                            }
                            break;
                        case '8':
                        	if(j>1)
                        	{
	                            system("display -remote 8.jpg");
                            }
                            else
                            {
                            	j++;
                            }
                            break;
                        case '9':
                        	if(j>1)
                        	{
                            	system("display -remote 9.jpg");
                            }
                            else
                            {
                            	j++;
                            }
                            break;
                    }
                    close(FileDescriptor);
                    if (signal(SIGINT, senial) 	== SIG_ERR)
                    {
	  					printf("\nNo segnial");
	  				}
                }while (bandera2==1);
            }
        }
 }

