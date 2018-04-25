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
// Do not change this file directly. Instead change CFunctionMockHelper.m4
// and regenerate this file.
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
: public TypeIntrospection<T() >
{
    using argument_tuple_t = std::tuple<ARGS...>;
};


/**
 * Creates a bridge between a global function with 0 parameters and GMock
 * The resulting mock class has the name METHODMock, and is a standard GMock class.
 * Additionally, a global function METHOD is generated which calls the mock with the provided parameters.
 *
 * This is not thread-safe since a static variable is used to dispatch to the appropriate mock class.
 *
 * @param METHOD name of method to mock
 * @param MTYPE type of method (usual GMock syntax)
 */
#define SPECTRE_MOCK_INTERFACE_0(METHOD, MTYPE)                        \
    class SPECTRE_MOCK_##METHOD##_INTERFACE {                           \
    public:                                                             \
    virtual TypeIntrospection<MTYPE>::return_t METHOD(std::tuple_element<0, TypeIntrospection<MTYPE>::argument_tuple_t>::type arg0) = 0; \
                                                                        \
    static SPECTRE_MOCK_##METHOD##_INTERFACE* S_MOCK_INSTANCE;          \
    };                                                                  \
    SPECTRE_MOCK_##METHOD##_INTERFACE* SPECTRE_MOCK_##METHOD##_INTERFACE::S_MOCK_INSTANCE = nullptr; \
                                                                        \
    template<typename T = TypeIntrospection<MTYPE>::return_t>           \
    typename std::enable_if<std::is_void<T>::value>::type METHOD(std::tuple_element<0, TypeIntrospection<MTYPE>::argument_tuple_t>::type arg0) \
    {                                                                   \
        SPECTRE_MOCK_##METHOD##_INTERFACE::S_MOCK_INSTANCE->METHOD(arg0); \
    }                                                                   \
    template<typename T = TypeIntrospection<MTYPE>::return_t>           \
    typename std::enable_if<!std::is_void<T>::value, T>::type METHOD(std::tuple_element<0, TypeIntrospection<MTYPE>::argument_tuple_t>::type arg0) \
    {                                                                   \
        return SPECTRE_MOCK_##METHOD##_INTERFACE::S_MOCK_INSTANCE->METHOD(arg0); \
    }                                                                   \
    class METHOD##Mock : public SPECTRE_MOCK_##METHOD##_INTERFACE \
    {                                                                   \
    public:                                                             \
        METHOD##Mock()                                                \
            {                                                           \
                SPECTRE_MOCK_##METHOD##_INTERFACE::S_MOCK_INSTANCE = this; \
            }                                                           \
                                                                        \
        MOCK_METHOD0(METHOD, MTYPE);                                    \
    };

/**
 * Creates a bridge between a global function with 1 parameters and GMock
 * The resulting mock class has the name METHODMock, and is a standard GMock class.
 * Additionally, a global function METHOD is generated which calls the mock with the provided parameters.
 *
 * This is not thread-safe since a static variable is used to dispatch to the appropriate mock class.
 *
 * @param METHOD name of method to mock
 * @param MTYPE type of method (usual GMock syntax)
 */
#define SPECTRE_MOCK_INTERFACE_1(METHOD, MTYPE)                        \
    class SPECTRE_MOCK_##METHOD##_INTERFACE {                           \
    public:                                                             \
    virtual TypeIntrospection<MTYPE>::return_t METHOD(std::tuple_element<0, TypeIntrospection<MTYPE>::argument_tuple_t>::type arg0) = 0; \
                                                                        \
    static SPECTRE_MOCK_##METHOD##_INTERFACE* S_MOCK_INSTANCE;          \
    };                                                                  \
    SPECTRE_MOCK_##METHOD##_INTERFACE* SPECTRE_MOCK_##METHOD##_INTERFACE::S_MOCK_INSTANCE = nullptr; \
                                                                        \
    template<typename T = TypeIntrospection<MTYPE>::return_t>           \
    typename std::enable_if<std::is_void<T>::value>::type METHOD(std::tuple_element<0, TypeIntrospection<MTYPE>::argument_tuple_t>::type arg0) \
    {                                                                   \
        SPECTRE_MOCK_##METHOD##_INTERFACE::S_MOCK_INSTANCE->METHOD(arg0); \
    }                                                                   \
    template<typename T = TypeIntrospection<MTYPE>::return_t>           \
    typename std::enable_if<!std::is_void<T>::value, T>::type METHOD(std::tuple_element<0, TypeIntrospection<MTYPE>::argument_tuple_t>::type arg0) \
    {                                                                   \
        return SPECTRE_MOCK_##METHOD##_INTERFACE::S_MOCK_INSTANCE->METHOD(arg0); \
    }                                                                   \
    class METHOD##Mock : public SPECTRE_MOCK_##METHOD##_INTERFACE \
    {                                                                   \
    public:                                                             \
        METHOD##Mock()                                                \
            {                                                           \
                SPECTRE_MOCK_##METHOD##_INTERFACE::S_MOCK_INSTANCE = this; \
            }                                                           \
                                                                        \
        MOCK_METHOD1(METHOD, MTYPE);                                    \
    };

