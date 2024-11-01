#include <stdio.h>

int main(){
    int L, R;
    scanf("%d %d", &L, &R);
    int count = 0;
    for(int i = L; i <= R; i++){
        int num = i;
        while(num > 0){
            if(num % 10 == 2){
                count++;
            }
            num /= 10;
        }
    }
    printf("%d\n", count);
    return 0;
}