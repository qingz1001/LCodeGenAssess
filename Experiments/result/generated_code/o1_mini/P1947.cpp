pp
#include <cstdio>

extern "C" int Seniorious(int);

extern "C" int Chtholly(int n, int c) {
    int l = 1, r = n, mid, ans = 1;
    while (l <= r && c > 0) {
        mid = l + (r - l) / 2;
        int res = Seniorious(mid);
        c--;
        if (res == 0) {
            return mid;
        } else if (res < 0) {
            l = mid + 1;
        } else {
            ans = mid;
            r = mid - 1;
        }
    }
    return ans;
}