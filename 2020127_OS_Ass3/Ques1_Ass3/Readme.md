## Readme for Operating System (CSE 231) Assignment 3 Question 1

### [**Shivansh Choudhary - 2020127**]

## Description
	In this question we have to change the linux scheduler.
	So for this we first go deep down into the file linux/include/linux/sched.h file which will be used to store new time.
	Then we have to change the scheduler in the file linux/sched/fair.c file. 
	This fair.c will be used to change the scheduler and in it we will increase the time i.e delta_exec. This delta_exec will automatically increase the vruntime and replace the current process with the next process.

	Then to add the system call we have to add the system call in the file linux/kernel/sys.c file.

	Then to initialize the new variable we go deep down to linux/kernel/sched/core.c.
	Then the task left is to add system call. This we will add in the syscall_64.tbl file which is located inside linux/arch/x86/entry/syscall64.
	Then the final task left is to compile the modified kernel. This is done as follows:
		1. cd to the directory where the kernel is present.
		2. sudo su
		3. make -j2 
		4. sudo make modules_install
		5. sudo cp  arch/x86_64/boot/bzImage /boot/vmlinuz-linux-5.15.8
		6. sudo cp System.map System.map-5.15.8
 		7. sudo mkinitcpio -k 5.15.8 -g /boot/initramfs-linux-5.15.8.img
		8. sudo grub-mkconfig -o /boot/grub/grub.cfg
		9. sudo reboot

## Test File 
	There is a test file which is present in the folder to test the scheduler.
	The file is named as test.c and inside it we have a fork() function which is used to create a child process.
	Both the child and parent process will be used to test the scheduler. One will be executed in less time and other will be executed in more time. The delay will be because of the change in the vruntime. The time for which a process will be flushed onto the output stream and that the is the time taken bu individual process to execute. The time is calculated using clock() function.


