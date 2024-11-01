#include <stdio.h>

int main() {
    int a, b, c, d, e;
    scanf("%d %d %d %d %d", &a, &b, &c, &d, &e);
    
    int score = a + b + c + d + e;
    
    if (score >= 300) {
        printf("Red");
    } else if (score >= 200) {
        printf("Orange");
    } else if (score >= 100) {
        printf("Green");
    } else if (score >= 50) {
        printf("Blue");
    } else {
        printf("Gray");
    }
    
    return 0;
}