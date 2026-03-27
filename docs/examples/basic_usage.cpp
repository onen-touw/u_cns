/**
 * @example basic_usage.cpp
 * @brief Базовый пример использования UFO Console
 * @ingroup public_api
 * 
 * Этот пример демонстрирует основные возможности модуля:
 * - Создание консоли с UART интерфейсом
 * - Регистрация пользовательских команд
 * - Работа с аргументами команд
 * - Запуск консоли в отдельном потоке
 */

#include "u_cns.h"
#include "u_drivers/u_uart.h"
#include "u_sys/thread.h"
#include <cstdio>

// Пример 1: Простая команда без аргументов
void setup_simple_commands(ufo::u_console_t& console) {
    console.mk_blank("hello", "Print greeting message", [](const ufo::u_console_msg_block_t& bl) {
        bl << "Hello from UFO Console!\n";
        bl << "Current time: " << __TIME__ << "\n";
    });
    
    console.mk_blank("status", "Show system status", [](const ufo::u_console_msg_block_t& bl) {
        bl << "System Status:\n";
        bl << "  CPU Load: 15%\n";
        bl << "  Memory: 128KB/256KB\n";
        bl << "  Uptime: 2 days, 3 hours\n";
    });
}

// Пример 2: Команда с аргументами
void setup_parameterized_commands(ufo::u_console_t& console) {
    console.mk_blank("gpio", "Control GPIO pins", [](const ufo::u_console_msg_block_t& bl) {
        const auto& parser = bl.get_opt_list();
        
        int pin = -1;
        bool set = false;
        bool clear = false;
        
        if (parser.bind(&pin, "-p,--pin")) {
            if (parser.find("--set")) {
                bl << "Setting GPIO " << pin << " to HIGH\n";
                // gpio_set(pin, 1);
            } else if (parser.find("--clear")) {
                bl << "Setting GPIO " << pin << " to LOW\n";
                // gpio_set(pin, 0);
            } else {
                bl << "GPIO " << pin << " state: " << "UNKNOWN\n";
            }
        } else {
            bl << "Usage: gpio --pin=<num> [--set|--clear]\n";
            bl << "Example: gpio --pin=5 --set\n";
        }
    });
}

// Пример 3: Команда с массивом аргументов
void setup_array_commands(ufo::u_console_t& console) {
    console.mk_blank("average", "Calculate average of numbers", [](const ufo::u_console_msg_block_t& bl) {
        const auto& parser = bl.get_opt_list();
        std::vector<int> numbers;
        
        if (parser.bind(&numbers, "-n,--numbers")) {
            if (numbers.empty()) {
                bl << "No numbers provided\n";
                return;
            }
            
            long long sum = 0;
            for (auto n : numbers) {
                sum += n;
            }
            double avg = static_cast<double>(sum) / numbers.size();
            
            bl << "Numbers: [";
            for (size_t i = 0; i < numbers.size(); ++i) {
                if (i > 0) bl << ", ";
                bl << numbers[i];
            }
            bl << "]\n";
            bl << "Average: " << avg << "\n";
        } else {
            bl << "Usage: average --numbers=10,20,30,40\n";
        }
    });
}

// Пример 4: Команда с интерактивным вводом
void setup_interactive_command(ufo::u_console_t& console) {
    console.mk_blank("delete", "Delete file with confirmation", [](const ufo::u_console_msg_block_t& bl) {
        const auto& parser = bl.get_opt_list();
        std::string filename;
        
        if (!parser.bind(&filename, "-f,--file")) {
            bl << "Usage: delete --file=<filename>\n";
            return;
        }
        
        bl << "Are you sure you want to delete '" << filename << "'? (y/n): ";
        auto answer = bl.read_line();
        
        if (answer == "y" || answer == "Y") {
            bl << "Deleting " << filename << "...\n";
            // delete_file(filename);
            bl << "File deleted successfully\n";
        } else {
            bl << "Operation cancelled\n";
        }
    });
}

// Пример 5: Использование pre/post callbacks
bool console_pre_run() {
    printf("Console is starting...\n");
    // Проверяем, что система готова к работе
    return true;  // вернуть false, чтобы отменить запуск
}

void console_post_run() {
    printf("Console has stopped\n");
}

// Главная функция
int main() {
    // Инициализация UART (пример)
    ufo::u_uart_t uart;
    uart.init(115200);
    
    // Создаем UART поток для консоли
    ufo::u_console_uart_stream_t io(&uart);
    
    // Создаем консоль с pre/post колбэками
    ufo::u_console_t console(&io, 255, console_pre_run, console_post_run);
    
    // Регистрируем команды
    setup_simple_commands(console);
    setup_parameterized_commands(console);
    setup_array_commands(console);
    setup_interactive_command(console);
    
    // Запускаем консоль в отдельном потоке
    ufo::thread console_task(cns_cfg, &__u_console::console_t::ctask, std::move(cns));
    
    // Ожидаем завершения консоли
    console_thread.join();
    
    printf("Application finished\n");
    return 0;
}