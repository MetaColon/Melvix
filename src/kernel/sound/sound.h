#ifndef MELVIX_SOUND_H
#define MELVIX_SOUND_H

#include <stdint.h>

/**
 * Beep in specific frequency for amount of ticks
 * @param frequency The frequency of the beep
 * @param ticks The duration in ticks
 */
void beep(u32 frequency, u32 ticks);

#endif