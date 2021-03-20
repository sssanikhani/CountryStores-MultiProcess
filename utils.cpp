#include "utils.h"
using namespace std;


void split_str(const string &s, vector<string> &v, const char sep) {

    v.clear();

    string word;
    istringstream ss(s);
    while(getline(ss, word, sep))
        v.push_back(word);

}


void read_csv_file(const string &path, vector<vector<string>> &lines) {

    lines.clear();
    
    const char csv_separator = ',';
    
    fstream file;
    file.open(path);

    string line;
    getline(file, line); // Header Line

    while(getline(file, line)) {

        vector<string> line_words;
        split_str(line, line_words, csv_separator);
        lines.push_back(line_words);

    }

    file.close();

}


void fetch_prices(
    const vector<vector<string>> &data, 
    vector<int> &prices, 
    const string &pid,
    const string &sdate,
    const string &fdate
) {
    prices.clear();

    int data_size = data.size();
    for (int i = 0; i < data_size; i++) {

        if (
            data[i][DATA_PRODUCT_ID] == pid &&
            data[i][DATA_DATE] >= sdate &&
            data[i][DATA_DATE] <= fdate
        ) {

            prices.push_back(stoi(data[i][DATA_PRICE]));

        }

    }

}


string get_fifo_path(const string &prefix, const int &id) {

    string res = prefix + to_string(id);
    return res;

}


int read_directory(const string &name, vector<string> &v) {
    int count = 0;
    v.clear();
    DIR* dirp = opendir(name.c_str());
    struct dirent *dp;
    string dot = ".";
    string two_dot = "..";
    while ((dp = readdir(dirp)) != NULL) {
        if (dp->d_name != dot && dp->d_name != two_dot) {
            v.push_back(dp->d_name);
            count++;
        }
    }
    closedir(dirp);
    return count;
}


void get_information_from_parent(

    const int pd[PIPE_ENDS_NUM], 
    string &command

) {

    close(pd[WRITE]);
    char buff[BUFF_SIZE];

    read(pd[READ], buff, sizeof(buff));
    command = buff;

    close(pd[READ]);
}


void give_information_to_child(
    
    const int pd[PIPE_ENDS_NUM], 
    const string &command

) {

    write(pd[WRITE], command.c_str(), command.length() + 1);
    
}


void create_child(
    const string &child_process,
    const string &command,
    const string &child_dir,
    const string &fifo_prefix,
    const int &child_index
) {

    int pd[PIPE_ENDS_NUM];
    pipe(pd);

    string fifo_path = get_fifo_path(fifo_prefix, child_index);
    mkfifo(fifo_path.c_str(), 0777);

    int pid = fork();
    
    // Parent Process
    if (pid > 0) {

        close(pd[READ]);
        give_information_to_child(pd, command);            

    }

    //Child Process
    else if (pid == 0) {

        char pd_read[BUFF_SIZE], pd_write[BUFF_SIZE];

        int read_len = sprintf(pd_read, "%d", pd[READ]);
        pd_read[read_len] = '\0';

        int write_len = sprintf(pd_write, "%d", pd[WRITE]);
        pd_write[write_len] = '\0';

        int com_len = child_process.length();
        char com[com_len + 1];
        strcpy(com, child_process.c_str());

        int dir_len = child_dir.length();
        char dir[dir_len + 1];
        strcpy(dir, child_dir.c_str());

        int path_len = fifo_path.length();
        char path[path_len + 1];
        strcpy(path, fifo_path.c_str());

        char *argvs[] = { com, pd_read, pd_write, dir, path, NULL };
        execv(argvs[0], argvs);

    }

    else {
        cout << "Fork Error" << endl;
        exit(1);
    }

}


void create_all_childs(

    const vector<string> &child_dirs, 
    const string &child_process,
    const string &command,
    const string &mydir, 
    const string &fifo_prefix

) {
    int child_dirs_count = child_dirs.size();
    for (int i = 0; i < child_dirs_count; i++) {
        string child_dir = mydir + "/" + child_dirs[i];
        create_child(
            child_process,
            command,
            child_dir,
            fifo_prefix,
            i
        );

    }

}


void get_childs_result(
    
    vector<int> &res,
    const int &size,
    const string &prefix

) {

    res.clear();

    for (int i = 0; i < size; i++) {

        char buff[BUFF_SIZE];
        string fifo_path = get_fifo_path(prefix, i);
        int fifo = open(fifo_path.c_str(), O_RDONLY);
        int len = read(fifo, buff, sizeof(buff));
        
        string res_str = buff;
        if (res_str != FAIL_RES)
            res.push_back(atoi(res_str.c_str()));

    }

}


int find_max_or_min(const vector<int> &res, const string &command) {

    int max_ = res[0];
    int min_ = res[0];
    int res_count = res.size();
    for (int i = 0; i < res_count; i++) {

        if(res[i] <  min_)
            min_ = res[i];
        if(res[i] > max_)
            max_ = res[i];

    }

    if(command == MAX_COMMAND)
        return max_;
    else
        return min_;
    
}


string calculate_response(

    const string &command,
    const int &childs_count,
    const string &child_fifo_prefix

) {

    string base_command;
    istringstream ss(command);
    ss >> base_command;

    string res;

    vector<int> childs_res;
    get_childs_result(childs_res, childs_count, child_fifo_prefix);

    int childs_res_count = childs_res.size();
    
    if (childs_res_count == 0) {
        res = FAIL_RES;
    }
    else {
        int res_num = find_max_or_min(childs_res, base_command);
        res = to_string(res_num);
    }

    return res;

}


void unlink_pipes(const string &prefix, const int &count) {

    for (int i = 0; i < count; i++) {

        string path = get_fifo_path(prefix, i);
        unlink(path.c_str());

    }

}


void common_main(
    int argc, 
    char *argv[], 
    const string &child_fifo_prefix, 
    const string &child_exec_name    
) {

    char buff[BUFF_SIZE];

    string command, myfifo, mydir;

    int pd[PIPE_ENDS_NUM];
    pd[READ] = atoi(argv[1]);
    pd[WRITE] = atoi(argv[2]);
    mydir = argv[3];
    myfifo = argv[4];

    get_information_from_parent(pd, command);

    string prefix = myfifo + "_" + child_fifo_prefix;
    
    vector<string> child_names;
    int childs_count = read_directory(mydir, child_names);

    
    create_all_childs(child_names, child_exec_name, command, mydir, prefix);    
    
    string res = calculate_response(command, childs_count, prefix);
    
    int wpid, status;
    while((wpid = wait(&status)) > 0);
    unlink_pipes(prefix, childs_count);

    int pipe = open(myfifo.c_str(), O_WRONLY);
    write(pipe, res.c_str(), res.length() + 1);
    close(pipe);

    exit(1);

}