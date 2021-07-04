#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <cmath>
#include <fstream>

void set_random_seed();
int randn(int n);

struct mm_code_maker{

    void init(int i_length, int i_num){
        length = i_length;
        num = i_num;
    }

    void generate_sequence(){
        for(int i = 0; i < length; i++){
            sequence.push_back(randn(num));
        }
    }

    void give_feedback(const std::vector<int>& attempt, int& black_hits, int& white_hits){
        for (int i = 0; i < attempt.size() ; i++){
            if( attempt[i] == sequence[i] ){
                black_hits++;
        /// and provides feedback in terms of black hitst
            }
        }
        int total = 0;
        for(int i = 0; i < num ; i++){
            int numincode = 0;
            int numinguess = 0;
            for (int j = 0 ; j < sequence.size() ; j++){
                if( sequence[j] == i){
                    numincode++;
                }
                if( attempt[j] == i){
                    numinguess++;
                }

            }

            if( numincode <= numinguess ){
                total = total + numincode;
            }
            else{
                total = total + numinguess;
            }
        }
        white_hits = total - black_hits;
        /// and white hits (see linked paper)
    }

    std::vector<int> sequence;

    int length;
    int num;
};

struct mm_solver{

    void init(int i_length, int i_num){
        length = i_length;
        num = i_num;
    }

     /// this member function creates an attempt to find the right code
    void create_attempt(std::vector<int>& attempt){

        if(saved_case.size() == 0){
            for(int i = 0; i < length; i++ ){
                attempt.push_back( randn(num) );
            }
        }
        else{
            attempt = saved_case[randn(saved_case.size())];
        }
    }

  /// this member function acquires the feedback about a certain attempt
    void learn(std::vector<int>& attempt, const int& black_hits, const int& white_hits){
        int blacks, whites;
        long long int possible = std::pow(num, length);

        for(int n = 0; n < length; n++){
            case.push_back(0);
        }

        if( saved_case.size() == 0 ){

            for (int i = 1; i <= possible; i++) {
                for (int j = 0; j < length; j++) {

                    if ( j == (length - 1)) {
                        int unit = (i-1) % num ;
                        case[j] = unit ;
                    }

                    else{
                        int denominator = std::pow(num, (length - 1 - j) );
                        int digit = ( ((i-1)/denominator) ) % num ;
                        case[j] = digit;
                    }

                }

                blacks = 0;
                whites = 0;
                attempt_hit_counter(case, attempt, blacks, whites);
                if( (blacks == black_hits) && (whites == white_hits)){
                    saved_case.push_back(case);

                }
            }

        }

        else{
            std::vector< std::vector<int> > replace;
            for(int i = 0; i < saved_case.size(); i++){
                blacks = 0;
                whites = 0;
                attempt_hit_counter(saved_case[i], attempt, blacks, whites);
                if( (blacks == black_hits) && (whites == white_hits)){
                    replace.push_back(saved_case[i]);
                }

            }
            saved_case = replace ;
        }

    }

    void attempt_hit_counter(const std::vector<int>& case, const std::vector<int>& attempt , int& black_hits, int& white_hits){

        for (int i = 0; i < attempt.size() ; i++){
            if( attempt[i] == case[i] ){
                black_hits++;
            }
        }

        int total = 0;
        for(int i = 0; i < num ; i++){
            int numincode = 0;
            int numinguess = 0;
            for (int j = 0; j < attempt.size() ; j++){
                if( case[j] == i){
                    numincode++;
                }
                if( attempt[j] == i){
                    numinguess++;
                }
            }
            if( numincode <= numinguess ){
                total = total + numincode;
            }
            else{
                total = total + numinguess;
            }
        }
        white_hits = total - black_hits;
    }

    std::vector<int> case;
    std::vector< std::vector<int> > saved_case;
    std::vector<int> newv;


    int length;
    int num;
};

int main(){
    set_random_seed();
    int length, num;
    std::cout << "Please enter length of sequence and number of possible values:" << std::endl;
    std::cin >> length >> num;

    mm_solver solver;
    solver.init(length, num);

    mm_code_maker maker;
    maker.init(length, num);
    maker.generate_sequence();

    int black_hits=0, white_hits=0;
    int attempts_limit = 10000;
    int attempts = 0;

    while((black_hits < length) && (attempts < attempts_limit)){
        black_hits = 0;
        white_hits = 0;
        std::vector<int> attempt;
        solver.create_attempt(attempt);
        maker.give_feedback(attempt, black_hits, white_hits);
        std::cout << "Attempt: " << std::endl;
        for(int i = 0; i < attempt.size(); i++){
            std::cout << attempt[i] << " ";
        }
        std::cout << std::endl;
        std::cout << "Black pegs: " << black_hits << " " << " White pegs: " << white_hits << std::endl;
        solver.learn(attempt, black_hits, white_hits);
        attempts++;

    }

    if(black_hits == length){
        std::cout << "The solver has found the sequence in " << attempts << " attempts" << std::endl;
    }
    else{
        std::cout << "After " << attempts << " attempts, still no solution" << std::endl;
    }
    std::cout << "The sequence generated by the code maker was:" << std::endl;
    for(int i = 0; i < maker.sequence.size(); i++){
        std::cout << maker.sequence[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}

void set_random_seed(){
    srand((unsigned)time (NULL));
}

/*void set_random_seed(){
    std::srand(std:time(0));
}*/

int randn(int n){
    return rand() % n;
}
