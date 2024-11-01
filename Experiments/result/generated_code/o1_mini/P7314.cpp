#include <stdio.h>
#include <stdlib.h>

int main(){
    int N;
    scanf("%d", &N);
    if(N < 2){
        // As per problem constraints, N >=2
        return 0;
    }
    long long a_prev, a_curr;
    scanf("%lld", &a_prev);
    long long min_diff = 2000000000; // Initialize to a large value
    for(int i=1;i<N;i++){
        scanf("%lld", &a_curr);
        long long diff = a_curr - a_prev;
        if(diff < 0) diff = -diff;
        if(diff ==0){
            min_diff = 0;
            break;
        }
        if(diff < min_diff){
            min_diff = diff;
        }
        a_prev = a_curr;
    }
    printf("%lld", min_diff);
    return 0;
}