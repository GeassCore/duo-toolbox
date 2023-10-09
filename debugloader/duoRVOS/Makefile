CROSS_COMPILE = riscv64-unknown-elf-
CFLAGS = -nostdlib -fno-builtin -mcmodel=medany -g -Wall -Iinclude

GDB = gdb-multiarch
CC = ${CROSS_COMPILE}gcc
OBJCOPY = ${CROSS_COMPILE}objcopy
OBJDUMP = ${CROSS_COMPILE}objdump
LD = ${CROSS_COMPILE}ld

SRCS_ASM = \
	start.S \

SRCS_C = \
	kernel.c \
	drv_uart.c \

OBJS = $(SRCS_ASM:.S=.o)
OBJS += $(SRCS_C:.c=.o)

.DEFAULT_GOAL := all
all: os.elf

os.elf: ${OBJS}
	${CC} ${CFLAGS} -Tos_link_payload.ld -o os.elf $^
	${LD} -Tos_link_payload.ld -o os.elf ${OBJS} -Map os.map
	${OBJCOPY} -O binary os.elf os.bin
	${OBJDUMP} -D os.elf > os.asm

%.o : %.c
	${CC} ${CFLAGS} -c -o $@ $<

%.o : %.S
	${CC} ${CFLAGS} -c -o $@ $<

.PHONY : debug
debug: all
	@echo "Press Ctrl-C and then input 'quit' to exit GDB and QEMU"
	@echo "-------------------------------------------------------"
	@${QEMU} ${QFLAGS} -kernel os.elf -s -S &
	@${GDB} os.elf -q -x ../gdbinit

.PHONY : code
code: all
	@${OBJDUMP} -S os.elf | less

.PHONY : clean
clean:
	rm -rf *.o *.elf *.asm *.map
	rm os.bin

