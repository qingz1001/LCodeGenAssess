#include <stdio.h>

int main(){
    int n;
    scanf("%d", &n);
    int t[n];
    for(int i=0;i<n;i++) scanf("%d", &t[i]);
    
    int inc[n];
    for(int i=0;i<n;i++){
        inc[i] = 1;
        for(int j=0;j<i;j++) {
            if(t[j] < t[i] && inc[j] +1 > inc[i]){
                inc[i] = inc[j] +1;
            }
        }
    }
    
    int dec[n];
    for(int i=n-1;i>=0;i--){
        dec[i] =1;
        for(int j=i+1;j<n;j++) {
            if(t[j] < t[i] && dec[j] +1 > dec[i]){
                dec[i] = dec[j] +1;
            }
        }
    }
    
    int maxk =0;
    for(int i=0;i<n;i++) {
        if(inc[i] + dec[i] -1 > maxk){
            maxk = inc[i] + dec[i] -1;
        }
    }
    
    printf("%d\n", n - maxk);
    return 0;
}