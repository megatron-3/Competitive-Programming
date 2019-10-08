#include <iostream>
#include <vector>
#include <utility> 
#include <algorithm>

using namespace std;

bool compare (pair <long long, long long> p1, pair<long long, long long> p2) {
    return p1.first < p2.first;
}

int main() {
    long long n, q;
    cin >> n >> q;

    vector <pair <long long, long long> > edges(n-1);
    for (long long i=0;i<n-1;i++) {
        long long a, b;
        cin >> a >> b;
        if (a > b) {
            long long temp = b;
            b = a;
            a = temp;
        }
        edges[i] = make_pair(a, b);
    }

    sort (edges.begin(), edges.end(), compare);

    vector <vector <long long> > children (n+1);
    vector <long long> done (n+1, 0);
    done[1] = 1;
    int k = edges.size();

    while (k != 0) {
        for (long long i=0;i<=edges.size();i++) {
            if (done[edges[i].first] == 1) {
                children[edges[i].first].push_back(edges[i].second);
                done[edges[i].second] = 1;
                auto itr = find (edges.begin(), edges.end(), edges[i]);
                if (itr != edges.end()) {
                    edges.erase(itr);
                }
                k--;
            }
            else if (done[edges[i].second] == 1){
                children[edges[i].second].push_back(edges[i].first);
                done[edges[i].first] = 1;
                auto itr = find (edges.begin(), edges.end(), edges[i]);
                if (itr != edges.end()) {
                    edges.erase(itr);
                }
                k--;
            }
        }
    }

    vector <pair <long long, long long> > bact (n+1);
    for (long long i=0;i<n;i++) {
        long long a;
        cin >> a;
        bact[i+1] = make_pair (a, 0);
    }

    while (q--) {
         
        for (long long i=1;i<n+1;i++) {
            if (children[i].size() != 0) {
                for (long long j=0;j<children[i].size();j++) {
                    bact[children[i][j]].second += bact[i].first;
                }
                bact[i].first = bact[i].second;
                bact[i].second = 0;
            }
            else {
                bact[i].first += bact[i].second;
                bact[i].second = 0;
            }
        }

        for (int i=1;i<n+1;i++) {
            bact[i].first += bact[i].second;
            bact[i].second = 0;
        }

        char ch;
        cin >> ch;

        if (ch == '+') {
            long long v, k;
            cin >> v >> k;
            bact[v].first += k;
        }
        else {
            long long v;
            cin >> v;
            cout << bact[v].first + bact[v].second << "\n";
        }
    }
}
