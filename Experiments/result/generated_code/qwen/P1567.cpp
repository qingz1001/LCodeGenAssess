#include <stdio.h>

int main() {
    int N;
    scanf("%d", &N);
    int temperatures[N];
    for (int i = 0; i < N; i++) {
        scanf("%d", &temperatures[i]);
    }

    int max_length = 0;
    int current_length = 1;

    for (int i = 1; i < N; i++) {
        if (temperatures[i] > temperatures[i - 1]) {
            current_length++;
        } else {
            if (current_length > max_length) {
                max_length = current_length;
            }
            current_length = 1;
        }
    }

    if (current_length > max_length) {
        max_length = current_length;
    }

    printf("%d\n", max_length);

    return 0;
}