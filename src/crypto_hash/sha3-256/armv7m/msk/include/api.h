#ifndef JADE_HASH_sha3_256_armv7m_msk_API_H
#define JADE_HASH_sha3_256_armv7m_msk_API_H

#define JADE_HASH_sha3_256_armv7m_msk_BYTES 32

#define JADE_HASH_sha3_256_armv7m_msk_ALGNAME "SHA3-256"
#define JADE_HASH_sha3_256_armv7m_msk_ARCH    "armv7m"
#define JADE_HASH_sha3_256_armv7m_msk_IMPL    "msk"

#include <stdint.h>

int jade_hash_sha3_256_armv7m_msk(
 uint8_t *hash,
 const uint8_t *input,
 uint32_t input_length
);

#endif
