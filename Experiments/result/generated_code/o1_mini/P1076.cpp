#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int has_stair;
    int x;
} Room;

int main(){
    int N, M;
    scanf("%d %d", &N, &M);
    Room** floors = (Room**)malloc(N * sizeof(Room*));
    for(int i=0;i<N;i++){
        floors[i] = (Room*)malloc(M * sizeof(Room));
        for(int j=0;j<M;j++){
            scanf("%d %d", &floors[i][j].has_stair, &floors[i][j].x);
        }
    }
    int start;
    scanf("%d", &start);
    // Precompute staircase lists
    int** stairs = (int**)malloc(N * sizeof(int*));
    int* stair_count = (int*)malloc(N * sizeof(int));
    for(int i=0;i<N;i++){
        stair_count[i] =0;
        for(int j=0;j<M;j++) if(floors[i][j].has_stair) stair_count[i]++;
        stairs[i] = (int*)malloc(stair_count[i] * sizeof(int));
        int idx=0;
        for(int j=0;j<M;j++) if(floors[i][j].has_stair) stairs[i][idx++] = j;
    }
    long long sum=0;
    int current_room = start;
    for(int i=0;i<N;i++){
        sum += floors[i][current_room].x;
        if(stair_count[i]==0){
            // No stairs, cannot go up
            break;
        }
        int x = floors[i][current_room].x;
        // Find the first staircase >= current_room
        int pos=0;
        while(pos < stair_count[i] && stairs[i][pos] < current_room) pos++;
        if(pos == stair_count[i]) pos=0;
        int target = (pos + (x-1)) % stair_count[i];
        current_room = stairs[i][target];
    }
    printf("%lld\n", sum%20123);
    // Free memory
    for(int i=0;i<N;i++) {
        free(floors[i]);
        free(stairs[i]);
    }
    free(floors);
    free(stairs);
    free(stair_count);
    return 0;
}