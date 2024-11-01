#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(){
    int n;
    while(scanf("%d", &n)!=EOF){
        if(n == 1){
            printf("Jolly\n");
            // Read the single number
            int tmp;
            scanf("%d", &tmp);
            continue;
        }
        int *arr = (int*)malloc(n * sizeof(int));
        for(int i=0;i<n;i++) scanf("%d", &arr[i]);
        bool *diff = (bool*)calloc(n, sizeof(bool));
        bool jolly = true;
        for(int i=0;i<n-1;i++){
            int d = abs(arr[i+1] - arr[i]);
            if(d >=1 && d <=n-1){
                diff[d] = true;
            }
            else{
                jolly = false;
                break;
            }
        }
        if(jolly){
            for(int i=1;i<n;i++) if(!diff[i]){jolly = false; break;}
        }
        printf("%s\n", jolly ? "Jolly" : "Not jolly");
        free(arr);
        free(diff);
    }
    return 0;
}