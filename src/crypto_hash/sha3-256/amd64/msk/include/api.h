#ifndef JADE_HASH_sha3_256_amd64_msk_API_H
#define JADE_HASH_sha3_256_amd64_msk_API_H

#define JADE_HASH_sha3_256_amd64_msk_BYTES 32

#define JADE_HASH_sha3_256_amd64_msk_ALGNAME "SHA3-256"
#define JADE_HASH_sha3_256_amd64_msk_ARCH    "amd64"
#define JADE_HASH_sha3_256_amd64_msk_IMPL    "msk"

#include <stdint.h>

int jade_hash_sha3_256_amd64_msk(
 uint8_t *hash,
 const uint8_t *input,
 uint64_t input_length
);

#endif
