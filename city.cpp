#include "main.h"
#include "utils.h"
using namespace std;


int main(int argc, char *argv[]) {
    
    string store_fifo_prefix = STORE_PREFIX;
    string store_exec_name = STORE_PROCESS;
    common_main(argc, argv, store_fifo_prefix, store_exec_name);

}