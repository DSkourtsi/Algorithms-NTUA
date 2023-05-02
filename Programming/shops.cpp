#include <iostream>
#include <climits>

using namespace std;

#define Nmax 20000
#define Kmax 1000000

int p[Nmax+1];
int sums[Nmax+1];
int N, K;

int find_min_l(int k, int start)
{
    int min_l = INT_MAX;
    int curr_sum = 0;
    for (int i = start; i<N+1; i++)
    {
        curr_sum += p[i];
        while (curr_sum > k)
        {
            curr_sum -= p[start];
            start++;
        }
        if (curr_sum == k)
        {
            if ((i-start+1) < min_l) min_l = i-start+1;
            curr_sum = 0;
            start = i+1;
        }   
    }
    return min_l;
}

int main()
{
    scanf("%d %d\n", &N, &K);

    int sum = 0;
    sums[0] = 0;
    p[0]=-1;
    for(int i=0; i<N; i++)
    {
        int pi;
        scanf("%d", &pi);
        p[i+1]=pi;
        sum += pi;
        sums[i+1] = sum;
    }

    int min_l = INT_MAX;
    for (int j=1; j<N+1; j++)
    {
        int curr_sum = 0;
        int start = j;
        for (int i = start; i<N+1; i++)
        {
            curr_sum += p[i];
            while (curr_sum > K)
            {
                curr_sum -= p[start];
                start++;
            }
            int possible_l = i-start+1;
            if (curr_sum == K)
            {
                if ((possible_l) < min_l) min_l = possible_l;
                curr_sum = 0;
                start = i+1;
            } 
            else
            {
                int second_l = find_min_l(K-curr_sum, i+1); 
                if (second_l != INT_MAX && ((possible_l + second_l) < min_l)) min_l = possible_l + second_l;
            }  
        } 
    }
    if (min_l == INT_MAX) min_l = -1;
    printf("%d\n", min_l);
}