#include <stdio.h>

typedef unsigned long long ull;

int main(){
    int T;
    scanf("%d", &T);
    while(T--){
        ull a, c;
        scanf("%llu %llu", &a, &c);
        if(a < c){
            printf("-1\n");
            continue;
        }
        ull n = a / c;
        if(n == 0){
            printf("-1\n");
            continue;
        }
        ull b = a / n;
        // To compute ceil(b / (c +1)) = (b + c) / (c +1)
        ull m_min = (c +1) == 0 ? 0 : (b + c) / (c +1);
        ull m_max = (c ==0) ? 0 : b / c;
        if(m_min <= m_max && m_max >=1){
            printf("%llu\n", b);
        }
        else{
            printf("-1\n");
        }
    }
    return 0;
}