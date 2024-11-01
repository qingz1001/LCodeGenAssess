#include <stdio.h>

int main(){
    int n;
    scanf("%d", &n);
    if(n <1 || n >10){
        return 0;
    }
    int total = 2*n -1;
    for(int i=1;i<=total;i++){
        int stars, spaces;
        if(i <=n){
            stars = 2*i -1;
            spaces = n -i;
        }
        else{
            stars = 2*(total -i +1) -1;
            spaces = i -n;
        }
        for(int s=0;s<spaces;s++) printf(" ");
        for(int s=0;s<stars;s++) printf("*");
        printf("\n");
    }
    return 0;
}