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
    int max_sum = INT_MIN;
    for(int start=0; start<n; start++){
        int temp[120] = {0};
        for(int end=start; end<n; end++){
            for(int col=0; col<n; col++){
                temp[col] += matrix[end][col];
            }
            // Kadane's algorithm
            int current_sum = temp[0];
            int local_max = temp[0];
            for(int k=1; k<n; k++){
                if(current_sum < 0){
                    current_sum = temp[k];
                }
                else{
                    current_sum += temp[k];
                }
                if(current_sum > local_max){
                    local_max = current_sum;
                }
            }
            if(local_max > max_sum){
                max_sum = local_max;
            }
        }
    }
    printf("%d\n", max_sum);
    return 0;
}