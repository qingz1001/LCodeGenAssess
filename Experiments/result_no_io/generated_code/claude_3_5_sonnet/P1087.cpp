#include <stdio.h>
#include <string.h>

char str[1024];
int n;

char determine_type(int start, int end) {
    int zeros = 0, ones = 0;
    for (int i = start; i < end; i++) {
        if (str[i] == '0') zeros++;
        else ones++;
    }
    if (zeros == end - start) return 'B';
    if (ones == end - start) return 'I';
    return 'F';
}

void build_tree(int start, int end) {
    if (start == end - 1) {
        printf("%c", determine_type(start, end));
        return;
    }
    
    int mid = (start + end) / 2;
    build_tree(start, mid);
    build_tree(mid, end);
    printf("%c", determine_type(start, end));
}

int main() {
    scanf("%d", &n);
    scanf("%s", str);
    
    int len = 1 << n;
    build_tree(0, len);
    printf("\n");
    
    return 0;
}