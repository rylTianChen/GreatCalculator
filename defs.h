#ifndef DEFS_GR
#define DEFS_GR 5

#include<vector>
typedef std::vector<int> vi;
typedef long long ll;

#define COLOR_RES "\033[36m"
#define COLOR_ERR "\033[31m"
#define COLOR_INS "\033[33m"
#define COLOR_ORI "\033[0m"

constexpr int NO_ERROR = 0;

constexpr int DIVISION_BY_ZERO = 1;
constexpr int NEGATIVE_POWER = 2;
constexpr int ZERO_POW_ZERO = 3;
constexpr int MODULE_BY_ZERO = 4;
constexpr int LARGE_RES = 5;

constexpr int INCOMPLETE_INPUT = 11;
constexpr int REDUNDANT_CONTENT = 12;
constexpr int UNKNOWN_CHAR = 13;

const char version[] = "1.5";

#endif
