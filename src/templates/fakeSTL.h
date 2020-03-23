/*
 * ====================== fakeSTL.h ==========================
 *                          -- tpr --
 *                                        CREATE -- 2020.03.23
 *                                        MODIFY -- 
 * ----------------------------------------------------------
 * stl 现有模版工具的 抄录（源自 cppreference.cpm ）
 */
#ifndef TPR_SMALL_FUNCS_H
#define TPR_SMALL_FUNCS_H
#include "pch.h"

namespace fake_stl_1{//~ fake_stl ~


//=======================================================//
//               std::integral_constant
//-------------------------------------------------------//
// 包装一个指定类型的 静态常量
// 是 C++ type traits 的基础
// ----
template<class T, T v>
struct integral_constant {
    static constexpr T value = v;
    using value_type = T;
    using type = integral_constant; // using injected-class-name
    constexpr operator value_type() const noexcept { return value; }
    constexpr value_type operator()() const noexcept { return value; }
};

// Helper templates:
template <bool B>
using bool_constant = integral_constant<bool, B>;
//
using true_type = integral_constant<bool, true>;
using false_type = integral_constant<bool, false>;




//=======================================================//
//                 std::is_same
//-------------------------------------------------------//
// 判断两种类型 是否相同
// 通过 模板函数重载 来实现
// 继承自 std::integral_constant
template<class T, class U>
struct is_same : std::false_type {};
 
template<class T>
struct is_same<T, T> : std::true_type {};


// Helper variable template:
template< class T, class U >
inline constexpr bool is_same_v = is_same<T, U>::value;




//=======================================================//
//                std::conditional
//-------------------------------------------------------//
// 功能类似 三目运算符: ( B ? T : F )
// 通过 模板函数重载 来实现
// ---
template<bool B, class T, class F>
struct conditional { typedef T type; };
 
template<class T, class F>
struct conditional<false, T, F> { typedef F type; };


// Helper types:
template< bool B, class T, class F >
using conditional_t = typename conditional<B,T,F>::type;






//=======================================================//
//              std::remove_reference
//-------------------------------------------------------//
// 剥掉 参数类型T 的 const, &, && 外壳，获得最原本的 T 类型
// 无法将 指针 剥掉，比如 T*
// ---
template< class T > struct remove_reference      {typedef T type;};
template< class T > struct remove_reference<T&>  {typedef T type;};
template< class T > struct remove_reference<T&&> {typedef T type;};

// Helper types:
template< class T >
using remove_reference_t = typename remove_reference<T>::type;






//=======================================================//
//              std::remove_pointer
//-------------------------------------------------------//
// 剥掉 参数类型T 的 指针
template< class T > struct remove_pointer                    {typedef T type;};
template< class T > struct remove_pointer<T*>                {typedef T type;};
template< class T > struct remove_pointer<T* const>          {typedef T type;};
template< class T > struct remove_pointer<T* volatile>       {typedef T type;};
template< class T > struct remove_pointer<T* const volatile> {typedef T type;};

// Helper types:
template< class T >
using remove_pointer_t = typename remove_pointer<T>::type;



//=======================================================//
//                std::remove_extent
//-------------------------------------------------------//
// 如果 参数类型T 是一个 array，获得其 元素的类型 T
// 如果传入 多维数组: T[][]，将报错，只能改传 T[0] 来处理 首元素（也是个数组）
//
//
template<class T>
struct remove_extent { typedef T type; };
 
template<class T>
struct remove_extent<T[]> { typedef T type; };
 
template<class T, std::size_t N>
struct remove_extent<T[N]> { typedef T type; };


// Helper types:
template< class T >
using remove_extent_t = typename remove_extent<T>::type;




//=======================================================//
//                    std::rank
//-------------------------------------------------------//
// 若 参数类型T 不是数组，value 为0，否则，value 为 数组维度值
// 
template<class T>
struct rank : public std::integral_constant<std::size_t, 0> {};
 
template<class T>
struct rank<T[]> : public std::integral_constant<std::size_t, rank<T>::value + 1> {};
 
template<class T, std::size_t N>
struct rank<T[N]> : public std::integral_constant<std::size_t, rank<T>::value + 1> {};


// Helper types:
template< class T >
inline constexpr std::size_t rank_v = rank<T>::value;






}//~ fake_stl ~







#endif

