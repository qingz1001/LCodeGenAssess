#include <stdio.h>

char* check_dogs(int a, int b, int c, int d, int time) {
    int dog1 = time % (a + b) < a;
    int dog2 = time % (c + d) < c;
    int angry_count = dog1 + dog2;
    
    if (angry_count == 0) return "none";
    if (angry_count == 1) return "one";
    return "both";
}

int main() {
    int a, b, c, d, p, m, g;
    
    scanf("%d %d %d %d", &a, &b, &c, &d);
    scanf("%d %d %d", &p, &m, &g);
    
    printf("%s\n", check_dogs(a, b, c, d, p));
    printf("%s\n", check_dogs(a, b, c, d, m));
    printf("%s\n", check_dogs(a, b, c, d, g));
    
    return 0;
}