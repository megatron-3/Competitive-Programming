#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int t;
    cin >> t;

    while (t--) {
        int n, m;
        cin >> n >> m;

        vector <vector <int> > edges(n);
        for (int i=0;i<m;i++) {
            int a, b;
            cin >> a >> b;
            edges[a-1].push_back (b-1);
            edges[b-1].push_back (a-1);
        }

        vector <int> ans (n, 0);
        int c_ans = 1;

        while (1) {
            start:;
            if (m%2 == 0) {
                for (int i=0;i<n;i++) {
                    if (ans[i] == 0) {
                        ans[i] = c_ans;
                    }
                }
            }
            else {
                int found_odd = -1;
                for (int i=0;i<n;i++) {
                    if (edges[i].size()%2 == 1) {
                        found_odd = i;
                        break;
                    }
                }

                if (found_odd != -1) {
                    for (int i=0;i<n;i++) {
                        if (ans[i] == 0) {
                            if (found_odd == i) {
                                ans[i] = c_ans + 1;
                            }
                            else {
                                ans[i] = c_ans;
                            }
                        }
                    }
                }
                else {
                    int max = 0, index = 0;
                    for (int i=0;i<n;i++) {
                        if (edges[i].size() > max) {
                            index = i;
                            max = edges[i].size();
                        }
                    }

                    ans[index] = c_ans;
                    c_ans++;

                    m = m - edges[index].size();

                    for (int i=0;i<edges[index].size();i++) {
                        auto itr = find (edges[edges[index][i]].begin(), edges[edges[index][i]].end(), index);
                        if (itr != edges[edges[index][i]].end()) {
                            edges[edges[index][i]].erase(itr);
                        }
                    }
                    edges[index].clear();
                }
            }

            for (int i=0;i<n;i++) {
                if (ans[i] == 0) {
                    goto start;
                }
            }
            goto end;
        }
        end:;
        cout << *(max_element(ans.begin(), ans.end())) << "\n";
        for (int i=0;i<n;i++) {
            cout << ans[i] << " ";
        }
        cout << "\n";
    }
    return 0;
}

Made By - Megatron-3
