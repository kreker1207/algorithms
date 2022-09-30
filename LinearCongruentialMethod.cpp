#include <iostream> 
#include <vector> 
#include <bitset>
const int m = 16;
using namespace std;

// Function to generate random numbers 
void linearCongruentialMethod(int Xo, int m, int a, int c,vector<int>& randomNums,int noOfRandomNums)
{

    // Initialize the seed state 
    randomNums[0] = Xo;

    // Traverse to generate required 
    // numbers of random numbers 
    for (int i = 1; i < noOfRandomNums; i++) {
        // Follow the linear congruential method 
        randomNums[i] = ((randomNums[i - 1] * a) + c) % m;
    }
}
void print_num(int32_t value)
{
    cout << "Binary code is:  "<< bitset<32>(value) << "\n";
}


int flipBit(unsigned a)
{
    /* If all bits are l, binary representation
       of 'a' has all 1s */
    if (~a == 0)
        return 8 * sizeof(int);
    
    int currLen = 0, prevLen = 0, maxLen = 0;
    while (a != 0)
    {
        // If Current bit is a 1 then increment currLen++
        if ((a & 1) == 1) {
            currLen++;
           
        }
        // If Current bit is a 0 then check next bit of a
        else if ((a & 1) == 0)
        {
            /* Update prevLen to 0 (if next bit is 0)
            or currLen (if next bit is 1). */
            prevLen = (a & 2) == 0 ? 0 : currLen;

            // If two consecutively bits are 0
            // then currLen also will be 0.
            currLen = 0;
        }

        // Update maxLen if required
        maxLen = max(prevLen + currLen, maxLen);

        // Remove last bit (Right shift)
        a >>= 1;
    }

    // We can always have a sequence of
    // at least one 1, this is fliped bit
    return currLen;
}


// Driver Code 
int main()
{
    int test=0;
    int Xo; // Seed value 
    int m; // Modulus parameter 
    int a; // Multiplier term 
    int c; // Increment term 
   

    // Number of Random numbers 
    // to be generated 
    int noOfRandomNums;
    cout << "Enter number of elements" << endl;
    cin >> noOfRandomNums;
    if (noOfRandomNums > 256) { cout << "Error" << endl; return 0; }
    cout << "Enter Seed value" << endl;
    cin >> Xo;
    cout << "Enter Multiplier term " << endl;
    cin >> a;
    cout << "Enter Increment term " << endl;
    cin >> c;
    cout << "Enter Modulus parameter " << endl;
    cin >> m;
    // To store random numbers 
    vector<int> randomNums(
        noOfRandomNums);
  

    // Function Call 
    linearCongruentialMethod(
        Xo, m, a, c,
        randomNums, noOfRandomNums);

    // Print the generated random numbers 
    for (int i = 0; i < noOfRandomNums; i++) {
        cout << randomNums[i] << " ";
       
    }
    cout << endl << "*******************" << endl;
    for (int i = 0; i < noOfRandomNums; i++) {
        print_num(randomNums[i]);
    }
    cout << endl << "*******************" << endl;
    for (int i = 0; i < noOfRandomNums; i++) {
       
        cout << flipBit(randomNums[i])<<" "; 
    }
    for (int i = 0; i < noOfRandomNums; i++) {
    test = test + flipBit(randomNums[i]);
    
    }
    cout << test;
    if (test<=(m/2)) {
        cout << "Frequence is random";
    }
    else { cout << "Frequence is not random"; }
    return 0;
}
