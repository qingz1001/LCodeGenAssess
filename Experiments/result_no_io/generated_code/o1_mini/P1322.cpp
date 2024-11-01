#include <stdio.h>
#include <string.h>
#include <ctype.h>

typedef long long ll;

const char *s;
int n;

void skip_spaces() {
    while (s[n] && isspace(s[n])) n++;
}

ll parse_expression() {
    ll res = 0;
    while (s[n] && s[n] != ']') {
        skip_spaces();
        if (strncmp(&s[n], "FD", 2) == 0) {
            n += 2;
            skip_spaces();
            int sign = 1;
            if (s[n] == '-') { sign = -1; n++; }
            ll val = 0;
            while (isdigit(s[n])) { val = val * 10 + (s[n++] - '0'); }
            res += sign * val;
        }
        else if (strncmp(&s[n], "BK", 2) == 0) {
            n += 2;
            skip_spaces();
            int sign = 1;
            if (s[n] == '-') { sign = -1; n++; }
            ll val = 0;
            while (isdigit(s[n])) { val = val * 10 + (s[n++] - '0'); }
            res -= sign * val;
        }
        else if (strncmp(&s[n], "REPEAT", 6) == 0) {
            n += 6;
            skip_spaces();
            int repeat = 0;
            while (isdigit(s[n])) { repeat = repeat * 10 + (s[n++] - '0'); }
            skip_spaces();
            if (s[n] == '[') n++;
            ll inner = parse_expression();
            res += repeat * inner;
            if (s[n] == ']') n++;
        }
        else {
            break;
        }
    }
    return res;
}

int main(){
    char buffer[1000005];
    fgets(buffer, sizeof(buffer), stdin);
    s = buffer;
    n = 0;
    ll ans = parse_expression();
    printf("%lld\n", ans);
}