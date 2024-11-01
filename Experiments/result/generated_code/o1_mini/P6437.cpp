#include <stdio.h>

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    int a[n];
    for(int i=0;i<n;i++) scanf("%d", &a[i]);
    int max_sum = 0;
    for(int i=0;i<n-2;i++){
        for(int j=i+1;j<n-1;j++){
            for(int k=j+1;k<n;k++){
                int s = a[i] + a[j] + a[k];
                if(s <= m && s > max_sum){
                    max_sum = s;
                }
            }
        }
    }
    printf("%d\n", max_sum);
    return 0;
}