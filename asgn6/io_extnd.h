#ifndef __IO_EXTND_H__
#define __IO_EXTND_H__

#include "code.h"
#include "header.h"

#include <stdbool.h>
#include <stdint.h>

int write_header(int outfile, Header *h);

int read_header(int infile, Header *h);

#endif
