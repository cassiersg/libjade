#ifndef JADE_HASH_sha3_256_armv7m_ref_API_H
#define JADE_HASH_sha3_256_armv7m_ref_API_H

#define JADE_HASH_sha3_256_armv7m_ref_BYTES 32

#define JADE_HASH_sha3_256_armv7m_ref_ALGNAME "SHA3-256"
#define JADE_HASH_sha3_256_armv7m_ref_ARCH    "armv7m"
#define JADE_HASH_sha3_256_armv7m_ref_IMPL    "ref"

#include <stdint.h>

int jade_hash_sha3_256_armv7m_ref(
 uint8_t *hash,
 const uint8_t *input,
 uint32_t input_length
);

#endif