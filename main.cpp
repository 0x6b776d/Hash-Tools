#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <Windows.h>
#include <ctime>
#include <stdio.h>
#include <conio.h>
#include <string>
#include <tchar.h>
#include <urlmon.h>
#include <random>
#include "sha512.hpp"
#include "md5.hpp"


using namespace std;

string hashedstring;


const char AlphabetLower[72] =
{
    'a', 'b', 'c', 'd', 'e', 'f', 'g',
    'h', 'i', 'j', 'k', 'l', 'm', 'n',
    'o', 'p', 'q', 'r', 's', 't', 'u',
    'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G',
    'H', 'I', 'J', 'K', 'L', 'M', 'N',
    'O', 'P', 'Q', 'R', 'S', 'T', 'U',
    'V', 'W', 'X', 'Y', 'Z', '1', '2', '3', '4', '5', '6', '7',
    '8', '9', '0', '!', '@', '#', '$', '%', '^', '&',
    '*', '(', ')'
};

class Color
{
public:
    Color(int desiredColor) {
        consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
        color = desiredColor;
    }

    friend ostream& operator<<(ostream& ss, Color obj) {
        SetConsoleTextAttribute(obj.consoleHandle, obj.color);
        return ss;
    }
private:
    int color;
    HANDLE consoleHandle;
    /*
    0 = black
    1 = blue
    2 = green?
    3 = light blue
    4 = red
    5 = purple
    6 = gold
    7 = white
    */
};

void currenttime() //should be a string with return value but lazy and not public
{
    time_t curr_time;
    curr_time = time(NULL);
    tm* tm_local = localtime(&curr_time);

    cout << Color(7) << "[" << tm_local->tm_hour << ":" << tm_local->tm_min << ":" << tm_local->tm_sec << "] ";
}

void printlogo()
{
    std::cout << Color(12) << R"(
 __    __                      __              ________                   __ 
/  |  /  |                    /  |            /        |                 /  |
$$ |  $$ |  ______    _______ $$ |____        $$$$$$$$/______    ______  $$ |
$$ |__$$ | /      \  /       |$$      \          $$ | /      \  /      \ $$ |
$$    $$ | $$$$$$  |/$$$$$$$/ $$$$$$$  |         $$ |/$$$$$$  |/$$$$$$  |$$ |
$$$$$$$$ | /    $$ |$$      \ $$ |  $$ |         $$ |$$ |  $$ |$$ |  $$ |$$ |
$$ |  $$ |/$$$$$$$ | $$$$$$  |$$ |  $$ |         $$ |$$ \__$$ |$$ \__$$ |$$ |
$$ |  $$ |$$    $$ |/     $$/ $$ |  $$ |         $$ |$$    $$/ $$    $$/ $$ |
$$/   $$/  $$$$$$$/ $$$$$$$/  $$/   $$/          $$/  $$$$$$/   $$$$$$/  $$/ 
                                                                        
        )";
    cout << "\n";
}

void Generatemd5(unsigned int length, std::string s)
{
    if (length == 0) // when length has been reached
    {
        if (md5(s) == hashedstring)
        {
            currenttime();
            cout << Color(7) << "Tried " << s << Color(2) << " [SUCCEEDED] \n";
            Sleep(99999999999999999);
        }
        else
        {
            currenttime();
            cout << Color(7) << "Tried " << s << Color(4) << " [FAILED] \n";
            return;
        }
    }

    for (unsigned int i = 0; i < 72; i++) // iterate through alphabet
    {
        // Create new string with next character
        // Call generate again until string has reached it's length
        std::string appended = s + AlphabetLower[i];
        Generatemd5(length - 1, appended);
    }
}

void Generatesha512(unsigned int length, std::string s)
{
    if (length == 0) // when length has been reached
    {
        if (sha512(s) == hashedstring)
        {
            currenttime();
            cout << Color(7) << "Tried " << s << Color(2) << " [SUCCEEDED] \n";
            Sleep(99999999999999999);
        }
        else
        {
            currenttime();
            cout << Color(7) << "Tried " << s << Color(4) << " [FAILED] \n";
            return;
        }
    }

    for (unsigned int i = 0; i < 72; i++) // iterate through alphabet
    {
        // Create new string with next character
        // Call generate again until string has reached it's length
        std::string appended = s + AlphabetLower[i];
        Generatesha512(length - 1, appended);
    }
}

void Crackmd5()
{
    while (1)
    {
        // Keep growing till I get it right
        static unsigned int stringlength = 1;
        Generatesha512(stringlength, "");
        stringlength++;
    }
}

void Cracksha512()
{
    while (1)
    {
        // Keep growing till I get it right
        static unsigned int stringlength = 1;
        Generatemd5(stringlength, "");
        stringlength++;
    }
}

void bruteforcesha512hash()
{
    system("cls");
    printlogo();
    cout << Color(7) << "Enter Hashed String: ";
    cin >> hashedstring;
    Cracksha512();
}

void bruteforcemd5hash()
{
    system("cls");
    printlogo();
    cout << Color(7) << "Enter Hashed String: ";
    cin >> hashedstring;
    Crackmd5();
}

void sha512options()
{
    string sha512choice;
    system("cls");
    printlogo();
    cout << Color(7) << "Choose Option" << endl;
    cout << Color(7) << "1) Hash String" << endl;
    cout << Color(7) << "2) Bruteforce Hash" << endl;
    cout << Color(7) << ">>";
    cin >> sha512choice;

    if (sha512choice == "1")
    {
        createsha512hash();
    }
    else if (sha512choice == "2")
    {
        bruteforcesha512hash();
    }
    else
    {
        cout << Color(4) << "Not an option, exiting";
        Sleep(2000);
        exit(1);
    }
}

void md5options()
{
    string md5choice;
    system("cls");
    printlogo();
    cout << Color(7) << "Choose Option" << endl;
    cout << Color(7) << "1) Hash String" << endl;
    cout << Color(7) << "2) Bruteforce Hash" << endl;
    cout << Color(7) << ">>";
    cin >> md5choice;

    if (md5choice == "1")
    {
        createmd5hash();
    }
    else if (md5choice == "2")
    {
        bruteforcemd5hash();
    }
    else
    {
        cout << Color(4) << "Not an option, exiting";
        Sleep(2000);
        exit(1);
    }
}

void choosehashingmethod()
{
    string choice;
    Sleep(400);
    cout << Color(7) << "Choose hashing method" << endl;
    cout << Color(7) << "1) SHA512" << endl;
    cout << Color(7) << "2) MD5" << endl;
    cout << Color(7) << ">>";
    cin >> choice;
    if (choice == "1")
    {
        Sleep(1000);
        sha512options();
    }
    else if (choice == "2")
    {
        Sleep(1000);
        md5options();
    }
    else
    {
        cout << Color(4) << "Not an option, exiting";
        Sleep(2000);
        exit(1);
    }
}


int main()
{
    SetPriorityClass(GetCurrentProcess(), HIGH_PRIORITY_CLASS);
    printlogo();
    choosehashingmethod();
}
