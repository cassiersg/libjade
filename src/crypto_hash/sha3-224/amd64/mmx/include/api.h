#ifndef JADE_HASH_SHA3_224_AMD64_MMX_API_H
#define JADE_HASH_SHA3_224_AMD64_MMX_API_H

#define JADE_HASH_SHA3_224_AMD64_MMX_BYTES 28
#define JADE_HASH_SHA3_224_AMD64_MMX_ALGNAME "SHA3-224"

#include <stdint.h>

int jade_hash_sha3_224_amd64_mmx(
 uint8_t *out,
 uint8_t *in,
 uint64_t length
);

#endif