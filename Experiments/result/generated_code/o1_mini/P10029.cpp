#include <stdio.h>

int main(){
    int T;
    scanf("%d", &T);
    while(T--){
        long long n, m, p;
        scanf("%lld %lld %lld", &n, &m, &p);
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