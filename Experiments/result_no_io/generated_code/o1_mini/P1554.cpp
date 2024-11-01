#include <stdio.h>

int main(){
    long long M, N;
    scanf("%lld %lld", &M, &N);
    long long counts[10] = {0};
    for(long long num = M; num <= N; num++){
        long long tmp = num;
        while(tmp > 0){
            long long digit = tmp % 10;
            counts[digit]++;
            tmp /=10;
        }
    }
    for(int i=0; i<10; i++){
        if(i>0) printf(" ");
        printf("%lld", counts[i]);
    }
    printf("\n");
    return 0;
}