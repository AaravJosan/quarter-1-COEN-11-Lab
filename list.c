#include "lab10.h"


//Function to add name to the linked list
void read_from_keyboard(void){
    struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
    char firstName[10];
    char lastName[10];
    char phoneNumber[11];

    printf("Enter first name, last name and phone number\n");
    scanf("%s", firstName);
    scanf("%s", lastName);

    //checks if name is already in the linked list
    if(check_duplicate(firstName, lastName)){
        printf("The name is already in the list\n");    
        free(newNode);
        return;
    }

    scanf("%s", phoneNumber);

    strcpy(newNode -> fname, firstName);
    strcpy(newNode -> lname, lastName);
    strcpy(newNode -> number, phoneNumber);

    int option;
    printf("Enter option 0, 1 or 2\n");
    scanf("%d", &option);
    newNode -> type = 2;

    if(option == 0) {
        int month, day;
        printf("Enter bday month\n");
        scanf("%d", &month);
        printf("Enter bday day\n");
        scanf("%d", &day);
        newNode -> extra.bday[0] = month;
        newNode -> extra.bday[1] = day;
        newNode -> type = 0;
    }
    else if(option == 1){
        char otherPhone[20];
        printf("Enter office phone number\n");
        scanf("%s", otherPhone);
        strcpy(newNode -> extra.ophone, otherPhone);
        newNode -> type = 1;
    }

    int lastNameAscii = lastName[0];

    //a to k
    if(lastNameAscii >= 97 && lastNameAscii <= 107){
        if(heads[0] == NULL){
            heads[0] = newNode;
            return;
        }
        newNode -> next = heads[0];
        heads[0] = newNode;
        sort();
    }

    //l to r
    else if(lastNameAscii >= 108 && lastNameAscii <= 114){
        if(heads[1] == NULL){
            heads[1] = newNode;
            return;
        }
        newNode -> next = heads[1];
        heads[1] = newNode;
        sort();
    }

    //s to z
    else if(lastNameAscii >= 115 && lastNameAscii <= 122){
        if(heads[2] == NULL){
            heads[2] = newNode;
            return;
        }
        newNode -> next = heads[2];
        heads[2] = newNode;
        sort();
    }
}

//function to print all the information in the linked list
void show_all(void){
    for(int i = 0; i < 3; i++){
        struct Node *current = heads[i];
        while(current != NULL) {
            if(current->type == 0)
                printf("%s %s: %s. Birthday: %d/%d \n", current -> fname, current -> lname, current -> number, current -> extra.bday[0], current -> extra.bday[1]);
            else if(current->type == 1)
                printf("%s %s: %s. Office phone: %s\n", current -> fname, current -> lname, current -> number, current -> extra.ophone);
            else if(current->type == 2)
                printf("%s %s: %s \n", current -> fname, current -> lname, current -> number);
            current = current -> next;
            }
    }
}

//Function to check if name is already present in the linked list
bool check_duplicate(char first[], char last[]){
    for(int i = 0; i < 3; i++){
        struct Node *current = heads[i];
        while(current != NULL) {
            if(strcmp(first, current -> fname) == 0 && strcmp(last, current -> lname) == 0)
                return true;
            current = current -> next;
        }
    }
    return false;
}

//function to search for a name in the linked list
void show_name(void){
    if(heads[0] == NULL && heads[0] == NULL && heads[2] == NULL) {
        printf("The list is empty\n");
        return;
    }

    char lastName[10];
    bool found = false;
    printf("Enter last name\n");
    scanf("%s", lastName);
    for(int i = 0; i < 3; i++){
        struct Node *current = heads[i];
        while(current != NULL) {
            if(strcmp(current -> lname, lastName) == 0){
                found = true;
                if(current->type == 0)
                    printf("%s %s: %s. Birthday: %d/%d \n", current -> fname, current -> lname, current -> number, current -> extra.bday[0], current -> extra.bday[1]);
                else if(current->type == 1)
                    printf("%s %s: %s. Office phone: %s\n", current -> fname, current -> lname, current -> number, current -> extra.ophone);
                else if(current->type == 2)
                    printf("%s %s: %s \n", current -> fname, current -> lname, current -> number);
            }
            current = current -> next;
        }
    }
    if(!found)
        printf("The last name is not in the list\n");
}

//function to delete a name from the linked list using thier full name 
void delete(void){
    if(heads[0] == NULL && heads[0] == NULL && heads[2] == NULL){
        printf("The list is empty\n");
        return;
    }
    char firstName[10];
    char lastName[10];

    printf("Enter the persons full name\n");
    scanf("%s", firstName);
    scanf("%s", lastName);

    for(int i = 0; i < 3; i++){
        if(strcmp(firstName, heads[i] -> fname) == 0 && strcmp(lastName, heads[i] -> lname) == 0){
            printf("The name has been deleted!\n");
            if(heads[i] -> next == NULL){
                heads[i] = NULL;
                return;
            }
            struct Node *temp = heads[i];
            heads[i] = heads[i] -> next;
            free(temp);
        return;
        }

        struct Node *current = heads[i];
        while(current != NULL){ 
            if(strcmp(firstName, current -> next -> fname) == 0 && strcmp(lastName, current -> next -> lname) == 0){
                struct Node *temp = current -> next;
                current -> next = current -> next -> next;
                free(temp);
                printf("The name has been deleted!\n");
            return;
            }
            current = current->next;
        }
    }
}

//function to delete all first names inputed
void delete_name(void) {
    if (heads[0] == NULL && heads[1] == NULL && heads[2] == NULL) {
        printf("The list is empty\n");
        return;
    }

    char firstName[10];
    printf("Enter first name\n");
    scanf("%s", firstName);

    bool found = false;

    for (int i = 0; i < 3; i++) {
        if (heads[i] == NULL)
            continue;

        struct Node* current = heads[i];
        struct Node* prev = NULL;

        while (current != NULL) {
            if (strcmp(firstName, current->fname) == 0) {
                found = true;
                if (prev == NULL) {
                    heads[i] = current->next;
                    free(current);
                    current = heads[i]; 
                } else {
                    prev->next = current->next;
                    free(current);
                    current = prev->next; 
                }
            } else {
                prev = current;
                current = current->next;
            }
        }
    }

    if (found) {
        printf("The names have been deleted\n");
    } else {
        printf("Name not found in list\n");
    }
}

//function to sort the code using the persons last name
void sort() {
    if(heads[0] == NULL && heads[0] == NULL && heads[2] == NULL){
        return;
    }

    for(int i = 0; i < 3; i++){
            struct Node* sorted = NULL;
            struct Node* current = heads[i];

             while (current != NULL) {
                struct Node* prev = NULL;
                struct Node* node = sorted;

                struct Node* nextNode = current->next; 

             while (node && strcmp(current->lname, node->lname) > 0) {
            prev = node;
            node = node->next;
                }

            if (prev) {
                prev->next = current;
            } else {
                sorted = current;
            }
            current->next = node;
            current = nextNode;
            }
        heads[i] = sorted;
        }
    
}

struct Node *delete_all(struct Node *current){
    if(current == NULL)
        exit(0);

    struct Node *temp = current;
    current = current -> next;
    free(temp);
    return current;
}
