#include <stdio.h>
#include <string.h>

#define MAX_NODES 100000
#define MAX_CHILDREN 100

typedef struct {
    char name[101];
    int child_id;
} Child;

typedef struct {
    int num_children;
    Child children[MAX_CHILDREN];
} Node;

Node tree[MAX_NODES];
int node_count = 1; // Start from 1 since 0 is the root
int main(){
    int N;
    scanf("%d", &N);
    getchar(); // Consume the newline after N

    tree[0].num_children = 0;
    int total_created = 0;

    char buffer[201];
    for(int i=0;i<N;i++){
        if(!fgets(buffer, sizeof(buffer), stdin)){
            buffer[0] = '\0';
        }
        // Remove trailing newline
        int len = strlen(buffer);
        if(len >0 && buffer[len-1]=='\n'){
            buffer[len-1]='\0';
        }

        // Split the path
        char path_copy[201];
        strcpy(path_copy, buffer);
        char *token = strtok(path_copy, "/");
        int current = 0;
        int created_this_path = 0;
        while(token != NULL){
            // Search for the token in current node's children
            int found = -1;
            for(int j=0; j < tree[current].num_children; j++){
                if(strcmp(tree[current].children[j].name, token)==0){
                    found = tree[current].children[j].child_id;
                    break;
                }
            }
            if(found == -1){
                // Create new child
                if(tree[current].num_children < MAX_CHILDREN && node_count < MAX_NODES){
                    strcpy(tree[current].children[tree[current].num_children].name, token);
                    tree[current].children[tree[current].num_children].child_id = node_count;
                    tree[current].num_children++;
                    tree[node_count].num_children = 0;
                    current = node_count;
                    node_count++;
                    created_this_path++;
                }
                else{
                    // Exceeded limits, should not happen based on constraints
                    // Handle as needed, here we just exit
                    return 0;
                }
            }
            else{
                current = found;
            }
            token = strtok(NULL, "/");
        }
        total_created += created_this_path;
        printf("%d\n", total_created);
    }
    return 0;
}