/**
 * Creates a bridge between a global function with 2 parameters and GMock
 * The resulting mock class has the name METHODMock, and is a standard GMock class.
 * Additionally, a global function METHOD is generated which calls the mock with the provided parameters.
 *
 * This is not thread-safe since a static variable is used to dispatch to the appropriate mock class.
 *
 * @param METHOD name of method to mock
 * @param MTYPE type of method (usual GMock syntax)
 */
#define SPECTRE_MOCK_INTERFACE_2(METHOD, MTYPE)                        \
    class SPECTRE_MOCK_##METHOD##_INTERFACE {                           \
    public:                                                             \
    virtual TypeIntrospection<MTYPE>::return_t METHOD(std::tuple_element<0, TypeIntrospection<MTYPE>::argument_tuple_t>::type arg0, \
                                              std::tuple_element<1, TypeIntrospection<MTYPE>::argument_tuple_t>::type arg1) = 0; \
                                                                        \
    static SPECTRE_MOCK_##METHOD##_INTERFACE* S_MOCK_INSTANCE;          \
    };                                                                  \
    SPECTRE_MOCK_##METHOD##_INTERFACE* SPECTRE_MOCK_##METHOD##_INTERFACE::S_MOCK_INSTANCE = nullptr; \
                                                                        \
    template<typename T = TypeIntrospection<MTYPE>::return_t>           \
    typename std::enable_if<std::is_void<T>::value>::type METHOD(std::tuple_element<0, TypeIntrospection<MTYPE>::argument_tuple_t>::type arg0, \
                                              std::tuple_element<1, TypeIntrospection<MTYPE>::argument_tuple_t>::type arg1) \
    {                                                                   \
        SPECTRE_MOCK_##METHOD##_INTERFACE::S_MOCK_INSTANCE->METHOD(arg0,arg1); \
    }                                                                   \
    template<typename T = TypeIntrospection<MTYPE>::return_t>           \
    typename std::enable_if<!std::is_void<T>::value, T>::type METHOD(std::tuple_element<0, TypeIntrospection<MTYPE>::argument_tuple_t>::type arg0, \
                                              std::tuple_element<1, TypeIntrospection<MTYPE>::argument_tuple_t>::type arg1) \
    {                                                                   \
        return SPECTRE_MOCK_##METHOD##_INTERFACE::S_MOCK_INSTANCE->METHOD(arg0,arg1); \
    }                                                                   \
    class METHOD##Mock : public SPECTRE_MOCK_##METHOD##_INTERFACE \
    {                                                                   \
    public:                                                             \
        METHOD##Mock()                                                \
            {                                                           \
                SPECTRE_MOCK_##METHOD##_INTERFACE::S_MOCK_INSTANCE = this; \
            }                                                           \
                                                                        \
        MOCK_METHOD2(METHOD, MTYPE);                                    \
    };

/**
 * Creates a bridge between a global function with 3 parameters and GMock
 * The resulting mock class has the name METHODMock, and is a standard GMock class.
 * Additionally, a global function METHOD is generated which calls the mock with the provided parameters.
 *
 * This is not thread-safe since a static variable is used to dispatch to the appropriate mock class.
 *
 * @param METHOD name of method to mock
 * @param MTYPE type of method (usual GMock syntax)
 */
