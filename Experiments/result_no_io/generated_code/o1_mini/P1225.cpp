#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STATE 65536

int main(){
    unsigned short initial = 0, target = 0;
    int i, j;
    // Read initial grid
    for(i=0;i<4;i++){
        for(j=0;j<4;j++){
            int cell;
            scanf("%d", &cell);
            if(cell){
                initial |= (1 << (i*4 + j));
            }
        }
    }
    // Read target grid
    for(i=0;i<4;i++){
        for(j=0;j<4;j++){
            int cell;
            scanf("%d", &cell);
            if(cell){
                target |= (1 << (i*4 + j));
            }
        }
    }
    // Precompute adjacency list
    int adj[16][4];
    int adj_count[16];
    for(i=0;i<16;i++){
        adj_count[i]=0;
        int row = i /4;
        int col = i %4;
        if(row >0){
            adj[i][adj_count[i]++] = i -4;
        }
        if(row <3){
            adj[i][adj_count[i]++] = i +4;
        }
        if(col >0){
            adj[i][adj_count[i]++] = i -1;
        }
        if(col <3){
            adj[i][adj_count[i]++] = i +1;
        }
    }
    // Initialize BFS
    int distance_arr[MAX_STATE];
    memset(distance_arr, -1, sizeof(distance_arr));
    unsigned short parent_arr[MAX_STATE];
    unsigned char move_a[MAX_STATE], move_b[MAX_STATE], move_c[MAX_STATE], move_d[MAX_STATE];
    // Initialize queue
    unsigned short queue[MAX_STATE];
    int head_q=0, tail_q=0;
    queue[tail_q++] = initial;
    distance_arr[initial] = 0;
    // BFS
    while(head_q < tail_q){
        unsigned short current = queue[head_q++];
        if(current == target){
            break;
        }
        for(i=0;i<16;i++){
            for(j=0;j<adj_count[i];j++){
                int neighbor = adj[i][j];
                if(neighbor < i) continue; // avoid duplicate swaps
                unsigned short new_state = current;
                int bit_i = (current >> i) & 1;
                int bit_j = (current >> neighbor) &1;
                if(bit_i != bit_j){
                    new_state ^= (1<<i) | (1 << neighbor);
                }
                if(distance_arr[new_state] == -1){
                    distance_arr[new_state] = distance_arr[current] +1;
                    parent_arr[new_state] = current;
                    // Convert cell i and neighbor to a,b,c,d
                    int row1 = (i /4) +1, col1 = (i%4) +1;
                    int row2 = (neighbor /4) +1, col2 = (neighbor%4) +1;
                    move_a[new_state] = row1;
                    move_b[new_state] = col1;
                    move_c[new_state] = row2;
                    move_d[new_state] = col2;
                    queue[tail_q++] = new_state;
                }
            }
        }
    }
    // Now reconstruct the path
    if(distance_arr[target]==-1){
        // No solution
        printf("0\n");
        return 0;
    }
    int n = distance_arr[target];
    printf("%d\n", n);
    if(n ==0) return 0;
    // Collect moves
    int path_n = n;
    int path_a[n], path_b[n], path_c[n], path_d[n];
    unsigned short current = target;
    for(i=path_n-1;i>=0;i--){
        path_a[i] = move_a[current];
        path_b[i] = move_b[current];
        path_c[i] = move_c[current];
        path_d[i] = move_d[current];
        current = parent_arr[current];
    }
    // Print path
    for(i=0;i<n;i++){
        printf("%d %d %d %d\n", path_a[i], path_b[i], path_c[i], path_d[i]);
    }
    return 0;
}