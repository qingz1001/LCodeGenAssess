#include <stdio.h>
#include <stdint.h>

int main(){
    int n, s;
    scanf("%d %d", &n, &s);
    
    uint64_t l;
    uint64_t T = 0;
    uint64_t max_l = 0;
    for(int i=0;i<n;i++){
        scanf("%llu", &l);
        T += l;
        if(l > max_l){
            max_l = l;
        }
    }
    
    uint64_t d;
    for(int i=0;i<s;i++){
        scanf("%llu", &d);
        if(d < max_l){
            printf("NIE\n");
        }
        else{
            uint64_t k = (T + d -1) / d;
            printf("%llu\n", k);
        }
    }
    return 0;
}