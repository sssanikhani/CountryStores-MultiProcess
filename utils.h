#ifndef UTILS_H
#define UTILS_H

#include "main.h"
#include <dirent.h>


void split_str(const std::string &s, std::vector<std::string> &v, const char sep);


void read_csv_file(const std::string &path, std::vector<std::vector<std::string>> &lines);


void fetch_prices(
    const std::vector<std::vector<std::string>> &data, 
    std::vector<int> &prices, 
    const std::string &pid,
    const std::string &sdate,
    const std::string &fdate
);


std::string get_fifo_path(const std::string &prefix, const int &id);


int read_directory(const std::string &name, std::vector<std::string> &v);


void get_information_from_parent(

    const int pd[PIPE_ENDS_NUM], 
    std::string &command

);


void give_information_to_child(
    
    const int pd[PIPE_ENDS_NUM], 
    const std::string &command

);


void create_child(
    const std::string &child_process,
    const std::string &command,
    const std::string &child_dir,
    const std::string &fifo_prefix,
    const int &child_index
);


void create_all_childs(

    const std::vector<std::string> &child_dirs, 
    const std::string &child_command,
    const std::string &command,
    const std::string &mydir, 
    const std::string &fifo_prefix

);


void get_childs_result(
    
    std::vector<int> &res,
    const int &size,
    const std::string &prefix

);


int find_max_or_min(const std::vector<int> &res, const std::string &command);


std::string calculate_response(

    const std::string &command,
    const int &childs_count,
    const std::string &child_fifo_prefix

);


void unlink_pipes(const std::string &prefix, const int &count);


void common_main(
    int argc, 
    char *argv[], 
    const std::string &child_fifo_prefix, 
    const std::string &child_exec_name    
);


#endif