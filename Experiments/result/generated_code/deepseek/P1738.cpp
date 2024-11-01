#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATH_LENGTH 101
#define MAX_N 1000

typedef struct Node {
    char name[MAX_PATH_LENGTH];
    struct Node* children[26 + 10]; // 26 letters + 10 digits
    int childCount;
} Node;

Node* createNode(const char* name) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->name, name);
    for (int i = 0; i < 26 + 10; i++) {
        newNode->children[i] = NULL;
    }
    newNode->childCount = 0;
    return newNode;
}

int insertPath(Node* root, const char* path) {
    int count = 0;
    Node* current = root;
    char* token = strtok((char*)path, "/");
    while (token != NULL) {
        int index = -1;
        if (token[0] >= 'a' && token[0] <= 'z') {
            index = token[0] - 'a';
        } else if (token[0] >= '0' && token[0] <= '9') {
            index = 26 + (token[0] - '0');
        }
        if (index != -1) {
            if (current->children[index] == NULL) {
                current->children[index] = createNode(token);
                count++;
            }
            current = current->children[index];
        }
        token = strtok(NULL, "/");
    }
    return count;
}

int main() {
    int N;
    char paths[MAX_N][MAX_PATH_LENGTH];
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%s", paths[i]);
    }

    Node* root = createNode("");
    int totalCount = 0;
    for (int i = 0; i < N; i++) {
        totalCount += insertPath(root, paths[i]);
        printf("%d\n", totalCount);
    }

    return 0;
}