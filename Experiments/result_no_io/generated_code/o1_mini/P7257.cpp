#include <stdio.h>

int reverse_number(int num) {
    return (num % 10) * 100 + ((num / 10) % 10) * 10 + (num / 100);
}

int main(){
    int a, b;
    scanf("%d %d", &a, &b);
    int ra = reverse_number(a);
    int rb = reverse_number(b);
    if(ra > rb){
        printf("%d", ra);
    }
    else{
        printf("%d", rb);
    }
    return 0;
}