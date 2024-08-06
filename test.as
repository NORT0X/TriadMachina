# file: math.s

.global mathAdd, mathSub, mathMul, mathDiv

.section math
.word mathAdd, mathDiv
mathAdd:
    jmp 0x11223344
    jmp 0x55667788
    push %r2
    ld [%sp + 0x08], %r1
    ld [%sp + 0x0C], %r2
    add %r2, %r1 # r1 used for the result
    pop %r2
    ret

mathSub:
    push %r2
    ld [%sp + 0x08], %r1
    ld [%sp + 0x0C], %r2
    sub %r2, %r1 # r1 used for the result
    pop %r2
    ret

mathMul:
    push %r2
    ld [%sp + 0x08], %r1
    ld [%sp + 0x0C], %r2
    mul %r2, %r1 # r1 used for the result
    pop %r2
    ret

mathDiv:
    push %r2
    ld [%sp + 0x08], %r1
    ld [%sp + 0x0C], %r2
    div %r2, %r1 # r1 used for the result
    pop %r2
    ret

.section test
methodTest:
    jmp 0x12345678
    sub %r2, %r1

.end
