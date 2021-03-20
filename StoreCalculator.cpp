#include "main.h"
#include "utils.h"
using namespace std;

int create_command_childs(const string &commands_path, const string &assets_dir) {
    
    string command;
    int commands_count = 0;

    fstream file;
    file.open(commands_path);

    while (getline(file, command)) {
        create_child(COMMAND_PROCESS, command, assets_dir, COMMAND_PREFIX, commands_count);
        commands_count++;
    }

    file.close();

    return commands_count;

}


void print_command_output (const string &pipe_path) {

    char buff[BUFF_SIZE];
    int pipe = open(pipe_path.c_str(), O_RDONLY);

    read(pipe, buff, sizeof(buff));
    string pipe_val = buff;

    close(pipe);
    
    cout << pipe_val << endl;

}


int main(int argc, char* argv[]) {
    string commands_path = argv[1];
    string assets_dir = argv[2];

    char buf[BUFF_SIZE];

    int commands_count = create_command_childs(commands_path, assets_dir);

    for(int i = 0; i < commands_count; i++) {

        string pipe_path = get_fifo_path(COMMAND_PREFIX, i);
        print_command_output(pipe_path);

    }

    int status, wpid;
    while ((wpid = wait(&status)) > 0);
    
    unlink_pipes(COMMAND_PREFIX, commands_count);
    
    return 0;
}