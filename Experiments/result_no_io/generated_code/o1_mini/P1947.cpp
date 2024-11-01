pp
#include <cstdio>

extern "C" int Seniorious(int);

extern "C" int Chtholly(int n, int c) {
    int l = 1, r = n, ans = 1;
    while (l <= r && c > 0) {
        int mid = l + (r - l) / 2;
        int res = Seniorious(mid);
        c--;
        if (res == 0) {
            return mid;
        } else if (res == 1) {
            r = mid - 1;
            ans = mid - 1;
        } else {
            l = mid + 1;
            ans = mid + 1;
        }
    }
    return ans;
}