#include <stdio.h>

int main() {
    int N, X;
    scanf("%d %d", &N, &X);
    
    int total_value = 0;
    
    for (int i = 0; i < N; i++) {
        int p1, p2, p3;
        if (scanf("%d %d", &p1, &p2) == 2) {
            total_value += (p1 - p2 <= X) ? ((p1 > p2) ? p1 : p2) : p3;
        } else if (scanf("%d %d\n%d", &p1, &p2, &p3) == 3) {
            total_value += (p1 - p2 <= X) ? ((p1 > p2) ? p1 : p2) : p3;
        }
    }
    
    printf("%d\n", total_value);
    
    return 0;
}