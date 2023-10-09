riscv64-unknown-elf-gcc -nostdlib -c entry.s -o entry.o
riscv64-unknown-elf-gcc -nostdlib -c main.c -o main.o
riscv64-unknown-elf-ld -o fw_bin/sbi.elf -Tlink.ld entry.o main.o
riscv64-unknown-elf-objcopy -Obinary fw_bin/sbi.elf fw_bin/sbi.bin
riscv64-unknown-elf-objdump -D fw_bin/sbi.elf > fw_bin/sbi.asm
