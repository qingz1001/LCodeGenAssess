#include <stdio.h>

int main(){
    int T;
    if(scanf("%d", &T)!=1) return 0;
    while(T--){
        long long n, m, p;
        if(scanf("%lld %lld %lld", &n, &m, &p)!=3) return 0;
        if(m < p){
            printf("Alice\n");
        }
        else if(n < p){
            printf("Bob\n");
        }
        else{
            printf("Lasting Battle\n");
        }
    }
    return 0;
}