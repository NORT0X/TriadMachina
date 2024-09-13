ASSEMBLER=../build/asembler
LINKER=../build/linker
EMULATOR=../build/emulator

${ASSEMBLER} -o main.o main.s
${ASSEMBLER} -o handler.o handler.s
${ASSEMBLER} -o isr_terminal.o isr_terminal.s
${ASSEMBLER} -o isr_timer.o isr_timer.s
${LINKER} -relocatable \
  -o test.o \
  main.o isr_terminal.o
${LINKER} -hex \
  -place=my_code@0x40000000 \
  -o program.hex \
  test.o isr_timer.o handler.o
${EMULATOR} program.hex