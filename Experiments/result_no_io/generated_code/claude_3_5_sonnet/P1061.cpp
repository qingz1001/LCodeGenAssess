#include <stdio.h>
#include <string.h>

#define MAX_W 26

char jam[MAX_W + 1];
int s, t, w;

int next_jam() {
    int i = w - 1;
    while (i >= 0 && jam[i] == 'a' + t - (w - i)) {
        i--;
    }
    if (i < 0) return 0;
    
    jam[i]++;
    for (int j = i + 1; j < w; j++) {
        jam[j] = jam[j-1] + 1;
    }
    return 1;
}

int main() {
    scanf("%d %d %d", &s, &t, &w);
    scanf("%s", jam);
    
    for (int i = 0; i < 5; i++) {
        if (next_jam()) {
            printf("%s\n", jam);
        } else {
            break;
        }
    }
    
    return 0;
}