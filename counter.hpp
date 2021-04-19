#ifndef __COUNTER_H_
#define __COUNTER_H_

#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <boost/filesystem.hpp>
#include <thread>
#include <boost/thread.hpp>

using namespace boost;

class Counter{
    private:
        std::queue<std::string> files_queue;
        std::string folder_path;
        std::queue<std::string> fill_files_queue(std::string);
        long long get_words_count(std::string);
    public:
        Counter();
        void count_first_file();
        Counter(std::string);
        void print_files();


};


#endif // __COUNTER_H_



