#ifndef MAIN_H
#define MAIN_H

#include <vector>
#include <string>
#include <string.h>
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sstream>
#include <fstream>

#define BUFF_SIZE 1024
#define READ 0
#define WRITE 1
#define PIPE_ENDS_NUM 2

//Command Parts
#define COM_BASE 0
#define COM_PRODUCT_ID 1
#define COM_SDATE 2
#define COM_FDATE 3

// CSV Line Parts
#define DATA_DATE 0
#define DATA_PRODUCT_ID 1
#define DATA_PRICE 2

#define COMMAND_PROCESS "./command"
#define PROVINCE_PROCESS "./province"
#define CITY_PROCESS "./city"
#define STORE_PROCESS "./store"

const std::string MAX_COMMAND = "MAX";
const std::string MIN_COMMAND = "MIN";

const std::string FAIL_RES = "-1";

const std::string COMMAND_PREFIX = "c_";
const std::string PROVINCE_PREFIX = "p_";
const std::string CITY_PREFIX = "c_";
const std::string STORE_PREFIX = "s_";

#endif