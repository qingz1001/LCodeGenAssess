#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

int main(){
    int N, M, K;
    scanf("%d %d %d", &N, &M, &K);
    
    // Allocate height map with 1-based indexing and padding
    int **h = (int **)malloc((N+2) * sizeof(int *));
    for(int i=0;i<N+2;i++) {
        h[i] = (int *)malloc((M+2) * sizeof(int));
        memset(h[i], 0, (M+2)*sizeof(int));
    }
    
    // Read height map
    for(int x=1;x<=N;x++){
        for(int y=1;y<=M;y++){
            scanf("%d", &h[x][y]);
        }
    }
    
    // Identify mountains
    char **is_mountain = (char **)malloc((N+1) * sizeof(char *));
    for(int x=0;x<=N;x++) {
        is_mountain[x] = (char *)malloc((M+1) * sizeof(char));
        memset(is_mountain[x], 0, (M+1)*sizeof(char));
    }
    
    for(int x=1;x<=N;x++){
        for(int y=1;y<=M;y++){
            int flag = 1;
            // Up
            if(x >1 && h[x][y] < h[x-1][y]) { flag =0;}
            // Down
            if(x <N && h[x][y] < h[x+1][y]) { flag =0;}
            // Left
            if(y >1 && h[x][y] < h[x][y-1]) { flag =0;}
            // Right
            if(y <M && h[x][y] < h[x][y+1]) { flag =0;}
            if(flag){
                is_mountain[x][y] =1;
            }
        }
    }
    
    // Precompute min_distance
    int **min_distance = (int **)malloc((N+1) * sizeof(int *));
    for(int x=0;x<=N;x++) {
        min_distance[x] = (int *)malloc((M+1) * sizeof(int));
        for(int y=1;y<=M;y++) {
            if(is_mountain[x][y]){
                min_distance[x][y] =0;
            }
            else{
                min_distance[x][y] = M+1;
            }
        }
    }
    
    for(int x=1;x<=N;x++){
        // Left to Right
        int tmp = M+1;
        for(int y=1;y<=M;y++){
            if(is_mountain[x][y]){
                tmp =0;
            }
            else{
                if(tmp < M+1){
                    tmp +=1;
                }
            }
            if(tmp < min_distance[x][y]){
                min_distance[x][y] = tmp;
            }
        }
        // Right to Left
        tmp = M+1;
        for(int y=M;y>=1;y--){
            if(is_mountain[x][y]){
                tmp =0;
            }
            else{
                if(tmp < M+1){
                    tmp +=1;
                }
            }
            if(tmp < min_distance[x][y]){
                min_distance[x][y] = tmp;
            }
        }
    }
    
    // Read queries
    int *a = (int *)malloc(K * sizeof(int));
    int *b = (int *)malloc(K * sizeof(int));
    for(int i=0;i<K;i++){
        scanf("%d %d", &a[i], &b[i]);
    }
    
    // Process queries
    char output_buffer[K][25];
    for(int i=0;i<K;i++){
        if(a[i] ==1){
            strcpy(output_buffer[i], "Pool Babingbaboom!");
            continue;
        }
        int left =1;
        int right = a[i]-1;
        int answer = -1;
        while(left <=right){
            int mid = left + (right -left)/2;
            int x = a[i] - mid;
            if(x <1){
                right = mid -1;
                continue;
            }
            if(min_distance[x][b[i]] <= mid){
                answer = mid;
                right = mid -1;
            }
            else{
                left = mid +1;
            }
        }
        if(answer != -1){
            sprintf(output_buffer[i], "%d", answer);
        }
        else{
            strcpy(output_buffer[i], "Pool Babingbaboom!");
        }
    }
    
    // Print all outputs
    for(int i=0;i<K;i++){
        printf("%s\n", output_buffer[i]);
    }
    
    // Free allocated memory
    for(int x=0;x<=N+1;x++) free(h[x]);
    free(h);
    for(int x=0;x<=N;x++) free(is_mountain[x]);
    free(is_mountain);
    for(int x=0;x<=N;x++) free(min_distance[x]);
    free(min_distance);
    free(a);
    free(b);
    
    return 0;
}