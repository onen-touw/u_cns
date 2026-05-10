/*
* u_cns is © 2026, Anton Granitov (onen-touw), BSTU Voenmeh
*
* u_cns is published and distributed under 
* the Academic Software License v1.0 (ASL).
*
* u_cns is distributed in the hope that it will be useful 
* for non-commercial academic research, but WITHOUT ANY WARRANTY; without
* even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  
* See the ASL for more details.
*
* You should have received a copy of the ASL along with this program; 
* if not, write to anton.granitov123@gmail.com or https://github.com/onen-touw.  
* It is also published at LICENSE.md in root folder of this repository.
*
* You may contact the original licensor at anton.granitov123@gmail.com or https://github.com/onen-touw.
*/

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