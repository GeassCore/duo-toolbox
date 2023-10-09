
fw_bin/sbi.elf:     file format elf64-littleriscv


Disassembly of section .text.boot:

0000000080000000 <_start>:
    80000000:	00001117          	auipc	sp,0x1
    80000004:	00010113          	mv	sp,sp
    80000008:	6291                	lui	t0,0x4
    8000000a:	9116                	add	sp,sp,t0
    8000000c:	0480006f          	j	80000054 <sbi_main>

Disassembly of section .text:

0000000080000010 <write32>:
    80000010:	1101                	addi	sp,sp,-32
    80000012:	ec22                	sd	s0,24(sp)
    80000014:	1000                	addi	s0,sp,32
    80000016:	87aa                	mv	a5,a0
    80000018:	872e                	mv	a4,a1
    8000001a:	fef42623          	sw	a5,-20(s0)
    8000001e:	87ba                	mv	a5,a4
    80000020:	fef42423          	sw	a5,-24(s0)
    80000024:	fec46783          	lwu	a5,-20(s0)
    80000028:	873e                	mv	a4,a5
    8000002a:	fe842783          	lw	a5,-24(s0)
    8000002e:	c31c                	sw	a5,0(a4)
    80000030:	0001                	nop
    80000032:	6462                	ld	s0,24(sp)
    80000034:	6105                	addi	sp,sp,32
    80000036:	8082                	ret

0000000080000038 <read32>:
    80000038:	1101                	addi	sp,sp,-32
    8000003a:	ec22                	sd	s0,24(sp)
    8000003c:	1000                	addi	s0,sp,32
    8000003e:	87aa                	mv	a5,a0
    80000040:	fef42623          	sw	a5,-20(s0)
    80000044:	fec46783          	lwu	a5,-20(s0)
    80000048:	439c                	lw	a5,0(a5)
    8000004a:	2781                	sext.w	a5,a5
    8000004c:	853e                	mv	a0,a5
    8000004e:	6462                	ld	s0,24(sp)
    80000050:	6105                	addi	sp,sp,32
    80000052:	8082                	ret

