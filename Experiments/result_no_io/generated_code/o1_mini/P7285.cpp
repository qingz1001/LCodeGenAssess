#include <stdio.h>

int main(){
    int T;
    scanf("%d", &T);
    while(T--){
        int n;
        scanf("%d", &n);
        int arr[n];
        int total_ones = 0;
        for(int i=0;i<n;i++){
            scanf("%d", &arr[i]);
            if(arr[i]==1){
                total_ones++;
            }
        }
        // Modify the array by setting all 0's to 1's
        for(int i=0;i<n;i++){
            if(arr[i]==0){
                arr[i]=1;
            }
        }
        // Output x - y
        printf("%d\n", total_ones);
        // Output modified array
        for(int i=0;i<n;i++){
            printf("%d%c", arr[i], (i<n-1)?' ':'\n');
        }
    }
    return 0;
}