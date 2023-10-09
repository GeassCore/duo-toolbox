
.PHONY: memory-map

TOP_DIR=$(shell pwd)
export BUILD_PATH=${TOP_DIR}/build

CVI_BOARD_MEMMAP_H_PATH := ${TOP_DIR}/build/output/cvi_board_memmap.h
CVI_BOARD_MEMMAP_CONF_PATH := ${TOP_DIR}/build/output/cvi_board_memmap.conf
CVI_BOARD_MEMMAP_LD_PATH := ${TOP_DIR}/build/output/cvi_board_memmap.ld

BOARD_MMAP_PATH := build/scripts/memmap.py
MMAP_CONV_PY := build/scripts/mmap_conv.py


${CVI_BOARD_MEMMAP_H_PATH}: ${BOARD_MMAP_PATH} ${MMAP_CONV_PY}
	$(call print_target)
	mkdir -p $(dir $@)
	@${MMAP_CONV_PY} --type h $< $@

${CVI_BOARD_MEMMAP_CONF_PATH}: ${BOARD_MMAP_PATH} ${MMAP_CONV_PY}
	$(call print_target)
	@mkdir -p $(dir $@)
	@${MMAP_CONV_PY} --type conf $< $@

${CVI_BOARD_MEMMAP_LD_PATH}: ${BOARD_MMAP_PATH} ${MMAP_CONV_PY}
	$(call print_target)
	@mkdir -p $(dir $@)
	@${MMAP_CONV_PY} --type ld $< $@

ifeq ($(wildcard ${BOARD_MMAP_PATH}),)
memory-map:
else
memory-map: ${CVI_BOARD_MEMMAP_H_PATH} ${CVI_BOARD_MEMMAP_CONF_PATH} ${CVI_BOARD_MEMMAP_LD_PATH}
endif

rtos: memory-map
	$(call print_target)
	cd freertos/cvitek && ./build_cv180x.sh

rtos-clean:
	$(call print_target)
	cd freertos/cvitek && rm -rf build 

####################u-boot########################

UBOOT_OUTPUT_FOLDER=build

UBOOT_CVI_BOARD_INIT_PATH := u-boot/board/cvitek/cvi_board_init.c
UBOOT_CVITEK_PATH := u-boot/include/cvitek/cvitek.h
UBOOT_CVITEK_CONFIG_PATH := u-boot/configs/cvitek_cv1800b_milkv_duo_sd_defconfig

UBOOT_CVIPART_DEP := u-boot/include/imgs.h u-boot/include/cvipart.h

FLASH_PARTITION_XML := ${BUILD_PATH}/uboot/partition_sd.xml


u-boot-dts:
	$(call print_target)
	${Q}find ${BUILD_PATH}/dts \
	\( -path "*.dts*" \) \
	-exec cp {} u-boot/arch/riscv/dts/ \;


${UBOOT_CVIPART_DEP}: ${FLASH_PARTITION_XML}
	$(call print_target)
	${Q}python3 ${BUILD_PATH}/scripts/mkcvipart.py ${FLASH_PARTITION_XML} u-boot/include
	${Q}python3 ${BUILD_PATH}/scripts/mk_imgHeader.py ${FLASH_PARTITION_XML} u-boot/include



u-boo%: export CHIP=cv1800b
u-boo%: export CVIBOARD=milkv_duo_sd
u-boo%: export CHIP_ARCH=CV180X
u-boo%: export CVIARCH=CV180X
u-boot-build: memory-map
u-boot-build: u-boot-dts
u-boot-build: ${UBOOT_CVIPART_DEP}
	$(call print_target)
	${Q}ln -snrf ${CVI_BOARD_MEMMAP_H_PATH} u-boot/include/
	${Q}rm -f ${UBOOT_CVI_BOARD_INIT_PATH}
	${Q}ln -s ${BUILD_PATH}/uboot/cvi_board_init.c ${UBOOT_CVI_BOARD_INIT_PATH}
	${Q}rm -f ${UBOOT_CVITEK_PATH}
	${Q}ln -s ${BUILD_PATH}/uboot/cvitek.h ${UBOOT_CVITEK_PATH}
	${Q}rm -f ${UBOOT_CVITEK_CONFIG_PATH}
	${Q}cp ${BUILD_PATH}/uboot/cvitek_cv1800b_milkv_duo_sd_defconfig ${UBOOT_CVITEK_CONFIG_PATH}
	${Q}$(MAKE) -C u-boot ARCH=riscv CROSS_COMPILE=riscv64-unknown-linux-musl- cvitek_cv1800b_milkv_duo_sd_defconfig O=${UBOOT_OUTPUT_FOLDER}
	${Q}$(MAKE) -C u-boot/${UBOOT_OUTPUT_FOLDER} ARCH=riscv CROSS_COMPILE=riscv64-unknown-linux-musl- -j${NPROC} all
	${Q}cat u-boot/build/u-boot.bin > u-boot/build/u-boot-raw.bin

u-boot-clean:
	$(call print_target)
	${Q}$(MAKE) -C u-boot clean

opensbi: export CROSS_COMPILE=riscv64-unknown-linux-musl-
opensbi: u-boot-build
	$(call print_target)
	${Q}$(MAKE) -j${NPROC} -C opensbi PLATFORM=generic \
		FW_PAYLOAD_PATH=../u-boot/build/u-boot-raw.bin \
		FW_FDT_PATH=../u-boot/build/arch/riscv/dts/cv1800b_milkv_duo_sd.dtb
opensbi-clean:
	$(call print_target)
	${Q}$(MAKE) -C opensbi PLATFORM=generic distclean


FSBL_OUTPUT_PATH = fsbl/build
fsbl-build: opensbi
fsbl-build: rtos
fsbl%: export CHIP_ARCH=CV180X
fsbl%: export CVIARCH=CV180X
fsbl%: export BOOT_CPU=riscv
fsbl%: export BLCP_2ND_PATH=${TOP_DIR}/freertos/cvirtos.bin
#fsbl%: export LOADER_2ND_PATH=${TOP_DIR}/os.bin
fsbl%: export LOADER_2ND_PATH=${TOP_DIR}/u-boot/build/u-boot-raw.bin
fsbl%: export RTOS_DUMP_PRINT_ENABLE=y
fsbl%: export RTOS_DUMP_PRINT_SZ_IDX=17
fsbl%: export RTOS_FAST_IMAGE_TYPE=0
fsbl%: export RTOS_ENABLE_FREERTOS=y
fsbl%: export ARCH=riscv
fsbl%: export PROJECT_FULLNAME=cv1800b_sophpi_duo_sd
fsbl-build: u-boot-build memory-map
	$(call print_target)
	${Q}mkdir -p fsbl/build
	${Q}ln -snrf -t fsbl/build ${CVI_BOARD_MEMMAP_H_PATH}
	${Q}$(MAKE) BOOT_CPU=riscv ARCH=riscv CROSS_COMPILE=riscv64-unknown-linux-musl- -C fsbl O=build BLCP_2ND_PATH=${BLCP_2ND_PATH} \
		LOADER_2ND_PATH=${LOADER_2ND_PATH}
	${Q}cp fsbl/build/fip.bin build/

fsbl-clean: rtos-clean
	$(call print_target)
	${Q}$(MAKE) -C fsbl clean O=build
