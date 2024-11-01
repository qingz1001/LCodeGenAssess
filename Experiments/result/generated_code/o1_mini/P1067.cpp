#include <stdio.h>
#include <stdlib.h>

int main(){
    int n;
    scanf("%d", &n);
    int *a = (int*)malloc((n+1)*sizeof(int));
    for(int i=0;i<=n;i++) scanf("%d", &a[i]);
    int first = 1;
    for(int i=0;i<=n;i++){
        if(a[i]==0) continue;
        int degree = n - i;
        if(first){
            if(a[i]<0) printf("-");
        }
        else{
            if(a[i]>0) printf("+");
            else printf("-");
        }
        if(first){
            if(a[i]<0) {
                if(degree==0){
                    printf("%d", -a[i]);
                }
            }
        }
        if(!(first && a[i]==-1 && degree !=0)){
            if(degree !=0){
                if(abs(a[i]) !=1){
                    printf("%d", abs(a[i]));
                }
            }
            else{
                printf("%d", abs(a[i]));
            }
        }
        if(degree >1){
            printf("x^%d", degree);
        }
        else if(degree ==1){
            printf("x");
        }
        first = 0;
    }
    free(a);
    return 0;
}