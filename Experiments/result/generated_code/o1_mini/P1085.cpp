#include<stdio.h>

int main(){
    int a, b;
    int max_extra = 0;
    int unhappy_day = 0;
    for(int i=1;i<=7;i++){
        if(scanf("%d %d", &a, &b)!=2){
            return 0;
        }
        int sum = a + b;
        if(sum >8){
            int extra = sum -8;
            if(extra > max_extra){
                max_extra = extra;
                unhappy_day = i;
            }
        }
    }
    printf("%d", unhappy_day);
    return 0;
}