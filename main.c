/*
 * CH32V003 sample
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

#include "ch32v003_handlers.h"
#include "ch32v003_registers.h"

static volatile u32_t timer = 0;

void sys_tick_handler(void)
{
    if (timer)
        timer--;

    STK->SR = 0;
}

static void put(char data)
{
    while( !(USART1->STATR & USART_STATR_TC))
        continue;

    USART1->DATAR = data;
}

void main(void)
{
    RCC->APB2PCENR |= RCC_APB2PCENR_IOPDEN | RCC_APB2PCENR_USART1EN;

    USART1->CTLR1 = USART_CTLR1_TE;
    USART1->CTLR2 = 0;
    USART1->CTLR3 = 0;
    USART1->BRR = 8000000 / 115200;
    USART1->CTLR1 |= USART_CTLR1_UE;

    GPIOD->CFGLR = GPIO_CFGLR_GPI_FL(1) | GPIO_CFGLR_GPO_PP(4) | GPIO_CFGLR_AFO_PP(5);

    STK->CTLR = 0;
    STK->CMP = 1000;
    STK->CNT = 0;
    STK->CTLR = STK_CTLR_STE | STK_CTLR_STRE | STK_CTLR_STIE;

    PFIC->IENR[0] |= (1 << 12);

    while(1)
    {
        timer = 750;
        GPIOD->BSHR = GPIO_BSHR_BR4;
        put('A');
        while (timer)
            continue;

        timer = 250;
        GPIOD->BSHR = GPIO_BSHR_BS4;
        put('B');
        while (timer)
            continue;
    }
}
