#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NODES 40000
#define ALPHABET 2

typedef struct Node {
    int children[ALPHABET];
    int fail;
    int output;
} Node;

Node trie[MAX_NODES];
int node_count = 1;

int queue[MAX_NODES];
int head = 0, tail = 0;

char buffer[10005];
int adj[MAX_NODES][ALPHABET];
int visited[MAX_NODES];
int rec_stack[MAX_NODES];
int n;

// Function to create a new node
int create_node() {
    memset(trie[node_count].children, -1, sizeof(trie[node_count].children));
    trie[node_count].fail = 0;
    trie[node_count].output = 0;
    return node_count++;
}

// Insert a string into the trie
void insert(char *s) {
    int node = 0;
    for(int i = 0; s[i]; i++) {
        int c = s[i] - '0';
        if(trie[node].children[c] == -1) {
            trie[node].children[c] = create_node();
        }
        node = trie[node].children[c];
    }
    trie[node].output = 1;
}

// Build the Aho-Corasick automaton
void build_ac() {
    // Initialize queue
    for(int c = 0; c < ALPHABET; c++) {
        if(trie[0].children[c] != -1) {
            trie[trie[0].children[c]].fail = 0;
            queue[tail++] = trie[0].children[c];
        }
        else {
            trie[0].children[c] = 0;
        }
    }
    // BFS
    while(head < tail) {
        int current = queue[head++];
        for(int c = 0; c < ALPHABET; c++) {
            if(trie[current].children[c] != -1) {
                int child = trie[current].children[c];
                int fail = trie[current].fail;
                while(trie[fail].children[c] == -1 && fail != 0)
                    fail = trie[fail].fail;
                if(trie[fail].children[c] != -1)
                    fail = trie[fail].children[c];
                trie[child].fail = fail;
                trie[child].output |= trie[fail].output;
                queue[tail++] = child;
            }
            else {
                trie[current].children[c] = trie[trie[current].fail].children[c];
            }
        }
    }
}

// DFS to detect cycle
int has_cycle(int node) {
    visited[node] = 1;
    rec_stack[node] = 1;
    for(int c = 0; c < ALPHABET; c++) {
        int next = trie[node].children[c];
        if(trie[next].output) continue;
        if(!visited[next]) {
            if(has_cycle(next)) return 1;
        }
        else if(rec_stack[next]) {
            return 1;
        }
    }
    rec_stack[node] = 0;
    return 0;
}

int main(){
    memset(trie, -1, sizeof(trie));
    n = 0;
    scanf("%d", &n);
    for(int i = 0; i < n; i++) {
        scanf("%s", buffer);
        insert(buffer);
    }
    build_ac();
    if(has_cycle(0)) printf("TAK\n");
    else printf("NIE\n");
    return 0;
}