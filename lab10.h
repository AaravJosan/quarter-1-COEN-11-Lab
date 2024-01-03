//lab10.h
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <unistd.h>

union info{
    int bday[2];
    char ophone[20];
}info;

struct Node {
    char fname[10];
    char lname[10];
    char number[11];
    union info extra;
    int type;
    struct Node *next;
};

extern struct Node *heads[];
pthread_mutex_t mutex;


void read_from_keyboard(void);
void show_all(void);
bool check_duplicate(char[], char[]);
void show_name(void);
void delete(void);
void delete_name(void);
void sort(void);
void save_to_file(char[], int);
void read_from_file(char[], int);
struct Node *delete_all(struct Node *current);
void bin_read_from_file(char[]);
void *bin_write_to_file(void *arg);