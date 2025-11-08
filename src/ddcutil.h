#ifndef DDCUTIL_H
#define DDCUTIL_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <ddcutil_c_api.h>

#define VCP_BRIGHTNESS 0x10

int get_brightness(DDCA_Display_Handle dh);
int set_brightness(DDCA_Display_Handle dh, int percent);

#ifdef __cplusplus
}
#endif

#endif // DDCUTIL_H

