#include <stdio.h>
#include <stdlib.h>

int main(){
    int n;
    scanf("%d", &n);
    int* arr = (int*)malloc(n * sizeof(int));
    for(int i=0;i<n;i++) scanf("%d", &arr[i]);
    
    int count1=0, count2=0, count3=0;
    for(int i=0;i<n;i++){
        if(arr[i]==1) count1++;
        else if(arr[i]==2) count2++;
        else count3++;
    }
    
    // Define segments
    // S1: 0 to count1-1
    // S2: count1 to count1+count2-1
    // S3: count1+count2 to n-1
    int M[3][3] = {0};
    for(int i=0;i<n;i++){
        int segment;
        if(i < count1) segment = 0;
        else if(i < count1 + count2) segment = 1;
        else segment = 2;
        
        int val = arr[i];
        if(val ==1) {
            M[0][0]++;
        }
        else if(val ==2){
            M[1][1]++;
            if(segment ==0) M[0][1]++;
            else if(segment ==2) M[2][1]++;
        }
        else{
            if(segment ==0) M[0][2]++;
            else if(segment ==1) M[1][2]++;
            else M[2][2]++;
        }
    }
    
    // Recount M correctly
    // Reset M and recount
    for(int i=0;i<3;i++) {
        for(int j=0;j<3;j++) M[i][j]=0;
    }
    for(int i=0;i<n;i++){
        int segment;
        if(i < count1) segment = 0;
        else if(i < count1 + count2) segment = 1;
        else segment = 2;
        
        int val = arr[i];
        if(val ==1){
            M[0][0]++;
        }
        else if(val ==2){
            M[1][1]++;
            if(segment !=1) M[segment][1]++;
        }
        else{
            if(segment !=2) M[segment][2]++;
        }
    }
    
    // Initialize count1, count2, count3 not needed anymore
    // Calculate direct swaps
    int swaps=0;
    // Swap between 0 and1
    int tmp = M[0][1] < M[1][0] ? M[0][1] : M[1][0];
    swaps += tmp;
    M[0][1] -= tmp;
    M[1][0] -= tmp;
    
    // Swap between0 and2
    tmp = M[0][2] < M[2][0] ? M[0][2] : M[2][0];
    swaps += tmp;
    M[0][2] -= tmp;
    M[2][0] -= tmp;
    
    // Swap between1 and2
    tmp = M[1][2] < M[2][1] ? M[1][2] : M[2][1];
    swaps += tmp;
    M[1][2] -= tmp;
    M[2][1] -= tmp;
    
    // Remaining are in cycles
    int remaining=0;
    for(int i=0;i<3;i++) {
        for(int j=0;j<3;j++) {
            if(i !=j) remaining += M[i][j];
        }
    }
    swaps += (2 * (remaining /3));
    
    printf("%d\n", swaps);
    free(arr);
    return 0;
}