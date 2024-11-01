#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_PATHS 1000
#define MAX_LENGTH 101

typedef struct TrieNode {
    struct TrieNode* children[36];
    int count;
} TrieNode;

TrieNode* createNode() {
    TrieNode* node = (TrieNode*)malloc(sizeof(TrieNode));
    for (int i = 0; i < 36; i++) {
        node->children[i] = NULL;
    }
    node->count = 0;
    return node;
}

int getIndex(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    return c - 'a' + 10;
}

int insert(TrieNode* root, char* path) {
    TrieNode* node = root;
    int newFolders = 0;
    char* token = strtok(path, "/");
    
    while (token != NULL) {
        for (int i = 0; token[i]; i++) {
            int index = getIndex(token[i]);
            if (!node->children[index]) {
                node->children[index] = createNode();
                newFolders++;
            }
            node = node->children[index];
        }
        token = strtok(NULL, "/");
    }
    return newFolders;
}

int main() {
    int N;
    scanf("%d", &N);
    
    char paths[MAX_PATHS][MAX_LENGTH];
    TrieNode* root = createNode();
    
    for (int i = 0; i < N; i++) {
        scanf("%s", paths[i]);
        int newFolders = insert(root, paths[i]);
        printf("%d\n", newFolders);
    }
    
    return 0;
}