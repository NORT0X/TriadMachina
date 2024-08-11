# file: math.s

.global mathAdd, mathSub, mathMul, mathDiv

.section math
.word mathAdd, mathDiv
mathAdd:
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
    beq %r1, %r2, mathDiv
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
    csrrd %cause, %r0
    call mathDiv
    ld $mathDiv, %r3
    ld mathDiv, %r3
    sub %r2, %r1
    ret

.end
