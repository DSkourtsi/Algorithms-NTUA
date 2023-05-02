#include <iostream>   
#include <limits.h>  
#include <deque>          
        
using namespace std;  
  
#define max_N 8000  
#define max30_N 100000   
  
int N, pre[max30_N];  
long long p[max30_N], s[max30_N], adj_mat[max_N][max_N];  
long long dist[max30_N], delay[max30_N];  
  
void bfs(int start)  
{  
    bool visited[N];  
    deque<int> q;  
    q.push_back(start);  
    visited[start] = true;  
    for(int i=1; i<N; i++) visited[i] = false;  
    dist[start] = 0;  
    pre[0] = -1;  
    int curr;  
    while(!q.empty())  
    {  
        curr = q[0];  
        q.pop_front();  
        for (int i=0; i<N; i++)  
        {  
            if(adj_mat[curr][i] != 0 && (!visited[i]))  
            {  
                visited[i] = true;  
                q.push_back(i);  
                dist[i] = dist[curr] + adj_mat[curr][i];  
                pre[i] = curr;  
            }  
        }  
          
    }  
  
}  
  
int main()        
{        
    scanf("%d", &N);           
    for(int i=0; i<N-1; i++)   
    {  
        int vi, vj, d;  
        scanf("%d %d %d", &vi, &vj, &d);   
        adj_mat[vi-1][vj-1] = d;  
        adj_mat[vj-1][vi-1] = d;  
    }  
    p[0]=s[0]=0;  
    for(int i=1; i<N; i++)   
    {  
        scanf("%lld %lld", &p[i], &s[i]);  
    }  
      
   bfs(0);  
   delay[0] = 0;  
   for(int i=1; i<N; i++)  
   {  
        long long dist_v1 = p[i]+s[i]*dist[i];  
        long long dist_vj = LLONG_MAX;  
        int previous = pre[i];  
        while(previous>0)  
        {   
            long long temp = p[i]+s[i]*(dist[i]-dist[previous]) +delay[previous];  
            previous = pre[previous];  
            if(temp < dist_vj) dist_vj = temp;  
        }  
        if (dist_v1 < dist_vj) delay[i] = dist_v1;  
        else delay[i] = dist_vj;  
    }  
    for(int i=1; i<N-1; i++) printf("%lld ", delay[i]);  
    printf("%lld\n", delay[N-1]);  
    return 0;  
}