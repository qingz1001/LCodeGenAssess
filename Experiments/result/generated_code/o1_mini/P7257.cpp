#include <stdio.h>

int reverse(int num) {
    return (num % 10) * 100 + ((num / 10) % 10) * 10 + (num / 100);
}

int main(){
    int a, b;
    scanf("%d %d", &a, &b);
    int ra = reverse(a);
    int rb = reverse(b);
    if(ra > rb) printf("%d", ra);
    else printf("%d", rb);
    return 0;
}