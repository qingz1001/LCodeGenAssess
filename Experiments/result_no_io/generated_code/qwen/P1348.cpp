#include <stdio.h>

int main() {
    int a, b;
    scanf("%d %d", &a, &b);
    
    int count = 0;
    for (int n = a; n <= b; n++) {
        if ((n & 1) == 0) {
            count++;
        }
    }
    
    printf("%d\n", count);
    return 0;
}