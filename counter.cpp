#include "counter.hpp"

Counter::Counter(std::string folder)
    :folder_path(folder), files_queue(fill_files_queue(folder))
{}


std::queue<std::string> Counter::fill_files_queue(std::string folder){
    std::queue<std::string> result;
    filesystem::path p(folder);
    try{

        if(filesystem::exists(p)){

            if(filesystem::is_directory(p)){

                for(filesystem::directory_entry & x:
                        filesystem::directory_iterator(p)){
                    result.push(x.path().c_str());
                }
            }else{
                std::cerr << "this is not directory\n";
                exit(1);
            }

        }else{
            std::cerr << "this folder not exist\n";
            exit(1);
        }

    }catch( filesystem::filesystem_error& ex){
        std::cerr <<ex.what() << '\n';
    }

    return result;
}

void Counter::print_files(){
    std::queue<std::string> temp;
    while(!files_queue.empty()){
        std::cout << files_queue.front() << '\n';
        temp.push(files_queue.front());
        files_queue.pop();
    }
    files_queue = temp;
}

long long get_words_count(std::string path){
    std::ifstream file(path);
    long long i;
    std::string word;
    if(file.is_open()){
        while(file >> word){
            i++;
        }
    }else{
        std::cout << "not open\n";
    }
    return i;
}
