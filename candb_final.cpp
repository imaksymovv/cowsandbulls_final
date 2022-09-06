#include <iostream>

struct CowsAndBullsAnswer {
    unsigned int cows;
    unsigned int bulls;
    unsigned int index_number[4];
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
        CowsAndBullsAnswer counter2 = {};
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                std::cout << "\n";
                std::cout << number[i] << " " << this->operator[](j) << std::endl;
                if (number[i] == this->operator[](j)) {
                    if (i == j) {
                        counter2.bulls++;
                        counter2.index_number[i] = 1;
                    }
                    else {
                        counter2.cows++;
                        counter2.index_number[i] = 2;
                    }
                }
            }
        }
        std::cout <<"cows: "<< counter2.cows << " bulls: " << counter2.bulls << std::endl;
        return counter2;
    }

    int CowsAndBullsComputerNumber(CowsAndBullsAnswer c, unsigned int number[4]) {
        unsigned int compairing[4];
        unsigned int result[4];

        for (int i = 0; i < 4; i++) {
            std::cout << c.index_number[i];
            if (c.index_number[i] == 2) {
                compairing[i] = number[i];
                for (int i = 0; i < 4; i++) {
                    for (int j = 0; j < 4; j++) {
                        if (this->operator[](j) == compairing[i]) {
                            compairing[i] = result[i];
                        }
                    }
                }
                
            }
        }
        return result[4];
    };
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
    exit = false;
    CowsAndBullsLivePlayer p2(n);
    do {
        int c = 0;
        for (int i = 0; i < 4; i++) {
            std::cout << n[i] << " ";
        }
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
        
        p2.CowsAndBullsComputerNumber(p2.Ask(n), n);
        c++;
        if (c == 2) {
            exit = true;
        }
    } while (!exit);
   /* std::cout << "computer guessed ur number! it is:" << std::endl;
    for (int i = 0; i < 4; ++i) {
        std::cout << computer_answer.result[i];
    }
    std::cout << "\n";
    std::cout << computer_answer.turns_counter << " turns used to guess" << std::endl;*/
    return 0;
}