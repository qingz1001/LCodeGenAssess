#include <stdio.h>
#include <string.h>

void nextJamNumber(char *jam, int s, int t, int w) {
    int i = w - 1;
    while (i >= 0 && jam[i] == 'a' + t - (w - i)) {
        i--;
    }
    if (i < 0) {
        return; // No next Jam number
    }
    jam[i]++;
    for (int j = i + 1; j < w; j++) {
        jam[j] = jam[j - 1] + 1;
    }
}

int main() {
    int s, t, w;
    char jam[30];
    scanf("%d %d %d", &s, &t, &w);
    scanf("%s", jam);

    for (int i = 0; i < 5; i++) {
        nextJamNumber(jam, s, t, w);
        if (jam[0] < 'a' + s) {
            break;
        }
        printf("%s\n", jam);
    }

    return 0;
}