#include <stdio.h>

int main(){
    int n;
    scanf("%d", &n);
    int v[n+1];
    for(int i=1;i<=n;i++) scanf("%d", &v[i]);
    int max_sum = 0;
    for(int s=1;s<=n;s++){
        int left = (s ==1) ? n : s-1;
        int right = (s ==n) ?1 : s+1;
        int current_sum = v[s] > v[left] ? v[s] + v[s] : v[s] + v[right];
        if(v[left] > v[right]){
            current_sum = v[s] + v[left];
        }
        else{
            current_sum = v[s] + v[right];
        }
        if(current_sum > max_sum) max_sum = current_sum;
    }
    printf("%d\n", max_sum);
    return 0;
}