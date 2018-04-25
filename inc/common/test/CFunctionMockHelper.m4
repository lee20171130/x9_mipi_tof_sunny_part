dnl /****************************************************************************\
dnl * Copyright (C) 2017 pmdtechnologies ag
dnl *
dnl * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
dnl * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
dnl * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
dnl * PARTICULAR PURPOSE.
dnl *
dnl \****************************************************************************/
dnl
changecom($,)dnl
dnl Creates a list of arguments which types are based of the MTYPE of the main macro
dnl Arguments:
dnl 1: Number of arguments to extract
define(`GENERATE_ARGUMENT_LIST',`dnl
ifelse(`$#',`1',`GENERATE_ARGUMENT_LIST($1, $1)',`std::tuple_element<eval($1-$2), TypeIntrospection<MTYPE>::argument_tuple_t>::type arg`'eval($1-$2)`'dnl
ifelse(`$2',`1',`',`$1',`0',`',`, \
                                              GENERATE_ARGUMENT_LIST($1, decr($2))')')')dnl
dnl
dnl Creates a list in the form arg0,...,arg$1
dnl Arguments:
dnl 1: Number of argN
define(`GENERATE_MOCK_CALLER_ARGS',`dnl
ifelse(`$#',`1',`GENERATE_MOCK_CALLER_ARGS($1, $1)',`arg`'eval($1-$2)`'dnl
ifelse(`$2',`1',`',`$1',`0',`',`,GENERATE_MOCK_CALLER_ARGS($1, decr($2))')')')dnl
dnl
dnl
dnl Creates a SPECTRE_MOCK_INTERFACE_X macro definition
dnl Arguments:
dnl 1: Number of arguments of the functions which can be covered by this macro
define(`GENERATE_SPECTRE_MOCK_INTERFACE',`dnl
/**
 * Creates a bridge between a global function with $1 parameters and GMock
 * The resulting mock class has the name METHODMock, and is a standard GMock class.
 * Additionally, a global function METHOD is generated which calls the mock with the provided parameters.
 *
 * This is not thread-safe since a static variable is used to dispatch to the appropriate mock class.
 *
 * @param METHOD name of method to mock
 * @param MTYPE type of method (usual GMock syntax)
 */
#define SPECTRE_MOCK_INTERFACE_$1(METHOD, MTYPE)                        \
    class SPECTRE_MOCK_##METHOD##_INTERFACE {                           \
    public:                                                             \
    virtual TypeIntrospection<MTYPE>::return_t METHOD(GENERATE_ARGUMENT_LIST($1)) = 0; \
                                                                        \
    static SPECTRE_MOCK_##METHOD##_INTERFACE* S_MOCK_INSTANCE;          \
    };                                                                  \
    SPECTRE_MOCK_##METHOD##_INTERFACE* SPECTRE_MOCK_##METHOD##_INTERFACE::S_MOCK_INSTANCE = nullptr; \
                                                                        \
    template<typename T = TypeIntrospection<MTYPE>::return_t>           \
    typename std::enable_if<std::is_void<T>::value>::type METHOD(GENERATE_ARGUMENT_LIST($1)) \
    {                                                                   \
        SPECTRE_MOCK_##METHOD##_INTERFACE::S_MOCK_INSTANCE->METHOD(GENERATE_MOCK_CALLER_ARGS($1)); \
    }                                                                   \
    template<typename T = TypeIntrospection<MTYPE>::return_t>           \
    typename std::enable_if<!std::is_void<T>::value, T>::type METHOD(GENERATE_ARGUMENT_LIST($1)) \
    {                                                                   \
        return SPECTRE_MOCK_##METHOD##_INTERFACE::S_MOCK_INSTANCE->METHOD(GENERATE_MOCK_CALLER_ARGS($1)); \
    }                                                                   \
    class METHOD##Mock : public SPECTRE_MOCK_##METHOD##_INTERFACE \
    {                                                                   \
    public:                                                             \
        METHOD##Mock()                                                \
            {                                                           \
                SPECTRE_MOCK_##METHOD##_INTERFACE::S_MOCK_INSTANCE = this; \
            }                                                           \
                                                                        \
        MOCK_METHOD$1(METHOD, MTYPE);                                    \
    };
')dnl
dnl
dnl
/****************************************************************************\
* Copyright (C) 2017 pmdtechnologies ag
*
* THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
* KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
* PARTICULAR PURPOSE.
*
\****************************************************************************/
// **************************************************************************
// THIS FILE HAS BEEN GENERATED AUTOMATICALLY.
// Do not change this fi`'le directly. Instead change __file__
// and regenerate this fi`'le.
// **************************************************************************
#ifndef __CFUNCTIONMOCKHELPER_HPP__

#include <tuple>
#include <gmock/gmock.h>
#include <type_traits>

template<typename T>
struct TypeIntrospection;

template <typename T>
struct TypeIntrospection<T () >
{
    using return_t = T;
};

template <typename T, typename... ARGS>
struct TypeIntrospection<T (ARGS...) >
    :public TypeIntrospection<T()>
{
    using argument_tuple_t = std::tuple<ARGS...>;
};


GENERATE_SPECTRE_MOCK_INTERFACE(`0')
GENERATE_SPECTRE_MOCK_INTERFACE(`1')
GENERATE_SPECTRE_MOCK_INTERFACE(`2')
GENERATE_SPECTRE_MOCK_INTERFACE(`3')
GENERATE_SPECTRE_MOCK_INTERFACE(`4')
GENERATE_SPECTRE_MOCK_INTERFACE(`5')
GENERATE_SPECTRE_MOCK_INTERFACE(`6')
#define __CFUNCTIONMOCKHELPER_HPP__
#endif /*__CFUNCTIONMOCKHELPER_HPP__*/
