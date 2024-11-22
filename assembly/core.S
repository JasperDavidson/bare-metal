.syntax unified
.cpu cortex-m0
.fpu softvfp
.thumb

.global reset_handler

// Reset handler, called on reset
reset_handler:
    // Set the stack pointer to the end of the stack
    LDR r0, =_estack
    MOV sp, r0

    // Copy data from flash to RAM
    MOVS r0, #0

    LDR r1, =_sdata
    LDR r2, =_edata
    LDR r3, =_sidata
    B copy_sidata_loop

    copy_sidata:
        LDR r4, [r3, r0]
        STR r4, [r1, r0]
        ADDS r0, r0, #4

    copy_sidata_loop:
        ADDS r4, r0, r1
        CMP r4, r2
        BCC copy_sidata

    // Zero out the BSS
    MOVS r0, #0
    LDR r1, =_sbss
    LDR r2, =_ebss

    reset_bss:
        STR r0, [r1]
        ADDS r1, r1, #4

    reset_bss_loop:
        CMP r1, r2
        BCC reset_bss

    // Branch to main
    B main
.size reset_handler, .-reset_handler
