#include <iostream>
using namespace std;

int min3(int a, int b, int c) {
    return min(a, min(b, c));
}

int main() {
    int n;
    cin >> n;
    int a, b, c;
    int ans[n];
    for (int i = 0; i < n; ++i) {
        cin >> a >> b >> c;
        ans[i] = min3(a, b, c);
    }
    for (int i = 0; i < n; ++i) {
        cout << ans[i] << ' ';
    }
    return 0;
}
