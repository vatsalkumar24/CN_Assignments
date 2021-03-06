/**
 * @file Bug_3709_Regression_Test.cpp
 *
 * Reproduces the problems reported in bug 3709
 *   http://bugzilla.dre.vanderbilt.edu/show_bug.cgi?id=3709
 */

#include "test_config.h"
#include "ace/ACE.h"
#include "ace/OS_NS_stdio.h"
#include <vector>

using namespace std;

template<template<typename U, typename = std::allocator<U> > class container, typename DT>
container<DT> initializer(const DT &d)
{
  container<DT> t ;
  t.insert(t.end(), d);
  return t;
}

int
run_main (int, ACE_TCHAR *[])
{
  ACE_START_TEST (ACE_TEXT ("Bug_3709_Regression_Test"));

  vector<int> v = initializer<vector>(5);
  v.clear ();

  ACE_END_TEST;

  return 0;
}
