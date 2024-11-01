#include <stdio.h>
#include <stdlib.h>

int main(){
    int N, K;
    scanf("%d %d", &N, &K);
    
    int *H = (int*)malloc(N * sizeof(int));
    int *W = (int*)malloc(N * sizeof(int));
    int H_max = 0, W_max = 0;
    
    for(int i = 0; i < N; i++){
        scanf("%d %d", &H[i], &W[i]);
        if(H[i] > H_max) H_max = H[i];
        if(W[i] > W_max) W_max = W[i];
    }
    
    int low = 1, high = H_max < W_max ? H_max : W_max, res = 1;
    while(low <= high){
        int mid = low + (high - low) / 2;
        long long sum = 0;
        for(int i = 0; i < N; i++){
            sum += ((long long)(H[i] / mid)) * ((long long)(W[i] / mid));
            if(sum >= K){
                break;
            }
        }
        if(sum >= K){
            res = mid;
            low = mid + 1;
        }
        else{
            high = mid - 1;
        }
    }
    
    printf("%d\n", res);
    free(H);
    free(W);
    return 0;
}