#include <stdio.h>

int main() {
    int a, b, c, d;
    scanf("%d %d %d %d", &a, &b, &c, &d);
    
    int ops[3] = {1, -1, 0}; // 1 represents addition, -1 subtraction, 0 multiplication
    int result;
    int found = 0;
    
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (ops[i] == 0) {
                result = a * b;
            } else {
                result = a + ops[i] * b;
            }
            
            if (ops[j] == 0) {
                result *= c;
            } else {
                result += ops[j] * c;
            }
            
            if (result == d) {
                found = 1;
                break;
            }
        }
        if (found) break;
    }
    
    if (found) {
        printf("Yes\n");
    } else {
        printf("No\n");
    }
    
    return 0;
}