/*
MIT License

Copyright (c) 2020-2021 José Puga

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef ANSI_HPP
#define ANSI_HPP
#define ANSI_HPP_VERSION "1.0.2"
#include <string>
#include <string_view>
#include <vector>

#if defined(_WIN32)
#include <cstdio>
#include <windows.h>
//Some old MinGW/CYGWIN distributions don't define this:
#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#endif
namespace ansi {   //Warning: no error checked.
	static DWORD dwMode1 = 0;
	static auto dummyFoo = GetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE), &dwMode1);
    static DWORD dwMode2 = dwMode1 |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    static auto dummyFoo2 = SetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE), dwMode2);
    // UTF8 for Windows. TODO: Restore old CP. But ansi must be a class...
    static auto dummyFoo3 = SetConsoleOutputCP( CP_UTF8 );
}
#endif // _WIN32

namespace ansi {
    typedef struct rgb_t {
        uint8_t r {0};
        uint8_t g {0};
        uint8_t b {0};
        bool operator==(const rgb_t& rhs) const { 
                return r == rhs.r && g == rhs.g && b == rhs.b; }
        bool operator!=(const rgb_t& rhs) const {
                return !(*this == rhs); }
    } rgb_t;

    typedef struct pos_t {
        int x {0};
        int y {0};
        bool operator==(const pos_t& rhs) const {
                return x == rhs.x && y == rhs.y; }
        bool operator!=(const pos_t& rhs) const {
                return !(*this == rhs); }
    } pos_t;

    //Standard 16 Foreground colors
    static const std::vector<std::string_view> _fg = {
        "\033[38;5;0m", "\033[38;5;1m", "\033[38;5;2m", "\033[38;5;3m", 
        "\033[38;5;4m", "\033[38;5;5m", "\033[38;5;6m", "\033[38;5;7m", 
        "\033[38;5;8m", "\033[38;5;9m", "\033[38;5;10m", "\033[38;5;11m", 
        "\033[38;5;12m", "\033[38;5;13m", "\033[38;5;14m", "\033[38;5;15m"
    };

    //Standard 16 Background colors
   static const std::vector<std::string_view> _bg = {
        "\033[48;5;0m", "\033[48;5;1m", "\033[48;5;2m", "\033[48;5;3m", 
        "\033[48;5;4m", "\033[48;5;5m", "\033[48;5;6m", "\033[48;5;7m", 
        "\033[48;5;8m", "\033[48;5;9m", "\033[48;5;10m", "\033[48;5;11m", 
        "\033[48;5;12m", "\033[48;5;13m", "\033[48;5;14m", "\033[48;5;15m"
   };

   //Greyscale foreground colors (0-23)
   static const std::vector<std::string_view> _fg_grey = {     
        "\033[38;5;232m", "\033[38;5;233m", "\033[38;5;234m", "\033[38;5;235m", 
        "\033[38;5;236m", "\033[38;5;237m", "\033[38;5;238m", "\033[38;5;239m", 
        "\033[38;5;240m", "\033[38;5;241m", "\033[38;5;242m", "\033[38;5;243m", 
        "\033[38;5;244m", "\033[38;5;245m", "\033[38;5;246m", "\033[38;5;247m", 
        "\033[38;5;248m", "\033[38;5;249m", "\033[38;5;250m", "\033[38;5;251m", 
        "\033[38;5;252m", "\033[38;5;253m", "\033[38;5;254m", "\033[38;5;255m"
    };

   //Greyscale background colors (0-23)
   static const std::vector<std::string_view> _bg_grey = {
        "\033[48;5;232m", "\033[48;5;233m", "\033[48;5;234m", "\033[48;5;235m", 
        "\033[48;5;236m", "\033[48;5;237m", "\033[48;5;238m", "\033[48;5;239m", 
        "\033[48;5;240m", "\033[48;5;241m", "\033[48;5;242m", "\033[48;5;243m", 
        "\033[48;5;244m", "\033[48;5;245m", "\033[48;5;246m", "\033[48;5;247m", 
        "\033[48;5;248m", "\033[48;5;249m", "\033[48;5;250m", "\033[48;5;251m", 
        "\033[48;5;252m", "\033[48;5;253m", "\033[48;5;254m", "\033[48;5;255m"
    };

    //Special attributes.
    const std::string_view reset = "\033[0m";
    const std::string_view bold = "\033[1m";
    const std::string_view underline = "\033[4m";
    const std::string_view blink = "\033[5m";  //Not Win10 compatible
    const std::string_view reverse = "\033[7m";

    //Basic foreground normal colors (optional name).
    const std::string_view black = "\033[30m";
    const std::string_view red = "\033[31m";
    const std::string_view green = "\033[32m";
    const std::string_view yellow = "\033[33m";
    const std::string_view blue = "\033[34m";
    const std::string_view magenta = "\033[35m";
    const std::string_view cyan = "\033[36m";
    const std::string_view white = "\033[37m";

    //Basic foreground normal colors.
    const std::string_view fg_black = ansi::black;
    const std::string_view fg_red = ansi::red;
    const std::string_view fg_green = ansi::green;
    const std::string_view fg_yellow = ansi::yellow;
    const std::string_view fg_blue = ansi::blue;
    const std::string_view fg_magenta = ansi::magenta;
    const std::string_view fg_cyan = ansi::cyan;
    const std::string_view fg_white = ansi::white;

    //Basic foreground bold colors.
    const std::string_view fg_b_black = "\033[90m";
    const std::string_view fg_b_red = "\033[91m";
    const std::string_view fg_b_green = "\033[92m";
    const std::string_view fg_b_yellow = "\033[93m";
    const std::string_view fg_b_blue = "\033[94m";
    const std::string_view fg_b_magenta = "\033[95m";
    const std::string_view fg_b_cyan = "\033[96m";
    const std::string_view fg_b_white = "\033[97m";

    //Basic background normal colors.
    const std::string_view bg_black = "\033[40m";
    const std::string_view bg_red = "\033[41m";
    const std::string_view bg_green = "\033[42m";
    const std::string_view bg_yellow = "\033[43m";
    const std::string_view bg_blue = "\033[44m";
    const std::string_view bg_magenta = "\033[45m";
    const std::string_view bg_cyan = "\033[46m";
    const std::string_view bg_white = "\033[47m";

    //Basic background normal colors.
    const std::string_view bg_b_black = "\033[100m";
    const std::string_view bg_b_red = "\033[101m";
    const std::string_view bg_b_green = "\033[102m";
    const std::string_view bg_b_yellow = "\033[103m";
    const std::string_view bg_b_blue = "\033[104m";
    const std::string_view bg_b_magenta = "\033[105m";
    const std::string_view bg_b_cyan = "\033[106m";
    const std::string_view bg_b_white = "\033[107m";

    //Special actions
	const std::string_view save_position = "\033[s";
	const std::string_view restore_position = "\033[u";
	const std::string_view hide_cursor = "\033[?25l";
	const std::string_view show_cursor = "\033[?25h";

    //Clear creen actions
	const std::string_view clear_all = "\033[2J";
	const std::string_view clear_line = "\033[2K";
	const std::string_view clear_to_top = "\033[1J";
	const std::string_view clear_to_bottom = "\033[0J";
	const std::string_view clear_line_to_begin = "\033[1K";
	const std::string_view clear_line_to_end = "\033[0K";
	
    /**
     * @brief Set RGB foreground color
     * @param rgb_t Red (0-255), Green(0-255), Blue(0-255) struct.
     * @return Ansi sequence.
     * */
    inline const std::string fg_rgb(const ansi::rgb_t& t) {
        return  "\033[38;2;" + std::to_string(t.r) + ";" + std::to_string(t.g) 
            + ";" + std::to_string(t.b) + "m";
    }

    /**
     * @brief Set RGB foreground color
     * @param r Red 0-255
     * @param g Green 0-255
     * @param b Blue 0-255
     * @return Ansi sequence.
     * */
    inline const std::string fg_rgb(const uint8_t r, const uint8_t g, const uint8_t b) {
        return  "\033[38;2;" + std::to_string(r) + ";" + std::to_string(g) + ";"
            + std::to_string(b) + "m";
    }

    /**
     * @brief Set RGB foreground color
     * @param color uint32_t color value.
     * @return Ansi sequence.
     * */
    inline const std::string fg_rgb(const uint32_t c) {
        auto r = (c >> 16) & 0xff;
        auto g = (c >> 8) & 0xff;
        auto b = c & 0xff;
        return  "\033[38;2;" + std::to_string(r) + ";" + std::to_string(g) 
            + ";" + std::to_string(b) + "m";
    }


    /**
     * @brief Set RGB background color
     * @param rgb_t Red (0-255), Green(0-255), Blue(0-255) struct.
     * @return Ansi sequence.
     * */
    inline const std::string bg_rgb(const ansi::rgb_t& t) {
        return  "\033[48;2;" + std::to_string(t.r) + ";" + std::to_string(t.g) +
            ";" + std::to_string(t.b) + "m";
    }

    /**
     * @brief Set RGB background color
     * @param r Red 0-255
     * @param g Green 0-255
     * @param b Blue 0-255
     * @return Ansi sequence.
     * */
    inline const std::string bg_rgb(const uint8_t r, const uint8_t g, const uint8_t b) {
        return  "\033[48;2;" + std::to_string(r) + ";" + std::to_string(g) + ";"
            + std::to_string(b) + "m";
    }

    /**
     * @brief Set RGB background color
     * @param color uint32_t color value.
     * @return Ansi sequence.
     * */
    inline const std::string bg_rgb(const uint32_t c) {
        auto r = (c >> 16) & 0xff;
        auto g = (c >> 8) & 0xff;
        auto b = c & 0xff;
        return  "\033[48;2;" + std::to_string(r) + ";" + std::to_string(g) 
            + ";" + std::to_string(b) + "m";
    }

    /**
     * @brief Set standard foreground color. 
     * @param color Color code 0-15.
     * @return Ansi sequence.
     * */
    inline const std::string_view fg(const int color) {
        return ansi::_fg.at(color);
    }

    /**
     * @brief Set standard background color. 
     * @param color Color code 0-15.
     * @return Ansi sequence.
     * */
    inline const std::string_view bg(const int color) {
        return ansi::_bg.at(color);
    }

    /**
     * @brief Set the foreground color in a grey scale of 24. 0 is the 
     * darkest and 23 the whitest.
     * @param color Color code 0-23
     * @return Ansi sequence.
     * */
    inline const std::string_view fg_grey(const int color) {
        return ansi::_fg_grey.at(color);
    }

    /**
     * @brief Set the background color in a grey scale of 24. 0 is the 
     * darkest and 23 the whitest.
     * @param color Color code 0-23
     * @return Ansi sequence.
     * */    
    inline const std::string_view bg_grey(const int color) {
        return ansi::_bg_grey.at(color);
    }

	/**
     * @brief Moves cursor position n times up.
     * @param n N times to move, 1 by default.
     * @return Ansi sequence.
     * */
    inline const std::string up(const int n = 1) { 
        return "\033[" + std::to_string(n) + "A"; }

	/**
     * @brief Moves cursor position n times down.
     * @param n N times to move, 1 by default.
     * @return Ansi sequence.
     * */
    inline const std::string down(const int n = 1) { 
        return "\033[" + std::to_string(n) + "B"; }

	/**
     * @brief Moves cursor position n times right.
     * @param n N times to move, 1 by default.
     * @return Ansi sequence.
     * */
    inline const std::string right(const int n = 1) { 
        return "\033[" + std::to_string(n) + "C"; }

	/**
     * @brief Moves cursor position n times left.
     * @param n N times to move, 1 by default.
     * @return Ansi sequence.
     * */
    inline const std::string left(const int n = 1) { 
        return "\033[" + std::to_string(n) + "D"; }

	/**
     * @brief Delete n characters from the cursor position to the right.
     * @param n N characters to delete, 1 by default.
     * @return Ansi sequence.
     * */
    inline const std::string delete_char(const int n = 1) { 
        return "\033[" + std::to_string(n) +"Km"; }

	/**
     * @brief Set cursor position.
     * @param x Colum.
     * @param y Row.
     * @return Ansi sequence.
     * */
	inline const std::string goto_xy(const int x, const int y) { 
        return "\033[" + std::to_string(y) + ";" + std::to_string(x) + "f"; }

	/**
     * @brief Set cursor position.
     * @param pos_t Struct with X and Y coordinates.
     * @return Ansi sequence.
     * */
	inline const std::string goto_xy(const ansi::pos_t pos) { 
        return goto_xy(pos.x, pos.y); }

} //namespace

#endif // ANSI_HPP

