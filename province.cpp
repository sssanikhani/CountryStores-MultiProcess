#include "main.h"
#include "utils.h"
using namespace std;


int main(int argc, char *argv[]) {
    
    string city_fifo_prefix = CITY_PREFIX;
    string city_exec_name = CITY_PROCESS;
    common_main(argc, argv, city_fifo_prefix, city_exec_name);

}