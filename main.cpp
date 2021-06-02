#include <iostream>
#include <stack>

using namespace std;

int cur_ind;
int cur_subset[100];


struct GenCall
{
    int *a;
    int k, n, start, remain;
};


// for debugging only
void printMyStack(stack<GenCall> &s, int n)
{
    if (s.empty())
        return;


    GenCall tmp = s.top();

    s.pop();

    printMyStack(s, n);

    cout << "CALL\t" << "GenerateSubsetsIterative(";

    cout << "{";
    for (int i=0; i < n; i++)
    {
        cout << tmp.a[i];
        if (i != n - 1)  cout << ", ";
    }
    cout << "}, ";
    cout << tmp.k << ", " << tmp.n << ", " << tmp.start << ", " << tmp.remain << ")\n";

    s.push(tmp);
}


void GenerateSubsetsIterative(int* a, int k, int n)
{

    // define the stack call object which holds the parameters
    GenCall stcall;

    // Initialize parameters of the stack call
    stcall.a = a; stcall.k = k; stcall.n = n; stcall.start = 0; stcall.remain = k;

    // initialize global variable cursor index
    cur_ind=0;

    // Initialize the stack
    stack<GenCall> myStack;
    myStack.push(stcall);

    while(!myStack.empty())
    {
        // fetch the first call to execute
        GenCall call = myStack.top(); myStack.pop();

        // base case: when the subset is ready
        if (call.start == call.n)
        {
            if (cur_ind == k) {int i; for(i=0; i<k; i++) cout << cur_subset[i] << " "; cout << endl; cur_ind--;}

            // simulating the decrement of the cursor after the use current item call
            for (int i=k-1; i>0; i--) if (myStack.size() <= i) cur_ind--;

            continue;
        }

        // next call on the stack
        GenCall c1, c2;
        c1.a = call.a; c1.k = call.k; c1.n = call.n; c1.start = call.start;
        c2.a = call.a; c2.k = call.k; c2.n = call.n; c2.start = call.start;

        // use the current item
        if (call.remain > 0)
        {
            // append to the current subset
            cur_subset[cur_ind++] = a[call.start];

            // new call initialization
            c1.start = call.start + 1;
            c1.remain = call.remain - 1;
        }

        // ignore the current item
        if (call.n - call.start > call.remain)
        {
            // new call initialization
            c2.start = call.start + 1;
            c2.remain = call.remain;
        }

        // stack push control unit
        if (call.remain > 0 && call.n - call.start > call.remain)
        {
            myStack.push(c2); myStack.push(c1);
        }
        else if (call.remain > 0)
            myStack.push(c1);

        else if (call.n - call.start > call.remain)
            myStack.push(c2);
    }
}


int main()
{
    int a[]={1,3,5,8,10};
    int n=sizeof(a)/sizeof(a[0]), k=3;

    GenerateSubsetsIterative(a, k, n);
    return 0;
}
