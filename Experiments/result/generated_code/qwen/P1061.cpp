#include <stdio.h>
#include <string.h>

void next_permutation(char *str) {
    int n = strlen(str);
    int i = n - 2;
    while (i >= 0 && str[i] >= str[i + 1]) {
        i--;
    }
    if (i == -1) {
        return;
    }
    int j = n - 1;
    while (str[j] <= str[i]) {
        j--;
    }
    char temp = str[i];
    str[i] = str[j];
    str[j] = temp;
    for (int k = i + 1, l = n - 1; k < l; k++, l--) {
        temp = str[k];
        str[k] = str[l];
        str[l] = temp;
    }
}

int main() {
    int s, t, w;
    scanf("%d %d %d", &s, &t, &w);
    char str[w + 1];
    scanf("%s", str);
    
    for (int i = 0; i < 5; i++) {
        next_permutation(str);
        printf("%s\n", str);
    }
    
    return 0;
}