#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(){
    long long n, m;
    scanf("%lld %lld", &n, &m);
    
    // Initialize degree array
    // To save memory, use a dynamic array and sort edges to count degrees
    // But with m up to 2e5 and n up to 1e5, it's feasible
    // Initialize degrees to 0
    long long *deg = calloc(n+1, sizeof(long long));
    if (!deg){
        return 1;
    }
    
    long long u, v;
    for(long long i=0; i<m; i++){
        scanf("%lld %lld", &u, &v);
        deg[u]++;
        deg[v]++;
    }
    
    // Compute sum of C(deg[v],2)
    long long sumC2 =0;
    for(long long i=1; i<=n; i++){
        if(deg[i] >=2){
            sumC2 += (deg[i] * (deg[i]-1))/2;
        }
    }
    
    // Compute C(n,4)
    __int128 C4 = (__int128)n * (n-1) * (n-2) * (n-3) /24;
    
    // Compute m * C(n-2,2)
    __int128 term1 = (__int128)m * (n-2) * (n-3) /2;
    
    // Compute (n-4) * sumC2
    __int128 term2 = (__int128)(n-4) * sumC2;
    
    // Compute C(m,2)
    __int128 term3 = (__int128)m * (m-1) /2;
    
    // Compute Blue - Red = C4 - (term1 - term2 - term3)
    // Which is C4 - term1 + term2 + term3
    __int128 blue_minus_red = C4 - term1 + term2 + term3;
    
    // Since blue_minus_red can be negative, take absolute value
    if(blue_minus_red <0){
        blue_minus_red = -blue_minus_red;
    }
    
    // Since __int128 is not directly printable, cast to string
    char buffer[40];
    int idx=0;
    long long temp = (long long)blue_minus_red;
    if(temp ==0){
        printf("0\n");
        free(deg);
        return 0;
    }
    while(temp >0){
        buffer[idx++] = '0' + (temp %10);
        temp /=10;
    }
    for(int i=idx-1;i>=0;i--){
        putchar(buffer[i]);
    }
    putchar('\n');
    
    free(deg);
    return 0;
}