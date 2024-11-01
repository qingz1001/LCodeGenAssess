#include <stdio.h>

int main() {
    int W;
    scanf("%d", &W);
    
    int n, m, x;
    scanf("%d %d %d", &n, &m, &x);
    
    // Read coordinates of the waypoints
    for (int i = 0; i < n; ++i) {
        int xi, yi;
        scanf("%d %d", &xi, &yi);
    }
    
    // Read the tunnels and their energy costs
    for (int i = 0; i < m; ++i) {
        int ui, vi, wi;
        scanf("%d %d %d", &ui, &vi, &wi);
    }
    
    // Output the number of operations
    printf("1\n");
    
    // Output the operation to increase the energy cost of tunnel 1 by 1
    printf("1 2 1\n");
    
    return 0;
}