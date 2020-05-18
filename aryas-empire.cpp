#include <bits/stdc++.h>
using namespace std;

int n = 10005;

// To store Prime Numbers
vector<bool> Prime(n + 1, true);

// Function to find the prime numbers
// till 10^5
void SieveOfEratosthenes()
{

    int i, j;
    Prime[0] = Prime[1] = false;
    for (i = 2; i * i <= 10005; i++) {

        // Traverse all multiple of i
        // and make it false
        if (Prime[i]) {

            for (j = 2 * i; j < 10005; j += i) {
                Prime[j] = false;
            }
        }
    }
}

// Function to print the nodes having
// prime degree
void primeDegreeNodes(int N, int M,
                      int edges[][2])
{
    // To store Adjacency List of
    // a Graph
    vector<int> Adj[N + 1];

    // Make Adjacency List
    for (int i = 0; i < M; i++) {
        int x = edges[i][0];
        int y = edges[i][1];

        Adj[x].push_back(y);
        Adj[y].push_back(x);
    }

    // To precompute prime numbers
    // till 10^5
    SieveOfEratosthenes();

    // Traverse each vertex
    for (int i = 1; i <= N; i++) {

        // Find size of Adjacency List
        int x = Adj[i].size();

        // If length of Adj[i] is Prime
        // then print it
        if (Prime[x])
            cout << i << " " ;
    }
}

// Driver code
int main()
{
    int t;
    cin>> t;
    for(int x=0;x<t;x++){
// Vertices and Edges
    int N, M;
    cin >> N;
    cin >> M;

    // Edges
    int edges[M][2];
    for(int i=0;i<M;i++){
    cin >> edges[i][0]>>edges[i][1];
}
    // Function Call
    primeDegreeNodes(N, M, edges);
cout<<endl;
}

    return 0;
}
