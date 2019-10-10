#include <iostream>

using namespace std;

typedef struct Node {
    int data;
    Node *next;
}Node;

void Insert (Node *node, int data) {
    Node *temp = node->next;
    node->next = new Node;
    node->next->data = data;
    node->next->next = temp; 
}

void BFS (Node *graph[], int source, int n, int d) {
    int tree_edge = 0, back_edge = 0, cross_edge = 0;
    int queue[n], start = 0, end = 1, levels[n], parent[n];
    int visited[n], c_level = 0;

    levels[0] = 1;

    for (int i=0;i<n;i++) {
        visited[i] = queue[i] = parent[i] = 0;
    }
    
    queue[start] = source;
    parent[source] = -1;

    while (start != end) {
        int node = queue[start];
        visited[node] = -1;
        start++;

        Node *i = graph[node]->next;
        while (i != NULL) {
            if (visited[i->data] == 1) {
                cross_edge++;
            }
            else if (visited[i->data] == 0) {
                queue[end] = i->data;
                visited[i->data] = 1;
                levels[end] = levels[c_level] + 1;
                parent[i->data] = node;
                end++;
                tree_edge++;
            }
            else if (visited[i->data] == -1 && d == 1) {
                int current = parent[node];
                while (current != -1) {
                    if (current == i->data) {
                        back_edge++;
                        goto a;
                    }
                    current = parent[current];
                }
                cross_edge++;
                a:;
            }
            i = i->next;
        }
        c_level++;
    }

    c_level = 1;
    for (int i=2;i<n;i++) {
        if (levels[i-1] == levels[i]) {
            c_level++;
        }
        else {
            cout << c_level << " ";
            c_level = 1;
        }
    }
    cout << c_level << " 0 ";
    if (d == 0) {
        cout << tree_edge << " " << cross_edge << "\n";
    }
    else {
        cout << tree_edge << " 0 " << back_edge << " " << cross_edge << "\n";
    }
}

void DFS (Node *graph[], int source, int )

int main () {
    int t;
    cin >> t;
    while (t--) {
        int q, n, d, s, tmp;
        cin >> q >> n;
        
        Node *graph[n];

        for (int i=0;i<n;i++) {
            graph[i] = new Node;
            graph[i]->next = NULL;
            graph[i]->data = i;
        }

        if (q == 1 || q == 2 || q == 4 || q == 5) {
            cin >> d >> s;
            int matrix[n][n];

            for (int i=0;i<n;i++) {
                for (int j=0;j<n;j++) {
                    cin >> matrix[i][j];
                }
            }
            

            for (int i=0;i<n;i++) {
                for (int j=n-1;j>=0;j--) {
                    if (matrix[i][j] == 1) {
                        Insert (graph[i], j);
                    }
                }
            }

            if (q == 1) {
                BFS (graph, s-1, n, d);
            }
            else if (q == 2) {
                DFS (graph, s-1, n, d);
            }
            else if (q == 3) {

            }
            else {

            }
        }
        else if (q == 3) {

        }
        else {

        }
    }
}
