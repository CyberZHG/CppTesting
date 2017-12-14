#ifndef INCLUDE_STATIC_ASSERTS_H_
#define INCLUDE_STATIC_ASSERTS_H_

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

}  // namespace ztest

#endif  // INCLUDE_STATIC_ASSERTS_H_
