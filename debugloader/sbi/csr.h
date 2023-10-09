#ifndef _CSR_H
#define _CSR_H

#define INSERT_FIELD(val, which, fieldval) \
	(((val) & ~(which)) | ((fieldval) * ((which) & ~((which)-1))))

#define PRV_U				(0UL)
#define PRV_S				(1UL)
#define PRV_M				(3UL)

#define MSTATUS_MPP_SHIFT	11
#define MSTATUS_MPP	(3UL << MSTATUS_MPP_SHIFT)
#define MSTATUS_MPIE	0x00000080UL

#define read_csr(csr)						\
({								\
	register unsigned long __v;				\
	__asm__ __volatile__ ("csrr %0, " #csr			\
			      : "=r" (__v) :			\
			      : "memory");			\
	__v;							\
})

#define write_csr(csr, val)					\
({								\
	unsigned long __v = (unsigned long)(val);		\
	__asm__ __volatile__ ("csrw " #csr ", %0"		\
			      : : "rK" (__v)			\
			      : "memory");			\
})

#endif