#define SPECTRE_MOCK_INTERFACE_3(METHOD, MTYPE)                        \
    class SPECTRE_MOCK_##METHOD##_INTERFACE {                           \
    public:                                                             \
    virtual TypeIntrospection<MTYPE>::return_t METHOD(std::tuple_element<0, TypeIntrospection<MTYPE>::argument_tuple_t>::type arg0, \
                                              std::tuple_element<1, TypeIntrospection<MTYPE>::argument_tuple_t>::type arg1, \
                                              std::tuple_element<2, TypeIntrospection<MTYPE>::argument_tuple_t>::type arg2) = 0; \
                                                                        \
    static SPECTRE_MOCK_##METHOD##_INTERFACE* S_MOCK_INSTANCE;          \
    };                                                                  \
    SPECTRE_MOCK_##METHOD##_INTERFACE* SPECTRE_MOCK_##METHOD##_INTERFACE::S_MOCK_INSTANCE = nullptr; \
                                                                        \
    template<typename T = TypeIntrospection<MTYPE>::return_t>           \
    typename std::enable_if<std::is_void<T>::value>::type METHOD(std::tuple_element<0, TypeIntrospection<MTYPE>::argument_tuple_t>::type arg0, \
                                              std::tuple_element<1, TypeIntrospection<MTYPE>::argument_tuple_t>::type arg1, \
                                              std::tuple_element<2, TypeIntrospection<MTYPE>::argument_tuple_t>::type arg2) \
    {                                                                   \
        SPECTRE_MOCK_##METHOD##_INTERFACE::S_MOCK_INSTANCE->METHOD(arg0,arg1,arg2); \
    }                                                                   \
    template<typename T = TypeIntrospection<MTYPE>::return_t>           \
    typename std::enable_if<!std::is_void<T>::value, T>::type METHOD(std::tuple_element<0, TypeIntrospection<MTYPE>::argument_tuple_t>::type arg0, \
                                              std::tuple_element<1, TypeIntrospection<MTYPE>::argument_tuple_t>::type arg1, \
                                              std::tuple_element<2, TypeIntrospection<MTYPE>::argument_tuple_t>::type arg2) \
    {                                                                   \
        return SPECTRE_MOCK_##METHOD##_INTERFACE::S_MOCK_INSTANCE->METHOD(arg0,arg1,arg2); \
    }                                                                   \
    class METHOD##Mock : public SPECTRE_MOCK_##METHOD##_INTERFACE \
    {                                                                   \
    public:                                                             \
        METHOD##Mock()                                                \
            {                                                           \
                SPECTRE_MOCK_##METHOD##_INTERFACE::S_MOCK_INSTANCE = this; \
            }                                                           \
                                                                        \
        MOCK_METHOD3(METHOD, MTYPE);                                    \
    };

/**
 * Creates a bridge between a global function with 4 parameters and GMock
 * The resulting mock class has the name METHODMock, and is a standard GMock class.
 * Additionally, a global function METHOD is generated which calls the mock with the provided parameters.
 *
 * This is not thread-safe since a static variable is used to dispatch to the appropriate mock class.
 *
 * @param METHOD name of method to mock
 * @param MTYPE type of method (usual GMock syntax)
 */
#define SPECTRE_MOCK_INTERFACE_4(METHOD, MTYPE)                        \
    class SPECTRE_MOCK_##METHOD##_INTERFACE {                           \
    public:                                                             \
    virtual TypeIntrospection<MTYPE>::return_t METHOD(std::tuple_element<0, TypeIntrospection<MTYPE>::argument_tuple_t>::type arg0, \
                                              std::tuple_element<1, TypeIntrospection<MTYPE>::argument_tuple_t>::type arg1, \
                                              std::tuple_element<2, TypeIntrospection<MTYPE>::argument_tuple_t>::type arg2, \
                                              std::tuple_element<3, TypeIntrospection<MTYPE>::argument_tuple_t>::type arg3) = 0; \
                                                                        \
    static SPECTRE_MOCK_##METHOD##_INTERFACE* S_MOCK_INSTANCE;          \
    };                                                                  \
    SPECTRE_MOCK_##METHOD##_INTERFACE* SPECTRE_MOCK_##METHOD##_INTERFACE::S_MOCK_INSTANCE = nullptr; \
                                                                        \
    template<typename T = TypeIntrospection<MTYPE>::return_t>           \
    typename std::enable_if<std::is_void<T>::value>::type METHOD(std::tuple_element<0, TypeIntrospection<MTYPE>::argument_tuple_t>::type arg0, \
                                              std::tuple_element<1, TypeIntrospection<MTYPE>::argument_tuple_t>::type arg1, \
                                              std::tuple_element<2, TypeIntrospection<MTYPE>::argument_tuple_t>::type arg2, \
                                              std::tuple_element<3, TypeIntrospection<MTYPE>::argument_tuple_t>::type arg3) \
    {                                                                   \
        SPECTRE_MOCK_##METHOD##_INTERFACE::S_MOCK_INSTANCE->METHOD(arg0,arg1,arg2,arg3); \
    }                                                                   \
    template<typename T = TypeIntrospection<MTYPE>::return_t>           \
    typename std::enable_if<!std::is_void<T>::value, T>::type METHOD(std::tuple_element<0, TypeIntrospection<MTYPE>::argument_tuple_t>::type arg0, \
                                              std::tuple_element<1, TypeIntrospection<MTYPE>::argument_tuple_t>::type arg1, \
                                              std::tuple_element<2, TypeIntrospection<MTYPE>::argument_tuple_t>::type arg2, \
                                              std::tuple_element<3, TypeIntrospection<MTYPE>::argument_tuple_t>::type arg3) \
    {                                                                   \
        return SPECTRE_MOCK_##METHOD##_INTERFACE::S_MOCK_INSTANCE->METHOD(arg0,arg1,arg2,arg3); \
    }                                                                   \
    class METHOD##Mock : public SPECTRE_MOCK_##METHOD##_INTERFACE \
    {                                                                   \
    public:                                                             \
        METHOD##Mock()                                                \
            {                                                           \
                SPECTRE_MOCK_##METHOD##_INTERFACE::S_MOCK_INSTANCE = this; \
            }                                                           \
                                                                        \
        MOCK_METHOD4(METHOD, MTYPE);                                    \
    };

