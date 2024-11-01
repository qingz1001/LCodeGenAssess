#include <stdio.h>

int main() {
    int N;
    scanf("%d", &N);

    int level = 1, count = 1;
    while (count + level * 2 <= N) {
        count += level * 2;
        level++;
    }

    int offset = N - count;
    if (level % 2 == 0) {
        printf("%d/%d\n", offset + 1, level - offset);
    } else {
        printf("%d/%d\n", level - offset, offset + 1);
    }

    return 0;
}