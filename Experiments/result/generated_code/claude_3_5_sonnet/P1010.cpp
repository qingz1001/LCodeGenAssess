#include <stdio.h>
#include <string.h>

void convert(int n) {
    if (n == 0) {
        printf("2(0)");
        return;
    }
    if (n == 1) {
        printf("2");
        return;
    }
    if (n == 2) {
        printf("2(2)");
        return;
    }
    
    int first = 1;
    for (int i = 14; i >= 0; i--) {
        if (n & (1 << i)) {
            if (!first) {
                printf("+");
            }
            first = 0;
            
            if (i == 1) {
                printf("2");
            } else {
                printf("2(");
                convert(i);
                printf(")");
            }
        }
    }
}

int main() {
    int n;
    scanf("%d", &n);
    convert(n);
    return 0;
}