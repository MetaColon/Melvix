#ifndef MELVIX_SYSTEM_H
#define MELVIX_SYSTEM_H

#include <multiboot.h>
#include <stddef.h>
#include <stdint.h>

// Passed by low level things
u32 multiboot_address;
extern u32 text_start;
extern u32 data_start;
extern u32 bss_start;
extern u32 kernel_end;

/**
 * The ASM registers as packed structure
 */
typedef struct __attribute__((packed)) {
	u16 di, si, bp, sp, bx, dx, cx, ax;
	u16 gs, fs, es, ds, eflags;
} regs16_t;

/**
 * Execute BIOS interrupts by switching to real mode
 * @param intnum The interrupt number (e.g. 0x10)
 * @param regs The ASM registers
 */
extern void int32(u8 intnum, regs16_t *regs);

// Filename macro
#define __FILENAME__                                                                               \
	(__builtin_strrchr(__FILE__, '/') ? __builtin_strrchr(__FILE__, '/') + 1 : __FILE__)

/**
 * Display a general log message
 * @param fmt The message
 */
void _debug(const char *f, const char *fmt, ...);
#define debug(fmt, ...) _debug(__func__, fmt, ##__VA_ARGS__)

/**
 * Display an information message
 * @param fmt The information
 */
void _info(const char *f, const char *fmt, ...);
#define info(fmt, ...) _info(__func__, fmt, ##__VA_ARGS__)

/**
 * Display a warning message
 * @param fmt The warning cause/reason
 */
void _warn(const char *f, const char *fmt, ...);
#define warn(fmt, ...) _warn(__func__, fmt, ##__VA_ARGS__)

/**
 * Log into serial console
 * @param fmt The log message
 */
void _log(const char *f, const char *fmt, ...);
#define log(fmt, ...) _log(__func__, fmt, ##__VA_ARGS__)

/**
 * Halt the entire system and display a message
 * @param msg The error cause/reason
 */
void _panic(const char *f, const char *msg);
#define panic(msg) _panic(__func__, msg)

/**
 * Assert that a value is non-zero, else panic
 * @param x The value
 */
void _assert(const char *file, int line, const char *func, const char *exp);
#define assert(exp) (exp) ? 0 : _assert(__FILENAME__, __LINE__, __func__, #exp)

/**
 * Creates an infinite halt loop
 */
void halt_loop();

/**
 * Executes int32 with paging disable/enable
 * @param code The interrupt code
 * @param regs The registers
 */
void v86(u8 code, regs16_t *regs);

// Colors
#define RED "\x1B[31m"
#define GRN "\x1B[32m"
#define YEL "\x1B[33m"
#define BLU "\x1B[34m"
#define MAG "\x1B[35m"
#define CYN "\x1B[36m"
#define WHT "\x1B[37m"
#define RES "\x1B[0m"

#endif