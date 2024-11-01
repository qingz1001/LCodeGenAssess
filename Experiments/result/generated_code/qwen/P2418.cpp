#include <stdio.h>

int main() {
    int N, M;
    scanf("%d %d", &N, &M);
    
    int last = 0, count = 0;
    for (int i = 0; i < N; i++) {
        int current;
        scanf("%d", &current);
        
        if (last == 0) {
            last = current;
            count++;
        } else {
            if (abs(current - last) <= M) {
                last = current;
            } else {
                last = current;
                count++;
            }
        }
    }
    
    printf("%d\n", count);
    return 0;
}