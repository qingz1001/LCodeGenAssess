#include <stdio.h>
#include <stdlib.h>

int main(){
    int n;
    scanf("%d", &n);
    int *s = (int*)malloc(sizeof(int)*n);
    for(int i=0;i<n;i++) scanf("%d", &s[i]);
    int i=0, j=1, k=0;
    while(i < n && j < n && k < n){
        int a = s[(i+k)%n];
        int b = s[(j+k)%n];
        if(a < b){
            j = j + k +1;
            k =0;
        }
        else if(a > b){
            i = i + k +1;
            k =0;
        }
        else{
            k++;
        }
        if(i == j){
            j++;
        }
    }
    int start = i < j ? i : j;
    for(int m=0;m<n;m++){
        if(m>0) printf(" ");
        printf("%d", s[(start +m)%n]);
    }
    printf("\n");
    free(s);
    return 0;
}