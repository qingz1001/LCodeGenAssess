#include <stdio.h>
#include <string.h>
#include <ctype.h>

typedef long long ll;

ll parse_commands(char* s, char** pos) {
    ll movement = 0;
    while (**pos != '\0' && **pos != ']') {
        // Skip any whitespace
        while (isspace(**pos)) (*pos)++;

        if (strncmp(*pos, "FD", 2) == 0) {
            *pos += 2;
            // Skip whitespace
            while (isspace(**pos)) (*pos)++;
            // Read number
            int sign = 1;
            if (**pos == '-') {
                sign = -1;
                (*pos)++;
            }
            int num = 0;
            while (isdigit(**pos)) {
                num = num * 10 + (**pos - '0');
                (*pos)++;
            }
            movement += sign * num;
        }
        else if (strncmp(*pos, "BK", 2) == 0) {
            *pos += 2;
            // Skip whitespace
            while (isspace(**pos)) (*pos)++;
            // Read number
            int sign = 1;
            if (**pos == '-') {
                sign = -1;
                (*pos)++;
            }
            int num = 0;
            while (isdigit(**pos)) {
                num = num * 10 + (**pos - '0');
                (*pos)++;
            }
            movement -= sign * num;
        }
        else if (strncmp(*pos, "REPEAT", 6) == 0) {
            *pos += 6;
            // Skip whitespace
            while (isspace(**pos)) (*pos)++;
            // Read number
            int repeat = 0;
            while (isdigit(**pos)) {
                repeat = repeat * 10 + (**pos - '0');
                (*pos)++;
            }
            // Skip to '['
            while (isspace(**pos)) (*pos)++;
            if (**pos == '[') {
                (*pos)++;
            }
            // Recursively parse inside the brackets
            ll inner = parse_commands(s, pos);
            // Skip ']'
            if (**pos == ']') {
                (*pos)++;
            }
            movement += repeat * inner;
        }
        else {
            // If unexpected token, skip it
            while (**pos != '\0' && !isspace(**pos) && **pos != '[' && **pos != ']') {
                (*pos)++;
            }
        }
    }
    return movement;
}

int main(){
    char s[100005];
    if (!fgets(s, sizeof(s), stdin)) {
        return 0;
    }
    // Remove newline if present
    int len = strlen(s);
    if (len > 0 && s[len-1] == '\n') {
        s[len-1] = '\0';
    }
    char* pos = s;
    ll result = parse_commands(s, &pos);
    printf("%lld\n", result);
    return 0;
}