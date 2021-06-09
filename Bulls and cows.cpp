#include <iostream>
#include <cstdlib>
#include <random>
#include <chrono>

class Number {
private:
    std::mt19937 generator;
public:
    int len = rand() % 9;
    char* number = nullptr;
    Number() :
        generator((unsigned int)std::chrono::system_clock::now().time_since_epoch().count())
    {
        //int len = rand()%9;
        //std::cout<<len<<std::endl;
        number = new char[len + 1];
        for (int i = 0; i < len; i++) {
            char symb = (48 + generator() % 10);
            while (!(CheckSymbol(number, symb))) {
                symb = (48 + generator() % 10);
            }
            number[i] = symb;
        }
        number[len] = '\0';     // А в code::blocks не надо было это писать
        std::cout << "Generated number: " << number << std::endl;
    }
    // Проврека на повторяющееся число
    bool CheckSymbol(char* str, char symbol) {
        for (int j = 0; str[j] != '\0'; j++) {   // j < len ??
            if (str[j] == symbol) {
                return false;
            }
        }
        return true;
    }


};

class Game {
    //Number *n_ptr;
    int cows = 0;
    int bulls = 0;
    bool isFinish;
public:
    Game(Number* n_ptr) {
        char* str_ = n_ptr->number;
        isFinish = false;
        cows = 0; bulls = 0;
        char* user = new char[n_ptr->len + 1];
        while (!isFinish) {
            Enter(user);
            CheckString(n_ptr, user);
            if (bulls == (n_ptr->len)) {
                std::cout << "\t\t\tRIGHT";
                break;
            }
            if (CheckUser(user)) {
                std::cout << "repeated numbers";
                break;
            }
            std::cout << '\t' << bulls << '\t' << '\t' << cows << std::endl;
            cows = 0; bulls = 0;
        }
        //std::cout<<user;
    }

    void Enter(char* user_str) {
        std::cin >> user_str;
    }

    bool CheckUser(char* user_) {
        bool repeat = false;
        for (int i = 0; user_[i] != '\0'; i++) {
            for (int j = i + 1; user_[j] != '\0'; j++) {
                if (user_[i] == user_[j])
                    repeat = true;
            }
        }
        return repeat;
    }
    void CheckString(Number* ptr, char* user_) {
        char* string_ = ptr->number;
        bool isBull = false;
        for (int j = 0; string_[j] != '\0'; j++) {
            if (string_[j] == user_[j]) {
                isBull = true;
                ++bulls;
                cows--;
            }
        }

        for (int i = 0; string_[i] != '\0'; i++) {
            for (int j = 0; user_[j] != '\0'; j++) {
                if (user_[i] == string_[j]) {
                    cows++;
                }
            }
        }
    }


};

class Interface {


};

int main()
{
    Number* num = new Number;
    std::cout << '\t' << "Bykov: " << '\t' << '\t' << "Korov:" << std::endl;
    Game gm(num);

    return 0;
}
