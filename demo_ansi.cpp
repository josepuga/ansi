//Demo for ansi.h by José Puga
#include <iomanip> 
#include <iostream>
#include <thread> 
#include <chrono> 
#include <map>
#include "ansi.h"     //Only this header

using namespace std;

void Pause()
{
    cout << ansi::white << ansi::bg_black << "\nPress " << ansi::bold <<
    ansi::underline << "ENTER" << ansi::reset << " to continue the demo...";
    cin.get();
}

void ClearAndReset()
{
    //ansi::reset to turn off special attributes like blink or bold.
    //ansi::clear_all to clear screen
    //Strange behavior sometimes clear_all is not enought in Windows.
    //Is good idea add goto_xy(1,1)
    cout << ansi::reset << ansi::clear_all << ansi::goto_xy(1,1);
}
int main()
{ 
    //TEST STANDARD 16 FOREGROUNDS COLORS    
    ClearAndReset();
    cout << ansi::right(10) << ansi::underline << 
          "FOREGROUND STANDARD 16 COLORS TEST:" << ansi::reset;
    cout << "\nUsing " << ansi::bold << "'ansi::fg(n)'" << 
        ansi::reset << ". Where n = 0-15:\n\n";

    auto maxColums = 8, colum = 0; //Demo with 80 colums
    for (auto i = 0; i < 16; i++) {
        cout << ansi::bg_black << ansi::white << " " << setw(3) << i << "=";
        cout << ansi::fg(i) << "#%@AB";
        colum++;
        if (colum == maxColums) {
            colum = 0;
            cout << "\n";
        }
    }

    //TEST STANDARD 16 BACKGROUNDS COLORS    
    cout << "\n\n\n" << ansi::right(10) << ansi::underline <<
        "BACKGROUND STANDARD 16 COLORS TEST:" << ansi::reset;
    cout << "\nUsing " << ansi::bold << "'ansi::bg(n)'" << 
        ansi::reset << ". Where n = 0-15:\n\n";
    colum = 0;
    for (auto i = 0; i < 16; i++) {
        cout << ansi::bg_black << ansi::white << " " << setw(3) << i << "=";
        cout << ansi::bg(i) << "#%@AB";
        colum++;
        if (colum == maxColums) {
            colum = 0;
            cout << "\n";
        }
    }
    Pause();
    ClearAndReset();

    //TEST GREYSCALE FOREGROUND COLORS    
    cout << ansi::right(10) << ansi::underline << "GREYSCALE COLORS TEST:" << 
        ansi::reset;
    cout << "\n\nTest Foreground Greyscale using " << ansi::bold << 
        "'ansi::fg_grey(n)'" << ansi::reset << " where n = 0-23:\n\n";
    colum = 0;
    for (auto i = 0; i < 24; i++) {
        cout << ansi::bg_black << ansi::white << " " << setw(3) << i << "=";
        cout << ansi::fg_grey(i) << "#%@AB";
        colum++;
        if (colum == maxColums) {
            colum = 0;
            cout << "\n";
        }
    }

    //TEST GREYSCALE BACKGROUND COLORS    
    cout << ansi::reset;
    cout << "\n\n\nTest Background Greyscale using " << ansi::bold
        << "'ansi::bg_grey(n)'" << ansi::reset << " where n = 0-23:\n\n";
    colum = 0;
    for (auto i = 0; i < 24; i++) {
        cout << ansi::bg_black << ansi::white << " " << setw(3) << i << "=";
        cout << ansi::bg_grey(i) << "#%@AB";
        colum++;
        if (colum == maxColums) {
            colum = 0;
            cout << "\n";
        }
    }
    Pause();
    ClearAndReset();

    //TEST COLOR NAMED
    cout << ansi:: goto_xy(1,4) << "The most common and most compatible colors"
        << " are the first 16.\nYou can use they directly with the color name."
        << "\nLike " << ansi::blue << "'ansi::blue' or 'ansi::fg_blue'" << 
        ansi::reset << " for normal foreground blue,\nor " << ansi::fg_b_blue << 
        "'ansi::fb_b_blue'" << ansi::reset << " for bold foreground blue.\n\n";
    cout << "Same for background colors. Normal like " << ansi::bg_green <<
        "'ansi::bg_green'" << ansi::reset << ".\nAnd bold version " <<
        ansi::bg_b_green << "ansi::bg_b_green" << ansi::reset << ".\n";
    cout << "ansi_fg::XXX (or ansi::XXX), ansi::fg_b_XXX, ansi::bg_XXX, ansi::"
        << "bg_b_XXX.\nWhere XXX can be: red, green, yellow, blue, "
        << "magenta, cyan, white, black. (8 normal + 8 bold = 16)\n";
    Pause();
    ClearAndReset();

    //TEST RGB COLORS
    cout << "Of course, RBG colors are availables.\n" << ansi::bold << 
        "'ansi::rgb(const int r, const int g, const int b)'" << ansi::reset <<
        " or with rgb type ansi::rgb_t\n" << ansi::bold << 
        "'ansi::rgb(const ansi::rgb_t&)'\n" << ansi::reset;

    //Common HTML color names: https://www.w3schools.com/colors/colors_names.asp
    const map<string, ansi::rgb_t> commonsRGB {
        {"Maroon", {128, 0, 0}},
        {"Olive", {128, 128, 0}},
        {"Aqua", {0, 255, 55}},
        {"Purple", {128, 0, 128}},
        {"Khaki", {0xf0, 0Xe6, 0x8c}},
        {"Sienna", {0xa0, 0x52, 0x2d}},
        {"Teal", {0, 0x80, 0x80}},
        {"Torquoise", {0x40, 0xe0, 0xd0}},
        {"Wheat", {0xf5, 0xde, 0xb3}},
        {"Indigo", {0x4b, 0, 0x82}},
        {"Azure", {0xf0, 0xff, 0xff}},
        {"Almond",{0xff, 0xeb, 0xcd}}
    };
    maxColums = 4;
    colum = 0;
    for (auto it = commonsRGB.begin(); it != commonsRGB.end(); it++) {
        cout << ansi::reset << setw(11) << right << it->first << ": " <<
            ansi::fg_rgb(it->second) << "#%@AB";
        colum++;
        if (colum == maxColums) {
            colum = 0;
            cout << "\n";
        }
    }

    cout << "\n";
    colum = 0;
    for (auto it = commonsRGB.begin(); it != commonsRGB.end(); it++) {
        cout << ansi::reset << setw(11) << right << it->first << ": " <<
            ansi::bg_rgb(it->second) << "#%@AB";
        colum++;
        if (colum == maxColums) {
            colum = 0;
            cout << "\n";
        }
    }

    cout << ansi::reset << "\n\nSmooth greyscale with RGB: ";
    for (auto i = 0; i < 255; i+=8) {
        cout << ansi::bg_rgb(i, i, i) << "*";
    }
    cout << "\n";
    Pause();
    ClearAndReset();
    //TEST SAVE/RESTORE CURSOR POSITION
    cout << "\n\nYou can save and restore the cursor position at any time with\n" <<
        "'ansi::save_position' and 'ansi::restore_position'. Now press ENTER" <<
        " to save your cursor position.\n" << ansi::save_position;
    cin.get();
    cout << "Press ENTER again to restore the position and write the text " <<
        "'Here we are...'\n\n\n";
    cin.get();
    cout << ansi::restore_position << ansi::blink << "Here we are..." <<
        ansi::reset << " (Press ENTER)";
    cin.get();

    //TEST GOTO_XY AND HIDE CURSOR
    ClearAndReset();
    cout << ansi::goto_xy(1, 10);
    cout << "Two of the most powerful features are\n" << ansi::yellow << 
        "'ansi::goto_xy(x, y)'" << ansi::reset << " and " << ansi::yellow <<
        "ansi::up(), down(), left() or right()" << ansi::reset << ".\n" <<
        "In this sample I'm using " << ansi::yellow << "'ansi::hide_cursor'" <<
        ansi::reset << " too.\n\n" << 
        ansi::hide_cursor << ansi::save_position;
    srand(time(0)); // Yes I know!. Rand and Seed C style...
    for (auto i = 0; i < 85; i++) {
        cout << ansi::goto_xy((rand() % 40) + 10, (rand() % 6) + 2) <<
            ansi::bg((rand() % 15)+1) << " ";
        std::this_thread::sleep_for (std::chrono::milliseconds(100));
        cout << flush; //On some linux terminals you need to flush the buffer.
    }

    //TEST SHOW AND MOVE CURSOR
    cout << ansi::show_cursor << ansi::reset;
    for (auto i = 0; i < 2; i++) {
        //NOTE: flush is only necessary on some linux terminals.
        cout << ansi::right(10) << flush;
        std::this_thread::sleep_for (std::chrono::milliseconds(500));
        cout <<  ansi::right(3) << flush;
        std::this_thread::sleep_for (std::chrono::milliseconds(500));
        cout <<  ansi::left() << flush;
        std::this_thread::sleep_for (std::chrono::milliseconds(500));
        cout <<  ansi::left() << flush;
        std::this_thread::sleep_for (std::chrono::milliseconds(500));
        cout <<  ansi::down() << flush;
    }
    cout << ansi::restore_position << ansi::reset << 
        "There are more features, don't forget to read the header file.\nThanks for watching. Jose Puga.";
    cin.get();

    cout << ansi::white << ansi::bg_black << "\n"; //Default console colors fg/bg
    return 0;
}
