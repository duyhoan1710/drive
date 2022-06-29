CC = gcc

obj-m := des_encrypt.o

KDIR := /lib/modules/`uname -r`/build

all:
	make -C $(KDIR) M=`pwd` modules

test: test.c
	${CC} -o test test.c

clean:
	make -C $(KDIR) M=`pwd` clean

install:
	sudo dmesg -C
	sudo insmod des_encrypt.ko

remove:
	sudo rmmod des_encrypt