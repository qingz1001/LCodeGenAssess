#include <stdio.h>

int main(){
    int n, T;
    scanf("%d %d", &n, &T);
    int vi, ti;
    long long height, max_height = -1;
    int ans = 1;
    for(int i=1;i<=n;i++){
        scanf("%d %d", &vi, &ti);
        if(T >= ti){
            height = (long long)vi * (T - ti);
        }
        else{
            height = 0;
        }
        if(height > max_height){
            max_height = height;
            ans = i;
        }
    }
    printf("%d\n", ans);
    return 0;
}