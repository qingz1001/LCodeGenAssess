#include <stdio.h>

int is_aggressive(int time, int aggressive, int calm) {
    int cycle = aggressive + calm;
    time %= cycle;
    return time < aggressive;
}

char* get_state(int time, int a, int b, int c, int d) {
    int dog1 = is_aggressive(time, a, b);
    int dog2 = is_aggressive(time, c, d);
    int count = dog1 + dog2;
    
    if (count == 0) return "none";
    if (count == 1) return "one";
    return "both";
}

int main() {
    int a, b, c, d;
    int p, m, g;
    
    scanf("%d %d %d %d", &a, &b, &c, &d);
    scanf("%d %d %d", &p, &m, &g);
    
    printf("%s\n", get_state(p, a, b, c, d));
    printf("%s\n", get_state(m, a, b, c, d));
    printf("%s\n", get_state(g, a, b, c, d));
    
    return 0;
}