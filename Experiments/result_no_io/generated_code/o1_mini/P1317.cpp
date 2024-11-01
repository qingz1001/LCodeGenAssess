#include <stdio.h>

int main(){
    int n;
    scanf("%d", &n);
    int height[n];
    for(int i=0;i<n;i++) scanf("%d", &height[i]);
    
    int left_max[n];
    left_max[0] = height[0];
    for(int i=1;i<n;i++) {
        if(height[i] > left_max[i-1]) left_max[i] = height[i];
        else left_max[i] = left_max[i-1];
    }
    
    int right_max[n];
    right_max[n-1] = height[n-1];
    for(int i=n-2;i>=0;i--){
        if(height[i] > right_max[i+1]) right_max[i] = height[i];
        else right_max[i] = right_max[i+1];
    }
    
    int count=0;
    int in_basin=0;
    for(int i=0;i<n;i++){
        int water = left_max[i] < right_max[i] ? left_max[i] : right_max[i];
        water -= height[i];
        if(water > 0){
            if(!in_basin){
                count++;
                in_basin=1;
            }
        }
        else{
            in_basin=0;
        }
    }
    printf("%d", count);
    return 0;
}