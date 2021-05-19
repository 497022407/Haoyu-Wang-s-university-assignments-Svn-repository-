//====================================
// Algorithm & Data Structure Analysis
// Student: Haoyu Wang
// Student ID: a1785394
// Semester: 2
// Year: 2020
// Assignment: 1
// Partner: Chun Yee Herman Lai (a1797912)
//=====================================

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <cstdlib>
/*
* void setL0();
void sets0();
int fullAdd(int a, int b);
void toArray();
void printArray();
int schoolAdd(int a[101], int b[101]);
int add(int a[101]);
void print(int a[50]);
void split(int size1, int size2);
int getSize(int a[101]);
int schoolAdd50(int a[50], int b[50]);
int add50(int a[50]);
void setArray0(int a[100]);

template<class T>

int length(T& arr)
{
    //cout << sizeof(arr[0]) << endl;
    //cout << sizeof(arr) << endl;
    return sizeof(arr) / sizeof(arr[0]);
}

int L1[101], L2[101], s[101], L1h[50], L1l[50], L2h[50], L2l[50];
int l1, l2, c, B;
*/
using namespace std;

vector<int> karatsuba(vector<int> I1, vector<int> I2, int B);
void printVector(vector<int> v);
vector<int> schoolAdd(vector<int> I1, vector<int> I2, int B);
vector<int> subtraction(vector<int> I1, vector<int> I2, int B);
vector <int> schoolMul(vector<int> I1, vector<int> I2, int B);
vector<int> changeBase(int i, int B);

vector<int> karatsuba(vector<int> I1, vector<int> I2, int B) {
    vector<int> al, ah, bl, bh, c0, c1, c2, p0, p1, p2, p3, p4, karatsubaMul;
    int size = max(I1.size(), I2.size());
    if (size = 3) {
        return schoolMul(I1, I2, B);
    }
    else {
        int halfSize = ceil(size / 2);

        if (I1.size() <= halfSize) {
            ah.push_back(0);
            al = I1;
        }
        else {
            for (int i = 0; i < I1.size() - halfSize; i++) {
                ah.push_back(I1[i]);
                reverse(ah.begin(), ah.end());
            }
            for (int i = halfSize; i < I1.size(); i++) {
                al.push_back(I1[i]);
                reverse(al.begin(), al.end());
            }
        }

        if (I2.size() <= halfSize) {
            bh.push_back(0);
            bl = I2;
        }
        else {
            for (int i = 0; i < I2.size() - halfSize; i++) {
                bh.push_back(I2[i]);
                reverse(bh.begin(), bh.end());
            }
            for (int i = halfSize; i < I2.size(); i++) {
            }
        }

        c0 = karatsuba(al, ah, B);
        c1 = karatsuba(subtraction(al, ah, B), subtraction(bl, bh, B), B);
        c2 = karatsuba(ah, bh, B);
        p0 = schoolMul(c2, changeBase(int(pow(B, 2 * halfSize)), B), B);
        p1 = schoolAdd(p0, c0, B);
        p2 = schoolAdd(p1, c2, B);
        p3 = subtraction(p2, c1, B);
        p4 = schoolMul(p3, changeBase(int(pow(B, halfSize)), B), B);

        karatsubaMul = schoolAdd(p4, c0, B);
    }
    return karatsubaMul;
}

void printVector(vector<int> v) {
    for (int i = 0; i < v.size(); i++) {
        cout << v[i];
    }
}

vector<int> schoolAdd(vector<int> I1, vector<int> I2, int B) {
    while (I1.size() > I2.size()) {
        I2.insert(I2.begin(), 0);
    }
    while (I2.size() > I1.size()) {
        I1.insert(I1.begin(), 0);
    }

    int carry = 0;
    vector<int> sum;

    for (int i = I1.size() - 1; i >= 0; i--) {
        if (I1[i] + I2[i] + carry >= B) {
            sum.insert(sum.begin(), I1[i] + I2[i] + carry - B);
            carry = 1;
        }
        else {
            sum.insert(sum.begin(), I1[i] + I2[i] + carry);
            carry = 0;
        }
    }

    if (carry == 1) {
        sum.insert(sum.begin(), 1);
    }
    return sum;
}

vector<int> subtraction(vector<int> I1, vector<int> I2, int B) {
    while (I1.size() > I2.size()) {
        I2.insert(I2.begin(), 0);
    }
    while (I2.size() > I1.size()) {
        I1.insert(I1.begin(), 0);
    }

    int carry = 0;
    vector<int> sub;

    for (int i = I1.size() - 1; i >= 0; i--) {
        if (I1[i] - I2[i] - carry < 0) {
            sub.insert(sub.begin(), I1[i] - I2[i] - carry + B);
            carry = 1;
        }
        else {
            sub.insert(sub.begin(), I1[i] - I2[i] - carry);
            carry = 0;
        }
    }

    if (carry == 1) {
        sub.insert(sub.begin(), 1);
    }
    return sub;
}

