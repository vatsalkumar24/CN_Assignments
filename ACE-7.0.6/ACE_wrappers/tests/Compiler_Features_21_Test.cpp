/**
 * This program checks if the compiler doesn't have a certain bug
 * that we encountered when testing C++11 features
 */

#include "test_config.h"

template<class _T1>
struct A
{
  _T1 a;
  constexpr A() : a() { }
};

struct B
{
  B() : b(new A<int>[0]) {}
  ~B() { delete [] b; }
  A<int> *b;
};

int xxx()
{
  B local_array;
  return 0;
}

int
run_main (int, ACE_TCHAR *[])
{
  ACE_START_TEST (ACE_TEXT("Compiler_Features_21_Test"));

  ACE_DEBUG ((LM_INFO,
              ACE_TEXT ("Compiler Feature 21 Test does compile and run.\n")));

  int retval = xxx();

  ACE_END_TEST;

  return retval;
}
