#include <stdio.h>

int main(){
    int heights[10];
    int H;
    int count = 0;

    // Read the heights of the 10 apples
    for(int i = 0; i < 10; i++){
        scanf("%d", &heights[i]);
    }

    // Read Taotao's maximum reach
    scanf("%d", &H);

    // Count the number of apples Taotao can reach directly or using the stool
    for(int i = 0; i < 10; i++){
        if(heights[i] <= H + 30){
            count++;
        }
    }

    // Output the result
    printf("%d\n", count);

    return 0;
}