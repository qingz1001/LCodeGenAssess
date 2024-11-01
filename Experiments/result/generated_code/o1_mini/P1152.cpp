#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int main(){
    int n;
    while(scanf("%d", &n) == 1){
        if(n <1 || n >1000){
            // handle invalid n, but as per problem constraints, assume valid
        }
        int arr[n];
        for(int i=0;i<n;i++) scanf("%d", &arr[i]);
        if(n ==1){
            printf("Jolly\n");
            continue;
        }
        int found[n];
        memset(found, 0, sizeof(found));
        int jolly = 1;
        for(int i=1;i<n;i++){
            int diff = abs(arr[i] - arr[i-1]);
            if(diff >=1 && diff <=n-1){
                found[diff] =1;
            }
            else{
                jolly =0;
                break;
            }
        }
        if(jolly){
            for(int i=1;i<n;i++) if(!found[i]) { jolly =0; break;}
        }
        printf("%s\n", jolly ? "Jolly" : "Not jolly");
    }
    return 0;
}