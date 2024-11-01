#include <stdio.h>
#include <string.h>

int main(){
    int input[3];
    int sorted[3];
    char order[4];
    scanf("%d %d %d", &input[0], &input[1], &input[2]);
    scanf("%s", order);
    
    // Sort the input numbers
    for(int i=0;i<3;i++) sorted[i]=input[i];
    for(int i=0;i<2;i++) {
        for(int j=i+1;j<3;j++){
            if(sorted[i] > sorted[j]){
                int temp = sorted[i];
                sorted[i] = sorted[j];
                sorted[j] = temp;
            }
        }
    }
    
    int A = sorted[0];
    int B = sorted[1];
    int C = sorted[2];
    
    for(int i=0;i<3;i++){
        if(order[i]=='A') printf("%d ", A);
        else if(order[i]=='B') printf("%d ", B);
        else if(order[i]=='C') printf("%d ", C);
    }
    return 0;
}