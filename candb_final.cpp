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
    bool numbers_are_not_same = false;
    for (size_t i = 0; i < 9; i++) {
        substitute = i + 1;
        for (size_t j = 0; j < 4; j++) {
            if (substitute == r.computer[j]) {
                numbers_are_not_same = false;
                break;
            }
            else {
                numbers_are_not_same = true;
            }
        }
        if (numbers_are_not_same == true) {
            break;
        }
    }
    return substitute;
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
        std::cout << std::endl;
        for (size_t i = 0; i < 4; i++) {
            std::cout << static_cast<int>(this->number[i]);
        }
        std::cout << std::endl;
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
    int reshuffle(CowsAndBullsComputerHelper r, bool false_numbers[4]) {
        CowsAndBullsAnswer k = {};
        int b = 0;
        
        if (index_for_reshuffle == 24) {
            for (size_t i = 0; i < 4; i++) {
                b = 0;
                for (size_t j = 0; j < 9; j++) {
                    r.computer[i] = b + 1;
                    b++;
                    if (false_numbers[j] == false) {
                        false_numbers[j] = true;
                        break;
                    }
                }
            }
        }
        for (size_t i = 0; i < 4; i++) {
            memory_for_reshuffle[i] = r.computer[i];
        }
        if (index_for_reshuffle == 5 || index_for_reshuffle == 29) {
            r.computer[0] = memory_for_reshuffle[3];
            r.computer[3] = memory_for_reshuffle[0];
        }
        if (index_for_reshuffle == 11 || index_for_reshuffle == 17 || index_for_reshuffle == 35 || index_for_reshuffle == 41) {
            r.computer[0] = memory_for_reshuffle[2];
            r.computer[2] = memory_for_reshuffle[0];
        }
        else if (index_for_reshuffle % 2 != 0) {
            r.computer[1] = memory_for_reshuffle[2];
            r.computer[2] = memory_for_reshuffle[1];
        }
        else {
            r.computer[2] = memory_for_reshuffle[3];
            r.computer[3] = memory_for_reshuffle[2];
        }
        index_for_reshuffle++;
        k = Ask(r.computer);
        std::cout << "bulls :" << static_cast<int>(k.bulls) << std::endl;
        if (k.bulls >= 1) {
            return 0;
        }
        else {
            return reshuffle(r, false_numbers);
        }
    }

    CowsAndBullsComputerHelper number_including_bulls_creating() {
        CowsAndBullsComputerHelper r;
        unsigned int index_for_false_numbers = 0;
        for (size_t i = 0; i < 4; i++) {
            if (founded_bulls[i] == 1) {
                r.computer[i] = memory_for_bulls[i];
            }
        }
        for (size_t i = 0; i < 4; i++) {
            if (founded_bulls[i] != 1) {
                index_for_false_numbers = 0;
                if (cow_number_substitute == true) {
                    for (size_t j = 0; j < 9; j++) {
                        r.computer[i] = index_for_false_numbers + 1;
                        index_for_false_numbers++;
                        if (false_numbers[j] == false && r.computer[i] != cows_checker) {
                            false_numbers[j] = true;
                            break;
                        }
                    }
                }
                else {
                    for (size_t j = 0; j < 9; j++) {
                        r.computer[i] = index_for_false_numbers + 1;
                        index_for_false_numbers++;
                        if (false_numbers[j] == false) {
                            false_numbers[j] = true;
                            break;
                        }
                    }
                }
            }
        }
        for (size_t i = 0; i < 4; i++) {
            if (founded_bulls[i] != 1) {
                index_for_false_numbers = r.computer[i] - 1;
                false_numbers[index_for_false_numbers] = false;
            }
        }
        return r;
    }

     CowsAndBullsComputerHelper computer_guessing(CowsAndBullsAnswer k) {
         CowsAndBullsComputerHelper r;
         r = previous;
         unsigned int index_for_false_numbers = 0;
         if (number_have_bulls == false) {
             if (k.bulls >= 1) {
                 for (size_t i = 0; i < 9; i++) {
                     false_numbers[i] = false;
                 }
                 number_have_bulls = true;
                 substitute = substitute_creating(r);
             }
             else {
                 for (size_t i = 0; i < 9; i++) {
                     false_numbers[i] = false;
                 }
                 /*for (int i = 0; i < 4; ++i) {
                     r.computer[i] = 1 + rand() % 9;
                     for (int j = 0; j < i; j++) {
                         if (r.computer[j] == r.computer[i]) {
                             i--;
                             break;
                         }
                     }
                 }*/
                 for (size_t i = 0; i < 4; i++) {
                     index_for_false_numbers = 0;
                     for (size_t j = 0; j < 9; j++) {
                         r.computer[i] = index_for_false_numbers + 1;
                         index_for_false_numbers++;
                         if (false_numbers[j] == false) {
                             false_numbers[j] = true;
                             break;
                         }
                     }
                 }
                 reshuffle(r, false_numbers);
                 std::cout << std::endl;
                 for (size_t i = 0; i < 4; i++) {
                     std::cout << static_cast<int>(r.computer[i]);
                 }
                 for (size_t i = 0; i < 4; i++) {
                     memory_for_number[i] = r.computer[i];
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
                 memory_for_bulls[searching_for_bulls_index] = memory_for_number[searching_for_bulls_index];
                 founded_bulls[searching_for_bulls_index] = 1;

                 index_for_false_numbers = memory_for_bulls[searching_for_bulls_index] - 1;
                 false_numbers[index_for_false_numbers] = true;
             }
             if (k.bulls > number_of_bulls) {
                 memory_for_bulls[searching_for_bulls_index] = r.computer[searching_for_bulls_index];
                 founded_bulls[searching_for_bulls_index] = 1;

                 index_for_false_numbers = memory_for_bulls[searching_for_bulls_index] - 1;
                 false_numbers[index_for_false_numbers] = true;
                 new_bull++;
             }
             for (size_t i = 0; i < 4; i++) {
                 r.computer[i] = memory_for_number[i];
             }
             searching_for_bulls_index++;
             if (searching_for_bulls_index == 4) {
                 bulls_before_cows_part = k.bulls + new_bull;
                 r = number_including_bulls_creating();
                 for (size_t i = 0; i < 4; i++) {
                     memory_for_number[i] = r.computer[i];
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
             if (k.bulls > number_of_bulls || k.bulls > bulls_before_cows_part) {
                 bull_founded = true;
                 bulls_before_cows_part = k.bulls;
                 number_of_bulls = k.bulls;
                 start_substitution = false;
                 cows_founded = false;
                 for (size_t i = 0; i < 4; i++) {
                     memory_for_number[i] = r.computer[i];
                 }
             }
             if (bull_founded == true) {
                 std::cout << std::endl;
                 std::cout << "bulls" << std::endl;
                 number_of_cows = 0;
                 if (index_when_bulls_founded == -1) {
                     number_of_bulls1 = k.bulls;
                     substitute = substitute_creating(r);
                 }
                 for (size_t i = 0; i < 4; i++) {
                     r.computer[i] = memory_for_number[i];
                 }
                 if (k.bulls < number_of_bulls1) {
                     memory_for_bulls[index_when_bulls_founded] = r.computer[index_when_bulls_founded];
                     founded_bulls[index_when_bulls_founded] = 1;

                     index_for_false_numbers = memory_for_bulls[index_when_bulls_founded] - 1;
                     false_numbers[index_for_false_numbers] = true;
                 }
                 if (k.bulls > number_of_bulls1) {
                     memory_for_bulls[index_when_bulls_founded] = substitute;
                     founded_bulls[index_when_bulls_founded] = 1;

                     substitute = substitute_creating(r);
                     index_for_false_numbers = memory_for_bulls[index_when_bulls_founded] - 1;
                     false_numbers[index_for_false_numbers] = true;
                 }
                 do {
                     index_when_bulls_founded++;
                     if (index_when_bulls_founded == 4) {
                         r = number_including_bulls_creating();
                         for (size_t i = 0; i < 4; i++) {
                             memory_for_number[i] = r.computer[i];
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
             if (k.cows > 0 && start_substitution == false && bull_founded == false) {
                 cows_founded = true;
             }
             if (number_of_cows > k.cows) {
                 number_of_cows = 0;
                 cows_checker = memory_for_number[index_when_cows_founded];
                 cow_number_substitute = true;
                 do {
                     r = number_including_bulls_creating();
                 } while (r.computer[0] == cows_checker || r.computer[1] == cows_checker || r.computer[2] == cows_checker || r.computer[3] == cows_checker);
                 cow_number_substitute = false;
                 for (size_t i = 0; i < 4; i++) {
                     memory_for_number[i] = r.computer[i];
                 }
                 index_when_cows_founded = -1;
                 cows_founded = false;
                 start_substitution = true;
             }
             if (cows_founded == true) {
                 std::cout << std::endl;
                 std::cout << "cows" << std::endl;
                 if (index_when_cows_founded == -1) {
                     number_of_cows = k.cows;
                 }
                 for (size_t i = 0; i < 4; i++) {
                     r.computer[i] = memory_for_number[i];
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
                 std::cout << std::endl;
                 std::cout << "subst" << std::endl;
                 for (size_t i = 0; i < 4; i++) {
                     r.computer[i] = memory_for_number[i];
                 }
                 do{
                     index_for_substitution++;
                     if (index_for_substitution == 4) {
                         index_for_substitution = -1;
                         start_substitution = false;
                         previous = r;
                         return r;
                     }
                 } while (founded_bulls[index_for_substitution] == 1);
                 r.computer[index_for_substitution] = cows_checker;
                 index_for_substitution++;
                 previous = r;
                 return r;
             }

             if(k.cows == 0 && bull_founded == false && cows_founded == false && start_substitution == false) {
                 for (size_t i = 0; i < 4; i++) {
                     if (founded_bulls[i] != 1) {
                         index_for_false_numbers = r.computer[i] - 1;
                         false_numbers[index_for_false_numbers] = true;
                     }
                 }
                 r = number_including_bulls_creating();
                 substitute = substitute_creating(r);
                 for (size_t i = 0; i < 4; i++) {
                     memory_for_number[i] = r.computer[i];
                 }
             }
         }
         previous = r;
         return r;
     }

    explicit CowsAndBullsComputerPlayer(unsigned char n[4]) : CowsAndBullsPlayer(n) {}

private:
    unsigned char bulls_before_cows_part = 0;
    unsigned char number_of_bulls = 0;
    unsigned char number_of_bulls1 = 0;
    unsigned char memory_for_number[4];
    unsigned char memory_for_bulls[4];
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
    bool false_numbers[9];
    unsigned char new_bull = 0;
    bool cow_number_substitute = false;
    unsigned int index_for_reshuffle;
    unsigned char memory_for_reshuffle[4];
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