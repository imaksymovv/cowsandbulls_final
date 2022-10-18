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
        for (size_t i = 0; i < 4; i++) {
            std::cout << static_cast<short>(num[i]);
        }
        std::cout << "\n";
        std::cout << "cows: " << static_cast<unsigned short>(counter.cows) << " bulls: " << static_cast<unsigned short>(counter.bulls) << std::endl;

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
     CowsAndBullsComputerHelper computer_guessing(CowsAndBullsAnswer k, CowsAndBullsComputerHelper r) {
         //CowsAndBullsComputerHelper r = previous; - переделать с одной
         if (end == true) {
             if (k.bulls >= 1) {
                 end = false;
                 for (size_t i = 0; i < 4; i++) {
                     r.computer[i] = memory[i];
                 }
                 for (size_t i = 0; i < 4; i++) {
                     previous.computer[i] = r.computer[i];
                 }
                 for(size_t i = 0; i < 4; i++){
                     substitute = 1 + rand() % 9;
                     for (int j = 0; j < 4; j++) {
                         if (substitute == r.computer[j]) {
                             i--;
                             break;
                         }
                     }
                 }
                 std::cout << "SUBSTITUTE " << static_cast<short>(substitute) << std::endl;
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
             //std::cout << static_cast<short>(k.bulls) << std::endl;
             if (b == 0) {
                 b = k.bulls;
             }
             if (k.bulls < b) {
                 checking[i] = memory[i];
                 index[i] = 1;
                 if (index[i] != 1) {
                     index[i] = 0;
                 }
             }
             if (k.bulls > b) {
                 checking[i] = r.computer[i];
                 index[i] = 1;
                 if (index[i] != 1) {
                     index[i] = 0;
                 }
             }
             for (size_t i = 0; i < 4; i++) {
                 r.computer[i] = memory[i];
             }
             i++;
             r.computer[i] = substitute;     
             if (i == 4) {
                 std::cout << "part 2" << std::endl;
             }
         }
         else {
             if (start == true) {
                 int i = j;
                 int i1 = 0;
                 if (index[i1] == 1) {

                 }
                 else {
                     r.computer[i1] = memory[i];
                 }
                 i1++;
                 if (i1 == 4) {
                     start = false;
                 }
             }
             if (start1 == true) {
                 j = 0;
                 for (size_t i = 0; i < 4; i++) {
                     r.computer[i] = memory[i];
                 }
                 if (index[j] == 1) {

                 }
                 else {
                     r.computer[j] = substitute;
                 }
                 j++;
                 if (j == 4) {
                     start1 = false;
                 }
             }
             if (end1 == false) {
                 b = k.bulls;
                 end1 = true;
             }
             if (k.bulls > b) {
                 checking[j] = r.computer[j];
                 index[j] = 1;
                 if (index[j] != 1) {
                     index[j] = 0;
                 }
                 end1 = false;
             }
             if (k.cows >= 1 && start == false && start1 == false) {
                 if (c == 0) {
                     c = k.cows;
                 }
                 if (c > k.cows) {
                    start = true;
                    return r;
                 }
                 if (c < k.cows) {
                     start1 = true;
                     return r;
                 }
                 for (size_t i = 0; i < 4; i++) {
                    r.computer[i] = memory[i];
                 }
                 j++;
                 if (j >= 4) {
                      j = 0;
                 }
                 if (index[j] == 1) {

                 }
                 else {
                     r.computer[j] = substitute;
                 }
             }
             if(k.cows == 0) {
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
    unsigned char memory[4];
    unsigned char checking[4];
    unsigned char index[4];
    CowsAndBullsComputerHelper previous;
    unsigned char c = 0;
    bool end = true;
    bool end1 = false;
    bool start = false;
    bool start1 = false;
    unsigned char substitute = 0;
    int i = -1;
    int j = -1;
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
        t = p1.computer_guessing(p,t);
        p = p2.Ask(t.computer);
    } while (p.bulls != 4);
    //} while (p.bulls != 4);
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