#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char data;
    int count;
    struct Node* next;
} Node;

Node* createNode(char c) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = c;
    newNode->count = 1;
    newNode->next = NULL;
    return newNode;
}

void insertOrUpdate(Node** head, char c) {
    if (*head == NULL) {
        *head = createNode(c);
        return;
    }
    
    Node* current = *head;
    while (current != NULL) {
        if (current->data == c) {
            current->count++;
            return;
        }
        if (current->next == NULL) break;
        current = current->next;
    }
    current->next = createNode(c);
}

void printList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        printf("%c : %d\n", current->data, current->count);
        current = current->next;
    }
}

void freeList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
}

int main() {
    FILE* file = fopen(__FILE__, "r");
    if (file == NULL) {
        printf("Cannot open file\n");
        return 1;
    }

    Node* head = NULL;
    char c;
    
    while ((c = fgetc(file)) != EOF) {
        insertOrUpdate(&head, c);
    }
    
    printList(head);
    freeList(head);
    fclose(file);
    
    return 0;
}
