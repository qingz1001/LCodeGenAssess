#include <stdio.h>

int main(){
    int h1, m1, s1;
    int h2, m2, s2;
    int n;
    // Read first time
    scanf("%d:%d:%d", &h1, &m1, &s1);
    // Read second time
    scanf("%d:%d:%d", &h2, &m2, &s2);
    // Read n
    scanf("%d", &n);
    
    // Convert times to seconds
    long long t1 = (long long)h1 * 3600 + m1 * 60 + s1;
    long long t2 = (long long)h2 * 3600 + m2 * 60 + s2;
    
    // Compute difference
    long long diff = t2 - t1;
    
    // Compute result
    long long result = diff * n;
    
    // Print result
    printf("%lld\n", result);
    
    return 0;
}