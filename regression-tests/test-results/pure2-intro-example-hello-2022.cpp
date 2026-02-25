
#define CPP2_INCLUDE_STD         Yes

//=== Cpp2 type declarations ====================================================


#include "cpp2util.h"

#line 1 "pure2-intro-example-hello-2022.cpp2"


//=== Cpp2 type definitions and function declarations ===========================

#line 1 "pure2-intro-example-hello-2022.cpp2"
[[nodiscard]] auto main() -> int;

#line 11 "pure2-intro-example-hello-2022.cpp2"
[[nodiscard]] auto decorate(auto& x) -> int;

#line 16 "pure2-intro-example-hello-2022.cpp2"
auto print_it(auto const& x, auto const& len) -> void;

//=== Cpp2 function definitions =================================================

#line 1 "pure2-intro-example-hello-2022.cpp2"
[[nodiscard]] auto main() -> int{
#line 2 "pure2-intro-example-hello-2022.cpp2"
    std::vector<std::string> vec {
            "hello", "2022"}; 

    for ( auto& str : cpp2::move(vec) ) {
        auto len {decorate(str)}; 
        print_it(str, cpp2::move(len));
    }
}

[[nodiscard]] auto decorate(auto& thing) -> int{
    thing = "[" + thing + "]";
    return CPP2_UFCS_0(ssize, thing); 
}

#line 16 "pure2-intro-example-hello-2022.cpp2"
auto print_it(auto const& x, auto const& len) -> void{
    std::cout 
        << ">> " << x 
        << " - length " 
        << len << "\n";
}

