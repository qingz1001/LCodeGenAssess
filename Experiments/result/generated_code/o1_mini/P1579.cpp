#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX 20000

int main(){
    bool sieve[MAX+1];
    memset(sieve, true, sizeof(sieve));
    sieve[0] = sieve[1] = false;
    for(int i=2;i*i<=MAX;i++){
        if(sieve[i]){
            for(int j=i*i;j<=MAX;j+=i){
                sieve[j]=false;
            }
        }
    }
    int n;
    scanf("%d", &n);
    for(int p1=2;p1<=n-4;p1++){
        if(sieve[p1]){
            for(int p2=p1;p2<=n-p1-2;p2++){
                if(sieve[p2]){
                    int p3 = n - p1 - p2;
                    if(p3 >= p2 && sieve[p3]){
                        printf("%d %d %d", p1, p2, p3);
                        return 0;
                    }
                }
            }
        }
    }
    return 0;
}