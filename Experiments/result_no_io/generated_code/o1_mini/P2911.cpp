#include <stdio.h>

int main(){
    int s1, s2, s3;
    scanf("%d %d %d", &s1, &s2, &s3);
    
    int freq[81] = {0};
    
    for(int i=1;i<=s1;i++){
        for(int j=1;j<=s2;j++){
            for(int k=1;k<=s3;k++){
                int sum = i + j + k;
                freq[sum]++;
            }
        }
    }
    
    int max_freq = 0;
    int result = 0;
    for(int sum=3; sum<=s1+s2+s3; sum++){
        if(freq[sum] > max_freq){
            max_freq = freq[sum];
            result = sum;
        }
    }
    
    printf("%d\n", result);
    return 0;
}