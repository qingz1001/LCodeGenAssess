#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATH_LEN 100

typedef struct Node {
    char name[MAX_PATH_LEN];
    struct Node* children;
    struct Node* next;
} Node;

Node* root = NULL;

Node* createNode(const char* name) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->name, name);
    newNode->children = NULL;
    newNode->next = NULL;
    return newNode;
}

void addPath(const char* path) {
    Node* curr = root;
    Node* prev = NULL;
    char* token = strtok((char*)path, "/");
    
    while (token != NULL) {
        Node* child = curr->children;
        Node* prevChild = NULL;
        
        while (child != NULL) {
            if (strcmp(child->name, token) == 0) {
                break;
            }
            prevChild = child;
            child = child->next;
        }
        
        if (child == NULL) {
            child = createNode(token);
            if (prevChild == NULL) {
                curr->children = child;
            } else {
                prevChild->next = child;
            }
        }
        
        prev = curr;
        curr = child;
        token = strtok(NULL, "/");
    }
}

int countNewFolders(const char* path) {
    Node* curr = root;
    Node* prev = NULL;
    char* token = strtok((char*)path, "/");
    int count = 0;
    
    while (token != NULL) {
        Node* child = curr->children;
        Node* prevChild = NULL;
        
        while (child != NULL) {
            if (strcmp(child->name, token) == 0) {
                break;
            }
            prevChild = child;
            child = child->next;
        }
        
        if (child == NULL) {
            count++;
            child = createNode(token);
            if (prevChild == NULL) {
                curr->children = child;
            } else {
                prevChild->next = child;
            }
        }
        
        prev = curr;
        curr = child;
        token = strtok(NULL, "/");
    }
    
    return count;
}

int main() {
    int N;
    scanf("%d", &N);
    
    root = createNode("/");
    
    for (int i = 0; i < N; i++) {
        char path[MAX_PATH_LEN];
        scanf("%s", path);
        printf("%d\n", countNewFolders(path));
    }
    
    return 0;
}