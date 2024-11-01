#include <stdio.h>

int main(){
    int s1, s2, s3;
    scanf("%d %d %d", &s1, &s2, &s3);
    
    int counts[81] = {0}; // sums can range from 3 to 80
    for(int i=1;i<=s1;i++){
        for(int j=1;j<=s2;j++){
            for(int k=1;k<=s3;k++){
                int sum = i + j + k;
                counts[sum]++;
            }
        }
    }
    
    int max_count = -1;
    int result_sum = 0;
    int max_possible_sum = s1 + s2 + s3;
    for(int sum=3; sum<=max_possible_sum; sum++){
        if(counts[sum] > max_count){
            max_count = counts[sum];
            result_sum = sum;
        }
        else if(counts[sum] == max_count && sum < result_sum){
            result_sum = sum;
        }
    }
    
    printf("%d\n", result_sum);
    return 0;
}