#include <stdio.h>
#include <stdlib.h>

#define MAX_H 6

int main() {
    int H;
    scanf("%d", &H);
    char front[MAX_H][7], back[MAX_H][7];

    for (int i = 0; i < H; i++) {
        scanf("%s", front[i]);
    }
    for (int i = 0; i < H; i++) {
        scanf("%s", back[i]);
    }

    // Placeholder for the solution logic
    // You need to implement the logic here to calculate the number of valid placements

    printf("0\n"); // Placeholder output, replace with actual result

    return 0;
}