#include <stdio.h>
#include <stdint.h>

int main(){
    // Precompute Fibonacci numbers
    uint64_t fib[94];
    fib[1] = 1;
    fib[2] = 2;
    for(int i=3;i<=93;i++) fib[i] = fib[i-1] + fib[i-2];
    
    int m;
    scanf("%d", &m);
    while(m--){
        uint64_t a, b;
        scanf("%llu %llu", &a, &b);
        if(a == b){
            printf("%llu\n", a);
        }
        else{
            uint64_t larger = a > b ? a : b;
            uint64_t smaller = a > b ? b : a;
            // Binary search to find index of larger
            int n=1, m_idx=93;
            while(n <= m_idx){
                int mid = (n + m_idx) / 2;
                if(fib[mid] == larger){
                    n = mid;
                    break;
                }
                else if(fib[mid] < larger){
                    n = mid +1;
                }
                else{
                    m_idx = mid -1;
                }
            }
            // LCA is fib[n-2] if n >2, else 1
            if(n >2){
                printf("%llu\n", fib[n-2]);
            }
            else{
                printf("1\n");
            }
        }
    }
}