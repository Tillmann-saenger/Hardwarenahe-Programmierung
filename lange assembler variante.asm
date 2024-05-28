.file    "main.c"
    .option nopic
    .attribute arch, "rv32i2p0_m2p0_c2p0"
    .attribute unaligned_access, 0
    .attribute stack_align, 16
    .text
    .section    .text.startup.main,"ax",@progbits
    .align    1
    .globl    main
    .type    main, @function
main:
    li    a5,1610629120
    addi    a4,a5,1404
    li    a3,640
    sw    a3,0(a4)
    lw    a4,32(a5)
    addi    sp,sp,-16
    li    a3,1610629120
    andi    a4,a4,-1025
    sw    a4,32(a5)
    lw    a4,32(a5)
    ori    a4,a4,1024           //bitschift
    sw    a4,32(a5)             //gpio enable
    li    a4,999424
    addi    a4,a4,575           //128
.L4:
    sw    zero,12(sp)
.L2:
    lw    a5,12(sp)
    ble    a5,a4,.L3
    lw    a5,4(a3)              //toggle
    xori    a5,a5,1024          //
    sw    a5,4(a3)              //
    j    .L4
.L3:
    lw    a5,12(sp)
    addi    a5,a5,1
    sw    a5,12(sp)
    j    .L2
    .size    main, .-main
    .ident    "GCC: (Alpine Linux) 11.2.0"