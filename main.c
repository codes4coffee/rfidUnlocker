#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>

#define KEY_LENG 12
#define VALID_KEY "611751298265"
#define SERIAL_LOCATION "/dev/cu.usbmodem1411"

//"/dev/serial/by-id/usb-Arduino__www.arduino.cc__0043_755333431363512132E0-if00"

//volatile sig_atomic_t childHandle = 0;

void do_things (int sig){
    //exit(0);
}

void readPort(){

    char c;
    FILE *file;
    //Initialize the serial read
    file = fopen(SERIAL_LOCATION, "r");

    if (file) {
        char inputKey[KEY_LENG + 1] = {0}; //Set the final index in the array to \0 to make this a string
        while(1){
            //Loop through and read every number in the card id
            for (int i = 0; i < KEY_LENG; i++) {
                fread(&c, 1, 1, file);
                printf("%c",c);
                inputKey[i] = c;
            }
            fflush(stdout);
            inputKey[KEY_LENG] = 0;
            if(!strcmp(inputKey, VALID_KEY)){
                fprintf(stdout, "Compare sucessful\n");
                break;
            }else{
                printf("%s\n", inputKey);
            }
            sleep(1);
        }
        fclose(file);
        printf("Closed file");
    }
}

int main() {
    /*struct sigaction usr_action;
    sigset_t mask;
    sigfillset(&mask);
    usr_action.sa_handler = do_things;
    usr_action.sa_mask = mask;
    usr_action.sa_flags = 0;
    sigaction (SIGCHLD, &usr_action, NULL);

    pid_t lockPID = fork();
    if(lockPID == -1){
        fprintf(stderr, "Shit hit the fan");
        return 1;
    }

    if(!lockPID){
        execlp("i3lock","i3lock");
    }
    printf("%i\n", lockPID);
    readPort();
    execlp("killall", "killall", "i3lock", NULL);*/
    readPort();
    return 0;
}