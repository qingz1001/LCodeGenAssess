#include <stdio.h>
#include <string.h>

int main() {
    char s[100];
    scanf("%s", s);
    
    int a = 0, b = 0;
    int i = 0, j = 0;
    
    // Parse the first number
    while (s[i] != '+' && s[i] != '\0') {
        if (s[i] == ',') {
            i++;
            continue;
        }
        a = a * 10 + (s[i] - '0');
        i++;
    }
    
    // Parse the second number
    while (s[j] != '\0') {
        if (s[j] == ',') {
            j++;
            continue;
        }
        b = b * 10 + (s[j] - '0');
        j++;
    }
    
    // Calculate the sum
    int result = a + b;
    
    // Print the result
    printf("%d\n", result);
    
    return 0;
}