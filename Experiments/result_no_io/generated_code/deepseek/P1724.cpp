#include <stdio.h>
#include <string.h>

int main() {
    char S[5001];
    int T;
    scanf("%s", S);
    scanf("%d", &T);

    int len = strlen(S);
    int x = 0, y = 0;

    // Calculate the position after one full cycle of the command string
    for (int i = 0; i < len; i++) {
        switch (S[i]) {
            case 'E': x++; break;
            case 'S': y--; break;
            case 'W': x--; break;
            case 'N': y++; break;
        }
    }

    // Calculate the number of full cycles and the remaining seconds
    int full_cycles = T / len;
    int remaining_seconds = T % len;

    // Update the position based on full cycles
    x *= full_cycles;
    y *= full_cycles;

    // Update the position based on the remaining seconds
    for (int i = 0; i < remaining_seconds; i++) {
        switch (S[i]) {
            case 'E': x++; break;
            case 'S': y--; break;
            case 'W': x--; break;
            case 'N': y++; break;
        }
    }

    printf("%d %d\n", x, y);

    return 0;
}