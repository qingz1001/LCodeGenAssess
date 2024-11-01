#include <stdio.h>
#include <stdint.h>

int main(){
    int n;
    scanf("%d", &n);
    if(n <5){
        printf("0");
        return 0;
    }
    // Define the 12 lines
    uint32_t lines[12] = {0};
    // Rows
    for(int r=0;r<5;r++) {
        lines[r] = 0;
        for(int c=0;c<5;c++) {
            lines[r] |= (1U << (r*5 + c));
        }
    }
    // Columns
    for(int c=0;c<5;c++) {
        lines[5+c] = 0;
        for(int r=0;r<5;r++) {
            lines[5+c] |= (1U << (r*5 + c));
        }
    }
    // Diagonals
    lines[10] = 0;
    for(int i=0;i<5;i++) {
        lines[10] |= (1U << (i*5 + i));
    }
    lines[11] = 0;
    for(int i=0;i<5;i++) {
        lines[11] |= (1U << (i*5 + (4-i)));
    }
    uint32_t set_k =0;
    // Initialize first mask
    if(n >25){
        printf("0");
        return 0;
    }
    uint32_t mask;
    if(n ==0){
        mask=0;
    }
    else{
        mask = (1U << n) -1;
    }
    while(mask < (1U <<25)){
        // Count k
        int k=0;
        for(int i=0;i<12;i++){
            if( (mask & lines[i]) == lines[i]){
                k++;
            }
        }
        set_k |= (1U <<k);
        // Generate next mask
        uint32_t smallest = mask & -mask;
        uint32_t ripple = mask + smallest;
        uint32_t new_smallest = mask ^ ripple;
        new_smallest = (new_smallest >> 2) / smallest;
        mask = ripple | new_smallest;
    }
    // Handle the case when n=25
    if(n ==25){
        int k=0;
        for(int i=0;i<12;i++) k++;
        set_k |= (1U <<k);
    }
    // Sum the set k's
    int sum=0;
    for(int k=0;k<=12;k++) {
        if(set_k & (1U <<k)){
            sum +=k;
        }
    }
    printf("%d", sum);
    return 0;
}