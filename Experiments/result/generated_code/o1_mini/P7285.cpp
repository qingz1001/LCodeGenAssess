#include <stdio.h>
#include <stdlib.h>

int main(){
    int T;
    scanf("%d", &T);
    while(T--){
        int n;
        scanf("%d", &n);
        int* arr = (int*)malloc(n * sizeof(int));
        for(int i=0; i<n; i++) scanf("%d", &arr[i]);
        
        int first1 = -1, last1 = -1;
        for(int i=0; i<n; i++){
            if(arr[i]==1){
                if(first1 == -1) first1 = i;
                last1 = i;
            }
        }
        
        if(first1 == -1){
            printf("0\n");
            for(int i=0; i<n; i++) printf("%d%c", arr[i], i<n-1?' ':'\n');
        }
        else{
            int sum1 =0;
            for(int i=first1; i<=last1; i++) if(arr[i]==1) sum1++;
            printf("%d\n", sum1);
            for(int i=first1; i<=last1; i++) arr[i]=1;
            for(int i=0; i<n; i++) printf("%d%c", arr[i], i<n-1?' ':'\n');
        }
        free(arr);
    }
    return 0;
}