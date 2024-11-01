#include<stdio.h>
#include<string.h>
int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        int n;
        scanf("%d",&n);
        int freq[n+1];
        memset(freq, 0, sizeof(freq));
        for(int i=0;i<n;i++){
            int x;
            scanf("%d",&x);
            if(x<=n) freq[x]++;
        }
        int m=0;
        for(int i=1;i<=n;i++) if(freq[i]==1) m++;
        int ans=(m+1)/2;
        printf("%d\n",ans);
    }
}