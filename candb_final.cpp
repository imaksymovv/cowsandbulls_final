#include <iostream>

bool ContainsNumber(unsigned char n[4], unsigned char number) {
    return n[0] == number ||
           n[1] == number ||
           n[2] == number ||
           n[3] == number;
}

struct CowsAndBullsAnswer {
    unsigned char cows;
    unsigned char bulls;
};

class CowsAndBullsPlayer {
public:
    CowsAndBullsAnswer Ask(unsigned char number[4]) const {
        CowsAndBullsAnswer counter = { };
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (number[i] == this->number[j]) {
                    if (j == i) {
                        counter.bulls++;
                    }
                    else {
                        counter.cows++;
                    }
                }
            }
        }
        return counter;
    }
    unsigned int operator[](size_t index) const {
        return number[index];
    }
protected:
    explicit CowsAndBullsPlayer(unsigned char n[4]) :
        number{ n[0], n[1], n[2], n[3] } {}
private:
    CowsAndBullsPlayer() = delete;
    unsigned char number[4];
};

class CowsAndBullsComputerPlayer : public CowsAndBullsPlayer {
public:
    int computer_number(unsigned char n[4]) {
        unsigned short input = 0;
        for (int i = 0; i < 4; ++i) {
            input = 1 + rand() % 9;
            n[i] = input;
            for (int j = 0; j < i; j++) {
                if (n[j] == n[i]) {
                    do {
                        n[i] = 1 + rand() % 9;
                    } while (n[i] == n[j]);
                }
            }
        }
        return n[4];
    }

    explicit CowsAndBullsComputerPlayer(unsigned char n[4]) : CowsAndBullsPlayer(n) {}


};

class CowsAndBullsLivePlayer : public CowsAndBullsPlayer {
public:
    explicit CowsAndBullsLivePlayer(unsigned char n[4]) : CowsAndBullsPlayer(n) {}
};

int main() {
    srand(time(NULL));

    unsigned char n[4];
    unsigned short input = 0;

    for (int i = 0; i < 4; ++i) {
        input = 1 + rand() % 9;
        n[i] = input;
        for (int j = 0; j < i; j++) {
            if (n[j] == n[i]) {
                do {
                    n[i] = 1 + rand() % 9;
                } while (n[i] == n[j]);
            }
        }
    }
    CowsAndBullsLivePlayer p1(n);
    //std::cout << p1[0] << p1[1] << p1[2] << p1[3] << std::endl;

    std::cout << "try to guess computer number" << std::endl;
    bool exit = false;
    do {
        for (int i = 0; i < 4; i++) {
            std::cin >> input;
            n[i] = input;
        }

        auto answer = p1.Ask(n);
        std::cout << "cows: " << static_cast<unsigned short>(answer.cows) << " bulls: " << static_cast<unsigned short>(answer.bulls) << std::endl;
        if (answer.bulls != 4) {
            std::cout << "try again" << std::endl;
        }
        else {
            exit = true;
        }
    } while (!exit);
    std::cout << "you guessed it! now its computer's turn to guess" << std::endl;

    std::cout << "Enter your number" << std::endl;
    for (int i = 0; i < 4; i++) {
        std::cin >> input;
        n[i] = input;
    }
    for (size_t i = 0; i < 4; i++) {
        std::cout << static_cast<unsigned short>(n[i]);
    }
    int c = 0;
    CowsAndBullsComputerPlayer p2(n);
    p2.computer_number(n);
    auto answer = p2.Ask(n);
    return 0;
}