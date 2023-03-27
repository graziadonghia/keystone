#include "my_string.h"

unsigned long
print_string(uintptr_t string, size_t len, uintptr_t retbuf){
  char string_copy[128];
  copy_to_sm(string_copy, string, len);
  sbi_printf("I'm the sm: \r\n");
  int ret = sbi_printf("%s\r\n", string_copy);
  ret--;
  copy_from_sm(retbuf, &ret, sizeof(int));
  return SBI_ERR_SM_ENCLAVE_SUCCESS;
}