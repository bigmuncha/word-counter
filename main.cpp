#include "counter.hpp"

int main(int argc, char **argv){
    if(argc != 2){
        std::cerr <<"Usage <path>\n";
        return 1;
    }
    Counter counter(argv[1]);
    counter.start_counter();
    counter.show_result();
    std::cout << '\n'
              << counter.words_in_folder() <<'\n';
    return 0;

}
