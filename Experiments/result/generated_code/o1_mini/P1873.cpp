#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

int main(){
    int N;
    ll M;
    scanf("%d %lld", &N, &M);
    
    int *trees = (int*)malloc(N * sizeof(int));
    int max_h = 0;
    for(int i=0;i<N;i++){
        scanf("%d", &trees[i]);
        if(trees[i] > max_h){
            max_h = trees[i];
        }
    }
    
    ll left = 0, right = max_h, answer = 0;
    while(left <= right){
        ll mid = left + (right - left) / 2;
        ll total = 0;
        for(int i=0;i<N;i++){
            if(trees[i] > mid){
                total += trees[i] - mid;
                if(total >= M){
                    break;
                }
            }
        }
        if(total >= M){
            answer = mid;
            left = mid +1;
        }
        else{
            right = mid -1;
        }
    }
    
    printf("%lld", answer);
    free(trees);
    return 0;
}