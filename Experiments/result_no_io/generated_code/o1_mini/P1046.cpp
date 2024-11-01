#include<stdio.h>

int main(){
    int apples[10];
    for(int i=0;i<10;i++) scanf("%d", &apples[i]);
    int M;
    scanf("%d", &M);
    int limit = M + 30;
    int count =0;
    for(int i=0;i<10;i++) if(apples[i] <= limit) count++;
    printf("%d\n", count);
    return 0;
}