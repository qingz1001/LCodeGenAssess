#include <stdio.h>

int main() {
    int N;
    scanf("%d", &N);
    
    int temperatures[N];
    for (int i = 0; i < N; i++) {
        scanf("%d", &temperatures[i]);
    }
    
    int max_days = 1;
    int current_days = 1;
    
    for (int i = 1; i < N; i++) {
        if (temperatures[i] > temperatures[i - 1]) {
            current_days++;
            if (current_days > max_days) {
                max_days = current_days;
            }
        } else {
            current_days = 1;
        }
    }
    
    printf("%d\n", max_days);
    
    return 0;
}