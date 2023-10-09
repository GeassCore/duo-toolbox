.equ	STACK_SIZE, 16384
.text
.global	_start
_start:
#include "boot0.h"
_start_real:
	csrr    t0, mhartid	
	mv	tp, t0			
	bnez	t0, park		
	slli	t0, t0, 10		
	la	sp, stacks + STACK_SIZE	
	add	sp, sp, t0		
	j	start_kernel		

park:
	wfi
	j	park

.align 4
stacks:
	.skip	STACK_SIZE

.section .payload, "ax", %progbits
.globl payload_bin
payload_bin:
        .incbin "rtos.bin"
	.end			

