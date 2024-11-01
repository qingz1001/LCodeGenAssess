#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int has_stair;
    int x;
} Room;

int main(){
    int N, M;
    scanf("%d %d", &N, &M);
    
    // Allocate memory for floors
    Room **floors = (Room **)malloc(N * sizeof(Room *));
    for(int i = 0; i < N; i++){
        floors[i] = (Room *)malloc(M * sizeof(Room));
        for(int j = 0; j < M; j++){
            scanf("%d %d", &floors[i][j].has_stair, &floors[i][j].x);
        }
    }
    
    int s;
    scanf("%d", &s);
    
    // Prepare staircase lists for each floor
    int **stairs = (int **)malloc(N * sizeof(int *));
    int *stairs_cnt = (int *)malloc(N * sizeof(int));
    for(int i = 0; i < N; i++){
        stairs_cnt[i] = 0;
        for(int j = 0; j < M; j++) {
            if(floors[i][j].has_stair) stairs_cnt[i]++;
        }
        if(stairs_cnt[i] > 0){
            stairs[i] = (int *)malloc(stairs_cnt[i] * sizeof(int));
            int idx = 0;
            for(int j = 0; j < M; j++) {
                if(floors[i][j].has_stair) stairs[i][idx++] = j;
            }
        }
        else{
            stairs[i] = NULL;
        }
    }
    
    long long sum = 0;
    int current = s;
    for(int i = 0; i < N; i++){
        if(M == 0){
            break;
        }
        int x = floors[i][current].x;
        sum += x;
        if(stairs_cnt[i] == 0){
            break;
        }
        // Find the position to start counting
        int pos = 0;
        while(pos < stairs_cnt[i] && stairs[i][pos] < current) pos++;
        // Calculate the target index
        int target = (x - 1) % stairs_cnt[i];
        int idx = (pos + target) % stairs_cnt[i];
        current = stairs[i][idx];
    }
    
    printf("%lld\n", sum % 20123);
    
    // Free allocated memory
    for(int i = 0; i < N; i++) free(floors[i]);
    free(floors);
    for(int i = 0; i < N; i++) if(stairs[i]) free(stairs[i]);
    free(stairs);
    free(stairs_cnt);
    
    return 0;
}