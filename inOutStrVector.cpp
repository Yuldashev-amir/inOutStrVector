// inOutStringVector.cpp -- ��������� ������ ������������ ���� � ������
// �������� string, ��������� ��������� ���������� (�� �������!) � �����, �
// ����� �������� ���������� ����� ������� � ������ �������� string:
#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <cstring>
const char fileName[FILENAME_MAX] = "sstrings.txt";
void ShowStr(const std::string & str) { std::cout << str << std::endl; }

class Store
{
private:
    std::ofstream & out;
public:
    Store(std::ofstream & ft) : out(ft) { }
    ~Store() { std::cout << "Object Store is removed! " << std::endl; }

    void operator()(std::string & s)
    {
        size_t len = s.size();
        out.write(reinterpret_cast<const char*>(&len), sizeof(len));
        out.write(s.data(), len);
    }
};

void GetStr(std::ifstream & fin, std::vector<std::string> & vstr)
{
    while (fin.is_open())
    {
        size_t len;
        if (!fin.read(reinterpret_cast<char *>(&len), sizeof(len)))
            break;

        std::string temp(len, '\0');
        fin.read(&temp[0], len);
        vstr.push_back(temp);
    }
}

int main()
{
    using namespace std;
    vector<string> vostr;
    string temp;
    // �������� ������
    cout << "Enter strings (empty line to quit):\n";    // ������ �� ���� �����
    while (getline(cin, temp) && temp[0] != '\0')
        vostr.push_back(temp);

    cout << "Here is your input.\n";                    // ����� ��������� �����
    for_each(vostr.begin(), vostr.end(), ShowStr);

    // ��������� � �����
    ofstream fout(fileName, ios_base::out | ios_base::app | ios_base::binary);
    if (!fout.is_open())
    {
        std::cerr << "Could not open file for output 4.\n";
            // �� ������� ������� ���� ��� �����
        exit(EXIT_FAILURE);
    }
    cout << "Continue in file: \n";
    for_each(vostr.begin(), vostr.end(), Store(fout));
    for_each(vostr.begin(), vostr.end(), ShowStr);
    fout.close();

    // ������������ ���������� �����
    vector<string> vistr;
    ifstream fin(fileName, std::ios_base::in | std::ios_base::binary);
    GetStr(fin, vistr);


    cout << "\nHere are the strings read from the file:\n";
                    // ������, ����������� �� �����
    for_each(vistr.begin(), vistr.end(), ShowStr);

    fin.close();
    return 0;
}
