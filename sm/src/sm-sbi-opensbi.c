#include <sbi/sbi_trap.h>
#include <sbi/sbi_error.h>
#include <sbi/sbi_tlb.h>
#include <sbi/sbi_ipi.h>
#include <sbi/sbi_string.h>
#include <sbi/riscv_locks.h>
#include <sbi/sbi_console.h>
#include <sbi/sbi_scratch.h>
#include <sbi/riscv_asm.h>
#include <sbi/sbi_ecall.h>
#include "sm-sbi-opensbi.h"
#include "pmp.h"
#include "sm-sbi.h"
#include "sm.h"
#include "cpu.h"

#define SM_DEBUG_PRINT 0

static int sbi_ecall_keystone_enclave_handler(unsigned long extid, unsigned long funcid,
                     const struct sbi_trap_regs *regs,
                     unsigned long *out_val,
                     struct sbi_trap_info *out_trap)
{
  uintptr_t retval;

  if (funcid <= FID_RANGE_DEPRECATED) { return SBI_ERR_SM_DEPRECATED; }
  else if (funcid <= FID_RANGE_HOST)
  {
    if (cpu_is_enclave_context())
      return SBI_ERR_SM_ENCLAVE_SBI_PROHIBITED;
  }
  else if (funcid <= FID_RANGE_ENCLAVE)
  {
    if (!cpu_is_enclave_context())
      return SBI_ERR_SM_ENCLAVE_SBI_PROHIBITED;
  }

  switch (funcid) {
    case SBI_SM_CREATE_ENCLAVE:
      #if SM_DEBUG_PRINT
      sbi_printf("D[SM] Create enclave (sm/sm-sbi-opensbi.c)\r\n");
      #endif
      retval = sbi_sm_create_enclave(out_val, regs->a0);
      break;
    case SBI_SM_DESTROY_ENCLAVE:
      #if SM_DEBUG_PRINT
      sbi_printf("D[SM] Destroy enclave (sm/sm-sbi-opensbi.c)\r\n");
      #endif
      retval = sbi_sm_destroy_enclave(regs->a0);
      break;
    case SBI_SM_RUN_ENCLAVE:
      #if SM_DEBUG_PRINT
      sbi_printf("D[SM] Run enclave (sm/sm-sbi-opensbi.c)\r\n");
      #endif
      retval = sbi_sm_run_enclave((struct sbi_trap_regs*) regs, regs->a0);
      __builtin_unreachable();
      break;
    case SBI_SM_RESUME_ENCLAVE:
      #if SM_DEBUG_PRINT
      sbi_printf("D[SM] Resume enclave (sm/sm-sbi-opensbi.c)\r\n");
      #endif
      retval = sbi_sm_resume_enclave((struct sbi_trap_regs*) regs, regs->a0);
      __builtin_unreachable();
      break;
    case SBI_SM_RANDOM:
      #if SM_DEBUG_PRINT
      sbi_printf("D[SM] Random (sm/sm-sbi-opensbi.c)\r\n");
      #endif
      *out_val = sbi_sm_random();
      retval = 0;
      break;
    case SBI_SM_ATTEST_ENCLAVE:
      #if SM_DEBUG_PRINT
      sbi_printf("D[SM] Attest enclave (sm/sm-sbi-opensbi.c)\r\n");
      #endif
      retval = sbi_sm_attest_enclave(regs->a0, regs->a1, regs->a2);
      break;
    case SBI_SM_GET_SEALING_KEY:
      #if SM_DEBUG_PRINT
      sbi_printf("D[SM] Get sealing key (sm/sm-sbi-opensbi.c)\r\n");
      #endif
      retval = sbi_sm_get_sealing_key(regs->a0, regs->a1, regs->a2);
      break;
    case SBI_SM_STOP_ENCLAVE:
      #if SM_DEBUG_PRINT
      sbi_printf("D[SM] Stop enclave (sm/sm-sbi-opensbi.c)\r\n");
      #endif
      retval = sbi_sm_stop_enclave((struct sbi_trap_regs*) regs, regs->a0);
      __builtin_unreachable();
      break;
    case SBI_SM_EXIT_ENCLAVE:
      #if SM_DEBUG_PRINT
      sbi_printf("D[SM] Exit enclave (sm/sm-sbi-opensbi.c)\r\n");
      #endif
      retval = sbi_sm_exit_enclave((struct sbi_trap_regs*) regs, regs->a0);
      __builtin_unreachable();
      break;
    case SBI_SM_CALL_PLUGIN:
      #if SM_DEBUG_PRINT
      sbi_printf("D[SM] Call plugin (sm/sm-sbi-opensbi.c)\r\n");
      #endif
      retval = sbi_sm_call_plugin(regs->a0, regs->a1, regs->a2, regs->a3);
      break;
    case SBI_SM_PRINT_STRING:
      retval = sbi_sm_print_string(regs->a0, regs->a1, regs->a2);
      break;
    default:
      retval = SBI_ERR_SM_NOT_IMPLEMENTED;
      break;
  }

  return retval;

}

struct sbi_ecall_extension ecall_keystone_enclave = {
  .extid_start = SBI_EXT_EXPERIMENTAL_KEYSTONE_ENCLAVE,
  .extid_end = SBI_EXT_EXPERIMENTAL_KEYSTONE_ENCLAVE,
  .handle = sbi_ecall_keystone_enclave_handler,
};
