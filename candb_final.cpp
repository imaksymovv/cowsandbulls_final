#include <iostream>


struct CowsAndBullsAnswer {
    unsigned char cows;
    unsigned char bulls;
};

struct CowsAndBullsComputerHelper {
    unsigned char computer[4];
    CowsAndBullsComputerHelper& operator=(const CowsAndBullsComputerHelper& c)
    {
        for (size_t i = 0; i < 4; ++i)
        {
            this->computer[i] = c.computer[i];
        }
        return *this;
    }

    CowsAndBullsComputerHelper()
    {}
};



unsigned char substitute_creating(CowsAndBullsComputerHelper r) {
    unsigned char substitute = 0;
    for (size_t i = 0; i < 4; i++) {
        substitute = 1 + rand() % 9;
        for (int j = 0; j < 4; j++) {
            if (substitute == r.computer[j]) {
                i--;
                break;
            }
        }
    }
    return substitute;
}

CowsAndBullsComputerHelper number_including_bulls_creating(CowsAndBullsComputerHelper r,unsigned char founded_bulls[4], unsigned char checking[4]) {
    for (size_t i = 0; i < 4; i++) {
        if (founded_bulls[i] == 1) {
            r.computer[i] = checking[i];
            for (size_t j = 0; j < i; j++) {
                if (r.computer[i] == r.computer[j]) {
                    do {
                        r.computer[j] = 1 + rand() % 9;
                    } while (r.computer[i] == r.computer[j]);
                }
            }
            for (size_t t = 0; t < 4; t++) {
                if (founded_bulls[t] != 1) {
                    for (size_t j = 0; j < 4; j++) {
                        if (t != j) {
                            while (r.computer[t] == r.computer[j]) {
                                r.computer[t] = 1 + rand() % 9;
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
    return r;
}

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
         r = previous;
         if (number_have_bulls == false) {
             if (k.bulls >= 1) {
                 number_have_bulls = true;
                 substitute = substitute_creating(r);
             }
             else {
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
                 previous = r;
                 return r;
             }
         }
         if (searching_for_bulls_index != 4) {
             if (number_of_bulls == 0) {
                 number_of_bulls = k.bulls;
             }
             if (k.bulls < number_of_bulls) {
                 checking[searching_for_bulls_index] = memory[searching_for_bulls_index];
                 founded_bulls[searching_for_bulls_index] = 1;
             }
             if (k.bulls > number_of_bulls) {
                 checking[searching_for_bulls_index] = r.computer[searching_for_bulls_index];
                 founded_bulls[searching_for_bulls_index] = 1;
             }
             for (size_t i = 0; i < 4; i++) {
                 r.computer[i] = memory[i];
             }
             searching_for_bulls_index++;
             if (searching_for_bulls_index == 4) {
                 for (size_t i = 0; i < 4; i++) {
                     if (founded_bulls[i] == 1) {
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
                         for (size_t t = 0; t < i; t++) {
                             if (r.computer[i] == r.computer[t]) {
                                 i--;
                                 break;
                             }
                         }
                     }
                 }
                 for (size_t i = 0; i < 4; i++) {
                     memory[i] = r.computer[i];
                 }
                 substitute = substitute_creating(r);
                 previous = r;
                 return r;
             }
             r.computer[searching_for_bulls_index] = substitute;
         }
         else {
             if (searching_for_cows_started == false) {
                 number_of_bulls = k.bulls;
                 searching_for_cows_started = true;
             }
             if (k.bulls > number_of_bulls) {
                 bull_founded = true;
                 number_of_bulls = k.bulls;
                 start_substitution = false;
                 cows_founded = false;
                 for (size_t i = 0; i < 4; i++) {
                     memory[i] = r.computer[i];
                 }
             }
             if (bull_founded == true) {
                 if (index_when_bulls_founded == -1) {
                     number_of_bulls1 = k.bulls;
                     substitute = substitute_creating(r);
                 }
                 for (size_t i = 0; i < 4; i++) {
                     r.computer[i] = memory[i];
                 }
                 if (k.bulls < number_of_bulls1) {
                     checking[index_when_bulls_founded] = r.computer[index_when_bulls_founded];
                     founded_bulls[index_when_bulls_founded] = 1;
                 }
                 if (k.bulls > number_of_bulls1) {
                     checking[index_when_bulls_founded] = substitute;
                     founded_bulls[index_when_bulls_founded] = 1;
                 }
                 do {
                     index_when_bulls_founded++;
                     if (index_when_bulls_founded == 4) {
                         r = number_including_bulls_creating(r, founded_bulls, checking);
                         for (size_t i = 0; i < 4; i++) {
                             memory[i] = r.computer[i];
                         }
                         substitute = substitute_creating(r);
                         bull_founded = false;
                         index_when_bulls_founded = -1;
                         previous = r;
                         return r;
                     }
                 } while (founded_bulls[index_when_bulls_founded] == 1);
                 r.computer[index_when_bulls_founded] = substitute;
                 previous = r;
                 return r;
             }
             if (k.cows > 0) {
                 cows_founded = true;
             }
             if (number_of_cows > k.cows) {
                 number_of_cows = 0;
                 cows_checker = memory[index_when_cows_founded];
                 for (size_t i = 0; i < 4; i++) {
                     memory[index_when_cows_founded] = 1 + rand() % 9;
                     for (int j = 0; j < 4; j++) {
                         if (memory[index_when_cows_founded] == r.computer[j]) {
                             i--;
                             break;
                         }
                     }
                 }
                 index_when_cows_founded = -1;
                 cows_founded = false;
                 start_substitution = true;
             }
             if (cows_founded == true) {
                 if (index_when_cows_founded == -1) {
                     number_of_cows = k.cows;
                 }
                 for (size_t i = 0; i < 4; i++) {
                     r.computer[i] = memory[i];
                 }
                 do{
                 index_when_cows_founded++;
                 if (index_when_cows_founded == 4) {
                     index_when_cows_founded = -1;
                     cows_founded = false;
                     previous = r;
                     return r;
                 }
                 } while (founded_bulls[index_when_cows_founded] == 1);
                 r.computer[index_when_cows_founded] = substitute;
                 previous = r;
                 return r;
             }
             if (start_substitution == true) {
                 for (size_t i = 0; i < 4; i++) {
                     r.computer[i] = memory[i];
                 }
                 do {
                     index_for_substitution++;
                     if (index_for_substitution == 4) {
                         index_for_substitution = -1;
                         start_substitution = false;
                         previous = r;
                         return r;
                     }
                 } while (founded_bulls[index_for_substitution] == 1);
                 r.computer[index_for_substitution] = cows_checker;
                 previous = r;
                 return r;
             }

             if(k.cows == 0 && bull_founded == false) {
                 r = number_including_bulls_creating(r, founded_bulls, checking);
                 substitute = substitute_creating(r);
                 for (size_t i = 0; i < 4; i++) {
                     memory[i] = r.computer[i];
                 }
             }
         }
         previous = r;
         return r;
     }

    explicit CowsAndBullsComputerPlayer(unsigned char n[4]) : CowsAndBullsPlayer(n) {}

private:
    unsigned char number_of_bulls = 0;
    unsigned char number_of_bulls1 = 0;
    unsigned char memory[4];
    unsigned char checking[4];
    unsigned char founded_bulls[4];
    unsigned char cows_checker;
    CowsAndBullsComputerHelper previous;
    unsigned char number_of_cows = 0;
    bool number_have_bulls = false;
    bool searching_for_cows_started = false;
    bool start_substitution = false;
    bool bull_founded = false;
    bool cows_founded = false;
    unsigned char substitute = 0;
    int searching_for_bulls_index = -1;
    int index_for_substitution = -1;
    int index_when_cows_founded = -1;
    int index_when_bulls_founded = -1;
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
        for (size_t i = 0; i < 4; i++) {
            std::cout << static_cast<short>(t.computer[i]);
        }
        std::cout << std::endl;
        p = p2.Ask(t.computer);
    } while (p.bulls != 4);
    std::cout << "computer guessed your number! it is: ";
    for (size_t i = 0; i < 4; i++) {
        std::cout << static_cast<short>(t.computer[i]);
    }
    return 0;
}