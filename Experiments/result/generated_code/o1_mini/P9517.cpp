#include <stdio.h>

int main(){
    int n;
    scanf("%d", &n);
    int a;
    int first = -1, last = -1;
    for(int i=1;i<=n;i++){
        scanf("%d", &a);
        if(a == 1){
            if(first == -1){
                first = i;
            }
            last = i;
        }
    }
    if(first == -1){
        printf("0\n");
    }
    else{
        printf("%d\n", last - first +1);
    }
    return 0;
}