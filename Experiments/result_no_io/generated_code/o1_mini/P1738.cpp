#include <stdio.h>
#include <string.h>

#define MAX_NODES 100000
#define MAX_CHILDREN 100
#define MAX_NAME_LEN 101
#define MAX_PATH_LEN 102

struct Node {
    char name[MAX_NAME_LEN];
    int children_count;
    int children[MAX_CHILDREN];
} nodes[MAX_NODES];

int node_count = 1; // Start from 1 since 0 is the root

int find_child(int parent, char *name) {
    for(int i = 0; i < nodes[parent].children_count; i++) {
        int child = nodes[parent].children[i];
        if(strcmp(nodes[child].name, name) == 0) {
            return child;
        }
    }
    return -1;
}

int main(){
    int N;
    scanf("%d", &N);
    getchar(); // consume newline after N

    // Initialize root
    nodes[0].children_count = 0;

    char path[MAX_PATH_LEN];
    for(int i = 0; i < N; i++) {
        fgets(path, sizeof(path), stdin);
        // Remove trailing newline
        int len = strlen(path);
        if(path[len-1] == '\n') path[len-1] = '\0';

        int current_node = 0;
        int new_folders = 0;

        char *token = strtok(path, "/");
        while(token != NULL){
            int child = find_child(current_node, token);
            if(child == -1){
                // Create new node
                strcpy(nodes[node_count].name, token);
                nodes[node_count].children_count = 0;
                nodes[current_node].children[nodes[current_node].children_count++] = node_count;
                current_node = node_count;
                node_count++;
                new_folders++;
            }
            else{
                current_node = child;
            }
            token = strtok(NULL, "/");
        }
        printf("%d\n", new_folders);
    }

    return 0;
}