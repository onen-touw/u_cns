#pragma once

#include "impl/u_cns_console.h"
#include "impl/u_cns_uart_stream.h"

/**
 * @file u_cns.h
 * @brief Main file of UFO Console module
 * @ingroup public_api
 * 
 * This file provides all the necessary aliases for working with the console.
 * All implementation code is hidden in the impl/ directory.
 * 
 * Usage example:
 * @include docs/examples/basic_usage.cpp
 */

namespace ufo
{
    /**
     * @ingroup public_api
     * @brief Main console class
     * 
     * Provides an interface for registration commands and managing the console.
     * 
     * @note The class supports move-only, copying is prohibited.
     * @warning The console runs in a single thread
     * 
     * @see __u_console::console_t
     * 
     * @code{.cpp}
     * // Create console
     * ufo::u_console_t console(&io, 255);
     * 
     * // Command registr
     * console.mk_blank("status", "Show system status", [](const ufo::u_console_msg_block_t& bl) {
     *     bl << "System is running\n";
     * });
     * 
     * // Run in thread
     * ufo::thread task(console.ctask, std::move(console));
     * @endcode
     */
    using u_console_t = __u_console::console_t;

    /**
     * @ingroup public_api
     * @brief Console message block
     * 
     * This class is used in command callbacks for:
     * - Outputting information (operator<<)
     * - Accessing the argument parser (get_opt_list())
     * - Reading user input (read_line())
     * - Console cycle in concole command to execute subprocesses (run_internal())
     * 
     * @note The object is passed to the callback by const reference.
     * 
     * @see __u_console::msg_block_t
     * 
     * @code{.cpp}
     * // Example of use in a command
     * console.mk_blank("calc", "Simple calculator", [](const ufo::u_console_msg_block_t& bl) {
     *     // Parsing arguments
     *     const auto& parser = bl.get_opt_list();
     *     int a = 0, b = 0;
     *     
     *     if (parser.bind(&a, "--a") && parser.bind(&b, "--b")) {
     *         bl << "Result: " << (a + b) << "\n";
     *     } else {
     *         bl << "Usage: calc --a=10 --b=20\n";
     *     }
     * });
     * @endcode
     */
    using u_console_msg_block_t = __u_console::msg_block_t;


#ifdef U_CNS_UART_STREAM_DEFINED

    /**
     * @ingroup public_api
     * @brief UART adapter for console
     * 
     * Provides interaction with the UART driver.
     * Available only if u_drivers/u_uart.h is included.
     * 
     * @note Implements the __u_console::io_base_t interface
     * 
     * @code{.cpp}
     * #include "u_drivers/u_uart.h"
     * 
     * ufo::u_uart_t uart;  // initialized UART driver
     * ufo::u_console_uart_stream_t io(&uart);
     * ufo::u_console_t console(&io, 255);
     * @endcode
     */
    using u_console_uart_stream_t = __u_console::u_cns_uart_io_t;
#endif // U_CNS_UART_STREAM_DEFINED
    
} // ufo