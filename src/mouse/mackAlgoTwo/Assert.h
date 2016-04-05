#pragma once

#include <iostream>

#define OPENING "---------- Assertion failed! ----------"
#define CLOSING "---------------------------------------"

#define ASSERT_TR(condition)\
if (!(condition)) {\
    std::cerr << OPENING << std::endl\
              << "FILE: " <<  __FILE__  << std::endl\
              << "LINE: " <<  __LINE__  << std::endl\
              << "COND: " << #condition << std::endl\
              << CLOSING << std::endl;\
    exit(1);\
}

#define ASSERT_FA(condition)\
if (condition) {\
    std::cerr << OPENING << std::endl\
              << "FILE: " <<  __FILE__  << std::endl\
              << "LINE: " <<  __LINE__  << std::endl\
              << "COND: " << "!(" << #condition << ")" << std::endl\
              << CLOSING << std::endl;\
    exit(1);\
}

#define ASSERT_EQ(lhs, rhs)\
if (!((lhs) == (rhs))) {\
    std::cerr << OPENING << std::endl\
              << "FILE: " <<  __FILE__  << std::endl\
              << "LINE: " <<  __LINE__  << std::endl\
              << "COND: " << #lhs << " == " << #rhs << std::endl\
              << "LHS: " << lhs << std::endl\
              << "RHS: " << rhs << std::endl\
              << CLOSING << std::endl;\
    exit(1);\
}

#define ASSERT_NE(lhs, rhs)\
if (!((lhs) != (rhs))) {\
    std::cerr << OPENING << std::endl\
              << "FILE: " <<  __FILE__  << std::endl\
              << "LINE: " <<  __LINE__  << std::endl\
              << "COND: " << #lhs << " != " << #rhs << std::endl\
              << "LHS: " << lhs << std::endl\
              << "RHS: " << rhs << std::endl\
              << CLOSING << std::endl;\
    exit(1);\
}

#define ASSERT_LT(lhs, rhs)\
if (!((lhs) < (rhs))) {\
    std::cerr << OPENING << std::endl\
              << "FILE: " <<  __FILE__  << std::endl\
              << "LINE: " <<  __LINE__  << std::endl\
              << "COND: " << #lhs << " < " << #rhs << std::endl\
              << "LHS: " << lhs << std::endl\
              << "RHS: " << rhs << std::endl\
              << CLOSING << std::endl;\
    exit(1);\
}

#define ASSERT_LE(lhs, rhs)\
if (!((lhs) <= (rhs))) {\
    std::cerr << OPENING << std::endl\
              << "FILE: " <<  __FILE__  << std::endl\
              << "LINE: " <<  __LINE__  << std::endl\
              << "COND: " << #lhs << " <= " << #rhs << std::endl\
              << "LHS: " << lhs << std::endl\
              << "RHS: " << rhs << std::endl\
              << CLOSING << std::endl;\
    exit(1);\
}