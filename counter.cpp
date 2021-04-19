#include "counter.hpp"

Counter::Counter(std::string folder)
    :folder_path(folder),
     result_mapa()
{
    files_queue = fill_files_queue(folder);
    queue_size = files_queue.size();
}

/*fill queue by boost::filesystem*/
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

/*temp func*/
void Counter::print_files(){
    std::queue<std::string> temp;
    while(!files_queue.empty()){
        std::cout << files_queue.front() << '\n';
        temp.push(files_queue.front());
        files_queue.pop();
    }
    files_queue = temp;
}

long long Counter::get_words_count(std::string path){
    std::ifstream file(path);
    long long i=0;
    std::string word;
    if(file.is_open()){
        while(file >> word){
            i++;
        }
    }else{
        std::cout << "not open\n";
    }
    file.close();
    return i;
}

void Counter::count_first_file(){
    std::cout << files_queue.front() <<'\n';
    std::cout <<get_words_count(files_queue.front()) << '\n';
}


void Counter::thread_pool_start(MyFunc const & myfunc, int thread_count){

    for(int i=0; i < thread_count; i++){
        pool_th.push_back(std::thread(
                              [this, myfunc]()
                              {
                                  myfunc();
                              }
));
    }
    for(int i=0; i < thread_count; i++){
        pool_th[i].join();
    }
}


void Counter::worker_func(){

    for(int i=0; i < queue_size; i++){
        std::string current_file;

        {
            std::unique_lock<std::mutex> lock(g_lock);
            if(files_queue.empty()){
                break;
            }
            current_file = files_queue.front();
            files_queue.pop();

        }
        
        long long word_count = get_words_count(current_file);

        {
            std::unique_lock<std::mutex> lock(g_lock);
            result_mapa.insert({current_file,word_count});
        }
    }
}

void Counter::start_counter(int thread_count){
        this->thread_pool_start
            ([this](){this->worker_func();}, thread_count);

}


void Counter::show_result(){
    for(auto i: result_mapa){
        std::cout << i.first<<" "
                  << i.second <<'\n';
    }
}

long long Counter::words_in_folder(){
    return
        std::accumulate(std::begin(result_mapa),
                           std::end(result_mapa),
                           0,
                           [](long long sum,
                              const std::map<std::string,long long>::value_type& p)
                           {return sum + p.second;}
);
}
