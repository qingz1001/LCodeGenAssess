#include <stdio.h>

int main() {
    int N;
    scanf("%d", &N);
    int temperatures[N];
    for (int i = 0; i < N; i++) {
        scanf("%d", &temperatures[i]);
    }

    int max_streak = 0;
    int current_streak = 1;

    for (int i = 1; i < N; i++) {
        if (temperatures[i] > temperatures[i - 1]) {
            current_streak++;
        } else {
            if (current_streak > max_streak) {
                max_streak = current_streak;
            }
            current_streak = 1;
        }
    }

    if (current_streak > max_streak) {
        max_streak = current_streak;
    }

    printf("%d\n", max_streak);

    return 0;
}