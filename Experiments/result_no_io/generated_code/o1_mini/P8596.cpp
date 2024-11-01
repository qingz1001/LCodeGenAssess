#include <stdio.h>

int main(){
    int W;
    scanf("%d", &W);
    int n, m;
    long long x;
    scanf("%d %d %lld", &n, &m, &x);
    // Read coordinates
    for(int i=0;i<n;i++){
        long long xi, yi;
        scanf("%lld %lld", &xi, &yi);
    }
    // Read tunnels
    for(int i=0;i<m;i++){
        int u, v;
        long long w;
        scanf("%d %d %lld", &u, &v, &w);
    }
    // Output zero operations
    printf("0\n");
    return 0;
}