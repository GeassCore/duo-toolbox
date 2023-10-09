#ifndef __DUO_REG_H__
#define __DUO_REG_H__

#define TOP_BASE        0x03000000
#define PINMUX_BASE     (TOP_BASE + 0x1000)
#define WATCHDOG_BASE   (TOP_BASE + 0x00010000)
#define RTC_BASE   0x05026000

/*
 * RTC info registers
 */
#define RTC_INFO0 (RTC_BASE + 0x1C)

/*
 * General purpose registers
 */
#define GP_REG0 (TOP_BASE + 0x80)
#define GP_REG1 (TOP_BASE + 0x84)
#define GP_REG2 (TOP_BASE + 0x88
#define GP_REG3 (TOP_BASE + 0x8C)
#define GP_REG4 (TOP_BASE + 0x90)
#define GP_REG5 (TOP_BASE + 0x94)
#define GP_REG6 (TOP_BASE + 0x98)
#define GP_REG7 (TOP_BASE + 0x9C)
#define GP_REG8 (TOP_BASE + 0xA0)
#define GP_REG9 (TOP_BASE + 0xA4)
#define GP_REG10 (TOP_BASE + 0xA8)

/*
 * Pinmux definitions
 */
#define PINMUX_UART0    0
#define PINMUX_UART1    1
#define PINMUX_UART2    2
#define PINMUX_UART3    3
#define PINMUX_UART3_2  4
#define PINMUX_I2C0     5
#define PINMUX_I2C1     6
#define PINMUX_I2C2     7
#define PINMUX_I2C3     8
#define PINMUX_I2C4     9
#define PINMUX_I2C4_2   10
#define PINMUX_SPI0     11
#define PINMUX_SPI1     12
#define PINMUX_SPI2     13
#define PINMUX_SPI2_2   14
#define PINMUX_SPI3     15
#define PINMUX_SPI3_2   16
#define PINMUX_I2S0     17
#define PINMUX_I2S1     18
#define PINMUX_I2S2     19
#define PINMUX_I2S3     20
#define PINMUX_USBID    21
#define PINMUX_SDIO0    22
#define PINMUX_SDIO1    23
#define PINMUX_ND       24
#define PINMUX_EMMC     25
#define PINMUX_SPI_NOR  26
#define PINMUX_SPI_NAND 27
#define PINMUX_CAM0     28
#define PINMUX_CAM1     29
#define PINMUX_PCM0     30
#define PINMUX_PCM1     31
#define PINMUX_CSI0     32
#define PINMUX_CSI1     33
#define PINMUX_CSI2     34
#define PINMUX_DSI      35
#define PINMUX_VI0      36
#define PINMUX_VO       37
#define PINMUX_RMII1    38
#define PINMUX_EPHY_LED 39
#define PINMUX_I80      40
#define PINMUX_LVDS     41

#define REG_TOP_USB_ECO			(TOP_BASE + 0xB4)
#define BIT_TOP_USB_ECO_RX_FLUSH	0x80
/* rst */
#define REG_TOP_SOFT_RST        0x3000
#define BIT_TOP_SOFT_RST_USB    BIT(11)
#define BIT_TOP_SOFT_RST_SDIO   BIT(14)
#define BIT_TOP_SOFT_RST_NAND   BIT(12)

#define REG_TOP_USB_CTRSTS	(TOP_BASE + 0x38)

#define REG_TOP_CONF_INFO		(TOP_BASE + 0x4)
#define BIT_TOP_CONF_INFO_VBUS		BIT(9)
#define REG_TOP_USB_PHY_CTRL		(TOP_BASE + 0x48)
#define BIT_TOP_USB_PHY_CTRL_EXTVBUS	BIT(0)
#define USB_PHY_ID_OVERRIDE_ENABLE	BIT(6)
#define USB_PHY_ID_VALUE		BIT(7)
#define REG_TOP_DDR_ADDR_MODE		(TOP_BASE + 0x64)

/* irq */
#define IRQ_LEVEL   0
#define IRQ_EDGE    3

/* usb */
#define USB_BASE            0x04340000

