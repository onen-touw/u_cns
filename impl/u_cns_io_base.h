/**
 * @file impl/u_cns_io_base.h
 * @brief Internal implementation (not for direct use)
 * 
 * Don't include this file directly! Use @ref u_cns.h
 * 
 * @ingroup impl_details
 * @internal
 */


#pragma once
#include <string>

namespace __u_console
{
    class io_base_t
    {
    public:
        io_base_t(){}
        ~io_base_t(){}
        io_base_t(const io_base_t&) = delete;

        virtual size_t write(const std::string&) = 0;
        virtual size_t write(const char*, size_t) = 0;
        virtual size_t write(char) = 0;
        virtual size_t available() = 0;
        virtual char read() = 0;

    };


};