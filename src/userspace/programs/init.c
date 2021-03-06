#include <common.h>
#include <gui.h>
#include <stdio.h>
#include <stdlib.h>
#include <syscall.h>
#include <unistd.h>

u32 cpu_flags()
{
	u32 flags;
	asm volatile("pushf\n"
		     "pop %0\n"
		     : "=rm"(flags)::"memory");
	return flags;
}

int interrupts_enabled()
{
	return (cpu_flags() & 0x200) == 0x200;
}

void main()
{
	while (1) {
	};
	if (get_pid() != 1) {
		printf("Wrong PID!\n");
		exit(1);
	}

	if (interrupts_enabled())
		printf("INTs enabled :)\n");
	else
		printf("INTs disabled :(\n");

	// TODO: Fix page fault when mallocing
	printf("Initializing userspace... %d\n", 42);

	// TODO: Fix scheduler turning off after spawn
	spawn("/bin/sh");

	printf("Looping in init\n");
	while (1) {
		//printf("B");
	};
}