#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    
    long long X = 0;
    for (int i = 0; i < n; i++) {
        int qi;
        scanf("%d", &qi);
        int num = qi / 10;
        int p = qi % 10;
        X += (long long)num * num * p * p * p;
    }
    
    printf("%lld\n", X);
    
    return 0;
}