#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

bool compare (pair <int, int> p1, pair <int, int> p2) {
    return p1.first < p2.first;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n, tmp;
        cin >> n;

        vector <pair <int, int> > vec(n);
        for (int i=0;i<n;i++) {
            cin >> tmp;
            vec[i] = make_pair (tmp, 0);
        }

        for (int i=n-1;i>=0;i--) {
            if (vec[i].second != 0) {
                if (vec[i].second == -1) {
                    vec[i].second = 0;
                }
                continue;
            }

            vector <int> temp(n, 0);
            int count = 0;
            for (int j=i-1;j>=0;j--) {
                if (vec[j].first % vec[i].first == 0) {
                    temp[count] = j;
                    vec[j].second = -1;
                    count++;
                    vec[i].second++;

                    for (int k=0;k<count-1;k++) {
                        if (vec[j].first % vec[temp[k]].first == 0) {
                            if (vec[temp[k]].second == -1) {
                                vec[temp[k]].second++;
                            }
                            vec[temp[k]].second++;
                        }
                    }
                }
            }
        }

        int highest = 0;
        for (int i=0;i<n;i++) {
            if (highest < vec[i].second) {
                highest = vec[i].second;
            }
        }

        cout << highest << "\n";
    }
    return 0;
}

// Made By - Megatron-3
