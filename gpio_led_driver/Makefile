# 目标模块名称
obj-m := gpioled.o

# 内核源码路径
KDIR := /home/fanzeny/atk_dlrk3506_linux6.1_release_v1.3.1_20260326/kernel

# 指定目标架构和交叉编译器
ARCH := arm
CROSS_COMPILE := /home/fanzeny/atk_dlrk3506_linux6.1_release_v1.3.1_20260326/prebuilts/gcc/linux-x86/arm/gcc-arm-10.3-2021.07-x86_64-arm-none-linux-gnueabihf/bin/arm-none-linux-gnueabihf-  # 与当前内核构建一致的工具链

# 当前目录
PWD := $(shell pwd) #获取当前目录路径

all:
	$(MAKE) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) -C $(KDIR) M=$(PWD) modules #在内核源码目录下执行make命令，指定目标架构和交叉编译器，并且指定当前目录为模块源代码目录

clean:
	$(MAKE) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) -C $(KDIR) M=$(PWD) clean #在内核源码目录下执行make clean命令，清理模块构建生成的文件