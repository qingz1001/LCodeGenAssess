#include <stdio.h>
#include <string.h>

#define MAX_LEN 1024

char s[MAX_LEN];
int n;

char determine_type(int start, int end) {
    int has_zero = 0, has_one = 0;
    for (int i = start; i < end; i++) {
        if (s[i] == '0') has_zero = 1;
        if (s[i] == '1') has_one = 1;
    }
    if (has_zero && has_one) return 'F';
    if (has_zero) return 'B';
    return 'I';
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
    scanf("%s", s);
    
    int len = 1 << n;
    build_tree(0, len);
    printf("\n");
    
    return 0;
}