#include "csr.h"

#define FW_JUMP_ADDR 0x80200000

typedef unsigned int virtual_addr_t;
typedef unsigned int u32_t;
typedef unsigned int uint32_t;

static inline void write32(virtual_addr_t addr, unsigned int value)
{
    *((volatile unsigned int *)(addr)) = value;
}

static inline unsigned int read32(virtual_addr_t addr)
{
    return( *((volatile unsigned int *)(addr)));
}

/*
 * M模式
 */
void sbi_main(void)
{

    uint32_t led = 0;
    unsigned long val;
    led = read32(0x03020004);
    led |= ( 1 << 15);
    write32(0x03020004, led);
    led = read32(0x03020000);
    led |= ( 0 << 15);
    write32(0x03020000, led);
    led = read32(0x03022004);
    led |= ( 1 << 24);
    write32(0x03022004, led);
    led = read32(0x03022000);
    led |= ( 1 << 24);
    write32(0x03022000, led);

    val = read_csr(mstatus);
    val = INSERT_FIELD(val, MSTATUS_MPP, PRV_M);
    val = INSERT_FIELD(val, MSTATUS_MPIE, 0);
    write_csr(mstatus, val);

    write_csr(mepc, FW_JUMP_ADDR);
    write_csr(stvec, FW_JUMP_ADDR);
    write_csr(sie, 0);
    write_csr(satp, 0);

    asm volatile("mret");
}