0000000080000054 <sbi_main>:
    80000054:	711d                	addi	sp,sp,-96
    80000056:	ec86                	sd	ra,88(sp)
    80000058:	e8a2                	sd	s0,80(sp)
    8000005a:	e4a6                	sd	s1,72(sp)
    8000005c:	1080                	addi	s0,sp,96
    8000005e:	fc042e23          	sw	zero,-36(s0)
    80000062:	030207b7          	lui	a5,0x3020
    80000066:	00478513          	addi	a0,a5,4 # 3020004 <_start-0x7cfdfffc>
    8000006a:	fcfff0ef          	jal	ra,80000038 <read32>
    8000006e:	87aa                	mv	a5,a0
    80000070:	fcf42e23          	sw	a5,-36(s0)
    80000074:	fdc42703          	lw	a4,-36(s0)
    80000078:	67a1                	lui	a5,0x8
    8000007a:	8fd9                	or	a5,a5,a4
    8000007c:	fcf42e23          	sw	a5,-36(s0)
    80000080:	fdc42783          	lw	a5,-36(s0)
    80000084:	85be                	mv	a1,a5
    80000086:	030207b7          	lui	a5,0x3020
    8000008a:	00478513          	addi	a0,a5,4 # 3020004 <_start-0x7cfdfffc>
    8000008e:	f83ff0ef          	jal	ra,80000010 <write32>
    80000092:	03020537          	lui	a0,0x3020
    80000096:	fa3ff0ef          	jal	ra,80000038 <read32>
    8000009a:	87aa                	mv	a5,a0
    8000009c:	fcf42e23          	sw	a5,-36(s0)
    800000a0:	fdc42783          	lw	a5,-36(s0)
    800000a4:	85be                	mv	a1,a5
    800000a6:	03020537          	lui	a0,0x3020
    800000aa:	f67ff0ef          	jal	ra,80000010 <write32>
    800000ae:	030227b7          	lui	a5,0x3022
    800000b2:	00478513          	addi	a0,a5,4 # 3022004 <_start-0x7cfddffc>
    800000b6:	f83ff0ef          	jal	ra,80000038 <read32>
    800000ba:	87aa                	mv	a5,a0
    800000bc:	fcf42e23          	sw	a5,-36(s0)
    800000c0:	fdc42703          	lw	a4,-36(s0)
    800000c4:	010007b7          	lui	a5,0x1000
    800000c8:	8fd9                	or	a5,a5,a4
    800000ca:	fcf42e23          	sw	a5,-36(s0)
    800000ce:	fdc42783          	lw	a5,-36(s0)
    800000d2:	85be                	mv	a1,a5
    800000d4:	030227b7          	lui	a5,0x3022
    800000d8:	00478513          	addi	a0,a5,4 # 3022004 <_start-0x7cfddffc>
    800000dc:	f35ff0ef          	jal	ra,80000010 <write32>
    800000e0:	03022537          	lui	a0,0x3022
    800000e4:	f55ff0ef          	jal	ra,80000038 <read32>
    800000e8:	87aa                	mv	a5,a0
    800000ea:	fcf42e23          	sw	a5,-36(s0)
    800000ee:	fdc42703          	lw	a4,-36(s0)
    800000f2:	010007b7          	lui	a5,0x1000
    800000f6:	8fd9                	or	a5,a5,a4
    800000f8:	fcf42e23          	sw	a5,-36(s0)
    800000fc:	fdc42783          	lw	a5,-36(s0)
    80000100:	85be                	mv	a1,a5
    80000102:	03022537          	lui	a0,0x3022
    80000106:	f0bff0ef          	jal	ra,80000010 <write32>
    8000010a:	300027f3          	csrr	a5,mstatus
    8000010e:	84be                	mv	s1,a5
    80000110:	87a6                	mv	a5,s1
    80000112:	fcf43823          	sd	a5,-48(s0)
    80000116:	fd043703          	ld	a4,-48(s0)
    8000011a:	6789                	lui	a5,0x2
    8000011c:	80078793          	addi	a5,a5,-2048 # 1800 <_start-0x7fffe800>
    80000120:	8fd9                	or	a5,a5,a4
    80000122:	fcf43823          	sd	a5,-48(s0)
    80000126:	fd043783          	ld	a5,-48(s0)
    8000012a:	f7f7f793          	andi	a5,a5,-129
    8000012e:	fcf43823          	sd	a5,-48(s0)
    80000132:	fd043783          	ld	a5,-48(s0)
    80000136:	fcf43423          	sd	a5,-56(s0)
    8000013a:	fc843783          	ld	a5,-56(s0)
    8000013e:	30079073          	csrw	mstatus,a5
    80000142:	40100793          	li	a5,1025
    80000146:	07d6                	slli	a5,a5,0x15
    80000148:	fcf43023          	sd	a5,-64(s0)
    8000014c:	fc043783          	ld	a5,-64(s0)
    80000150:	34179073          	csrw	mepc,a5
    80000154:	40100793          	li	a5,1025
    80000158:	07d6                	slli	a5,a5,0x15
    8000015a:	faf43c23          	sd	a5,-72(s0)
    8000015e:	fb843783          	ld	a5,-72(s0)
    80000162:	10579073          	csrw	stvec,a5
    80000166:	fa043823          	sd	zero,-80(s0)
    8000016a:	fb043783          	ld	a5,-80(s0)
    8000016e:	10479073          	csrw	sie,a5
    80000172:	fa043423          	sd	zero,-88(s0)
    80000176:	fa843783          	ld	a5,-88(s0)
    8000017a:	18079073          	csrw	satp,a5
    8000017e:	30200073          	mret
    80000182:	0001                	nop
    80000184:	60e6                	ld	ra,88(sp)
    80000186:	6446                	ld	s0,80(sp)
    80000188:	64a6                	ld	s1,72(sp)
    8000018a:	6125                	addi	sp,sp,96
    8000018c:	8082                	ret

Disassembly of section .data:

0000000080001000 <stacks_start>:
	...

Disassembly of section .riscv.attributes:

0000000000000000 <.riscv.attributes>:
   0:	3441                	addiw	s0,s0,-16
   2:	0000                	unimp
   4:	7200                	ld	s0,32(a2)
   6:	7369                	lui	t1,0xffffa
   8:	01007663          	bgeu	zero,a6,14 <_start-0x7fffffec>
   c:	002a                	c.slli	zero,0xa
   e:	0000                	unimp
  10:	1004                	addi	s1,sp,32
  12:	7205                	lui	tp,0xfffe1
  14:	3676                	fld	fa2,376(sp)
  16:	6934                	ld	a3,80(a0)
  18:	7032                	0x7032
  1a:	5f30                	lw	a2,120(a4)
  1c:	326d                	addiw	tp,tp,-5
  1e:	3070                	fld	fa2,224(s0)
  20:	615f 7032 5f30      	0x5f307032615f
  26:	3266                	fld	ft4,120(sp)
  28:	3070                	fld	fa2,224(s0)
  2a:	645f 7032 5f30      	0x5f307032645f
  30:	30703263          	0x30703263
	...

Disassembly of section .comment:

0000000000000000 <.comment>:
   0:	3a434347          	fmsub.d	ft6,ft6,ft4,ft7,rmm
   4:	2820                	fld	fs0,80(s0)
   6:	2029                	0x2029
   8:	2e39                	addiw	t3,t3,14
   a:	00302e33          	sgtz	t3,gp
