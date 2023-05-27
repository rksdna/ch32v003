/*
 * CH32V003 startup code
 * Copyright (c) 2023 rksdna
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "ch32v003_types.h"

extern u32_t stack_section_end;
extern u32_t text_section_end;
extern u32_t data_section_begin;
extern u32_t data_section_end;
extern u32_t bss_section_begin;
extern u32_t bss_section_end;

extern void main(void);

void startup_table(void) __attribute__((naked)) __attribute((section(".startup")));
void startup_table(void)
{
    asm volatile(".align 2\n"
                 ".option norvc;\n"
                 "j reset_handler\n"
                 ".word null_handler\n"
                 ".word nmi_handler\n"
                 ".word hard_fault_handler\n"
                 ".word null_handler\n"
                 ".word null_handler\n"
                 ".word null_handler\n"
                 ".word null_handler\n"
                 ".word null_handler\n"
                 ".word null_handler\n"
                 ".word null_handler\n"
                 ".word null_handler\n"
                 ".word sys_tick_handler\n"
                 ".word null_handler\n"
                 ".word sw_handler\n"
                 ".word null_handler\n"
                 ".word wwdg_handler\n"
                 ".word pvd_handler\n"
                 ".word flash_handler\n"
                 ".word rcc_handler\n"
                 ".word exti7_0_handler\n"
                 ".word awu_handler\n"
                 ".word dma1_ch1_handler\n"
                 ".word dma1_ch2_handler\n"
                 ".word dma1_ch3_handler\n"
                 ".word dma1_ch4_handler\n"
                 ".word dma1_ch5_handler\n"
                 ".word dma1_ch6_handler\n"
                 ".word dma1_ch7_handler\n"
                 ".word adc1_handler\n"
                 ".word i2c1_ev_handler\n"
                 ".word i2c1_er_handler\n"
                 ".word usart1_handler\n"
                 ".word spi1_handler\n"
                 ".word tim1_brk_handler\n"
                 ".word tim1_up_handler\n"
                 ".word tim1_trg_com_handler\n"
                 ".word tim1_cc_handler\n"
                 ".word tim2_handler\n");
}

void reset_handler(void) __attribute__((naked));
void reset_handler(void)
{
    asm volatile(".option push\n"
                 ".option norelax\n"
                 "la gp, data_section_center\n"
                 ".option pop\n"
                 "la sp, stack_section_end\n"
                 "li a0, 0x80\n"
                 "csrw mstatus, a0\n"
                 "li a3, 0x3\n"
                 "csrw 0x804, a3\n"
                 "la a0, startup_table\n"
                 "or a0, a0, a3\n"
                 "csrw mtvec, a0\n"
                 "la a0, bss_section_begin\n"
                 "la a1, bss_section_end\n"
                 "li a2, 0\n"
                 "bge a0, a1, 2f\n"
                 "1: sw a2, 0(a0)\n"
                 "addi a0, a0, 4\n"
                 "blt a0, a1, 1b\n"
                 "2: la a0, text_section_end\n"
                 "la a1, data_section_begin\n"
                 "la a2, data_section_end\n"
                 "3: beq a1, a2, 4f\n"
                 "lw a3, 0(a0)\n"
                 "sw a3, 0(a1)\n"
                 "addi a0, a0, 4\n"
                 "addi a1, a1, 4\n"
                 "bne a1, a2, 3b\n"
                 "4: la a0, main\n"
                 "csrw mepc, a0\n"
                 "mret\n");
}

void null_handler(void) __attribute__((naked));
void null_handler(void)
{
    asm volatile("1: j 1b\n");
}

void nmi_handler(void) __attribute((weak, alias("null_handler")));
void hard_fault_handler(void) __attribute((weak, alias("null_handler")));
void sys_tick_handler(void) __attribute((weak, alias("null_handler")));
void sw_handler(void) __attribute((weak, alias("null_handler")));
void wwdg_handler(void) __attribute((weak, alias("null_handler")));
void pvd_handler(void) __attribute((weak, alias("null_handler")));
void flash_handler(void) __attribute((weak, alias("null_handler")));
void rcc_handler(void) __attribute((weak, alias("null_handler")));
void exti7_0_handler(void) __attribute((weak, alias("null_handler")));
void awu_handler(void) __attribute((weak, alias("null_handler")));
void dma1_ch1_handler(void) __attribute((weak, alias("null_handler")));
void dma1_ch2_handler(void) __attribute((weak, alias("null_handler")));
void dma1_ch3_handler(void) __attribute((weak, alias("null_handler")));
void dma1_ch4_handler(void) __attribute((weak, alias("null_handler")));
void dma1_ch5_handler(void) __attribute((weak, alias("null_handler")));
void dma1_ch6_handler(void) __attribute((weak, alias("null_handler")));
void dma1_ch7_handler(void) __attribute((weak, alias("null_handler")));
void adc1_handler(void) __attribute((weak, alias("null_handler")));
void i2c1_ev_handler(void) __attribute((weak, alias("null_handler")));
void i2c1_er_handler(void) __attribute((weak, alias("null_handler")));
void usart1_handler(void) __attribute((weak, alias("null_handler")));
void spi1_handler(void) __attribute((weak, alias("null_handler")));
void tim1_brk_handler(void) __attribute((weak, alias("null_handler")));
void tim1_up_handler(void) __attribute((weak, alias("null_handler")));
void tim1_trg_com_handler(void) __attribute((weak, alias("null_handler")));
void tim1_cc_handler(void) __attribute((weak, alias("null_handler")));
void tim2_handler(void) __attribute((weak, alias("null_handler")));
