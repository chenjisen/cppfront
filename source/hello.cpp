
#define CPP2_IMPORT_STD          Yes

//=== Cpp2 type declarations ====================================================


#include "cpp2util.h"

#line 1 "hello.cpp2"


//=== Cpp2 type definitions and function declarations ===========================

#line 1 "hello.cpp2"
auto main() -> int;

#line 8 "hello.cpp2"
[[nodiscard]] auto foo(cpp2::impl::in<int> n) -> double;

//=== Cpp2 function definitions =================================================

#line 1 "hello.cpp2"
auto main() -> int{
#line 2 "hello.cpp2"
    std::cout << "test parser: " << (1 + 2 * 3 - 4 / CPP2_ASSERT_NOT_ZERO_LITERAL(CPP2_TYPEOF(4),5) | 6 & 7) << "\n";
    std::vector numbers {-1, 123}; 
    std::cout << CPP2_ASSERT_IN_BOUNDS_LITERAL(numbers, 0) << " -> " << foo(CPP2_ASSERT_IN_BOUNDS_LITERAL(numbers, 0)) << "\n";
    std::cout << CPP2_ASSERT_IN_BOUNDS_LITERAL(numbers, 1) << " -> " << foo(CPP2_ASSERT_IN_BOUNDS_LITERAL(numbers, 1)) << "\n";
}

#line 8 "hello.cpp2"
[[nodiscard]] auto foo(cpp2::impl::in<int> n) -> double{
    return n / CPP2_ASSERT_NOT_ZERO(CPP2_TYPEOF(n),2.0); 
}

