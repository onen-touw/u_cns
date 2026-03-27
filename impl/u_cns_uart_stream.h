/**
 * @file impl/u_cns_uart_stream.h
 * @brief Internal implementation (not for direct use)
 * 
 * Don't include this file directly! Use @ref u_cns.h
 * 
 * @ingroup impl_details
 * @internal
 */

#pragma once

#if __has_include("u_drivers/u_uart.h")

#include "u_cns_io_base.h"
#include "u_drivers/u_uart.h"

namespace __u_console
{
    class u_cns_uart_io_t : public __u_console::io_base_t
    {
    private:
        ufo::u_uart_t* _uart = nullptr;
    public:
        u_cns_uart_io_t(ufo::u_uart_t* uart) : _uart(uart) {}
        ~u_cns_uart_io_t() {}

        virtual size_t write(const std::string& s) override
        {
            return _uart->write(s.c_str(), s.size());
        }

        virtual size_t write(const char* msg, size_t sz) override 
        {
            return _uart->write(msg, sz);
        }
        
        virtual size_t write(char c)
        {
            return _uart->write(c);
        }

        virtual size_t available()
        {
            return _uart->available();
        }
        virtual char read()
        {
            return _uart->read();
        }
};
} // __u_console
#define U_CNS_UART_STREAM_DEFINED
#endif // __has_include("u_drivers/u_uart.h")