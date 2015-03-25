#ifndef STATIC_ASSERTS_H_INCLUDED
#define STATIC_ASSERTS_H_INCLUDED

namespace ztest {

template<typename T1, typename T2>
struct StaticAssertTypeEqHelper;

template<typename T>
struct StaticAssertTypeEqHelper<T, T> {};

template<typename T1, typename T2>
bool StaticAssertTypeEq() {
  StaticAssertTypeEqHelper<T1, T2>();
  return true;
}

}

#endif // STATIC_ASSERTS_H_INCLUDED
