#include "counter.hpp"

int main(int argc, char **argv){
    if(argc != 2){
        std::cerr <<"Usage <path>\n";
        return 1;
    }
    Counter counter(argv[1]);
    counter.count_first_file();


    return 0;

}
