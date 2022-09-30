#include <iostream>
#include <stack>

using namespace std;

class Stack {
    int t;
public:
    Stack() { t = -1; }
    int arr[256];
    int pop();
    bool push(int a);
};
bool Stack::push(int a)
{
    if (t >= 256) {
        cout << "Stack Overflow";
        return false;
        return 0;
    }
    else {
        arr[++t] = a;
        return true;
    }
}
int Stack::pop()
{
    if (t < 0) {
        cout << "Stack Underflow";
        return 0;
    }
    else {
        int a = arr[t--];
        return a;
    }
}
int main() {
    Stack st;

    int n, a, bfmin = 0, pe, func;
    bool repeat = true;

    cout << "Enter number of elements: ";
    cin >> n;
    if (n > 256) {
        cout << "Error: Stack overflow" << endl;
        system("pause");
        return 0;
    }

    int i = 0;
    cout << "Enter elements of stack: " << endl;

    while (i != n) {
        cout << "Elemnt " << i + 1 << " is: ";
        cin >> a;
        st.push(a);
        i++;

    }
    cout << "The stack contains:" << n << " elements" << endl;
    for (int i = n - 1; i >= 0; i--)
        cout << st.arr[i] << " ";
    int max = st.arr[0];
    for (int i = 1; i < n; i++)
    {
        if (st.arr[i] > max)
            max = st.arr[i];

    }
    cout << endl << "The maximum element is " << max << endl;
    int min = st.arr[0];
    for (int i = 0; i < n; i++)
    {
        if (st.arr[i] < min)
        {
            min = st.arr[i];
            bfmin = i - 1;
        }
    }
    cout << "The minimum element is " << min;
    cout << ", and the element before the minimum is " << st.arr[bfmin] << endl;
    if (n < 4) {
        cout << "error there is no four elements" << endl;

    }
    cout << "fourth element is : " << st.arr[3] << endl;
    do
    {
        cout << "********************* \n";
        cout << "1.Add element \n" << "2.Delet last element \n" << "3.Exit\n";
        cin >> func;
        cout << endl;
        switch (func) {
        case 1:
            for (i = n; i < n+1 ; i++)
            {
                cin >> a;
                st.push(a);
            }
            n++;
            cout << "Now stack is:";
            for (int i = n-1; i >= 0; i--)
                cout << st.arr[i] << " ";
            break;
        case 2:
            for (i = n; i < n; i--)
            {
                st.pop();

            }
            n--;
            cout << "Now stack is:";
            for (int i = n; i >= 0; i--)
                cout << st.arr[i] << " ";
            break;
        case 3:
            return 0;

        }
        cout << "Use the progrem one more time? \n 0.NO \n 1.YES \n";
        cin >> repeat;
    } while (repeat);
     cout << "Lets make our stack empty" << endl;
    while (!st.pop())
    {
        st.pop();
    }
    return 0;
}