vector <int> schoolMul(vector<int> I1, vector<int> I2, int B) {
    vector<int> part, mul;
    int carry;
    for (int i = I2.size() - 1; i >= 0; i--) {
        carry = 0;
        for (int j = I1.size() - 1; j >= 0; j--) {
            if (I1[j] * I2[i] + carry >= B) {
                part.insert(part.begin(), (I1[j] * I2[i] + carry) % B);
                carry = (((I1[j] * I2[i] + carry) -
                    (I1[j] * I2[i] + carry) % B) / B);
            }
            else {
                part.insert(part.begin(), I1[j] * I2[i] + carry);
                carry = 0;
            }
        }
        if (carry != 0) {
            part.insert(part.begin(), carry);
        }

        for (int n = I2.size() - 1; n > i; n--) {
            part.push_back(0);
        }

        mul = schoolAdd(part, mul, B);
        part.clear();
    }
    return mul;
}

vector<int> changeBase(int i, int B) {
    vector<int> v;
    for (; i > 0; i /= B) {
        v.insert(v.begin(), i % B);
    }
    return v;
}

/*
int main()
{
    cin >> l1 >> l2 >> B;
    int p1 = 0, p2 = 0, p3 = 0;

    setL0();
    sets0();

    toArray();

    cout << schoolAdd(L1, L2) << endl;

    int sizeL1 = getSize(L1);
    int sizeL2 = getSize(L2);
    split(sizeL1, sizeL2);
    print(L1h);
    cout << " ";
    print(L1l);
    cout << endl;
    print(L2h);
    cout << " ";
    print(L2l);
    cout << endl;
    cout << schoolAdd50(L1h, L1l);
}
*/

int main() {
    vector<int> I1, I2;
    int B, count=0;
    string input, temp;
    getline(cin, temp); 
    stringstream s(temp); 

    while (s >> input) {
        if (count == 0) {
            for (int i = 0; i < input.size(); i++) {
                I1.push_back(input[i] - 48); 
            }
        }
        else if (count == 1) {    
            for (int i = 0; i < input.size(); i++) {
                I2.push_back(input[i] - 48);
            }
        }
        else if (count == 2) {  
            B = stoi(input);
        }
        count++;
    }

    printVector(schoolAdd(I1, I2, B));
    cout << " ";
    printVector(karatsuba(I1, I2, B));
    return 0;
}

/*
void split(int size1, int size2)
{
    for (int i = 0; i < size1/2; i++)
    {
        L1l[i] = L1[i];
    }
    for (int i = 0; i < size2 / 2; i++)
    {
        L2l[i] = L2[i];
    }
    int y = 0;
    for (int i = size1 / 2; i <= size1; i++)
    {
        L1h[y] = L1[i];
        y++;
    }
    y = 0;
    for (int i = size2/2; i <= size2; i++)
    {
        L2h[y] = L2[i];
        y++;
    }
}

int getSize(int a[101])
{
    for (int i = 100; i >= 0; i--)
    {
        if (a[i]!=0)
        {
            cout << i << endl;
            return i;
        }
    }
}

int schoolAdd50(int a[50], int b[50]) // School Method for Integer Addition
{
    int c = 0;
    int s0[51];
    setArray0(s0);
    for (int i = 0; i < 50; i++)
    {
        s0[i] = fullAdd(a[i], b[i]);
    }
    s0[51];
return add50(s0);
}

int add50(int a[51])
{
    int sum = 0;
    for (int i = 0; i < 50; i++)
    {
        sum += pow(10, i) * a[i];
    }
    return sum;
}

int schoolAdd(int a[101], int b[101]) // School Method for Integer Addition
{
    int c = 0;
    for (int i = 0; i < 101; i++)
    {
        s[i] = fullAdd(a[i], b[i]);
    }
    return add(s);
}

int add(int a[101])
{
    int sum = 0;
    for (int i = 0; i < 101; i++)
    {
        sum += pow(10, i) * a[i];
    }
    return sum;
}

int fullAdd(int a, int b)
{
    int sum = (c + a + b + B) % B;
    c = (c + a + b) / B;
    return sum;
}

void setL0()
{
    for (int i = 0; i < 101; i++)
    {
        L1[i] = 0;
        L2[i] = 0;
    }
}

void sets0()
{
    for (int i = 0; i < 101; i++)
    {
        s[i] = 0;
    }
}

void toArray()
{
    for (int i = 0; i < 101; i++)
    {
        L1[i] = l1 % B;
        l1 /= 10;
        L2[i] = l2 % B;
        l2 /= 10;
    }
}

void printArray()
{
    cout << L1[3] << " " << L1[2] << " " << L1[1] << " " << L1[0] << endl;
    cout << L2[3] << " " << L2[2] << " " << L2[1] << " " << L2[0] << endl;
}

void prints()
{
    cout << endl << s[4] << " " << s[3] << " " << s[2] << " " << s[1] << " " << s[0] << endl;
}

void print(int a[50])
{
    for (int i = 9; i >= 0; i--)
    {
        cout << a[i] << " ";
    }
}

void setArray0(int a[100])
{
    for (int i = 0; i < length(a); i++)
    {
        a[i] = 0;
    }
}
*/