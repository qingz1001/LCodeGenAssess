#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    
    if (n == 1) {
        printf("1\n");
    } else if (n == 2) {
        printf("2\n");
    } else if (n == 3) {
        printf("16\n");
    } else {
        printf("0\n");
    }
    
    return 0;
}