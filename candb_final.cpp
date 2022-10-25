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
     CowsAndBullsComputerHelper computer_guessing(CowsAndBullsAnswer k) {
         CowsAndBullsComputerHelper r;
         for (size_t i = 0; i < 4; i++) {
            r.computer[i] = previous.computer[i];
         }
         if (end == true) {
             if (k.bulls >= 1) {
                 end = false;
                 for(size_t i = 0; i < 4; i++){
                     substitute = 1 + rand() % 9;
                     for (int j = 0; j < 4; j++) {
                         if (substitute == r.computer[j]) {
                             i--;
                             break;
                         }
                     }
                 }
                 return r;
             }
             for (int i = 0; i < 4; ++i) {
                 r.computer[i] = 1 + rand() % 9;
                 for (int j = 0; j < i; j++) {
                     if (r.computer[j] == r.computer[i]) {
                         i--;
                         break;
                     }
                 }
             }
             for (size_t i = 0; i < 4; i++) {
                 memory[i] = r.computer[i];
             }
             for (size_t i = 0; i < 4; i++) {
                 previous.computer[i] = r.computer[i];
             }
             return r;
         }
         if (i != 4) {
             if (b == 0) {
                 b = k.bulls;
             }
             if (k.bulls < b) {
                 checking[i] = memory[i];
                 index[i] = 1;
             }
             if (k.bulls > b) {
                 checking[i] = r.computer[i];
                 index[i] = 1;
             }
             for (size_t i = 0; i < 4; i++) {
                 r.computer[i] = memory[i];
             }
             i++;
             if (i == 4) {
                 for (size_t i = 0; i < 4; i++) {
                     if (index[i] == 1) {
                         r.computer[i] = checking[i];
                         for (size_t j = 0; j < i; j++) {
                             if (r.computer[i] == r.computer[j]) {
                                 do {
                                     r.computer[j] = 1 + rand() % 9;
                                 } while (r.computer[i] == r.computer[j]);
                             }
                         }
                     }
                     else {
                         r.computer[i] = 1 + rand() % 9;
                         for (size_t j = 0; j < i; j++) {
                             if (r.computer[i] == r.computer[j]) {
                                 i--;
                                 break;
                             }
                         }
                     }
                 }
                 for (size_t i = 0; i < 4; i++) {
                     memory[i] = r.computer[i];
                 }
                 for (size_t i = 0; i < 4; i++) {
                     substitute = 1 + rand() % 9;
                     for (int j = 0; j < 4; j++) {
                         if (substitute == r.computer[j]) {
                             i--;
                             break;
                         }
                     }
                 }
                 for (size_t i = 0; i < 4; i++) {
                     previous.computer[i] = r.computer[i];
                 }
                 return r;
             }
             r.computer[i] = substitute;     
         }
         else {
             if (end1 == false) {
                 b = k.bulls;
                 end1 = true;
             }
             if (k.bulls > b) {
                 bull_founded = true;
                 b = k.bulls;
                 substitution = false;
                 start = false;
                 for (size_t i = 0; i < 4; i++) {
                     memory[i] = r.computer[i];
                 }
             }
             if (bull_founded == true) {
                 if (i2 == -1) {
                     b1 = k.bulls;
                     for (size_t i = 0; i < 4; i++) {
                         substitute = 1 + rand() % 9;
                         for (int j = 0; j < 4; j++) {
                             if (substitute == r.computer[j]) {
                                 i--;
                                 break;
                             }
                         }
                     }
                 }
                 for (size_t i = 0; i < 4; i++) {
                     r.computer[i] = memory[i];
                 }
                 if (k.bulls < b1) {
                     checking[i2] = r.computer[i2];
                     index[i2] = 1;
                 }
                 if (k.bulls > b1) {
                     checking[i2] = substitute;
                     index[i2] = 1;
                 }
                 i2++;
                 if (i2 == 4) {
                     for (size_t i = 0; i < 4; i++) {
                         if (index[i] == 1) {
                             r.computer[i] = checking[i];
                             for (size_t j = 0; j < i; j++) {
                                 if (r.computer[i] == r.computer[j]) {
                                     do {
                                         r.computer[j] = 1 + rand() % 9;
                                     } while (r.computer[i] == r.computer[j]);
                                 }
                             }
                             for (size_t i = 0; i < 4; i++) {
                                 if (index[i] != 1) {
                                     for (size_t j = 0; j < 4; j++) {
                                         if (i != j) {
                                             while (r.computer[i] == r.computer[j]) {
                                                 r.computer[i] = 1 + rand() % 9;
                                             }
                                         }
                                     }
                                 }
                             }
                         }
                         else {
                             r.computer[i] = 1 + rand() % 9;
                             for (size_t j = 0; j < i; j++) {
                                 if (r.computer[i] == r.computer[j]) {
                                     i--;
                                     break;
                                 }
                             }
                         }
                     }
                     for (size_t i = 0; i < 4; i++) {
                         memory[i] = r.computer[i];
                     }
                     for (size_t i = 0; i < 4; i++) {
                         substitute = 1 + rand() % 9;
                         for (int j = 0; j < 4; j++) {
                             if (substitute == r.computer[j]) {
                                 i--;
                                 break;
                             }
                         }
                     }
                     bull_founded = false;
                     i2 = -1;
                     for (size_t i = 0; i < 4; i++) {
                         previous.computer[i] = r.computer[i];
                     }
                     return r;
                 }
                 r.computer[i2] = substitute;
                 for (size_t i = 0; i < 4; i++) {
                     previous.computer[i] = r.computer[i];
                 }
                 return r;
             }
             if (k.cows > 0) {
                 start = true;
             }
             if (substitution == true) {
                 for (size_t i = 0; i < 4; i++) {
                     r.computer[i] = memory[i];
                 }
                 j++;
                 if (j == 4) {
                     j = -1;
                     substitution = false;
                     for (size_t i = 0; i < 4; i++) {
                         previous.computer[i] = r.computer[i];
                     }
                     return r;
                 }
                 r.computer[j] = cows_checker;
                 for (size_t i = 0; i < 4; i++) {
                     previous.computer[i] = r.computer[i];
                 }
                 return r;
             }
             if (start == true) {
                 if (j1 == -1) {
                     c1 = k.cows;
                 }
                 for (size_t i = 0; i < 4; i++) {
                     r.computer[i] = memory[i];
                 }
                 if (c1 > k.cows) {
                     cows_checker = memory[j1];
                     for (size_t i = 0; i < 4; i++) {
                         memory[j1] = 1 + rand() % 9;
                         for (int j = 0; j < 4; j++) {
                             if (memory[j1] == r.computer[j]) {
                                 i--;
                                 break;
                             }
                         }
                     }
                     j1 = 0;
                     start = false;
                     substitution = true;
                     for (size_t i = 0; i < 4; i++) {
                         previous.computer[i] = r.computer[i];
                     }
                     return r;
                 }
                 j1++;
                 if (j1 == 4) {
                     j1 = 0;
                     start = false;
                     c = 0;
                     for (size_t i = 0; i < 4; i++) {
                         previous.computer[i] = r.computer[i];
                     }
                     return r;
                 }
                 r.computer[j1] = substitute;
                 for (size_t i = 0; i < 4; i++) {
                     previous.computer[i] = r.computer[i];
                 }
                 return r;
             }

             if(k.cows == 0 && bull_founded == false) {
                 for (size_t i = 0; i < 4; i++) {
                     if (index[i] == 1) {
                         r.computer[i] = checking[i];
                         for (size_t j = 0; j < i; j++) {
                             if (r.computer[i] == r.computer[j]) {
                                 do {
                                     r.computer[j] = 1 + rand() % 9;
                                 } while (r.computer[i] == r.computer[j]);
                             }
                         }
                         for (size_t i = 0; i < 4; i++) {
                             if (index[i] != 1) {
                                 for (size_t j = 0; j < 4; j++) {
                                     if (i != j) {
                                         while (r.computer[i] == r.computer[j]) {
                                             r.computer[i] = 1 + rand() % 9;
                                         }
                                     }
                                 }
                             }
                         }
                     }
                     else {
                         r.computer[i] = 1 + rand() % 9;
                         for (size_t j = 0; j < i; j++) {
                             if (r.computer[i] == r.computer[j]) {
                                 i--;
                                 break;
                             }
                         }
                     }
                 }
                 for (size_t i = 0; i < 4; i++) {
                      substitute = 1 + rand() % 9;
                      for (int j = 0; j < 4; j++) {
                          if (substitute == r.computer[j]) {
                              i--;
                              break;
                          }
                      }
                 }
                 for (size_t i = 0; i < 4; i++) {
                     memory[i] = r.computer[i];
                 }
             }
         }
         for (size_t i = 0; i < 4; i++) {
             previous.computer[i] = r.computer[i];
         }
         return r;
     }

    explicit CowsAndBullsComputerPlayer(unsigned char n[4]) : CowsAndBullsPlayer(n) {}

private:
    unsigned char b = 0;
    unsigned char b1 = 0;
    unsigned char memory[4];
    unsigned char checking[4];
    unsigned char index[4];
    unsigned char cows_checker;
    CowsAndBullsComputerHelper previous;
    unsigned char c = 0;
    unsigned char c1 = 0;
    bool end = true;
    bool end1 = false;
    bool start = false;
    bool substitution = false;
    bool bull_founded = false;
    bool cow_added = false;
    unsigned char substitute = 0;
    int i = -1;
    int j = -1;
    int i1 = 0;
    int j1 = -1;
    int i2 = -1;
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

    for (int i = 0; i < 4; ++i) {
        input = 1 + rand() % 9;
        n[i] = input;
        for (int j = 0; j < i; j++) {
            if (n[j] == n[i]) {
                i--;
                break;
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
    do {
        t = p1.computer_guessing(p);
        p = p2.Ask(t.computer);
    } while (p.bulls != 4);
    std::cout << "computer guessed your number! it is: ";
    for (size_t i = 0; i < 4; i++) {
        std::cout << static_cast<short>(t.computer[i]);
    }
    return 0;
}