#include <stdio.h>
#include <string.h>

int main() {
    int n;
    scanf("%d", &n);
    
    char x[101], y[101], z[101];
    scanf("%s", x);
    scanf("%s", y);
    
    for (int i = 0; i < n; i++) {
        if (x[i] >= y[i]) {
            z[i] = y[i];
        } else {
            printf("-1\n");
            return 0;
        }
    }
    
    z[n] = '\0';
    printf("%s\n", z);
    
    return 0;
}