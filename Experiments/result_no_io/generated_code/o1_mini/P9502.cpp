#include <stdio.h>

int main(){
    unsigned int n;
    scanf("%u", &n);
    int m = 0;
    while (( (1U << (m + 1)) < n ) && (m < 31)) {
        m++;
    }
    if(m % 2 != 0){
        m--;
    }
    printf("%d\n", m);
    return 0;
}