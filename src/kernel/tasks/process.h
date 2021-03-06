#ifndef MELVIX_PROCESS_H
#define MELVIX_PROCESS_H

#include <interrupts/interrupts.h>
#include <memory/paging.h>
#include <stdint.h>

struct mmap {
	u32 text;
	u32 bss;
	u32 data;
	u32 stack;
};

struct process {
	u32 cr3;
	struct regs regs;

	u32 pid;
	char name[256];

	int state;

	u32 brk;
	u32 handlers[6];

	struct process *parent;
	struct process *next;
};

void scheduler(struct regs *regs);
void process_force_switch();

u32 process_spawn(struct process *process);
void process_suspend(u32 pid);
void process_wake(u32 pid);

struct process *process_from_pid(u32 pid);

void process_init(struct process *proc);

struct process *process_make_new();

u32 kexec(char *path);

u32 uexec(char *path);
u32 uspawn(char *path);

extern struct process *current_proc;

extern u32 stack_hold;

#define PID_NOT_FOUND ((struct process *)0xFFFFFFFF)

#define PROC_RUNNING 0
#define PROC_ASLEEP 1

#define PROC_THREAD 0
#define PROC_PROC 1
#define PROC_ROOT 2

#define WAIT_ERROR (-1)
#define WAIT_OKAY 0

#endif