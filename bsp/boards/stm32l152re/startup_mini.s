.syntax unified
.cpu cortex-m3
.thumb

.global _estack
.global Reset_Handler

/* Symbols from linker script */
.extern _sidata
.extern _sdata
.extern _edata
.extern _sbss
.extern _ebss

.extern SystemInit
.extern main

/* ================= VECTOR TABLE ================= */
.section .isr_vector, "a", %progbits
.type g_pfnVectors, %object

g_pfnVectors:
    .word _estack          /* Initial Stack Pointer */
    .word Reset_Handler    /* Reset Handler */
    .word Default_Handler  /* NMI */
    .word Default_Handler  /* HardFault */
    .word Default_Handler
    .word Default_Handler
    .word Default_Handler
    .word Default_Handler
    .word Default_Handler
    .word Default_Handler
    .word Default_Handler
    .word Default_Handler
    .word Default_Handler
    .word Default_Handler
    .word Default_Handler
    .word Default_Handler

/* ================= RESET HANDLER ================= */
.section .text.Reset_Handler
.type Reset_Handler, %function

Reset_Handler:
    /* 1. Copy .data from Flash to RAM */
    ldr r0, =_sidata
    ldr r1, =_sdata
    ldr r2, =_edata
1:
    cmp r1, r2
    ittt lt
    ldrlt r3, [r0], #4
    strlt r3, [r1], #4
    blt 1b

    /* 2. Zero .bss */
    ldr r0, =_sbss
    ldr r1, =_ebss
    movs r2, #0
2:
    cmp r0, r1
    it lt
    strlt r2, [r0], #4
    blt 2b

    /* 3. System init (optional but clean) */
    bl SystemInit

    /* 4. Enter main */
    bl main

    /* 5. If main returns → trap */
3:
    b 3b

/* ================= DEFAULT HANDLER ================= */
.section .text.Default_Handler
Default_Handler:
    b .