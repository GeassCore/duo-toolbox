# duo-toolbox
  简化duo sdk编译，用于测试基础组件更新调试

# Quick Start


```
仓库初始化,下载工具链和更新submodule
$ ./init.sh

生成通用fip.bin
$ cd fip
$ cat env
export 相关host-tools路径，一般是
$ export PATH=`pwd`/../host-tools/gcc/riscv64-linux-musl-x86_64/bin:$PATH
$ export PATH=`pwd`/../host-tools/gcc/riscv64-elf-x86_64/bin:$PATH
如自己替换注意修过相关路径和Makfile
$ make fsbl-build

生成boot.sd
$ cd boot
确保目录里有Image和对应cv1800b_milkv_duo_sd.dtb
$ ./mksdimg.sh

生成单独rtos fip.bin
$cd debugloader
$cd sbi && ./build.sh #生成 sbi.bin
$cd duoRVOS
选择要使用的rtos bin替换目录下rtos.bin
$ make #生成 os.bin
将os.bin sbi.bin 复制到fip目录下
修改Makefile中
fsbl%: export LOADER_2ND_PATH=${TOP_DIR}/u-boot/build/u-boot-raw.bin为
fsbl%: export LOADER_2ND_PATH=${TOP_DIR}/os.bin
如果rtos运行在M模式
修改fip/fsbl/make_helpers/fip.mk中
MONITOR_PATH = ../opensbi/build/platform/generic/firmware/fw_dynamic.bin为
MONITOR_PATH = ../sbi.bin
$make fsbl-build

```