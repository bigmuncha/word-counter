#include <iostream>
#include <boost/filesystem.hpp>
#include <fstream>

using namespace boost;

int main(int argc, char ** argv){

    if(argc < 2 ){
        std::cout << "Usage: <path>\n";
        return 1;
    }

    filesystem::path p (argv[1]);
    
    try{
        if(filesystem::exists(p)){
            if(filesystem::is_regular_file(p)){
                std::cout <<p << " size is "
                          <<filesystem::file_size(p)
                          << '\n';

                std::ifstream file(argv[1]);
                int i;
                std::string word;
                if(file.is_open()){
                    while(file >> word){
                        i++;
                    }
                }else{
                    std::cout << "not open\n";
                }
                std::cout <<"Words : " << i << '\n';
            }else if (filesystem::is_directory(p)){
                std::cout << p << "is a directory containing:\n";
                for (filesystem::directory_entry & x:
                         filesystem::directory_iterator(p)){
                    std::cout << "  "<< x.path() << '\n';
                }
            }else{
                std::cout << p << " exists, but status is not a regular file or directory\n";
            }
        }else{
            std::cout << p << " does not exist\n";
        }
    }catch( filesystem::filesystem_error& ex){
        std::cout <<ex.what() << '\n';
    }
    return 0;
}
