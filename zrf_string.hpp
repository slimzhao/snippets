/*
 * =====================================================================================
 *
 *       Filename:  zrf_string.hpp
 *
 *    Description:  string utility
 *
 *        Version:  1.0
 *        Created:  2012-4-21 13:49:02
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zhao.rufei
 *   Organization:  
 *
 * =====================================================================================
 */
#include <iosfwd>
#include <locale>

/// right-trim the space(isspace(c)) for string and wstring
/// @param T: actually only string and wstring in mind
/// @param str: instance of string or wstring
/// @return: the str
template<typename T>
T & rtrim(T & str)
{
    // What's the default locale?
    locale loc;

    typename T::size_type siz = str.size();
    typename string::size_type s = siz;
    for(; s > 0; --s)
    {
        if ( not std::isspace(str[s - 1], loc) )
            break;
    }
    if (siz > s)
    {
        str.resize(s, char());
    }
    return str;
}

/// left-trim the space(isspace(c)) for string and wstring
/// @param T: actually only string and wstring in mind
/// @param str: instance of string or wstring
/// @return: the str
template<typename T>
T & ltrim(T & str)
{
    // What's the default locale?
    locale loc;

    typename T::size_type siz = str.size();
    typename string::size_type s = 0;
    for(; s < siz; ++s)
    {
        if ( not std::isspace(str[s], loc) )
            break;
    }
    if (s > 0)
    {
        str.erase(0, s);
    }
    return str;
}

/// trim(left and right) the space(isspace(c)) for string and wstring
/// @param T: actually only string and wstring in mind
/// @param str: instance of string or wstring
/// @return: the str
template<typename T>
inline T & trim(T & str)
{
    return ltrim( rtrim(str ));
}

template<typename T>
inline T * rtrim(T * str)
{
    str->wish_a_compile_time_error();
    return str;
}

template<typename T>
inline T * ltrim(T * str)
{
    str->wish_a_compile_time_error();
    return str;
}

template<typename T>
inline T * trim(T * str)
{
    str->wish_a_compile_time_error();
    return str;
}

namespace pri {
    template<typename T>
    inline T * rtrim(T * str)
    {
        locale loc;
        T * end = str;
        while( *end ) { end++; }

        while( end-- > str)
        {
            if (not std::isspace(*end, loc) )
            {
                // current char *end is not space, next char is space,
                // set next char to NUL
                *(end + 1) = T();
                return str;
            }
        }

        if (std::isspace(*str, loc))
            *str = T();
        return str;
    }

    template<typename T>
    inline T * ltrim(T * str)
    {
        locale loc;
        T * p = str;
        while( *p )
        {
            if (not std::isspace(*p, loc) )
            {
                break;
            }
            p++;
        }

        if (p > str)
        {
            T * tp = p;
            for(; *tp != 0; ++tp) { NULL; }
            memmove(str, p, (tp - p) * sizeof(*str) + 1);
        }

        return str;
    }
}

template<>
inline char * trim(char * str)
{
    return pri::ltrim( pri::rtrim(str) );
}

template<>
inline char * ltrim(char * str)
{
    return pri::ltrim(str);
}

template<>
inline char * rtrim(char * str)
{
    return pri::rtrim(str);
}

template<>
inline wchar_t * trim(wchar_t * str)
{
    return pri::ltrim( pri::rtrim(str) );
}

template<>
inline wchar_t * ltrim(wchar_t * str)
{
    return pri::ltrim(str);
}

template<>
inline wchar_t * rtrim(wchar_t * str)
{
    return pri::rtrim(str);
}

// special version for CString or others?
