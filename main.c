#include "lab10.h"

struct Node *heads[3];
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int main(int argc, char *argv[]){
    if(argc < 4){
        printf("File not given\n");
        return 1;
    }
    int key = atoi(argv[3]);
    if(key > 255){
        printf("Enter a number between 0 and 255\n");
        return 1;
    }

    pthread_t saveThread;
    if (pthread_create(&saveThread, NULL, &bin_write_to_file, argv[2]) != 0) {
        perror("Thread creation failed");
        return 1;
    }

    read_from_file(argv[1], key);
    while(1){
        int userInput;
        printf("Enter 1, 2, 3, 4, 5, 6 or 0\n");
        scanf("%d", &userInput);
        if(userInput == 0){
            save_to_file(argv[1], key);
            pthread_cancel(saveThread);
            for(int i = 0; i < 3; i++)
                delete_all(heads[i]);
            break;
        }
        else if(userInput == 1) 
            read_from_keyboard();
        
        else if(userInput == 2)
            show_all();
        
        else if(userInput == 3)
            show_name();
        
        else if(userInput == 4)
            delete();
        
        else if(userInput == 5)
            delete_name();
        
        else if(userInput == 6){
            bin_read_from_file(argv[2]);
        }
    }
}	
