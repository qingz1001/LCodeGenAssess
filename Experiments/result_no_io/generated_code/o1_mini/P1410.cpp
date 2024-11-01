#include <stdio.h>
#include <stdlib.h>

int main(){
    int N;
    while(scanf("%d", &N) != EOF){
        int *arr = (int *)malloc(N * sizeof(int));
        for(int i=0;i<N;i++) scanf("%d", &arr[i]);
        int half = N/2;
        // Initialize last elements and counts
        long long last1 = -1e10, last2 = -1e10;
        int count1 = 0, count2 = 0;
        int possible = 1;
        for(int i=0;i<N;i++){
            if(arr[i] > last1 && count1 < half){
                last1 = arr[i];
                count1++;
            }
            else if(arr[i] > last2 && count2 < half){
                last2 = arr[i];
                count2++;
            }
            else{
                possible = 0;
                break;
            }
        }
        if(count1 == half && count2 == half && possible) printf("Yes!\n");
        else printf("No!\n");
        free(arr);
    }
    return 0;
}