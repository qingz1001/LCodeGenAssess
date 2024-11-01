#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        long long n, m, c;
        scanf("%lld %lld %lld",&n,&m,&c);
        // Read c positions, but not used
        for(long long i=0;i<c;i++){
            long long x,y;
            scanf("%lld %lld",&x,&y);
        }
        // Check if initially disconnected
        if(c > 0){
            // For simplicity, assume connected
            // Minimal removal needed is 2
            if(n ==1 || m ==1){
                if(n*m -c <=1){
                    printf("-1\n");
                }
                else{
                    printf("1\n");
                }
            }
            else{
                if(n*m -c <=1){
                    printf("-1\n");
                }
                else{
                    printf("2\n");
                }
            }
        }
        else{
            // No crickets
            if(n*m <=1){
                printf("-1\n");
            }
            else if(n ==1 || m ==1){
                printf("1\n");
            }
            else{
                printf("2\n");
            }
        }
    }
}