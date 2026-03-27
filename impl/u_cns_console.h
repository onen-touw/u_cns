/**
 * @file impl/u_cns_console.h
 * @brief Implementation of the main console class
 * @ingroup public_api
 * 
 * Don't include this file directly! Use @ref u_cns.h
 * 
 * This file contains the implementation of the console_t class, 
 * which manages command registration and the console's main loop.
 */


#pragma once

#include "u_cns_blank.h"
#include "u_sys/thread.h"


namespace __u_console
{

    /**
     * @ingroup public_api
     * @brief Main console class
     * 
     * Manages command registration (blanks) and the main input processing loop.
     * 
     * @section registration Registration commands
     * 
     * Commands are registered via the mk_blank() method:
     * @code{.cpp}
     * console.mk_blank("mycmd", "Description", [](const msg_block_t& bl) {
     *     // reaction to call
     * });
     * @endcode
     * 
     * @section internal_commands Internal Commands
     * 
     * The console automatically creates two built-in commands:
     * - **help** - displays a list of all registered commands and help-info
     * - **exit** - terminates the console
     * 
     * These commands cannot be removed or overridden.
     * 
     * @section threading Thread safety
     * 
     * The class is not thread-safe. It must be used in a single thread.
     * 
     * @section move_only Move-only semantics
     *
     * The class only supports moving; copying is prohibited.
     * This allows the console to be safely passed to a thread.
     * 
     * @code{.cpp}
     * ufo::u_console_t console(&io, 255);
     * ufo::thread console_task(cns_cfg, &__u_console::console_t::ctask, std::move(cns));
     * @endcode
     * 
     * @see msg_block_t
     */
    class console_t
    {
    private:
        using bl_map_t = std::map<std::string, blank_t>;

    public:
    
        /// @brief 
        // Callback that will be called when task is started
        // If it return false that task will not be executed.
        // Used to check whether the console or note can be launched
        using pre_run_callback_t = bool(*)();

        /// @brief 
        /// A callback function that will be called before the console task is destroyed.
        /// You can use this to notify other threads that the console has stopped working.  
        using post_run_callback_t = void(*)();

    public:
        static constexpr uint8_t max_blanks = 15;
    private:
        io_base_t* _port = nullptr;
        msg_block_t _block;

        bl_map_t _blanks;
        pre_run_callback_t _clb_pre = nullptr;
        post_run_callback_t _clb_post = nullptr;

    public:

        /// @brief Contructor of console
        /// @param port stream that proveide io funcrional (read/write, <<) 
        /// @param buf_sz size of stream buffer
        /// @param pre_clb (optional). A callback function that will be called before the console task is started.
        /// You can use this to notify other threads that the console has started or to check whether the console can be started.
        /// If the console cannot be started, the callback function should return false.
        /// @param post_clb (optional). A callback function that will be called before the console task is destroyed.
        /// You can use this to notify other threads that the console has stopped working.
        console_t(io_base_t* port, size_t buf_sz, pre_run_callback_t pre_clb = nullptr, post_run_callback_t post_clb = nullptr) 
        : _port(port), _block(port, buf_sz), _clb_pre(pre_clb), _clb_post(post_clb)
        {
            if (!port)
            {
                printf("cns:: !port error\n");
                throw;
            }

        }

        /// @brief move constructor. This class only can be moved in constructor (no copy, no assignment and move operators)
        console_t(console_t&& oth)
            : _port(oth._port),
            _block(std::move(oth._block)),
            _blanks(std::move(oth._blanks)),
            _clb_pre(oth._clb_pre),
            _clb_post(oth._clb_post)
        {
            oth._port = nullptr;
            oth._clb_pre = nullptr;
            oth._clb_post = nullptr;
        }

        console_t(const console_t&) =delete;
        console_t& operator= (const console_t&) =delete;

