#include "main.h"
#include "utils.h"
using namespace std;


int main(int argc, char *argv[]) {
    
    string province_fifo_prefix = PROVINCE_PREFIX;
    string province_exec_name = PROVINCE_PROCESS;
    common_main(argc, argv, province_fifo_prefix, province_exec_name);

}