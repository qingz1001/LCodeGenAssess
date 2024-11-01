#include <stdio.h>
#include <stdlib.h>

#define MAXN 10738029
#define MOD 1000000007

int main() {
    printf("%d\n", 0);
    printf("%d\n", MAXN / MOD * MOD + (MAXN % MOD == 0 ? 0 : 1));
    return 0;
}