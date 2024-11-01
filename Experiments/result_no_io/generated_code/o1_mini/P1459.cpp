#include <stdio.h>

int main(){
    int n;
    scanf("%d", &n);
    int sequence[n];
    for(int i=0;i<n;i++) {
        scanf("%d", &sequence[i]);
    }
    // Count number of 1s, 2s, 3s
    int c1=0, c2=0, c3=0;
    for(int i=0;i<n;i++) {
        if(sequence[i]==1) c1++;
        else if(sequence[i]==2) c2++;
        else c3++;
    }
    // Define regions
    // Region 1: 0 to c1-1
    // Region 2: c1 to c1+c2-1
    // Region 3: c1+c2 to n-1
    int M[3][3];
    for(int i=0;i<3;i++) {
        for(int j=0;j<3;j++) M[i][j]=0;
    }
    for(int i=0;i<c1;i++) {
        int val = sequence[i];
        M[0][val-1]++;
    }
    for(int i=c1;i<c1+c2;i++) {
        int val = sequence[i];
        M[1][val-1]++;
    }
    for(int i=c1+c2;i<n;i++) {
        int val = sequence[i];
        M[2][val-1]++;
    }
    int swaps=0;
    // Direct swaps between regions
    // Swap between region1 and region2
    int swap_12 = (M[0][1] < M[1][0]) ? M[0][1] : M[1][0];
    swaps += swap_12;
    M[0][1] -= swap_12;
    M[1][0] -= swap_12;
    // Swap between region1 and region3
    int swap_13 = (M[0][2] < M[2][0]) ? M[0][2] : M[2][0];
    swaps += swap_13;
    M[0][2] -= swap_13;
    M[2][0] -= swap_13;
    // Swap between region2 and region3
    int swap_23 = (M[1][2] < M[2][1]) ? M[1][2] : M[2][1];
    swaps += swap_23;
    M[1][2] -= swap_23;
    M[2][1] -= swap_23;
    // Remaining misplacements form cycles
    int remaining = M[0][1] + M[0][2] + M[1][0] + M[1][2] + M[2][0] + M[2][1];
    swaps += (remaining * 2) / 3;
    printf("%d\n", swaps);
    return 0;
}