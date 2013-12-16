obj-m += read_gps.o

CROSS = arm-linux-gnueabi-

KDIR = /home/ilya/drone_kernel

PWD := $(shell pwd)

all:
	make ARCH=arm -C $(KDIR) M=$(PWD) CROSS_COMPILE=$(CROSS) modules
	cp read_gps.ko /media/ilya/001B-9622
clean:
	make -C $(KDIR) M=$(PWD) CROSS_COMPILE=$(CROSS) clean
