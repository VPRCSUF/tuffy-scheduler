# Directory containing test files
TEST_PATH     := test
# Space-separated list of header files (e.g., algebra.hpp)
HEADERS       := scheduler.hpp
# Space-separated list of implementation files (e.g., algebra.cpp)
IMPLEMS       := scheduler.cpp
# File containing main
DRIVER        := main.cpp
# Expected name of executable file
EXECFILE      := main
CLANGTDY_CHKS := *,-google-build-using-namespace,-fuchsia-default-arguments,-llvm-header-guard,-modernize-use-nodiscard,-google-runtime-references,-cppcoreguidelines-avoid-c-arrays,-hicpp-avoid-c-arrays,-modernize-avoid-c-arrays,-cppcoreguidelines-pro-type-member-init,-hicpp-member-init,-llvm-include-order,-cppcoreguidelines-pro-bounds-array-to-pointer-decay,-hicpp-no-array-decay,-cppcoreguidelines-pro-bounds-pointer-arithmetic,-fuchsia-overloaded-operator,-cppcoreguidelines-pro-bounds-constant-array-index,-cppcoreguidelines-owning-memory,-hicpp-use-auto,-modernize-use-auto,-modernize-use-default-member-init,-hicpp-special-member-functions,-modernize-pass-by-value,-cppcoreguidelines-special-member-functions,-google-explicit-constructor,-hicpp-explicit-conversions
