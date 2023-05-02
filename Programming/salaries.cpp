#include <iostream>         
      
using namespace std;        
        
#define max_N 200001      
        
int N,K;      
int p_LDS[max_N], p_LIS[max_N];    
       
int LISCeilIndex(int arr[], int l, int r, int key)      
{      
    while (r - l > 1)       
    {      
        int m = l + (r - l) / 2;      
        if (arr[m] >= key)      
            r = m;      
        else      
            l = m;      
    }      
       
    return r;      
}      
      
int LDSCeilIndex(int arr[], int l, int r, int key)      
{      
    while (r - l > 1)       
    {      
        int m = l + (r - l) / 2;      
        if (arr[m] <= key)      
            r = m;      
        else      
            l = m;      
    }      
       
    return r;      
}      
       
void LIS(int arr[], int k)      
{      
    int m[N+1];      
    int length = 1;    
    m[1] = arr[0];      
    p_LIS[0]=1;      
    for (int i = 1; i < N; i++)       
    {         
        if (arr[i] + k <= m[1]) p_LIS[i]=1;     
        else if  (arr[i] + k > m[length]) p_LIS[i]=length+1;      
        else p_LIS[i]=LISCeilIndex(m, 0, length, arr[i] + k);     
            
        if (arr[i] <= m[1]) m[1] = arr[i];     
        else if  (arr[i] > m[length]) m[++length] = arr[i];      
        else m[LISCeilIndex(m, 0, length, arr[i])] = arr[i];     
    }      
}      
      
void LDS(int arr[])      
{       
    int m[N+1];      
    int length = 1;    
       
    m[1] = arr[N-1];      
    p_LDS[N-1]=1;      
    for (int i = N-2; i >= 0; i--)       
    {        
        if (arr[i] >= m[1])     
        {    
          m[1] = arr[i];    
          p_LDS[i]=1;      
        }    
        else if (arr[i] < m[length])     
        {    
          m[++length] = arr[i];    
          p_LDS[i]=length;      
        }    
        else     
        {    
          int len = LDSCeilIndex(m, 0, length, arr[i]);    
          m[len] = arr[i];      
          p_LDS[i]=len;    
        }    
    }      
}      
      
int main()      
{      
    scanf("%d %d", &N, &K);       
    int p[N];    
    for(int i=0; i<N; i++) scanf("%d", &p[i]);          
        
    int max_length = 0;     
    LDS(p);    
    LIS(p,K);    
            
    for(int i =0; i<N; i++)     
    {    
      int pos = p_LIS[i]+p_LDS[i]-1;    
      if (pos > max_length) max_length = pos;    
    }    
    printf("%d\n", max_length);      
      
    return 0;      
}