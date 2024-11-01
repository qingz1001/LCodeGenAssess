#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_FD 100
#define MAX_QUEUE 70000000
#define MAX_PATH 100

typedef struct {
    unsigned int lhs;
    unsigned int rhs;
    int number;
} FD;

// Global arrays for BFS
unsigned char *visited;
unsigned int *parent_closure;
unsigned char *fd_used_num;
unsigned int *queue;
unsigned int head_q, tail_q;

FD fds[MAX_FD];
int n;

// Function to convert string to bitmask
unsigned int str_to_bitmask(char *s) {
    unsigned int mask = 0;
    for(int i=0; s[i]; i++) {
        if(s[i]>='A' && s[i]<='Z') {
            mask |= (1U << (s[i]-'A'));
        }
    }
    return mask;
}

// Function to parse a FD line
void parse_fd(char *line, FD *fd) {
    char *arrow = strstr(line, "->");
    if(!arrow) {
        fd->lhs = 0;
        fd->rhs = 0;
        return;
    }
    *arrow = '\0';
    char *lhs = line;
    char *rhs = arrow + 2;
    fd->lhs = str_to_bitmask(lhs);
    fd->rhs = str_to_bitmask(rhs);
}

// Function to compute closure
unsigned int compute_closure(unsigned int initial, FD *list, int size) {
    unsigned int closure = initial;
    int changed;
    do {
        changed = 0;
        for(int i=0;i<size;i++) {
            if( (list[i].lhs & closure) == list[i].lhs ) {
                unsigned int new_attrs = list[i].rhs & (~closure);
                if(new_attrs) {
                    closure |= list[i].rhs;
                    changed = 1;
                }
            }
        }
    } while(changed);
    return closure;
}

// Function to perform BFS and find minimal sequence
int bfs(unsigned int X, unsigned int Y, FD *list, int size, int *path) {
    // Initialize visited, parent, fd_used
    // Allocate memory
    visited = calloc((1<<26)/8, sizeof(unsigned char));
    parent_closure = calloc(1<<26, sizeof(unsigned int));
    fd_used_num = calloc(1<<26, sizeof(unsigned char));
    if(!visited || !parent_closure || !fd_used_num) {
        // Memory allocation failed
        exit(1);
    }

    // Initialize queue
    queue = malloc(sizeof(unsigned int) * MAX_QUEUE);
    head_q = 0;
    tail_q = 0;
    queue[tail_q++] = X;
    // Mark visited
    visited[X / 8] |= (1 << (X % 8));

    while(head_q < tail_q) {
        unsigned int current = queue[head_q++];
        // Check if Y is subset of current
        if( (current & Y) == Y ) {
            // Reconstruct path
            int cnt = 0;
            unsigned int s = current;
            while(s != X) {
                int fd = fd_used_num[s];
                path[cnt++] = fd;
                s = parent_closure[s];
            }
            // Reverse the path
            for(int i=0;i<cnt/2;i++) {
                int temp = path[i];
                path[i] = path[cnt-1-i];
                path[cnt-1-i] = temp;
            }
            // Free memory
            free(visited);
            free(parent_closure);
            free(fd_used_num);
            free(queue);
            return cnt;
        }
        // Try all FDs
        for(int i=0;i<size;i++) {
            if( (list[i].lhs & current) == list[i].lhs ) {
                unsigned int new_closure = current | list[i].rhs;
                if( !((visited[new_closure / 8] >> (new_closure % 8)) & 1) ) {
                    // Mark visited
                    visited[new_closure / 8] |= (1 << (new_closure % 8));
                    // Set parent and fd_used
                    parent_closure[new_closure] = current;
                    fd_used_num[new_closure] = list[i].number;
                    // Enqueue
                    queue[tail_q++] = new_closure;
                    if(tail_q >= MAX_QUEUE) break;
                }
            }
        }
    }
    // Free memory
    free(visited);
    free(parent_closure);
    free(fd_used_num);
    free(queue);
    return -1; // Not found
}

int main(){
    scanf("%d\n", &n);
    char line[256];
    for(int i=0;i<n;i++){
        fgets(line, sizeof(line), stdin);
        // Remove newline
        line[strcspn(line, "\n")] = 0;
        parse_fd(line, &fds[i]);
        fds[i].number = i+1;
    }

    int redundant = 0;
    for(int i=0;i<n;i++){
        // Create list_rest
        FD list_rest[MAX_FD];
        int size = 0;
        for(int j=0;j<n;j++) {
            if(j != i){
                list_rest[size++] = fds[j];
            }
        }
        // Compute closure of X
        unsigned int closure = compute_closure(fds[i].lhs, list_rest, size);
        // Check if Y is subset of closure
        if( (closure & fds[i].rhs) == fds[i].rhs ){
            // It's redundant
            redundant = 1;
            // Find minimal sequence using BFS
            int path[MAX_FD];
            int path_len = bfs(fds[i].lhs, fds[i].rhs, list_rest, size, path);
            if(path_len == -1){
                // Should not happen as it's redundant
                continue;
            }
            // Print the result
            printf("FD %d is redundant using FDs:", fds[i].number);
            for(int p=0;p<path_len;p++) {
                printf(" %d", path[p]);
            }
            printf("\n");
        }
    }
    if(!redundant){
        printf("No redundant FDs\n");
    }
    return 0;
}