/**
 * Creates a bridge between a global function with 5 parameters and GMock
 * The resulting mock class has the name METHODMock, and is a standard GMock class.
 * Additionally, a global function METHOD is generated which calls the mock with the provided parameters.
 *
 * This is not thread-safe since a static variable is used to dispatch to the appropriate mock class.
 *
 * @param METHOD name of method to mock
 * @param MTYPE type of method (usual GMock syntax)
 */
#define SPECTRE_MOCK_INTERFACE_5(METHOD, MTYPE)                        \
    class SPECTRE_MOCK_##METHOD##_INTERFACE {                           \
    public:                                                             \
    virtual TypeIntrospection<MTYPE>::return_t METHOD(std::tuple_element<0, TypeIntrospection<MTYPE>::argument_tuple_t>::type arg0, \
                                              std::tuple_element<1, TypeIntrospection<MTYPE>::argument_tuple_t>::type arg1, \
                                              std::tuple_element<2, TypeIntrospection<MTYPE>::argument_tuple_t>::type arg2, \
                                              std::tuple_element<3, TypeIntrospection<MTYPE>::argument_tuple_t>::type arg3, \
                                              std::tuple_element<4, TypeIntrospection<MTYPE>::argument_tuple_t>::type arg4) = 0; \
                                                                        \
    static SPECTRE_MOCK_##METHOD##_INTERFACE* S_MOCK_INSTANCE;          \
    };                                                                  \
    SPECTRE_MOCK_##METHOD##_INTERFACE* SPECTRE_MOCK_##METHOD##_INTERFACE::S_MOCK_INSTANCE = nullptr; \
                                                                        \
    template<typename T = TypeIntrospection<MTYPE>::return_t>           \
    typename std::enable_if<std::is_void<T>::value>::type METHOD(std::tuple_element<0, TypeIntrospection<MTYPE>::argument_tuple_t>::type arg0, \
                                              std::tuple_element<1, TypeIntrospection<MTYPE>::argument_tuple_t>::type arg1, \
                                              std::tuple_element<2, TypeIntrospection<MTYPE>::argument_tuple_t>::type arg2, \
                                              std::tuple_element<3, TypeIntrospection<MTYPE>::argument_tuple_t>::type arg3, \
                                              std::tuple_element<4, TypeIntrospection<MTYPE>::argument_tuple_t>::type arg4) \
    {                                                                   \
        SPECTRE_MOCK_##METHOD##_INTERFACE::S_MOCK_INSTANCE->METHOD(arg0,arg1,arg2,arg3,arg4); \
    }                                                                   \
    template<typename T = TypeIntrospection<MTYPE>::return_t>           \
    typename std::enable_if<!std::is_void<T>::value, T>::type METHOD(std::tuple_element<0, TypeIntrospection<MTYPE>::argument_tuple_t>::type arg0, \
                                              std::tuple_element<1, TypeIntrospection<MTYPE>::argument_tuple_t>::type arg1, \
                                              std::tuple_element<2, TypeIntrospection<MTYPE>::argument_tuple_t>::type arg2, \
                                              std::tuple_element<3, TypeIntrospection<MTYPE>::argument_tuple_t>::type arg3, \
                                              std::tuple_element<4, TypeIntrospection<MTYPE>::argument_tuple_t>::type arg4) \
    {                                                                   \
        return SPECTRE_MOCK_##METHOD##_INTERFACE::S_MOCK_INSTANCE->METHOD(arg0,arg1,arg2,arg3,arg4); \
    }                                                                   \
    class METHOD##Mock : public SPECTRE_MOCK_##METHOD##_INTERFACE \
    {                                                                   \
    public:                                                             \
        METHOD##Mock()                                                \
            {                                                           \
                SPECTRE_MOCK_##METHOD##_INTERFACE::S_MOCK_INSTANCE = this; \
            }                                                           \
                                                                        \
        MOCK_METHOD5(METHOD, MTYPE);                                    \
    };

