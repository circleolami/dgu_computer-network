/*
Program name: verifier.cpp
Info
- generator.cpp의 출력을 읽고 메시지가 올바른지 여부를 확인
*/

#include <iostream>
#include <string>

using namespace std;

// XOR 연산 수행 함수
string xor1(string a, string b)
{
    string result = "";
    int size = b.size();
    for (int i = 1; i < size; i++)
    {
        if (a[i] == b[i])
        {
            result += "0";
        }
        else
        {
            result += "1";
        }
    }
    return result;
}

// mod2 연산 수행 함수
string mod2div(string divident, string divisor)
{
    int pick = divisor.size();
    string tmp = divident.substr(0, pick);
    int n = divident.size();
    while (pick < n)
    {
        if (tmp[0] == '1')
        {
            tmp = xor1(divisor, tmp) + divident[pick];
        }
        else
        {
            string dummy(pick, '0');
            tmp = xor1(dummy, tmp) + divident[pick];
        }
        pick += 1;
    }
    if (tmp[0] == '1')
    {
        tmp = xor1(divisor, tmp);
    }
    else
    {
        string dummy(pick, '0');
        tmp = xor1(dummy, tmp);
    }
    return tmp;
}

// 데이터 검증 함수
void checkData(string data, string key)
{
    string remainder = mod2div(data, key);
    for (char i : remainder)
    {
        if (i != '0')
        {
            cout << "Error in data transmission" << endl; // 오류 발견 시 출력
            return;
        }
    }
    cout << "Data received correctly" << endl; // 데이터 정상 수신 시 출력
}

int main()
{
    string data, key;
    getline(cin, data); // 메시지 입력
    getline(cin, key);  // 다항식 입력
    checkData(data, key);
    return 0;
}
