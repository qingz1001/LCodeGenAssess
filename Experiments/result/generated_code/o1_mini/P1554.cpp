#include <stdio.h>

int main(){
    long long M, N;
    scanf("%lld %lld", &M, &N);
    int count[10] = {0};
    for(long long i = M; i <= N; i++){
        long long num = i;
        if(num ==0){
            count[0]++;
        }
        else{
            while(num >0){
                int d = num %10;
                count[d]++;
                num /=10;
            }
        }
    }
    for(int i=0;i<10;i++){
        if(i>0) printf(" ");
        printf("%d", count[i]);
    }
    printf("\n");
    return 0;
}