/**
 * @file impl/u_cns_console.h
 * @brief Internal implementation (not for direct use)
 * @ingroup public_api
 * 
 * Don't include this file directly! Use @ref u_cns.h
 * 
 * This file contains the msg_block_t class, which is passed to the command callback functions
 * and provides an interface for working with input/output.
 */


#pragma once

#include "u_sys/utils.h"

#include <string>
#include <functional>

#include "u_cns_io_base.h"
#include "u_cns_streambuf.h"
#include "Console-parser/parser.h"
#include "string.h"


namespace __u_console
{
    enum class event_t
    {
        none,
        work,
        exit,
        error
    };

    /**
     * @ingroup public_api
     * @brief Console message block class
     * 
     * This class is the primary interface for interacting with the console within command callbacks. It provides methods for:
     * - Outputting information (operator<<)
     * - Accessing the argument parser (get_opt_list())
     * - Reading user input (read_line())
     * - Console cycle in concole command to execute subprocesses (run_internal())
     * 
     * @section output Information output
     * 
     * All basic data types are supported via overloaded operator<<:
     * @code{.cpp}
     * void my_command(const msg_block_t& bl) {
     *     bl << "Simple string\n";
     *     bl << "Number: " << 42 << "\n";
     *     bl << "Float: " << 3.14159f << "\n";
     *     bl << "Boolean: " << true << "\n";
     *     bl << "Pointer: " << (void*)0x1234 << "\n";
     * }
     * @endcode
     * 
     * @section parsing Parsing arguments
     * 
     * The registered command's callback receives the pre-parsed string. To access the arguments, use get_opt_list():
     * @code{.cpp}
     * void config_command(const msg_block_t& bl) {
     *     const auto& parser = bl.get_opt_list();
     *     
     *     int baudrate = 115200;
     *     if (parser.bind(&baudrate, "-b,--baudrate")) {
     *         bl << "Setting baudrate to: " << baudrate << "\n";
     *     }
     *     
     *     std::string mode;
     *     if (parser.bind(&mode, "-m,--mode")) {
     *         bl << "Mode: " << mode << "\n";
     *     }
     * }
     * @endcode
     * 
     * @section reading Reading additional input
     * 
     * In some cases, you may need to read an additional line:
     * @code{.cpp}
     * void confirm_command(const msg_block_t& bl) {
     *     bl << "Are you sure? (y/n): ";
     *     auto answer = bl.read_line();
     *     if (answer == "y" || answer == "Y") {
     *         bl << "Confirmed!\n";
     *     }
     * }
     * @endcode
     * 
     * @note Объект передается в callback по const ссылке
     * @warning Не пытайтесь сохранить ссылку на msg_block_t вне callback-функции
     * 
     * @see console_t::mk_blank()
     * @see Console_parser::parser
     */
    class msg_block_t
    {
    public:
        using cycle_callback_t = std::function<void(const msg_block_t&)>; // for wait inside console (warning!!! reqursion)
        using parser_t = Console_parser::parser;
        static constexpr size_t cycle_limit = 10;
    private:
        friend class console_t;

        static size_t _cycle_cnt;   // todo: in meta

        io_base_t* _port = nullptr;
        mutable event_t _event = event_t::none;

        parser_t _parser;

    public:
        msg_block_t(io_base_t* port, size_t buf_sz) : 
            _port(port), 
            _event(event_t::none),
            _parser(true)
        {
            _event = event_t::work;
            ++_cycle_cnt;
        }
        ~msg_block_t()
        {
            --_cycle_cnt;
        }

        msg_block_t(const msg_block_t&) = delete;   // no copy
        msg_block_t(msg_block_t&& oth) 
            : _port(oth._port), _event(oth._event),  _parser(std::move(oth._parser))
        {
            oth._port = nullptr;
            oth._event = event_t::none;
        }

        std::string read_line(size_t buf_sz = 255) const {
            char last_sig = 0;
            bool out_sig = false;

            u_cns_streambuf_t stream(buf_sz);
            size_t i = 0;

            // while user dont send enter or ctrl+c
            while (!out_sig)
            {
                uint16_t t = _port->available();
                if (t)
                {
                    while (t)
                    {
                        auto ch = _port->read();
                        --t;

                        last_sig = ch;
                        
                        // if user send ctrl+c or press enter
                        if (ch == 0x03 || ch == '\n' || ch == '\r')
                        {
                            if (t)
                            {
                                // for CRLF sequence
                                auto nc = _port->read();
                                if (nc == '\n' || nc == '\r')
                                {
                                    out_sig = true;
                                    // printf("\ncatch12 %u\n", static_cast<uint16_t>(nc));
                                    break;
                                }
                            }
                            out_sig = true;
                            break;
                            // printf("\ncatch15 %u\n", static_cast<uint16_t>(ch));
                        }
                        else if (ch == '\b')    // backspace
                        {
                            if (stream.size())
                            {
                                stream.pop_back();
                                _port->write("\b \b", 3);
                            }
                            continue;
                        }
                        else if (ch == '\033')  //skip all ecs-codes for arrows, pageup, home and other...
                        {
                            /*
                                \033[A UpArr                            
                                \033[B DwArr                            
                                \033[C RArr                            
                                \033[D LArr                            
                                \033[H or \033[1~ Home                            
                                \033[F or \033[4~ End                            
                                \033[3~ Delete                            
                                \033[2~ Insert                            
                                \033[5~ PgUp                        
                                \033[6~ PgDw                      
                            */
                            if (t)
                            {
                                --t;
                                _port->read();
                                if (t)
                                {
                                    --t;
                                    _port->read();
                                }
                                
                                if (t)
                                {
                                    --t;
                                    auto nc = _port->read();
                                    if (nc != '~')          // skip pgup pgdn that ends ~
                                    {
                                        stream << ch;
                                        _port->write(ch);
                                    }
                                }
                            }
                            continue;
                        }
                        stream << ch;
                        _port->write(ch);    // back typed text to console(user should see what he write)
                    }
                }

                if (i >= buf_sz)
                {
                    _port->write("\t!~symbol limit reached\n", 25);
                    break;
                }
                ufo::utl::sleep_for(5);
            }
            _port->write('\n');

            if (last_sig == 0x03)
            {
                printf("catch ctrl+c\n");
                return std::string();
            }

            // printf("msgblk: %s, last: %c, code: %u\n", stream.str().c_str(), last_sig, static_cast<uint16_t>(last_sig));
            ufo::utl::sleep_for(5);
            return stream.str();
        }

