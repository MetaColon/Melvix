#include <fs/fs.h>
#include <stdint.h>

u32 sys_read(char *path, u32 offset, u32 count, u8 *buf)
{
	return read(path, offset, count, buf);
}