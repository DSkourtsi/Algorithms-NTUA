#include <bits/stdc++.h>

using namespace std;
   
class DisjointSet
{
    unordered_map<int, int> parent;
    int *size;
 
public:
 
    void makeSet(int N)
    {
        size = new int[N];
        for (int i=0; i<N; i++) {
            parent[i] = i;
            size[i] = 1;
        }
    }

    int Find(int k)
    {
        if (parent[k] == k) {
            return k;
        }
        return Find(parent[k]);
    }

    int Union(int a, int b)
    {
        int x = Find(a);
        int y = Find(b);
        if(x!=y) 
        {
            if (size[x]<size[y]){
                parent[x] = y;
                size[y] += size[x];
                return size[y];
            }
            else{
                parent[y] = x;
                size[x] += size[y];
                return size[x];
            }
        }
        return -1;
    }

};
   

int main()
{   
    int N, F;
    scanf("%d %d", &N, &F);

    vector<int> sick;
    sick.push_back(0);
    int s;
    for(int i=0; i<63; i++){
        scanf("%d", &s);
        sick.push_back(s);
    }

    DisjointSet ds;
    ds.makeSet(N);

    vector<pair<int, int>> meets;
    int loops = 0;
    int same_pair = 0;
    int meetups = 0;
    int curr = 64;
    
    for(int i=1; i<INT_MAX; i++){

        for(int j = 0; j<2; j++){
            s = ( sick[curr-63] + sick[curr-31] ) % N;
            sick.push_back(s);
            curr++;
        }

        int A = sick[2*i-1];
        int B = sick[2*i];

        if(A==B) loops++;
        else if( find(meets.begin(), meets.end(), make_pair(A,B)) != meets.end() || find(meets.begin(), meets.end(), make_pair(B,A)) != meets.end() ) same_pair++;
        else {
            meets.push_back({A,B});
            meetups++;
        }

        int sick_size = ds.Union(A,B);
        if(sick_size >= (N*F)/100) break;

    } 
    
    printf("%d %d %d\n", meetups, same_pair, loops);
    return 0;
}