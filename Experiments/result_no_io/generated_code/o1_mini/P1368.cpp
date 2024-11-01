#include <stdio.h>
#include <stdlib.h>

int least_rotation(int a[], int n) {
    int i = 0, j = 1, k = 0;
    while(i < n && j < n && k < n){
        int aik = a[(i + k) % n];
        int ajk = a[(j + k) % n];
        if(aik == ajk){
            k++;
        }
        else{
            if(aik > ajk){
                i = i + k + 1;
            }
            else{
                j = j + k + 1;
            }
            if(i == j){
                i++;
            }
            k = 0;
        }
    }
    if(i < j){
        return i;
    }
    else{
        return j;
    }
}

int main(){
    int n;
    scanf("%d", &n);
    int *a = (int*)malloc(sizeof(int)*n);
    for(int i=0;i<n;i++) scanf("%d", &a[i]);
    int start = least_rotation(a, n);
    for(int i=0;i<n;i++){
        printf("%d", a[(start + i)%n]);
        if(i != n-1) printf(" ");
    }
    printf("\n");
    free(a);
    return 0;
}