/******************************************************************************
查找：O(1) - 直接通過陣列索引訪問
插入：O(1) - 直接定位到對應位置
總體處理每個字元：O(1)
*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH_SIZE 256  // ASCII字元集大小

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

// 使用陣列作為hash table來快速查找
void insertOrUpdate(Node* hash[], char c) {
    unsigned char uc = (unsigned char)c;  // 轉為unsigned以處理所有ASCII字元
    if (hash[uc] == NULL) {
        hash[uc] = createNode(c);
    } else {
        hash[uc]->count++;
    }
}

void printList(Node* hash[]) {
    for (int i = 0; i < HASH_SIZE; i++) {
        if (hash[i] != NULL) {
            printf("%c : %d\n", hash[i]->data, hash[i]->count);
        }
    }
}

void freeList(Node* hash[]) {
    for (int i = 0; i < HASH_SIZE; i++) {
        if (hash[i] != NULL) {
            free(hash[i]);
        }
    }
}

int main() {
    FILE* file = fopen(__FILE__, "r");
    if (file == NULL) {
        printf("Cannot open file\n");
        return 1;
    }

    Node* hash[HASH_SIZE] = {NULL};  // 初始化hash table
    char c;
    
    while ((c = fgetc(file)) != EOF) {
        insertOrUpdate(hash, c);
    }
    
    printList(hash);
    freeList(hash);
    fclose(file);
    
    return 0;
}
