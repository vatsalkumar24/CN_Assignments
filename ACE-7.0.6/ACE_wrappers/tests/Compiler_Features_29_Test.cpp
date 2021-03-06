/**
 * This program checks if the compiler doesn't have a certain bug
 * that we encountered when testing C++11 features
 */

#include "test_config.h"

#include <cstdint>

class A
{
public:
  static constexpr char const* adapter_name = "A";
  static constexpr float pi = 3.14150f;
};

int
run_main (int, ACE_TCHAR *[])
{
  ACE_START_TEST (ACE_TEXT("Compiler_Features_29_Test"));

  ACE_DEBUG ((LM_DEBUG, "Variable %C\n", A::adapter_name));

  ACE_END_TEST;

  return 0;
}
