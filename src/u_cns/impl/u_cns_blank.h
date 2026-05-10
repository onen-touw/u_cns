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
 * @file impl/u_cns_blank.h
 * @brief Internal implementation (not for direct use)
 * @ingroup impl_details
 * @internal
 * 
 * Don't include this file directly! Use @ref u_cns.h
 */

#pragma once 
 
#include <string>
#include "u_cns_msg_block.h"

namespace __u_console
{
    class blank_t
    {        
    public:
        using callback_t = msg_block_t::cycle_callback_t;

    private:
        std::string _desc;
        callback_t _clb = nullptr;
    public:

        blank_t(const char* desc, callback_t foo) : 
        _desc(desc),
        _clb(foo){}

        blank_t(blank_t &&other) : 
            _desc(std::move(other._desc)),
            _clb(std::move(other._clb))
        {}

        blank_t& operator = (blank_t&& other) 
        {
            if (&other != this)
            {
                _desc = std::move(other._desc);
                _clb = other._clb;
                other._clb = nullptr;
            }
            return *this;
        }

        blank_t(const blank_t&) = delete;
        blank_t& operator= (const blank_t&) = delete;

        ~blank_t() {}

        const std::string& get_desc() const {
            return _desc;
        }

        void run(const msg_block_t& b) const {
            if (!_clb)
            {
                throw;
            }
            _clb(b);
        }
    };

} // __u_console
