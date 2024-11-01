#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_N 100005
#define MAX_M 100005
#define ALPHABET_SIZE 26

typedef struct TrieNode {
    struct TrieNode *children[ALPHABET_SIZE];
    int end;
    int fail;
    int id;
} TrieNode;

TrieNode *root;
char input[MAX_N];
int n = 0, m;
int result[MAX_N];
int cnt[MAX_N];
int query[MAX_M][2];

TrieNode* createNode() {
    TrieNode* node = (TrieNode*)malloc(sizeof(TrieNode));
    memset(node->children, 0, sizeof(node->children));
    node->end = node->fail = node->id = 0;
    return node;
}

void insert(char* str) {
    TrieNode* current = root;
    for (int i = 0; str[i]; i++) {
        int index = str[i] - 'a';
        if (!current->children[index])
            current->children[index] = createNode();
        current = current->children[index];
    }
    current->end = 1;
    current->id = ++n;
}

void buildAC() {
    TrieNode* queue[MAX_N];
    int front = 0, rear = 0;
    queue[rear++] = root;

    while (front < rear) {
        TrieNode* node = queue[front++];
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            if (node->children[i]) {
                TrieNode* child = node->children[i];
                if (node == root) {
                    child->fail = root;
                } else {
                    TrieNode* failNode = node->fail;
                    while (failNode != root && !failNode->children[i])
                        failNode = failNode->fail;
                    if (failNode->children[i])
                        failNode = failNode->children[i];
                    child->fail = failNode;
                }
                queue[rear++] = child;
            }
        }
    }
}

void match(char* str) {
    TrieNode* current = root;
    for (int i = 0; str[i]; i++) {
        int index = str[i] - 'a';
        while (current != root && !current->children[index])
            current = current->fail;
        if (current->children[index])
            current = current->children[index];
        TrieNode* temp = current;
        while (temp != root) {
            if (temp->end)
                cnt[temp->id]++;
            temp = temp->fail;
        }
    }
}

int main() {
    root = createNode();
    scanf("%s", input);
    
    char buffer[MAX_N];
    int bufferLen = 0;
    
    for (int i = 0; input[i]; i++) {
        if (input[i] == 'P') {
            buffer[bufferLen] = '\0';
            insert(buffer);
        } else if (input[i] == 'B') {
            if (bufferLen > 0) bufferLen--;
        } else {
            buffer[bufferLen++] = input[i];
        }
    }
    
    buildAC();
    
    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &query[i][0], &query[i][1]);
    }
    
    memset(cnt, 0, sizeof(cnt));
    for (int i = 1; i <= n; i++) {
        char temp[MAX_N];
        int len = 0;
        for (int j = 0; input[j]; j++) {
            if (input[j] == 'P') {
                if (--i == 0) break;
            } else if (input[j] == 'B') {
                if (len > 0) len--;
            } else {
                temp[len++] = input[j];
            }
        }
        temp[len] = '\0';
        match(temp);
    }
    
    for (int i = 0; i < m; i++) {
        printf("%d\n", cnt[query[i][0]]);
    }
    
    return 0;
}