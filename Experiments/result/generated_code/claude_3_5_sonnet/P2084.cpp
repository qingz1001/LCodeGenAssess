#include <stdio.h>
#include <string.h>
#include <math.h>

int main() {
    int M;
    char N[1001];
    scanf("%d %s", &M, N);
    
    int len = strlen(N);
    int first = 1;
    
    for (int i = 0; i < len; i++) {
        int digit = N[i] - '0';
        if (digit != 0) {
            if (!first) {
                printf("+");
            }
            first = 0;
            
            if (digit != 1 || len - i - 1 == 0) {
                printf("%d", digit);
                if (len - i - 1 > 0) {
                    printf("*");
                }
            }
            
            if (len - i - 1 > 0) {
                printf("%d^%d", M, len - i - 1);
            }
        }
    }
    
    printf("\n");
    return 0;
}