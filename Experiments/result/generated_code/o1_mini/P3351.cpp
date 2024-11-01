#include <stdio.h>

int main(){
    long long n, m;
    scanf("%lld %lld", &n, &m);
    // Consume the m lines of edges
    long long u, v;
    for(long long i=0;i<m;i++) scanf("%lld %lld", &u, &v);
    printf("%lld\n", m);
    return 0;
}