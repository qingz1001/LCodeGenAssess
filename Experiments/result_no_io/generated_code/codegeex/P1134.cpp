#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    
    int count = 0;
    for (int i = 2; i <= n; i++) {
        int j = i;
        while (j % 10 == 0) {
            j /= 10;
            count++;
        }
    }
    
    int result = 1;
    for (int i = 2; i <= n; i++) {
        int j = i;
        while (j % 10 == 0) {
            j /= 10;
        }
        result *= j % 10;
        while (result >= 10) {
            result /= 10;
        }
    }
    
    printf("%d\n", result);
    return 0;
}