#ifndef MELVIX_IO_H
#define MELVIX_IO_H

#include <stdint.h>

/**
 * Receive from specified hardware port
 * @param port The hardware port
 * @return The hardware response
 */
u8 inb(u16 port);

/**
 * Receive from specified hardware port
 * @param port The hardware port
 * @return The hardware response
 */
u16 inw(u16 port);

/**
 * Receive from specified hardware port
 * @param port The hardware port
 * @return The hardware response
 */
u32 inl(u16 port);

int interrupts_enabled();
void interrupts_print();
void cli();
void sti();
void hlt();

/**
 * Send data to the specified hardware port
 * @param port The hardware port
 * @param data The data that should be sent
 */
void outb(u16 port, u8 data);

/**
 * Send data to the specified hardware port
 * @param port The hardware port
 * @param data The data that should be sent
 */
void outw(u16 port, u16 data);

/**
 * Send data to the specified hardware port
 * @param port The hardware port
 * @param data The data that should be sent
 */
void outl(u16 port, u32 data);

u32 cr3_get();
void cr3_set(u32 cr3);
u32 cr0_get();
void cr0_set(u32 cr0);
void invlpg(u32 addr);

/**
 * Initialize the serial conenction
 */
void serial_install();

/**
 * Write a single char to the serial port (QEMU logging)
 * @param ch The char
 */
void serial_put(char ch);

// Spinlock
static inline void spinlock(int *ptr)
{
	int prev;
	do
		asm volatile("lock xchgl %0,%1" : "=a"(prev) : "m"(*ptr), "a"(1));
	while (prev);
}

#endif