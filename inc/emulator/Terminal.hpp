#pragma once

#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <cstdint>

class Terminal
{
public:
    Terminal();
    ~Terminal();

    void enableRawMode();
    void disableRawMode();

    bool kbhit();
    char readCharacter();

    void putChar32(uint32_t value);

private:
    struct termios original_terminal_settings;
    struct termios new_terminal_settings;
};