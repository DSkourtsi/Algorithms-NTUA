#include <climits>
#include <iostream>

using namespace std;

#define Nmax 200000
#define Kmax 200000

int N, K;
int c[Nmax];

bool check_median(int median)
{
    int med_prefix[Nmax];
    int flag = 0;
    for (int i = 0; i < N; i++) {
        if (c[i] <= median)
            med_prefix[i] = -1;
        else 
            med_prefix[i] = 1;
        if (i > 0)
            med_prefix[i] += med_prefix[i - 1];
    }
 
    int max_sum = med_prefix[K - 1];
    int min_sum = INT_MAX;
 
    for (int i = K; i < N; i++) {
        if(med_prefix[i-K] < min_sum) min_sum = med_prefix[i-K];
        if(med_prefix[i] - min_sum > max_sum) max_sum = med_prefix[i] - min_sum;
    }
    if (max_sum <= 0)
        return true;
    return false;
}

int main()
{
    scanf("%d %d\n", &N, &K);

    for(int i=0; i<N; i++)
    {
        int ci;
        scanf("%d", &ci);
        c[i]=ci;

    }
    int max_m = -1;

    int left, right, mid;
    left = 0;
    right = N;
    
    while (left <= right)
    {
        int mid = (left+right)/2;
        if (check_median(mid))
        {
            max_m = mid;
            right = mid - 1;
        }
        else left = mid + 1;
    }
    printf("%d\n", max_m);

    return 0;
}