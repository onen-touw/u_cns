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
 * @file impl/u_cns_streambuf.h
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
    class u_cns_streambuf_t
    {
    private:
        std::string _buffer;
    public:
        u_cns_streambuf_t(size_t cap) 
        {
            _buffer.reserve(cap);
        }
        ~u_cns_streambuf_t() {}

        void push_back(char c) {
            if (_buffer.size() + 1 > _buffer.capacity())
            {
                return;
            }
            
            _buffer.push_back(c);
        }

        void pop_back() 
        {
            _buffer.pop_back();
        }

        void clear()
        {
            _buffer.clear();
        }

        size_t size() const { return _buffer.size(); }
        const std::string& str() const {return _buffer; }

        u_cns_streambuf_t &operator<<(char c)
        {
            _buffer.push_back(c);
            return *this;
        }

    };


} // namespace __u_console
