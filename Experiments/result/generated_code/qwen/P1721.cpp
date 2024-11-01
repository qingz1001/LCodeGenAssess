#include <stdio.h>
#include <stdlib.h>

#define EPSILON 1e-10

typedef struct {
    double value;
    int count;
} Decimal;

Decimal add(Decimal a, Decimal b) {
    if (a.count > b.count) {
        return (Decimal){a.value + b.value * (double)a.count / b.count, a.count};
    } else {
        return (Decimal){b.value + a.value * (double)b.count / a.count, b.count};
    }
}

Decimal multiply(Decimal a, double b) {
    return (Decimal){a.value * b, a.count};
}

int main() {
    int n, k, p;
    scanf("%d %d %d", &n, &k, &p);
    
    Decimal heights[n];
    for (int i = 0; i < n; i++) {
        scanf("%lf", &heights[i].value);
        heights[i].count = 1;
    }
    
    while (k--) {
        Decimal max_height = {0, 0};
        for (int i = 0; i < n; i++) {
            if (compare(max_height, heights[i]) < 0) {
                max_height = heights[i];
            }
        }
        
        Decimal new_height = multiply(add(max_height, multiply(heights[0], -1)), 1.0 / (double)n);
        for (int i = 0; i < n; i++) {
            heights[i] = add(new_height, multiply(heights[i], -new_height.value));
        }
    }
    
    printf("%.2f\n", heights[0].value);
    
    return 0;
}