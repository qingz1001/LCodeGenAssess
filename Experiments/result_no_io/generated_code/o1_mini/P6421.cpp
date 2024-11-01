#include <stdio.h>
#include <stdbool.h>

int main(){
    int n, k;
    scanf("%d %d", &n, &k);
    bool is_deleted[n+1];
    for(int i=0;i<=n;i++) is_deleted[i]=false;
    int count =0;
    for(int p=2;p<=n;p++){
        if(!is_deleted[p]){
            for(int multiple = p; multiple<=n; multiple+=p){
                if(!is_deleted[multiple]){
                    is_deleted[multiple]=true;
                    count++;
                    if(count == k){
                        printf("%d", multiple);
                        return 0;
                    }
                }
            }
        }
    }
    return 0;
}