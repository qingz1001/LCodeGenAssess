#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    scanf("%d", &n);
    
    int students[n];
    int total_students = 0;
    
    for (int i = 0; i < n; i++) {
        scanf("%d", &students[i]);
        total_students += students[i];
    }
    
    int L, R;
    scanf("%d %d", &L, &R);
    
    if (total_students < L * n || total_students > R * n) {
        printf("-1\n");
        return 0;
    }
    
    int excess = 0, deficit = 0;
    
    for (int i = 0; i < n; i++) {
        if (students[i] > R) {
            excess += students[i] - R;
        } else if (students[i] < L) {
            deficit += L - students[i];
        }
    }
    
    printf("%d\n", excess > deficit ? excess : deficit);
    
    return 0;
}