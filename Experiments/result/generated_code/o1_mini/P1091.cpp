#include <stdio.h>
#include <stdlib.h>

int max(int a, int b) {
    return a > b ? a : b;
}

int main(){
    int n;
    scanf("%d", &n);
    int t[n];
    for(int i=0;i<n;i++) scanf("%d", &t[i]);
    
    int inc[n];
    for(int i=0;i<n;i++){
        inc[i]=1;
        for(int j=0;j<i;j++) {
            if(t[j] < t[i]){
                if(inc[j]+1 > inc[i]){
                    inc[i]=inc[j]+1;
                }
            }
        }
    }
    
    int dec[n];
    for(int i=n-1;i>=0;i--){
        dec[i]=1;
        for(int j=i+1;j<n;j++) {
            if(t[j] < t[i]){
                if(dec[j]+1 > dec[i]){
                    dec[i]=dec[j]+1;
                }
            }
        }
    }
    
    int max_bitonic=0;
    for(int i=0;i<n;i++) {
        if(inc[i] + dec[i] -1 > max_bitonic){
            max_bitonic = inc[i] + dec[i] -1;
        }
    }
    printf("%d", n - max_bitonic);
    return 0;
}