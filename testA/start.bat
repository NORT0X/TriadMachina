@echo off

set ROOT_DIR=%~dp0..\  // Go one level up to the root directory
set ASSEMBLER=..\build\asembler.exe
set LINKER=..\linker.exe
set EMULATOR=..\emulator.exe

%ASSEMBLER% -o main.o main.s
%ASSEMBLER% -o math.o math.s
%ASSEMBLER% -o handler.o handler.s
%ASSEMBLER% -o isr_timer.o isr_timer.s
%ASSEMBLER% -o isr_terminal.o isr_terminal.s
%ASSEMBLER% -o isr_software.o isr_software.s

%LINKER% -hex ^
  -place=my_code@0x40000000 -place=math@0xF0000000 ^
  -o program.hex ^
  handler.o math.o main.o isr_terminal.o isr_timer.o isr_software.o

%EMULATOR% program.hex
