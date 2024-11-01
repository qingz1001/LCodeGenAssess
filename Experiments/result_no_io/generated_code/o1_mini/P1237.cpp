#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#define MAX_FDS 100
#define MAX_QUEUE 1000000
#define MAX_PATH 100
#define ATTRIBUTE_BITS 26

typedef struct {
    uint32_t left;
    uint32_t right;
} FD;

typedef struct {
    uint32_t closure;
    int path[MAX_FDS];
    int path_len;
} QueueItem;

// Global visited array: 1 << 26 bits = 8,388,608 bytes
unsigned char visited_global[1 << 23];

int main(){
    int n;
    scanf("%d", &n);
    FD fds[MAX_FDS];
    char line[256];
    for(int i=0;i<n;i++){
        scanf("%s", line);
        char *arrow = strstr(line, "->");
        *arrow = '\0';
        arrow += 2;
        // Parse left
        uint32_t left = 0;
        for(int j=0; line[j] != '\0'; j++) left |= 1U << (line[j]-'A');
        // Parse right
        uint32_t right = 0;
        for(int j=0; arrow[j] != '\0'; j++) right |= 1U << (arrow[j]-'A');
        fds[i].left = left;
        fds[i].right = right;
    }

    int redundant[MAX_FDS];
    int redundant_count = 0;
    int paths[MAX_FDS][MAX_FDS];
    int path_lengths[MAX_FDS];

    for(int x=0; x<n; x++){
        // Build remaining FDs excluding x
        FD remaining_fds[MAX_FDS];
        int rem_n = 0;
        for(int i=0;i<n;i++) if(i != x) remaining_fds[rem_n++] = fds[i];
        // Get X and Y
        uint32_t X = fds[x].left;
        uint32_t Y = fds[x].right;
        // Compute closure of X without FD x
        uint32_t closure = X;
        int changed = 1;
        while(changed){
            changed = 0;
            for(int i=0;i<rem_n;i++) {
                if( (remaining_fds[i].left & closure) == remaining_fds[i].left ){
                    if( (closure | remaining_fds[i].right) != closure ){
                        closure |= remaining_fds[i].right;
                        changed = 1;
                    }
                }
            }
        }
        if( (closure & Y) == Y ){
            // FD x is redundant
            // Now find the minimal path
            // Initialize BFS
            QueueItem *queue = malloc(sizeof(QueueItem)*MAX_QUEUE);
            int head=0, tail=0;
            queue[tail].closure = X;
            queue[tail].path_len = 0;
            tail++;
            // Initialize visited
            memset(visited_global, 0, sizeof(visited_global));
            visited_global[X >> 3] |= (1 << (X & 7));
            int found = 0;
            int min_path[MAX_FDS];
            int min_len = 0;
            while(head < tail && !found){
                QueueItem current = queue[head++];
                for(int i=0;i<rem_n;i++){
                    if( (remaining_fds[i].left & current.closure) == remaining_fds[i].left ){
                        uint32_t new_closure = current.closure | remaining_fds[i].right;
                        if( !( (visited_global[new_closure >> 3] ) & (1 << (new_closure & 7)) )){
                            visited_global[new_closure >> 3] |= (1 << (new_closure & 7));
                            // Prepare new path
                            QueueItem next = queue[head-1];
                            next.closure = new_closure;
                            memcpy(next.path, current.path, sizeof(int)*current.path_len);
                            next.path[current.path_len] = (i < x) ? i+1 : i+2;
                            next.path_len = current.path_len +1;
                            // Check if Y is included
                            if( (new_closure & Y) == Y ){
                                found = 1;
                                min_len = next.path_len;
                                for(int p=0;p<min_len;p++) min_path[p] = next.path[p];
                                break;
                            }
                            // Enqueue
                            if(tail < MAX_QUEUE){
                                queue[tail++] = next;
                            }
                        }
                    }
                }
            }
            free(queue);
            if(found){
                redundant[redundant_count] = x+1;
                path_lengths[redundant_count] = min_len;
                for(int p=0; p<min_len; p++) paths[redundant_count][p] = min_path[p];
                redundant_count++;
            }
        }
    }

    if(redundant_count == 0){
        printf("No redundant FDs\n");
    }
    else{
        for(int i=0;i<redundant_count;i++){
            printf("FD %d is redundant using FDs:", redundant[i]);
            for(int p=0; p<path_lengths[i]; p++) printf(" %d", paths[i][p]);
            printf("\n");
        }
    }

    return 0;
}