#include <stdio.h>
#include <stdlib.h>

int main(){
    int N;
    long long M;
    scanf("%d %lld", &N, &M);
    int *trees = (int*)malloc(N * sizeof(int));
    int max_h = 0;
    for(int i =0;i<N;i++){
        scanf("%d", &trees[i]);
        if(trees[i]>max_h) max_h = trees[i];
    }
    int res = 0;
    long long left = 0, right = max_h;
    while(left <= right){
        long long mid = (left + right)/2;
        long long total =0;
        for(int i=0;i<N;i++) {
            if(trees[i] > mid){
                total += (trees[i]-mid);
                if(total >= M) break;
            }
        }
        if(total >= M){
            res = mid;
            left = mid+1;
        }
        else{
            right = mid-1;
        }
    }
    printf("%d", res);
    free(trees);
    return 0;
}