        // for internal concole cycle in concole cycle in console cycle in...
        void run_internal(cycle_callback_t callback, size_t buf_sz = 255) const
        {
            if (!callback)
            {
                _port->write("\n\t!~null callback in internal cucle\n", 36);
                return;
            }

            if (_cycle_cnt > cycle_limit)
            {
                _port->write("\n\t!~cycle limit reached\n", 24);
                return;
            }
            auto mb_int = msg_block_t(_port, buf_sz);
            auto s = mb_int.read_line();
            mb_int._parser.parse(s, true);
            if (!mb_int._parser.good())
            {
                mb_int << "u_cns: bad arguments in line\n";
                return;
            }
            callback(mb_int);
        }

        void fwrite(const char* msg, ...) const {
            char data [127]= {};
            if (!strlen(msg))
            {
                return;
            }
            va_list ap;
            va_start(ap, msg);

            // calculate required string size
            va_list arg;
            va_copy(arg, ap);
            uint32_t req = 1+vsnprintf(NULL, 0, msg, arg);
            va_end(arg);

            if (req > 127)
            {
                req = 126;
            }

            int n = vsnprintf(data, req, msg, ap);
            va_end(ap);

            _port->write(data, n);
            return;
        }

        void write(const std::string& str) const {
            _port->write(str.c_str(), str.size());
        }

        void write(char c) const {
            _port->write(c);
        }

        char read() const
        {
            char c = 0;
            uint16_t t = _port->available();
            if (t)
            {
                c = _port->read();
            }
            return c;
        }

        const parser_t& get_opt_list() const {
            return _parser;
        }

    private:
        event_t get_event() const {
            return _event;
        }

        void exit_from_console() const {
            _event = event_t::exit;
        }

        void write_cns_prefix() const 
        {
            _port->write("u_cns>");
        }
        
        // faster fwrite for numeric types only!
        void fcwrite(const char *format, ...) const
        {
            va_list args;
            va_start(args, format);
            char bf[64] = {};
            size_t len = vsnprintf(bf, sizeof(bf), format, args);

            if (len > 0)
            {
                _port->write(bf, len);
            }
            va_end(args);
        }

    public:
        const msg_block_t& operator << (const char* msg) const {
            this->write(msg);
            return *this;
        }

        const msg_block_t& operator << (const std::string& msg) const {
            this->write(msg);
            return *this;
        }

        const msg_block_t& operator << (char c) const {
            this->write(c);
            return *this;
        }

        const msg_block_t& operator << (int8_t val) const {
            fcwrite("%" PRId8, val);
            return *this;
        }
        
        const msg_block_t& operator << (short val) const {
            fcwrite("%" PRId16, val);
            return *this;
        }
        
        const msg_block_t& operator << (long val) const {
            fcwrite("%" PRId32, val);
            return *this;
        }
        
        const msg_block_t& operator << (long long val) const {
            fcwrite("%" PRId64, val);
            return *this;
        }
        
        const msg_block_t& operator << (uint8_t val) const {
            fcwrite("%" PRIu8, val);
            return *this;
        }
        
        const msg_block_t& operator << (unsigned short val) const {
            fcwrite("%" PRIu16, val);
            return *this;
        }
        
        const msg_block_t& operator << (int val) const {
            fcwrite("%" PRId32, val);
            return *this;
        }
        
        const msg_block_t& operator << (unsigned int val) const {
            fcwrite("%" PRIu32, val);
            return *this;
        }

        const msg_block_t& operator << (unsigned long val) const {
            fcwrite("%" PRIu32, val);
            return *this;
        }
        
        const msg_block_t& operator << (unsigned long long val) const {
            fcwrite("%" PRIu64, val);
            return *this;
        }
        
        // Числа с плавающей точкой
        const msg_block_t& operator << (float val) const {
            fcwrite("%.6g", val);  // 6 значащих цифр
            return *this;
        }
        
        const msg_block_t& operator << (double val) const {
            fcwrite("%.6g", val);  // 6 значащих цифр
            return *this;
        }
        
        // Логический тип
        const msg_block_t& operator << (bool val) const {
            fcwrite("%s", val ? "true" : "false");
            return *this;
        }
        
        // Указатели
        const msg_block_t& operator << (const void* ptr) const {
            if (ptr == nullptr) {
                fcwrite("%s", "nullptr");
            } else {
                fcwrite("%p", ptr);
            }
            return *this;
        }
    };

    size_t msg_block_t::_cycle_cnt = 0;   // todo: in meta

} // __u_console