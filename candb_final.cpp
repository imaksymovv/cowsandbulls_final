#include <iostream>

struct CowsAndBullsAnswer {
    unsigned char cows;
    unsigned char bulls;
};

struct CowsAndBullsComputerHelper {
    unsigned char computer[4];
};

class CowsAndBullsPlayer {
public:
    CowsAndBullsAnswer Ask(unsigned char num[4]) const {
        CowsAndBullsAnswer counter = { };
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (num[i] == this->number[j]) {
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
     CowsAndBullsComputerHelper computer_number() {
         CowsAndBullsComputerHelper r = {};
        for (int i = 0; i < 4; ++i) {
            r.computer[i] = 1 + rand() % 9;
            for (int j = 0; j < i; j++) {
                if (r.computer[j] == r.computer[i]) {
                    do {
                        r.computer[i] = 1 + rand() % 9;
                    } while (r.computer[i] == r.computer[j]);
                }
            }
        }
        return r;
    }

     CowsAndBullsComputerHelper computer_guessing(CowsAndBullsAnswer k, CowsAndBullsComputerHelper r) {
         if (k.bulls == 0) {
             for (int i = 0; i < 4; ++i) {
                 r.computer[i] = 1 + rand() % 9;
                 for (int j = 0; j < i; j++) {
                     if (r.computer[j] == r.computer[i]) {
                         do {
                             r.computer[i] = 1 + rand() % 9;
                         } while (r.computer[i] == r.computer[j]);
                     }
                 }
             }
             return r;
         }
         else {
             //for (size_t i = 0; i < 4; i++) {
               //  memory[i] = r.computer[i];
             //}
             k.bulls = 4;
         }
         /*if (b == 0) {
             b = k.bulls;
         }
         if (k.bulls < b) {
             t.result[i] = t.memory[i];
         }
         if (k.bulls > b) {
             t.result[i] = t.computer[i];
         }
         i++;*/
         return r;
     }

    explicit CowsAndBullsComputerPlayer(unsigned char n[4]) : CowsAndBullsPlayer(n) {}

private:
    unsigned char b = 0;
    unsigned char memory[4];
    unsigned char c = 0;
    //int i = -1;
};

class CowsAndBullsLivePlayer : public CowsAndBullsPlayer {
public:
    explicit CowsAndBullsLivePlayer(unsigned char n[4]) : CowsAndBullsPlayer(n) {}
};

int main() {
    srand(time(NULL));
    CowsAndBullsAnswer p = {};
    CowsAndBullsComputerHelper t = {};
    unsigned char n[4];
    unsigned short input = 0;
    unsigned char guess[4];
    unsigned char answer[4];
    constexpr unsigned char o = 1;

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
    CowsAndBullsComputerPlayer p1(n);
    std::cout << p1[0] << p1[1] << p1[2] << p1[3] << std::endl;

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
    CowsAndBullsLivePlayer p2(n);
    exit = false;
    
    do{
        t = p1.computer_guessing(p, t);
        p = p2.Ask(t.computer);
    } while (p.bulls != 4);
    /*do {
      t = p1.computer_number();
      p = p2.Ask(t.computer);
    } while (p.bulls == 0);
    for (size_t i = 0; i < 4; i++) {
        t.memory[i] = t.computer[i];//memory внутри компьютера
    }
    int j = 0;
    do {
        t = p1.computer_guessing(p, t);
        for (size_t i = 0; i < 4; i++) {
            t.computer[i] = t.memory[i];
        }
        t.computer[j] = o;
        p = p2.Ask(t.computer);
        j++;
    } while (j != 4);
    for (size_t i = 0; i < 4; i++) {
        std::cout << static_cast<short>(t.result[i]);
    }*/
    return 0;
}