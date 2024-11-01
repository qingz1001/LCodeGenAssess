#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    long long a[n];
    for (int i = 0; i < n; ++i) {
        scanf("%lld", &a[i]);
    }
    
    long long operations = 0;
    for (int i = 0; i < n; ++i) {
        if (i == 0 || a[i] > a[i - 1]) {
            operations += a[i];
        } else {
            operations += a[i] - a[i - 1];
        }
    }
    
    printf("%lld\n", operations);
    return 0;
}