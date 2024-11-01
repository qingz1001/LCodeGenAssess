#include <stdio.h>
#include <stdlib.h>

int main(){
    int a, b;
    scanf("%d %d", &a, &b);
    int abs_a = abs(a);
    int abs_b = abs(b);
    int abs_diff = abs(a - b);
    int total1 = abs_a + abs_diff;
    int total2 = abs_b + abs_diff;
    int min_steps = total1 < total2 ? total1 : total2;
    printf("%d\n", min_steps);
    return 0;
}