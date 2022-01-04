# Readme of Question 2 

To seen the difference between the two kernel we first need to make a copy of the kernel in which we will make all change.

#### We will write the new system call in the following path :
* arch/x86_64/entry/syscalls/syscall_64.tbl 

as this is the table which is used by the kernel to make the system call and we will use this table to make the system call.

#### After this we will define the new system call in the following path :
* kernel/sys.c

as this is the file which defines the system call and we will use this file to make the system call.This definition will simultaneously when the kernel compiles.

#### Definition of System call
* we will pass double pointer in this system call and then create a new array of void type with rows and coulumns same as in that array which is passes as argument.

* then as defined in the question we will use __copy_to_user() and __copy_from_user() system call which will copy data from user space into the kernal space and then again perform vice versa operation i.e from kernel space to user space.

* then we will return the copied array.

After this we will need a `.c` program to test our added system call.

#### Working of `.c` code

* Allocate a 2-D space in the memory using malloc of a particular size i.e fixed rows and columns.

* then filling random values into that 2-D array 
* making another double pointer in which the original memory space is to be copied.
* then we will call syscall() we have made to performing the copy action.

After we have all done, we will compile kernel by using the following commands:
* make
* sudo make modules_install
* sudo cp  arch/x86_64/boot/bzImage /boot/vmlinuz-linux-5.14.21
* sudo cp System.map System.map-5.14.21
* sudo mkinitcpio -k 5.14.21 -g /boot/initramfs-linux-5.14.21.img
* sudo grub-mkconfig -o /boot/grub/grub.cfg
* sudo reboot

Now we have our original kernal and modified kernel and we have that functionality acheived in our modified kernel.

#### Now next task we have been assigned is to find the difference between the two kernel and make a `.patch` file from the modified kernel.

To perfom the above tasks we will follow the following commands:
* sudo diff -rupN path-to-original-kernel/ path-to-modified-kernel/ > kernpatch.patch 

* sudo diff path-to-original-kernelfile/ path-to-modified-kernelfile/ > diff.txt