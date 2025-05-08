obj-m += deadlock_test.o

all:
	make -C /lib/modules/6.1.135/build M=$(PWD) modules

clean:
	make -C /lib/modules/6.1.135/build M=$(PWD) clean

