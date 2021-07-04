#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <cmath>
#include <vector>
#include <ctime>
bool proc_num (std::vector<int>& v, int bi, int ei);
bool game_over(const std::vector<int>& v);
void print_grid(const std::vector<int>& v);
void rotate_anti_clock (std::vector<int>& v);
void generatetwo (std::vector<int>& v);
void get_col(int c, const std::vector<int>& in, std::vector<int>& out);
int twod_to_oned(int row, int col, int rowlen);

int main(){
    std::vector<int> vin;
    std::string input;
    std::string filename;

    std::cout << "please enter name of file" << std::endl;
    std::cin >> filename;

    std::ifstream infile;
    infile.open(filename.c_str());

    if(!infile.is_open()){
        std::cout<<"file not found, using default start configuration"<<std::endl;
        for (int i = 0; i<15 ; i++){
            vin.push_back(0);
        }
        vin.push_back(2);
    }
    else{
        int tmp;
        while(infile >> tmp){
            vin.push_back(tmp);
        }
    }
    int sidelen = std::sqrt( vin.size() );
    print_grid (vin);
    std::vector<int> before_move;
    while ( !( game_over(vin) ) ){
        before_move = vin;
        std::cin>>input;
        if (input == "w" ){
            rotate_anti_clock(vin);
            for (int i = 0; i <sidelen ; i++){
                proc_num(vin, i*sidelen, i*sidelen + sidelen - 1 ) ;
            }
            rotate_anti_clock(vin);
            rotate_anti_clock(vin);
            rotate_anti_clock(vin);
        }

        if (input == "a" ){
            for (int i = 0; i <sidelen ; i++){
                proc_num(vin, i*sidelen, i*sidelen + sidelen - 1 ) ;
            }
        }

        if (input == "s" ){
            rotate_anti_clock(vin);
            rotate_anti_clock(vin);
            rotate_anti_clock(vin);
            for (int i = 0; i <sidelen ; i++){
                proc_num(vin, i*sidelen, i*sidelen + sidelen - 1 ) ;
            }

            rotate_anti_clock(vin);
        }

        if (input == "d" ){
            rotate_anti_clock(vin);
            rotate_anti_clock(vin);
            for (int i = 0; i <sidelen ; i++){
                proc_num(vin, i*sidelen, i*sidelen + sidelen - 1 ) ;
            }
            rotate_anti_clock(vin);
            rotate_anti_clock(vin);
        }
        if (vin != before_move){
            generatetwo(vin);
            print_grid (vin);
            std::cout<<std::endl;
        }
        }

    std::cout<<"Game Over"<<std::endl;
    return 0;
}

bool proc_num( std::vector<int>& in, int bi, int ei){
    std::vector<int> without_zero, out;

    int sidelen = std::sqrt( in.size() );
    for (int i = bi; i <= ei; i++){
        if (in[i] != 0 ){
            without_zero.push_back( in[i] );
        }
    }
    if (without_zero.size() != 0){
        for (int i = without_zero.size() ;  i <= sidelen ; i++ ){
            without_zero.push_back(0);
        }
    }
    else{
        return true;
    }
    for (int i = 0 ; i<= sidelen - 1; i++) {
        if (i == sidelen - 1) {
            out.push_back( without_zero[i] );
        }
        else{
            if (without_zero[i] == without_zero [i+1] ) {
                out.push_back( 2 * without_zero[i] );
                for (int j = i+1 ; j < sidelen - 1; j++) {
                    without_zero[j] = without_zero [j+1];
                }
                without_zero[sidelen-1] = 0;
            }
            else{
                out.push_back( without_zero[i] );
            }
        }
    }
    int k = 0;
    for (int i = bi; i<= ei; i++) {
        if( in[i] != out[k] ){
            int j = 0;
            for (int i = bi; i<=ei; i++) {
                in[i] = out[j];
                j++;
            }
            return true;
        }
        k++;
    }
    return false;
}

bool game_over(const std::vector<int>& v){
    int sidelen = std::sqrt(v.size());
    std::vector<int> test;
    test = v;
    for (int i = 0; i < 4; i++ ){
        for (int i = 0; i < sidelen ; i++){
            if ( proc_num(test, i*sidelen, i*sidelen + sidelen - 1 )==true) {
                return false;
            }
        }
        rotate_anti_clock(test);
    }
    return true;
}

void print_grid(const std::vector<int>& v){
    int side = std::sqrt(v.size());
    for ( int j = 0; j < side; j++){
        for (int i = j*side ; i < j*side + side; i++){
            std::cout<<v[i]<<"\t";
        }
        std::cout<<std::endl;
    }
}

void rotate_anti_clock (std::vector<int>& v){
    std::vector<int> store_vec;
    int side = std::sqrt (v.size() );
    int width = side - 1;
    for (int i = 0; i<side; i++) {
        get_col(width-i,v, store_vec);
    }
    v = store_vec;
  }

        /*    store_vec.push_back( v[width - j + i*side] );
        }
    }
    v = store_vec;
}
*/
/////////////////////////////////////////////////
void get_col(int c, const std::vector<int>& in, std::vector<int>& out){
  	int side = std::sqrt( in.size() );
    	for (int i = 0; i < side; i++){
       		out.push_back( in[twod_to_oned(i, c, side)]  );
    }
}

int twod_to_oned(int row, int col, int rowlen){
    return row*rowlen+col;
}
///////////////////////////////////////////////

void generatetwo (std::vector<int>& v){
    std::vector<int> storezero, storevecnum;
    int k = 0;
    for(int i = 0; i <v.size(); i++){
        if (v[i]==0){
            storezero.push_back( v[i] );
            storevecnum.push_back( k );
        }
        k++;
    }
    if( storezero.size() != 0 ){
        srand((unsigned)time (NULL));
        int d =  ( rand()%storezero.size() ) ;
        int original_pos = storevecnum[d] ;
        v[ original_pos ] = 2;
    }
}
