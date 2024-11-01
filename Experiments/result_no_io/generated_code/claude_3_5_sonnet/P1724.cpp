#include <stdio.h>
#include <string.h>

#define MAX_LEN 5001

void calculate_position(char *commands, long long T, long long *x, long long *y) {
    int len = strlen(commands);
    long long cycles = T / len;
    int remaining_steps = T % len;
    
    *x = 0;
    *y = 0;
    
    for (int i = 0; i < len; i++) {
        switch (commands[i]) {
            case 'E': *x += cycles; break;
            case 'W': *x -= cycles; break;
            case 'N': *y += cycles; break;
            case 'S': *y -= cycles; break;
        }
    }
    
    for (int i = 0; i < remaining_steps; i++) {
        switch (commands[i]) {
            case 'E': (*x)++; break;
            case 'W': (*x)--; break;
            case 'N': (*y)++; break;
            case 'S': (*y)--; break;
        }
    }
}

int main() {
    char commands[MAX_LEN];
    long long T;
    long long x, y;
    
    scanf("%s", commands);
    scanf("%lld", &T);
    
    calculate_position(commands, T, &x, &y);
    
    printf("%lld %lld\n", x, y);
    
    return 0;
}