/* ethernet phy */
#define ETH_PHY_BASE        0x03009000
#define ETH_PHY_INIT_MASK   0xFFFFFFF9
#define ETH_PHY_SHUTDOWN    BIT(1)
#define ETH_PHY_POWERUP     0xFFFFFFFD
#define ETH_PHY_RESET       0xFFFFFFFB
#define ETH_PHY_RESET_N     BIT(2)
#define ETH_PHY_LED_LOW_ACTIVE  BIT(3)

/* watchdog */
#define DW_WDT_CR	0x00
#define DW_WDT_TORR	0x04
#define DW_WDT_CRR	0x0C

#define DW_WDT_CR_EN_OFFSET	0x00
#define DW_WDT_CR_RMOD_OFFSET	0x01
#define DW_WDT_CR_RMOD_VAL	0x00
#define DW_WDT_CRR_RESTART_VAL	0x76

/* SDIO Wifi */
#define WIFI_CHIP_EN_BGA    BIT(18)
#define WIFI_CHIP_EN_QFN    BIT(2)

/* RTC */
#define RTC_SYS_BASE		0x05000000
#define RTC_MACRO_BASE		(RTC_SYS_BASE + 0x00026400)
#define RTC_MACRO_DA_SOC_READY		0x8C
#define RTC_MACRO_RO_T		0xA8
#define RTC_CORE_SRAM_BASE	(RTC_SYS_BASE + 0x00026800)
#define RTC_CORE_SRAM_SIZE	0x0800 // 2KB

#define REG_RTC_CTRL_BASE	(RTC_SYS_BASE + 0x00025000)
#define RTC_CTRL0_UNLOCKKEY	0x4
#define RTC_CTRL0		0x8
#define RTC_CTRL0_STATUS0		0xC
#define RTCSYS_RST_CTRL	0x18

#define REG_RTC_BASE		(RTC_SYS_BASE + 0x00026000)
#define RTC_EN_PWR_WAKEUP	0xBC
#define RTC_EN_SHDN_REQ	0xC0
#define RTC_EN_PWR_CYC_REQ	0xC8
#define RTC_EN_WARM_RST_REQ	0xCC
#define RTC_EN_WDT_RST_REQ	0xE0
#define RTC_EN_SUSPEND_REQ	0xE4
#define RTC_PG_REG		0xF0
#define RTC_ST_ON_REASON	0xF8

#define REG_RTC_ST_ON_REASON	(REG_RTC_BASE + RTC_ST_ON_REASON)

#define RTCSYS_F32KLESS_BASE		(RTC_SYS_BASE + 0x0002A000)

#define RTC_INTERNAL_32K	0
#define RTC_EXTERNAL_32K	1

/* eFuse  */
#define EFUSE_BASE (TOP_BASE + 0x00050000)

/* AXI SRAM */
#define AXI_SRAM_BASE 0x0E000000
#define AXI_SRAM_SIZE 0x40

#define EFUSE_SW_INFO_ADDR (AXI_SRAM_BASE)
#define EFUSE_SW_INFO_SIZE 4

#define BOOT_SOURCE_FLAG_ADDR (EFUSE_SW_INFO_ADDR + EFUSE_SW_INFO_SIZE)
#define BOOT_SOURCE_FLAG_SIZE 4
#define MAGIC_NUM_USB_DL 0x4D474E31 // MGN1
#define MAGIC_NUM_SD_DL 0x4D474E32 // MGN2

#define BOOT_LOG_LEN_ADDR (BOOT_SOURCE_FLAG_ADDR + BOOT_SOURCE_FLAG_SIZE) // 0x0E000008
#define BOOT_LOG_LEN_SIZE 4

#define TIME_RECORDS_ADDR (AXI_SRAM_BASE + 0x10) // 0x0E000010

/* from fsbl/plat/mars/include/platform_def.h struct _time_records { ... } */
#define TIME_RECORDS_FIELD_UBOOT_START (TIME_RECORDS_ADDR + 0x10)
#define TIME_RECORDS_FIELD_BOOTCMD_START (TIME_RECORDS_ADDR + 0x12)
#define TIME_RECORDS_FIELD_DECOMPRESS_KERNEL_START (TIME_RECORDS_ADDR + 0x14)
#define TIME_RECORDS_FIELD_KERNEL_START (TIME_RECORDS_ADDR + 0x16)

#endif /* __MARS_REG_H__ */
