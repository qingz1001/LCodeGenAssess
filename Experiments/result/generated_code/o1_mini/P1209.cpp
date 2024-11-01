#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b){
    return (*(int*)b - *(int*)a);
}

int main(){
    int m, s, c;
    scanf("%d %d %d", &m, &s, &c);
    if(c == 0){
        printf("0\n");
        return 0;
    }
    int cows[c];
    for(int i=0;i<c;i++) scanf("%d", &cows[i]);
    // Sort the cow positions
    for(int i=0;i<c-1;i++) {
        for(int j=i+1;j<c;j++) {
            if(cows[i] > cows[j]){
                int temp = cows[i];
                cows[i] = cows[j];
                cows[j] = temp;
            }
        }
    }
    // Calculate gaps
    int gaps[c-1];
    for(int i=0;i<c-1;i++) gaps[i] = cows[i+1] - cows[i] -1;
    // Sort gaps in descending order
    if(c-1 >0){
        qsort(gaps, c-1, sizeof(int), compare);
    }
    // Sum the largest m-1 gaps
    int total_gaps =0;
    int splits = m-1 < c-1 ? m-1 : c-1;
    for(int i=0;i<splits;i++) total_gaps += gaps[i];
    // Total length is last - first +1 minus sum of gaps
    int total_length = cows[c-1] - cows[0] +1 - total_gaps;
    printf("%d\n", total_length);
}