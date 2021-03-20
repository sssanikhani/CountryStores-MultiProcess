#include "main.h"
#include "utils.h"
using namespace std;


int main(int argc, char *argv[]) {
    
    char buff[BUFF_SIZE];

    string raw_command, myfifo, mypath;

    int pd[PIPE_ENDS_NUM];
    pd[READ] = atoi(argv[1]);
    pd[WRITE] = atoi(argv[2]);
    mypath = argv[3];
    myfifo = argv[4];

    get_information_from_parent(pd, raw_command);

    vector<string> command;
    split_str(raw_command, command, ' ');

    vector<vector<string>> data;
    read_csv_file(mypath, data);

    vector<int> wanted_prices;
    fetch_prices(
        data, 
        wanted_prices, 
        command[COM_PRODUCT_ID], 
        command[COM_SDATE], 
        command[COM_FDATE]
    );

    string result;

    if (wanted_prices.size() > 0) {

        int res_price = find_max_or_min(wanted_prices, command[COM_BASE]);
        result = to_string(res_price);

    }
    else {
        result = FAIL_RES;
    }
    

    int fifo = open(myfifo.c_str(), O_WRONLY);
    write(fifo, result.c_str(), result.length() + 1);
    close(fifo);

    exit(1);
}