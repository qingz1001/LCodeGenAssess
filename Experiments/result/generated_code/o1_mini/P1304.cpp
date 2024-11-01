#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX 10000

int main(){
    int N;
    scanf("%d", &N);
    bool isPrime[MAX+1];
    memset(isPrime, true, sizeof(isPrime));
    isPrime[0] = isPrime[1] = false;
    for(int i=2;i*i<=N;i++){
        if(isPrime[i]){
            for(int j=i*i;j<=N;j+=i){
                isPrime[j] = false;
            }
        }
    }
    for(int num=4; num<=N; num+=2){
        for(int p=2; p<=num/2; p++){
            if(isPrime[p] && isPrime[num - p]){
                printf("%d=%d+%d\n", num, p, num - p);
                break;
            }
        }
    }
    return 0;
}