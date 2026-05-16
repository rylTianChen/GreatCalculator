#ifndef DEFS_GR
#define DEFS_GR

typedef std::vector<int> vi;

constexpr int LEN_LIMIT = 1e8;
constexpr int POW_LIMIT = 8;

constexpr int NO_ERR = 0;

constexpr int DIVISION_BY_ZERO = 1;
constexpr int NEGATIVE_POWER = 2;
constexpr int ZERO_POW_ZERO = 3;
constexpr int MODULE_BY_ZERO = 4;
constexpr int LARGE_RES = 5;

constexpr int EXPR_ERR = 6;
constexpr int CAL_ERR = 7;

constexpr int INCOMPLETE_INPUT = 11;
constexpr int REDUNDANT_CONTENT = 12;
constexpr int UNKNOWN_CHAR = 13;
constexpr int MUCH_RPAR = 14;
constexpr int MUCH_LPAR = 15;
constexpr int EMPTY_INPUT = 16;

#define COLOR_RES "\033[36m"
#define COLOR_ERR "\033[31m"
#define COLOR_INS "\033[33m"
#define COLOR_ORI "\033[0m"

#endif
