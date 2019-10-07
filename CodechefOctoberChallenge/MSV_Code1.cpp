#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector <int> vec(n);

        for (int i=0;i<n;i++) {
            cin >> vec[i];
        }

        vector <int> num (1000005, 0);
        int maxi = 0; 
        for (int i=0;i<n;i++) {
            if (maxi < num[vec[i]]) {
                maxi = num[vec[i]];
            }
            for (int j=1;j<=sqrt (vec[i]);j++) {
                if (vec[i]%j == 0) {
                    if (vec[i] / j == j) {
                        num[j]++;
                    }
                    else {
                        num[vec[i] / j]++;
                        num[j]++;
                    }
                }
            }
        }

        cout << maxi << "\n";
    }
    return 0;
}

// Made By - Megatron-3
