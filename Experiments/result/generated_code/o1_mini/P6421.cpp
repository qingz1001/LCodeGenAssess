#include <stdio.h>

int main(){
    int n, k;
    scanf("%d %d", &n, &k);
    int deleted[1001] = {0};
    int count = 0;
    for(int p=2; p<=n; p++){
        if(!deleted[p]){
            for(int multiple = p; multiple <=n; multiple +=p){
                if(!deleted[multiple]){
                    deleted[multiple] = 1;
                    count++;
                    if(count ==k){
                        printf("%d", multiple);
                        return 0;
                    }
                }
            }
        }
    }
    return 0;
}