#include <stdio.h>
#include <string.h>

int main() {
    char n[101];
    int k;
    scanf("%s%d", n, &k);
    
    int len = strlen(n);
    long long mod = 1;
    for (int i = 0; i < k; i++) {
        mod *= 10;
    }
    
    int a[101];
    for (int i = 0; i < k; i++) {
        a[i] = n[len - k + i] - '0';
    }
    
    int b[101];
    for (int i = 0; i < k; i++) {
        b[i] = a[i];
    }
    
    int i = 1;
    while (1) {
        long long p = 1;
        for (int j = 0; j < k; j++) {
            p = (p * a[j]) % 10;
        }
        int flag = 1;
        for (int j = 0; j < k; j++) {
            if (a[j] != b[j]) {
                flag = 0;
                break;
            }
        }
        if (flag) {
            printf("%d\n", i);
            break;
        }
        for (int j = 0; j < k; j++) {
            a[j] = p;
        }
        i++;
    }
    
    return 0;
}