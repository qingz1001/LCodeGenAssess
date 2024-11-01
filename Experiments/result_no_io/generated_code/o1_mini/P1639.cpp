#include <stdio.h>
#include <stdlib.h>

int main(){
    int a, b, x, y;
    scanf("%d %d %d %d", &a, &b, &x, &y);
    int option1 = abs(a - b);
    int option2 = abs(a - x) + abs(y - b);
    int option3 = abs(a - y) + abs(x - b);
    int min_val = option1;
    if(option2 < min_val) min_val = option2;
    if(option3 < min_val) min_val = option3;
    printf("%d\n", min_val);
}