#include <stdio.h>
#include <stdbool.h>

int main(){
    int N;
    scanf("%d", &N);
    
    bool sieve[10001];
    for(int i=0;i<=10000;i++) sieve[i]=true;
    sieve[0]=sieve[1]=false;
    for(int i=2;i*i<=10000;i++){
        if(sieve[i]){
            for(int j=i*i;j<=10000;j+=i){
                sieve[j]=false;
            }
        }
    }
    
    for(int num=4; num<=N; num+=2){
        for(int p1=2; p1<=num/2; p1++){
            if(sieve[p1] && sieve[num - p1]){
                printf("%d=%d+%d\n", num, p1, num - p1);
                break;
            }
        }
    }
    
    return 0;
}