#include <stdio.h>

int main() {
    int N;
    scanf("%d", &N);
    
    int current_streak = 1;
    int max_streak = 1;
    
    for (int i = 1; i < N; i++) {
        int temp;
        scanf("%d", &temp);
        
        if (temp > 0) {
            current_streak++;
        } else {
            if (current_streak > max_streak) {
                max_streak = current_streak;
            }
            current_streak = 0;
        }
    }
    
    if (current_streak > max_streak) {
        max_streak = current_streak;
    }
    
    printf("%d\n", max_streak);
    
    return 0;
}