        /// @brief Create blank(command or sub-program)
        /// 
        /// This console system has some internal 'blanks' such as "exit", "help" that cant be overridden.
        /// @param cl_name Name of you 'blank' (or command or sub-program)
        /// @param desc Description of 'blank' that shown when you entering "help" command
        /// @param foo A callback function that will be called when user type <cl_name> <--parameters...>(optional) 
        void mk_blank(const char* cl_name, const char* desc, blank_t::callback_t foo){
            
            if (!strcmp(cl_name, "help") || !strcmp(cl_name, "exit"))
            {
                return;
            }

            auto it = _blanks.find(cl_name);
            if (it != _blanks.end())
            {
                _blanks.erase(it);  // for user redefinition!
            }
            
            // just return
            if (_blanks.size() > max_blanks)
            {
                return;
            }
            
            _blanks.emplace(cl_name, blank_t(desc, foo));
        }

        /// @brief Remove blank(command or sub-program)
        /// 
        /// This console system has some internal 'blanks' such as "exit", "help" that cant be removed.
        /// @param cl_name Name of you 'blank' (or command or sub-program) that you want to delete
        void rm_blank(const char* cl_name){
            if (_blanks.empty())
            {
                return;
            }
            
            if (!strcmp(cl_name, "help") || !strcmp(cl_name, "exit"))
            {
                return;
            }

            _blanks.erase(cl_name);
        }

        /// @brief console task that run console loop
        /// @param token ufo-system-thread-parameter Use with caution
        void ctask(ufo::token_t token){
            if (_clb_pre)
            {
                bool r = _clb_pre();
                if (!r)
                {
                    return;
                }
            }
                        
            create_internal_blanks();

            _blanks.find("help")->second.run(_block);

            while (token && _block.get_event() != event_t::exit)
            {
                _block.write("u_cns>");    
                auto line = _block.read_line();
                if (line.empty())
                {
                    continue;
                }
                
                if (line.size())
                {
                    find_and_go(line);
                }
                ufo::utl::sleep_for(50);
            }
            _block.write("Catched exit command\nConcole closed\n");   
            
            if (_clb_post)
            {
                _clb_post();
            }
        }
        
    private:
        void create_internal_blanks() {
            
            if (_blanks.find("exit") != _blanks.end())
            {
                _blanks.emplace("exit", blank_t("Command for exit from console", exit_cns));
            }
            
            if (_blanks.find("help") != _blanks.end())
            {
                _blanks.emplace("help", blank_t("help", [&context = _blanks](const msg_block_t &bl) -> void
                {
                    bl << "\nWelcome to UFOConsole Interface!\n";
                    bl << "================================\n\n";
        
                    bl << "Available commands (" << context.size() << " total):\n";
        
                    if (context.empty()) {
                        bl << "  [empty] - no commands registered\n";
                    } else {
                        for (const auto &i : context) {
                            bl << "  "  << i.first << "\n";
                            bl << "  └─ " << i.second.get_desc() << "\n";
                        }
                    }
                    bl << "\nUsage: type command <name> <--opt1=123> and press Enter\n";
                    bl << "Type 'exit' to close console\n\n";
                }));
            }

        }

        void help_cns()
        {
            _block.write("class list:\n");
            if (_blanks.empty())
            {
                _block.write("\tempty\n");
                return;
            }

            for (const auto &i : _blanks)
            {
                _block << '\t' << i.first << '\t' << i.second.get_desc() << '\n';
            }
        }

        static void exit_cns(const msg_block_t& bl)
        {
            bl.exit_from_console();
        }

    private:
        void find_and_go(std::string& s)
        {
            if (_blanks.empty())
            {
                return;
            }

            _block._parser.parse(s, true);
            if (!_block._parser.good())
            {
                _block << "u_cns: bad arguments in line\n";
                return;
            }
            
            auto blank = _block._parser.get_prog_name();

            auto bl_it = _blanks.find(blank);
            if (bl_it != _blanks.end())
            {
                bl_it->second.run(_block);
                return;
            }
            _block << blank << ": command not found\n";
        }
    };        

} // __u_console