#include "../../inc/emulator/Terminal.hpp"

#include <iostream>

Terminal::Terminal()
{
    enableRawMode();
}

Terminal::~Terminal()
{
    disableRawMode();
}

void Terminal::enableRawMode()
{
    tcgetattr(STDIN_FILENO, &original_terminal_settings);
    new_terminal_settings = original_terminal_settings;

    new_terminal_settings.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &new_terminal_settings);

    fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);
}

void Terminal::disableRawMode()
{
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &original_terminal_settings);
}

bool Terminal::kbhit()
{
    struct timeval tv = {0L, 0L};
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds);
    return select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv) > 0;
}

char Terminal::readCharacter()
{
    char ch;
    if (kbhit())
    {
        read(STDIN_FILENO, &ch, 1);
        return ch;
    }
    return EOF;
}

void Terminal::putChar32(uint32_t value)
{
    for (int i = 0; i < 4; ++i)
    {
        char ch = (value >> (i * 8)) & 0xFF;

        write(STDOUT_FILENO, &ch, 1);
    }
}
