#include <stdio.h>
#include <string.h>

int main() {
    int s, t, w;
    scanf("%d%d%d", &s, &t, &w);
    char jam[w];
    scanf("%s", jam);

    int count = 0;
    while (count < 5) {
        int i;
        for (i = w - 1; i >= 0; i--) {
            if (jam[i] < t) {
                jam[i]++;
                for (int j = i + 1; j < w; j++) {
                    jam[j] = jam[i] + (j - i);
                }
                printf("%s\n", jam);
                count++;
                break;
            }
        }
        if (i == -1) break;
    }

    return 0;
}