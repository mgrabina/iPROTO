#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#define maxstdin 100

int main(int argc, char* argv[])
{
    char * stdin =malloc(maxstdin);
    int i=0;
    //como el echo que me mandan de la entrada
    while((stdin[i++]=getchar())!=-1){
    	if (i>maxstdin)
    		fprintf(stderr, "max input=%d\n",maxstdin);
    }
    stdin[--i]='\0';
    //creo pipes
    int my_pipe[2];
    if(pipe(my_pipe) == -1){
        fprintf(stderr, "Error creating pipe\n");
    }
    pid_t child_id;
    child_id = fork();
    if(child_id == -1){
        fprintf(stderr, "Fork error\n");
    }

    if(child_id == 0){ // child process
        close(my_pipe[0]); // child doesn't read
        dup2(my_pipe[1], 1); // redirijo la salida standard (el 1) a mi pipe 
        char *command=malloc(maxstdin);
        //armo el comando a ejecutar porque consumi el stdin de la entrada standard
        strcpy(command,"echo -n ");
        strcat(command,stdin);
        strcat(command,"|");
        strcat(command,argv[1]);
        system(command);
        free(command);
        return 0;
    }
    else{
        char * aux= malloc(maxstdin);
        int position=0;
        close(my_pipe[1]); // parent doesn't write

        char reading_buf[1];
        //leo el pipe que es el comando ejecutado en el hijo y lo voy almacenando en aux
        while(read(my_pipe[0], reading_buf, 1) > 0){
            aux[position++]=reading_buf[0];
        }
        aux[position]='\0';       
        printf("%s\n",aux );
        //hago el xor y lo imprimo en stderr
        int outparity=aux[0];
        int inparity=stdin[0];
        for(int x=1;aux[x]!='\0';x++){
            inparity=inparity^stdin[x];
            outparity=outparity^aux[x];
        }
        fprintf(stderr, "%d\n%d\n",inparity,outparity);
        close(my_pipe[0]);
        free(aux);
        free(stdin);
        return 0;
    }
}