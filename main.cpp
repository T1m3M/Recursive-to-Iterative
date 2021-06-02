#include <iostream>

using namespace std;

int cur_ind;
int cur_subset[100];

void GenerateSubsets(int* a, int k, int n, int start, int remain)
{
    // Base case
    if(start==n)
    {
        if(cur_ind==k){int i; for(i=0;i<k;i++) cout<<cur_subset[i]<<" "; cout<<endl;}
        return;
    }
    // Use the current item
    if(remain>0)
    {
        cur_subset[cur_ind++]=a[start];
        GenerateSubsets(a, k, n, start+1, remain-1);
        cur_ind--;
    }
    // Ignore the current item
    if(n-start>remain)
    {
        GenerateSubsets(a, k, n, start+1, remain);
    }
}

void GenerateSubsets(int* a, int k, int n)
{
    cur_ind=0;
    GenerateSubsets(a, k, n, 0, k);
}

int main()
{
    int a[]={1,3,5,8,10}; int n=sizeof(a)/sizeof(a[0]), k=3;
    GenerateSubsets(a, k, n);
    return 0;
}
