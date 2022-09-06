#include <iostream>

struct CowsAndBullsAnswer {
    unsigned int cows;
    unsigned int bulls;
};

class IAskNumber {
public:
    virtual CowsAndBullsAnswer Ask(unsigned int number[4]) const = 0;
};

class CowsAndBullsPlayer {
    CowsAndBullsPlayer() = delete;
protected:
    explicit CowsAndBullsPlayer(unsigned int n[4]) :
        number{ n[0], n[1], n[2], n[3] } {}
    unsigned int operator[](size_t index) const {
        return number[index];
    }
private:
    unsigned int number[4];
};

class CowsAndBullsComputerPlayer : private CowsAndBullsPlayer, public IAskNumber {
public:
    CowsAndBullsComputerPlayer(unsigned int n[4]) : CowsAndBullsPlayer(n) {}

    CowsAndBullsAnswer Ask(unsigned int number[4]) const override {
        CowsAndBullsAnswer counter = { };
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    if (number[i] == this->operator[](j)) {
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
        return CowsAndBullsPlayer::operator[](index);
    }
};

class CowsAndBullsLivePlayer : private CowsAndBullsPlayer, public IAskNumber {
public:
    CowsAndBullsLivePlayer(unsigned int n[4]) : CowsAndBullsPlayer(n) {}

    CowsAndBullsAnswer Ask(unsigned int number[4]) const override {
        CowsAndBullsAnswer counter = {};
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (number[i] == this->operator[](j)) {
                    if (i == j) {
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
};

int main() {
    srand(time(NULL));

    unsigned int n[4];

    for (int i = 0; i < 4; ++i) {
        n[i] = 1 + rand() % 9;
        for (int j = 0; j < i; j++) {
            if (n[j] == n[i]) {
                do {
                    n[i] = 1 + rand() % 9;
                } while (n[i] == n[j]);
            }
        }
    }
    CowsAndBullsComputerPlayer p1(n);
    std::cout << p1[0] << p1[1] << p1[2] << p1[3] << std::endl;

    std::cout << "try to guess computer number" << std::endl;
    bool exit = false;
    do {
        for (int i = 0; i < 4; i++) {
            std::cin >> n[i];
        }

        auto answer = p1.Ask(n);
        std::cout << "cows: " << answer.cows << " bulls: " << answer.bulls << std::endl;
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
        std::cin >> n[i];
    }
    int c = 0;
    exit = false;
    CowsAndBullsLivePlayer p2(n);
    auto answer = p2;
    do {
        for (int i = 0; i < 4; i++) {
            std::cout << n[i];
        }
        std::cout << "\n";
        for (int i = 0; i < 4; ++i) {
            n[i] = 1 + rand() % 9;
            for (int j = 0; j < i; j++) {
                if (n[j] == n[i]) {
                    do {
                        n[i] = 1 + rand() % 9;
                    } while (n[i] == n[j]);
                }
            }
        }
        c++;
    } while (c != 1 );
    return 0;
}