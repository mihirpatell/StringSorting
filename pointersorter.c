
#include "pointersorter.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int NUM_WORDS = 0; //holds the number of words in the string
node* root; //front of the linked list

void freeLL(node* root){ //Method to free malloc'd objects
    node* ptr = root;
    while(ptr != 0){
        free(ptr);
        ptr = ptr->next;
    }
}

node* createNode(char* argv){ //Create a new node and save argv into the data field
    if(argv == 0)
        return 0;
    node* link;
    link = (node *) malloc(sizeof(node));
    if(link == NULL){ //if malloc is unsuccessful, exit program and free malloc'd objects, if any
        printf("Memory allocation unsuccessful. Sorry :(\n");
        freeLL(root);
        exit(1);
    }
    link->data = argv;
    link->next = 0;
    return link;
}

char* isAlpha(char* a){ //Method to take the inputted string and check whether each character of that string is a letter
    int length = (strlen(a) - 1);
    int i;
    for(i = 0; a[i]; i++){
        if(!isalpha(a[i])){ //Checks if the character is a non-letter, if isalpha returns 0 it is a non-letter
            NUM_WORDS++;
            a[i] = '/'; //if a character is a non-letter, this changes it to a '/'
            continue;
        }
    }
    
    return a;
}

node* sort(node* root){ //Puts words in alphabetic order while adding them to the linked list
    int j = 0;
    while(j != NUM_WORDS){
        node* word = createNode(strtok(NULL, "/")); //next word in string is put into a node* variable called "word"
        if(word == 0)
            break;
        node* ptr;
        node* prev = 0; //node before ptr
        for(ptr = root; ptr != 0; ptr = ptr->next){
            int compare = strcmp(word->data, ptr->data);
            if(compare == 0){ //if the words are the same, insert word into the linked list after the original
                word->next = ptr->next;
                ptr->next = word;
                break;
            }
            else if(compare < 0){ //if word comes before ptr alphabetically, insert word into the linked list before ptr
                word->next = ptr;
                if(prev != 0)
                    prev->next = word;
                if(ptr == root)
                    root = word;
                break;
            }
            else if(ptr->next == 0){ //if ptr is the last node in the list, insert word after it
                ptr->next = word;
                break;
            }
            prev = ptr;
        }
        j++;
    }
    return root;
}

void printLL(node* root){ //Print linked list in alphabetic order
    node* ptr = root;
    while(ptr != 0){
        printf("%s\n", ptr->data);
        ptr = ptr->next;
    }
    if(root == 0)
        printf("\n");
}

int main(int argc, char *argv[]){
    
    if(argc != 2){ //if the number of parameters in the input is not 2, output a usage message to stderr and exit the program
        usage: fprintf(stderr,"Incorrect number of parameters\n" );
        exit(1);
    }
    
    root = sort(createNode(strtok(isAlpha(argv[1]), "/"))); //grab first word out of string using strtok and put in linked list as the root
    
    printLL(root);
    
    freeLL(root);

    return 0;
}
