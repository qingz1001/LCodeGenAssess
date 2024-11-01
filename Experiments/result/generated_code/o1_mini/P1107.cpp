#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 2001
#define MAX_H 2001

int main(){
    int N, H, Delta;
    scanf("%d %d %d", &N, &H, &Delta);
    
    // Allocate memory for has_persimmon
    unsigned char **has_persimmon = (unsigned char **)malloc((N +1) * sizeof(unsigned char *));
    for(int i=0;i<=N;i++) {
        has_persimmon[i] = (unsigned char *)calloc((H +1), sizeof(unsigned char));
    }
    
    // Read persimmons
    for(int i=1;i<=N;i++){
        int Ni;
        scanf("%d", &Ni);
        for(int j=0;j<Ni;j++){
            int th;
            scanf("%d", &th);
            if(th >=1 && th <=H){
                has_persimmon[i][th] = 1;
            }
        }
    }
    
    // Allocate memory for dp and global_max
    unsigned int **dp = (unsigned int **)malloc((N +1) * sizeof(unsigned int *));
    for(int i=0;i<=N;i++) {
        dp[i] = (unsigned int *)calloc((H +1), sizeof(unsigned int));
    }
    
    unsigned int *global_max = (unsigned int *)calloc((H +1), sizeof(unsigned int));
    
    // Dynamic Programming
    for(int h=1; h<=H; h++){
        unsigned int current_max = 0;
        for(int i=1; i<=N; i++){
            unsigned int collect = has_persimmon[i][h] ? 1 : 0;
            unsigned int option1 = (h >1) ? dp[i][h -1] : 0;
            unsigned int option2 = (h > Delta) ? global_max[h - Delta] : 0;
            unsigned int temp = option1 > option2 ? option1 : option2;
            dp[i][h] = collect + temp;
            if(dp[i][h] > current_max){
                current_max = dp[i][h];
            }
        }
        global_max[h] = current_max;
    }
    
    // Find the maximum dp[i][H] over all trees
    unsigned int answer = 0;
    for(int i=1; i<=N; i++){
        if(dp[i][H] > answer){
            answer = dp[i][H];
        }
    }
    
    printf("%u\n", answer);
    
    // Free memory
    for(int i=0;i<=N;i++) {
        free(has_persimmon[i]);
        free(dp[i]);
    }
    free(has_persimmon);
    free(dp);
    free(global_max);
    
    return 0;
}