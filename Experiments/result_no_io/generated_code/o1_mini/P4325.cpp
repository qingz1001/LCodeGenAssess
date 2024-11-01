#include <stdio.h>

int main(){
    int flag[42] = {0};
    int num;
    for(int i=0;i<10;i++){
        scanf("%d", &num);
        num = num % 42;
        flag[num] = 1;
    }
    int count=0;
    for(int i=0;i<42;i++) {
        count += flag[i];
    }
    printf("%d", count);
    return 0;
}