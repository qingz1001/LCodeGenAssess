#include <stdio.h>
#include <string.h>

#define MOD 100000000

struct pair {
    long long a;
    long long b;
};

struct pair fib_fast_doubling(long long n) {
    if (n == 0) {
        struct pair base = {0,1};
        return base;
    }
    struct pair p = fib_fast_doubling(n >> 1);
    long long c = (p.a * ((2*p.b)%MOD - p.a + MOD))%MOD;
    long long d = (p.a * p.a + p.b * p.b)%MOD;
    if (n & 1)
        return (struct pair){d, (c + d)%MOD};
    else
        return (struct pair){c, d};
}

int main(){
    char s[1001];
    scanf("%s", s);
    long long m = 150000000;
    long long nm = 0;
    int len = strlen(s);
    for(int i=0;i<len;i++){
        nm = (nm * 10 + (s[i]-'0')) % m;
    }
    long long k = (nm +1) % m;
    struct pair res = fib_fast_doubling(k);
    printf("%lld\n", res.a);
    return 0;
}