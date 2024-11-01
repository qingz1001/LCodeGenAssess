#include <stdio.h>
#include <limits.h>

int main(){
    int n;
    scanf("%d", &n);
    int matrix[120][120];
    for(int i=0;i<n;i++) {
        for(int j=0;j<n;j++) {
            scanf("%d", &matrix[i][j]);
        }
    }
    int global_max = INT_MIN;
    int temp[120];
    for(int start=0; start<n; start++){
        for(int i=0;i<n;i++) temp[i]=0;
        for(int end=start; end<n; end++){
            for(int col=0; col<n; col++) {
                temp[col] += matrix[end][col];
            }
            // Kadane's algorithm
            int current_max = temp[0];
            int max_current = temp[0];
            for(int k=1; k<n; k++){
                if(max_current + temp[k] > temp[k]){
                    max_current += temp[k];
                }
                else{
                    max_current = temp[k];
                }
                if(max_current > current_max){
                    current_max = max_current;
                }
            }
            if(current_max > global_max){
                global_max = current_max;
            }
        }
    }
    printf("%d\n", global_max);
    return 0;
}