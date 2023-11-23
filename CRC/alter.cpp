/*
Program name: alter.cpp
Info
- 첫 번째 줄에서 하나의 비트를 반대로 바꾸고, 나머지 두 줄을 복사
*/

#include <iostream>
#include <string>

using namespace std;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        cerr << "Usage: " << argv[0] << " <bit_position>" << endl;
        return 1;
    }

    int position = stoi(argv[1]); // 변경할 비트 위치
    string data, key;
    getline(cin, data); // 메시지 입력
    getline(cin, key);  // 다항식 입력

    if (position < 1 || position > data.size())
    {
        cerr << "Error: Bit position out of range" << endl; // 범위 오류 시 출력
        return 1;
    }

    // 지정된 위치의 비트 반전
    data[position - 1] = data[position - 1] == '0' ? '1' : '0';
    cout << data << endl; // 수정된 데이터 출력
    cout << key << endl;  // 다항식 출력

    return 0; // 프로그램 정상 종료
}
