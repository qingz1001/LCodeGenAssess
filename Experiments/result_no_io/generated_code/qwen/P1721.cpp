#include <stdio.h>
#include <stdlib.h>

#define EPSILON 1e-10

typedef struct {
    double value;
    int count;
} Decimal;

Decimal add(Decimal a, Decimal b) {
    if (a.count > b.count) {
        return (Decimal){a.value + b.value / (1 << (a.count - b.count)), a.count};
    } else {
        return (Decimal){b.value + a.value / (1 << (b.count - a.count)), b.count};
    }
}

Decimal divide(Decimal a, int n) {
    return (Decimal){a.value / n, a.count};
}

int main() {
    int n, k, p;
    scanf("%d %d %d", &n, &k, &p);
    
    Decimal heights[n];
    for (int i = 0; i < n; i++) {
        scanf("%lf", &heights[i].value);
        heights[i].count = p;
    }
    
    Decimal max_height = {0, 0};
    for (int i = 0; i < n; i++) {
        max_height = add(max_height, heights[i]);
    }
    max_height = divide(max_height, n);
    
    for (int i = 0; i < k; i++) {
        Decimal new_max_height = {0, 0};
        for (int j = 0; j < n; j++) {
            new_max_height = add(new_max_height, heights[j]);
        }
        new_max_height = divide(new_max_height, n);
        
        if (new_max_height.value <= max_height.value + EPSILON) {
            break;
        }
        
        max_height = new_max_height;
    }
    
    printf("%.0f\n", max_height.value);
    
    return 0;
}