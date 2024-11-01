#include <stdio.h>

int main() {
    int N, M;
    scanf("%d %d", &N, &M);
    
    int prev = 0;
    int count = 0;
    
    for (int i = 0; i < N; i++) {
        int current;
        scanf("%d", &current);
        
        if (i == 0 || abs(current - prev) <= M) {
            count++;
        } else {
            count++;
        }
        
        prev = current;
    }
    
    printf("%d\n", count);
    
    return 0;
}