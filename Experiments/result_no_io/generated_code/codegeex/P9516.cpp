#include <stdio.h>

int main() {
    int a, b, c, d, e;
    scanf("%d%d%d%d%d", &a, &b, &c, &d, &e);
    
    int score = a + b + c + d + e;
    
    if (score >= 450) {
        printf("Red\n");
    } else if (score >= 400) {
        printf("Orange\n");
    } else if (score >= 350) {
        printf("Green\n");
    } else if (score >= 250) {
        printf("Blue\n");
    } else {
        printf("Gray\n");
    }
    
    return 0;
}