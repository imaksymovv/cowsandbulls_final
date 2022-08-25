#include <iostream>

struct CowsAndBullsAnswer {
    unsigned int cows;
    unsigned int bulls;
};

class IAskNumber {
public:
    virtual CowsAndBullsAnswer Ask(unsigned int number[4], unsigned int n[4]) const = 0;
};

class CowsAndBullsPlayer {
    CowsAndBullsPlayer() = delete;
protected:
    explicit CowsAndBullsPlayer(unsigned int n[4]) :
        number{ *n } {}
    unsigned int operator[](size_t index);
private:
    unsigned int number[4];
};

class CowsAndBullsComputerPlayer : private CowsAndBullsPlayer, public IAskNumber {
public:
    CowsAndBullsComputerPlayer(unsigned int n[4]) : CowsAndBullsPlayer(n) {
        for (int i = 0; i < 4; ++i) {
            n[i] = 1 + rand() % 9;
            for (int j = 0; j < i; j++)
                if (n[j] == n[i]) {
                    do {
                        n[i] = 1 + rand() % 9;
                    } while (n[i] == n[j]);
                }
        }
        for (int i = 0; i < 4; ++i) {
                std::cout << n[i];
        }
        std::cout << "\n";
    }
    CowsAndBullsAnswer Ask(unsigned int number[4], unsigned int n[4]) const override {
    std::cout << "try to guess computer number" << std::endl;
    CowsAndBullsAnswer counter = { };
    do {
        for (int i = 0; i < 4; i++) {
            std::cin >> number[i];
        }
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (number[i] == n[j]) {
                    counter.cows++;
                }
            }
        }
        for (int i = 0; i < 4; ++i) {
            if (number[i] == n[i]) {
                counter.bulls++;
            }

        }
        if (counter.bulls == 4) {
            break;
        }
        else {
            std::cout << "cows: " << counter.cows << "\n" << "bulls: " << counter.bulls << std::endl;
            counter.cows = 0;
            counter.bulls = 0;
        }
    } while (counter.bulls != 4);
    std::cout << "you guessed it! now its computer's turn to guess" << std::endl;
    return counter;
}
};

class CowsAndBullsLivePlayer : private CowsAndBullsPlayer, public IAskNumber {
public:
    CowsAndBullsLivePlayer(unsigned int n[4]) : CowsAndBullsPlayer(n) {
        std::cout << "Enter your number" << std::endl;
        for (int i = 0; i < 4; i++) {
            std::cin >> n[i];
        }
    }
    CowsAndBullsAnswer Ask(unsigned int number[4], unsigned int n[4]) const override {
        CowsAndBullsAnswer l = {};
        int turns_counter = 0;
        unsigned int result[4];
        int c = 0;
        do {

            do {
                for (int i = 0; i < 4; ++i) {
                    number[i] = rand() % 9;
                    turns_counter++;
                }
            } while (number[3] != n[3]);
            result[3] = number[3];

            do {
                for (int i = 0; i < 3; ++i) {
                    number[i] = rand() % 9;
                    turns_counter++;
                }
            } while (number[2] != n[2]);
            result[2] = number[2];

            do {
                for (int i = 0; i < 2; ++i) {
                    number[i] = rand() % 9;
                    turns_counter++;
                }
            } while (number[1] != n[1]);
            result[1] = number[1];

            do {
                for (int i = 0; i < 1; ++i) {
                    number[i] = rand() % 9;
                    turns_counter++;
                }
            } while (number[0] != n[0]);
            result[0] = number[0];
            c = 4;
        } while (c != 4);
        std::cout << "computer guessed ur number! it is:" << std::endl;
        for (int i = 0; i < 4; ++i) {
            std::cout << result[i];
        } std::cout << "\n";
        std::cout << turns_counter << " turns used to guess" << std::endl;
        return l;
    }
};

int main() {
    unsigned int computer_number[4];
    unsigned int player_guesses[4];
    unsigned int player_number[4];
    unsigned int computer_guesses[4];
    IAskNumber* a = new CowsAndBullsComputerPlayer(computer_number);
    a->Ask(player_guesses, computer_number);
    IAskNumber* b = new CowsAndBullsLivePlayer(player_number);
    b->Ask(computer_guesses, player_number);
    return 0;
}