OUTPUT_ARCH( "riscv" )
OUTPUT_FORMAT("elf64-littleriscv", "elf64-littleriscv", "elf64-littleriscv")

ENTRY( _start )
SECTIONS
{
	INCLUDE "os_base.ld"

	. = 0x80210000;

	.payload :
	{
		PROVIDE(_payload_start = .);
		*(.payload)
		. = ALIGN(8);
		PROVIDE(_payload_end = .);
	}
}
