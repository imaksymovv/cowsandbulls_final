#include <iostream>

struct CowsAndBullsAnswer {
    unsigned int cows;
    unsigned int bulls;
    unsigned int result[4];
    unsigned int turns_counter;
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
                        counter.cows++;
                    }
                }
            }
            for (int i = 0; i < 4; ++i) {
                if (number[i] == this->operator[](i)) {
                    counter.bulls++;
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
        CowsAndBullsAnswer l = {};
        l.turns_counter = 0;
        l.result;
        unsigned int result[4];
        int c = 0;
        do {

            do {
                for (int i = 0; i < 4; ++i) {
                    number[i] = rand() % 9;
                    l.turns_counter++;
                }
            } while (number[3] != this->operator[](3));
            l.result[3] = number[3];

            do {
                for (int i = 0; i < 3; ++i) {
                    number[i] = rand() % 9;
                    l.turns_counter++;
                }
            } while (number[2] != this->operator[](2));
            l.result[2] = number[2];

            do {
                for (int i = 0; i < 2; ++i) {
                    number[i] = rand() % 9;
                    l.turns_counter++;
                }
            } while (number[1] != this->operator[](1));
            l.result[1] = number[1];

            do {
                for (int i = 0; i < 1; ++i) {
                    number[i] = rand() % 9;
                    l.turns_counter++;
                }
            } while (number[0] != this->operator[](0));
            l.result[0] = number[0];
            c = 4;
        } while (c != 4);
        return l;
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
        answer.cows = answer.cows - answer.bulls;
        std::cout << "cows: " << answer.cows << " bulls: " << answer.bulls << std::endl;
        if (answer.bulls != 4) {
            answer.cows = 0;
            answer.bulls = 0;
        }
        else {
            exit = true;
        }
    } while (exit == false);
    std::cout << "you guessed it! now its computer's turn to guess" << std::endl;

    std::cout << "Enter your number" << std::endl;
    for (int i = 0; i < 4; i++) {
        std::cin >> n[i];
    }

    CowsAndBullsLivePlayer p2(n);
    auto computer_answer = p2.Ask(n);
    std::cout << "computer guessed ur number! it is:" << std::endl;
    for (int i = 0; i < 4; ++i) {
        std::cout << computer_answer.result[i];
    }
    std::cout << "\n";
    std::cout << computer_answer.turns_counter << " turns used to guess" << std::endl;
    return 0;
}