/**
 * Creates a bridge between a global function with 6 parameters and GMock
 * The resulting mock class has the name METHODMock, and is a standard GMock class.
 * Additionally, a global function METHOD is generated which calls the mock with the provided parameters.
 *
 * This is not thread-safe since a static variable is used to dispatch to the appropriate mock class.
 *
 * @param METHOD name of method to mock
 * @param MTYPE type of method (usual GMock syntax)
 */
#define SPECTRE_MOCK_INTERFACE_6(METHOD, MTYPE)                        \
    class SPECTRE_MOCK_##METHOD##_INTERFACE {                           \
    public:                                                             \
    virtual TypeIntrospection<MTYPE>::return_t METHOD(std::tuple_element<0, TypeIntrospection<MTYPE>::argument_tuple_t>::type arg0, \
                                              std::tuple_element<1, TypeIntrospection<MTYPE>::argument_tuple_t>::type arg1, \
                                              std::tuple_element<2, TypeIntrospection<MTYPE>::argument_tuple_t>::type arg2, \
                                              std::tuple_element<3, TypeIntrospection<MTYPE>::argument_tuple_t>::type arg3, \
                                              std::tuple_element<4, TypeIntrospection<MTYPE>::argument_tuple_t>::type arg4, \
                                              std::tuple_element<5, TypeIntrospection<MTYPE>::argument_tuple_t>::type arg5) = 0; \
                                                                        \
    static SPECTRE_MOCK_##METHOD##_INTERFACE* S_MOCK_INSTANCE;          \
    };                                                                  \
    SPECTRE_MOCK_##METHOD##_INTERFACE* SPECTRE_MOCK_##METHOD##_INTERFACE::S_MOCK_INSTANCE = nullptr; \
                                                                        \
    template<typename T = TypeIntrospection<MTYPE>::return_t>           \
    typename std::enable_if<std::is_void<T>::value>::type METHOD(std::tuple_element<0, TypeIntrospection<MTYPE>::argument_tuple_t>::type arg0, \
                                              std::tuple_element<1, TypeIntrospection<MTYPE>::argument_tuple_t>::type arg1, \
                                              std::tuple_element<2, TypeIntrospection<MTYPE>::argument_tuple_t>::type arg2, \
                                              std::tuple_element<3, TypeIntrospection<MTYPE>::argument_tuple_t>::type arg3, \
                                              std::tuple_element<4, TypeIntrospection<MTYPE>::argument_tuple_t>::type arg4, \
                                              std::tuple_element<5, TypeIntrospection<MTYPE>::argument_tuple_t>::type arg5) \
    {                                                                   \
        SPECTRE_MOCK_##METHOD##_INTERFACE::S_MOCK_INSTANCE->METHOD(arg0,arg1,arg2,arg3,arg4,arg5); \
    }                                                                   \
    template<typename T = TypeIntrospection<MTYPE>::return_t>           \
    typename std::enable_if<!std::is_void<T>::value, T>::type METHOD(std::tuple_element<0, TypeIntrospection<MTYPE>::argument_tuple_t>::type arg0, \
                                              std::tuple_element<1, TypeIntrospection<MTYPE>::argument_tuple_t>::type arg1, \
                                              std::tuple_element<2, TypeIntrospection<MTYPE>::argument_tuple_t>::type arg2, \
                                              std::tuple_element<3, TypeIntrospection<MTYPE>::argument_tuple_t>::type arg3, \
                                              std::tuple_element<4, TypeIntrospection<MTYPE>::argument_tuple_t>::type arg4, \
                                              std::tuple_element<5, TypeIntrospection<MTYPE>::argument_tuple_t>::type arg5) \
    {                                                                   \
        return SPECTRE_MOCK_##METHOD##_INTERFACE::S_MOCK_INSTANCE->METHOD(arg0,arg1,arg2,arg3,arg4,arg5); \
    }                                                                   \
    class METHOD##Mock : public SPECTRE_MOCK_##METHOD##_INTERFACE \
    {                                                                   \
    public:                                                             \
        METHOD##Mock()                                                \
            {                                                           \
                SPECTRE_MOCK_##METHOD##_INTERFACE::S_MOCK_INSTANCE = this; \
            }                                                           \
                                                                        \
        MOCK_METHOD6(METHOD, MTYPE);                                    \
    };

#define __CFUNCTIONMOCKHELPER_HPP__
#endif /*__CFUNCTIONMOCKHELPER_HPP__*/
