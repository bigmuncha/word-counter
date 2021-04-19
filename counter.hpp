#ifndef __COUNTER_H_
#define __COUNTER_H_

#include <iostream>
#include <boost/filesystem.hpp>

#include <vector>
#include <queue>
#include <map>

#include <string>
#include <functional>
#include <memory>
#include <algorithm>
#include <numeric>

#include <thread>
#include <mutex>
#include <boost/thread.hpp>

using namespace boost;

class Counter{
        private:
                typedef std::function<void ()> MyFunc;
                int queue_size;
                std::string folder_path;
                std::queue<std::string> files_queue;
                std::vector<std::thread> pool_th;
                std::map<std::string, long long> result_mapa;
                std::mutex g_lock;
 
                std::queue<std::string> fill_files_queue(std::string);

                long long get_words_count(std::string);
                void thread_pool_start(MyFunc const&, int thread_count);
                void worker_func();

        public:
                void count_first_file();
                Counter(std::string);
                void print_files();
                void start_counter(int thread_count = 4);
                void show_result();
                long long words_in_folder();
                
};


#endif // __COUNTER_H_



