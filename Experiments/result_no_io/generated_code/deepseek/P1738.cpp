#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATH_LENGTH 101
#define MAX_N 1000

typedef struct Node {
    struct Node* children[26 + 10]; // 26 letters + 10 digits
} Node;

Node* createNode() {
    Node* node = (Node*)malloc(sizeof(Node));
    for (int i = 0; i < 36; i++) {
        node->children[i] = NULL;
    }
    return node;
}

int charToIndex(char c) {
    if (c >= 'a' && c <= 'z') {
        return c - 'a';
    } else if (c >= '0' && c <= '9') {
        return 26 + (c - '0');
    }
    return -1; // Invalid character
}

int insertPath(Node* root, char* path) {
    Node* current = root;
    int count = 0;
    char* token = strtok(path, "/");
    while (token != NULL) {
        int index = charToIndex(token[0]);
        if (current->children[index] == NULL) {
            current->children[index] = createNode();
            count++;
        }
        current = current->children[index];
        token = strtok(NULL, "/");
    }
    return count;
}

int main() {
    int N;
    char paths[MAX_N][MAX_PATH_LENGTH];
    Node* root = createNode();
    int totalFolders = 0;

    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%s", paths[i]);
        totalFolders += insertPath(root, paths[i]);
        printf("%d\n", totalFolders);
    }

    // Free memory
    // Note: This is a simplified version. In a real application, you would need to free all nodes recursively.
    free(root);

    return 0;
}