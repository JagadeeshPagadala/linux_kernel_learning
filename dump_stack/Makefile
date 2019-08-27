obj-m += dmp_stk.o
#compile step
all:
	$(MAKE) -C /lib/modules/`uname -r`/build/ M=$(PWD) modules

#clean step
clean:
	$(MAKE) -C /lib/modules/`uname -r`/build/ M=$(PWD) modules clean
