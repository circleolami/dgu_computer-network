/*
Program name: generator.cpp
Info
- input.txt의 첫 번째 줄은 n비트 메시지, 두 번째 줄은 k비트 다항식
- 표준 입력에서 ASCII 텍스트의 첫 번째 줄을 읽음
- 전송할 메시지를 나타내는 n+k개의 ASCII 텍스트를 표준 출력으로 출력
*/

#include <iostream>
#include <string>
#include <bitset>

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

// 데이터와 키를 인코딩하는 함수
void encodeData(string data, string key)
{
    int l_key = key.size();
    string appended_data = data + string(l_key - 1, '0');
    string remainder = mod2div(appended_data, key);
    string codeword = data + remainder;
    cout << codeword << endl;
    cout << key << endl;
}

int main()
{
    string data, key;
    getline(cin, data); // 메시지 입력
    getline(cin, key);  // 다항식 입력
    encodeData(data, key);
    return 0;
}
