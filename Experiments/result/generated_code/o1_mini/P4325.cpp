#include <stdio.h>

int main(){
    int num, rem;
    int present[42] = {0};
    for(int i = 0; i < 10; i++){
        scanf("%d", &num);
        rem = num % 42;
        present[rem] = 1;
    }
    int count = 0;
    for(int i = 0; i < 42; i++) {
        if(present[i]) count++;
    }
    printf("%d\n", count);
    return 0;
}