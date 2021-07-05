#ifndef __NODE_EXTND_H__
#define __NODE_EXTND_H__

#include "node.h"

#include <stdbool.h>
#include <stdint.h>

uint64_t node_frequency(Node *n);

uint8_t node_symbol(Node *n);

Node *node_left(Node *n);

Node *node_right(Node *n);

#endif
