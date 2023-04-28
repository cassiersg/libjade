#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <inttypes.h>

#include "randombytes.h"
#include "api.h"

#include "jade_scalarmult.h"
#include "print.h"

/*
int jade_scalarmult(
 uint8_t *q,
 const uint8_t *n,
 const uint8_t *p
);

int jade_scalarmult_base(
 uint8_t *q,
 const uint8_t *n
);
*/

int main(void)
{
  int r;
  uint8_t public_key_a[JADE_SCALARMULT_BYTES];
  uint8_t public_key_b[JADE_SCALARMULT_BYTES];

  uint8_t _secret_key_a[JADE_SCALARMULT_SCALARBYTES];
  uint8_t _secret_key_b[JADE_SCALARMULT_SCALARBYTES];
  uint8_t* secret_key_a = _secret_key_a;
  uint8_t* secret_key_b = _secret_key_b;

  uint8_t secret_a[JADE_SCALARMULT_BYTES];
  uint8_t secret_b[JADE_SCALARMULT_BYTES];

  //
  secret_key_a = __jasmin_syscall_randombytes__(secret_key_a, JADE_SCALARMULT_SCALARBYTES);
  secret_key_b = __jasmin_syscall_randombytes__(secret_key_b, JADE_SCALARMULT_SCALARBYTES);

  //
  r = jade_scalarmult_base(public_key_a, secret_key_a);
    assert(r == 0);
  r = jade_scalarmult_base(public_key_b, secret_key_b);
    assert(r == 0);

  //
  r = jade_scalarmult(secret_a, secret_key_a, public_key_b);
    assert(r == 0);
  r = jade_scalarmult(secret_b, secret_key_b, public_key_a);
    assert(r == 0);
    assert(memcmp(secret_a, secret_b, JADE_SCALARMULT_BYTES) == 0);

  print_info(JADE_SCALARMULT_ALGNAME, JADE_SCALARMULT_ARCH, JADE_SCALARMULT_IMPL);
  print_str_u8("secret_key_a", secret_key_a, JADE_SCALARMULT_SCALARBYTES);
  print_str_u8("public_key_a", public_key_a, JADE_SCALARMULT_BYTES);
  print_str_u8("secret_a",     secret_a,     JADE_SCALARMULT_BYTES);
  print_str_u8("secret_key_b", secret_key_b, JADE_SCALARMULT_SCALARBYTES);
  print_str_u8("public_key_b", public_key_b, JADE_SCALARMULT_BYTES);
  print_str_u8("secret_b",     secret_b,     JADE_SCALARMULT_BYTES);

  return 0;
}

