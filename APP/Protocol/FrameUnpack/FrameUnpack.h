#ifndef __FRAMEUNPACK_H__
#define __FRAMEUNPACK_H__

#include "HeaderFiles.h"

#define FU_BUF_SIZE     160

void frame_parser_init(void);
void frame_parser_feed(uint8_t ch);
int frame_unpack_ready(void);
const char* frame_unpack_get(size_t *out_len);
void frame_unpack_clear(void);

#endif

