#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <vector>

int twod_to_oned(int row, int col, int rowlen){
    return row*rowlen+col;
}

int main (){
    
    std::vector<int> s;	
    std::string Filename;
    std::cout << "Please enter the name of the file containing the initial configuration" << std::endl;
    std::cin >> Filename;

    std::ifstream infile;
    infile.open(Filename.c_str());
    if(!infile.is_open()){
        std::cout << "error, can't open input file" << std::endl;
        exit(EXIT_FAILURE);
    }

    int tmp;

    while(infile >> tmp){
        s.push_back(tmp);
	std::cout << tmp << std::endl;
	
    }

bool proc_num(std::vector<int>& v, int bi, int ei);
bool proc_num_all(std::vector<int>&v);

int main(){

    std::vector<int> v{1,0,1,0,1,0,1,0,1} ;

    bool c = left_push_all(v);

    if( c ){
        std::cout << "true" << std::endl;
    }

    if(!c){
        std::cout << "false" << std::endl;

    }

    for( int i =0; i<v.size(); i++){
        std::cout <<v[i];
    }

    return 0;
}


bool left_push(std::vector<int>& v, int bi, int ei){

    std::vector<int> tmp;
    std::vector<int> tmp2;
    int coun = 0;

    // takes out the zeros
    for(int i = bi; i< ei ; i++){
        if(v[i]!= 0){
            tmp.push_back(v[i]);
            coun++;
        }
    }

    // returns false if all equal to zero
    if( coun == 0){
        return false;
    }

    // takes out values for later testing
    for( int i = 0; i<v.size(); i++){
        tmp2.push_back(v[i]);
    }

    // adds if equal
    for(int i = 0; i < (tmp.size() - 1); i++){
      if (tmp[i] == tmp[i+1] && tmp.size() != 0){
        tmp[i] = tmp[i]+tmp[i];
        tmp.erase( tmp.begin() + (i+1));
      }
    }

    int x = 0;
    //prints values back in
    for( int i = bi; i< tmp.size(); i++){
        v[i] = tmp[x];
        x++;
    }
    // adds the zeros at the end
    for( int i = x; i<ei; i++){
        v[i] = 0;
    }
    //checks if there has been a change
        if(v==tmp2){
            return false;
        }
    return true;
}
bool left_push_all(std::vector<int>&v){

    int length = std::sqrt(v.size());
    bool check = false;

    for( int i = 0; i < length; i++){

        int bi = i*length  ;
        int ei = bi +length ;

        if(left_push(v, bi, ei)){
            check = true;
        }
    }
    return check;
}

if(v1 == v2){
    For(k=0;k<16;k++){
        if(=rand)
        v[k]=2

void rotate_anti_clock(std::vector<int>& v)
v[0]=v[3];v[1]=v[7];v[2]=v[11];v[3]=v[15];


void print_grid(const std::vector<int>& v)
	
bool game_over(std::vector<int>& v) {
  int num=std::sqrt(v.size()); //variable with a fixed value->more efficient
  for(int i=0;i<v.size();i++){
    if(v[i]==0){
      return false;
    }
  }
  int temp;
  int row_left, row_right;
  int col_up,col_down;
  for(int row=0;row<num;row++){
    for(int col=0;col<num;col++){
      temp=v[twod_to_oned(row,col,num)];
      if(row==0){
        if(col==0){
          col_down=v[twod_to_oned(row+1,col,num)];
          row_right=v[twod_to_oned(row,col+1,num)];
            if((temp==col_down)||(temp==row_right)){
              return false;
            }
        }
        else if(col==num-1){
          col_down=v[twod_to_oned(row+1,col,num)];
          row_left=v[twod_to_oned(row,col-1,num)];
            if((temp==col_down)||(temp==row_left)){
              return false;
            }
        }
        else{
          col_down=v[twod_to_oned(row+1,col,num)];
          row_left=v[twod_to_oned(row,col-1,num)];
          row_right=v[twod_to_oned(row,col+1,num)];
            if((temp==col_up)||(temp==col_down)||(temp==row_left)||(temp==row_right)){
              return false;
            }
        }
    }
    else if(row==num-1){
      if(col==0){
        col_up=v[twod_to_oned(row-1,col,num)];
        row_right=v[twod_to_oned(row,col+1,num)];
          if((temp==col_up)||(temp==row_right)){
            return false;
          }
      }
      else if(col==num-1){
        col_up=v[twod_to_oned(row-1,col,num)];
        row_left=v[twod_to_oned(row,col-1,num)];
          if((temp==col_up)||(temp==row_left)){
            return false;
          }
      }
      else{
        col_up=v[twod_to_oned(row-1,col,num)];
        row_left=v[twod_to_oned(row,col-1,num)];
        row_right=v[twod_to_oned(row,col+1,num)];
          if((temp==col_up)||(temp==row_left)||(temp==row_right)){
            return false;
          }
      }
    }
    else{
      col_up=v[twod_to_oned(row-1,col,num)];
      col_down=v[twod_to_oned(row+1,col,num)];
      row_left=v[twod_to_oned(row,col-1,num)];
      row_right=v[twod_to_oned(row,col+1,num)];
        if((temp==col_up)||(temp==col_down)||(temp==row_left)||(row_right)){
          return false;
        }

    }

  }
}

  return true;
}



std:vector<int>g;  
bool game_end()
{
   // Check for zero
   for ( int i = 0; i < 4; ++i ) 
   {
      for ( int j = 0; j < 4; ++j ) if ( g[i][j] == 0 ) return false;
   }
                           
   // Check within-row (i) adjacency
   for ( int i = 0; i < 4; ++i ) 
   {
      for ( int j = 0; j < 3; ++j ) if ( g[i][j] == g[i][j+1] ) return false;
   }
                           
   // Check within-column (j) adjacency
   for ( int j = 0; j < 4; ++j )
   {
      for ( int i = 0; i < 3; ++i ) if ( g[i][j] == g[i+1][j] ) return false;
   }

   return true;
}

return 0; 
}
