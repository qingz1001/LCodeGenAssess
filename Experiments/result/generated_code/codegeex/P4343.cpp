#include <stdio.h>
#include <limits.h>

int main() {
    long long l, k;
    scanf("%lld %lld", &l, &k);

    long long total_code = 0;
    long long max_code = LLONG_MIN;
    long long min_code = LLONG_MAX;

    for (long long i = 0; i < l; i++) {
        long long code_change;
        scanf("%lld", &code_change);

        total_code += code_change;
        if (total_code < 0) {
            total_code = 0;
        }
        max_code = (total_code > max_code) ? total_code : max_code;
        min_code = (total_code < min_code) ? total_code : min_code;
    }

    if (max_code < k || min_code < k) {
        printf("-1\n");
        return 0;
    }

    long long min_n = 0, max_n = 0;
    for (long long i = 0; i < l; i++) {
        long long code_change;
        scanf("%lld", &code_change);

        total_code += code_change;
        if (total_code >= k && total_code - code_change < k) {
            max_n = (max_n > total_code - k) ? max_n : total_code - k;
            min_n = (min_n < total_code - k) ? min_n : total_code - k;
        }
    }

    printf("%lld %lld\n", min_n, max_n);
    return 0;
}