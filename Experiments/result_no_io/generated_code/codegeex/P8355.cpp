#include <stdio.h>
#include <string.h>

int main() {
    int n;
    scanf("%d", &n);
    char s[1000005];
    scanf("%s", s);

    int max_match_prefix_length = 0;
    int current_length = 0;
    int left_brackets = 0;

    for (int i = 0; i < n; i++) {
        if (s[i] == '(') {
            left_brackets++;
        } else {
            if (left_brackets > 0) {
                left_brackets--;
                current_length += 2;
            } else {
                break;
            }
        }
        max_match_prefix_length = current_length;
    }

    printf("%d\n", max_match_prefix_length);
    return 0;
}