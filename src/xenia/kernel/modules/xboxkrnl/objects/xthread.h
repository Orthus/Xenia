/**
 ******************************************************************************
 * Xenia : Xbox 360 Emulator Research Project                                 *
 ******************************************************************************
 * Copyright 2013 Ben Vanik. All rights reserved.                             *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 */

#ifndef XENIA_KERNEL_MODULES_XBOXKRNL_XTHREAD_H_
#define XENIA_KERNEL_MODULES_XBOXKRNL_XTHREAD_H_

#include <xenia/kernel/modules/xboxkrnl/xobject.h>

#include <xenia/kernel/xbox.h>


namespace xe {
namespace cpu {
class ThreadState;
}
}


namespace xe {
namespace kernel {
namespace xboxkrnl {


class XEvent;


class XThread : public XObject {
public:
  XThread(KernelState* kernel_state,
          uint32_t stack_size,
          uint32_t xapi_thread_startup,
          uint32_t start_address, uint32_t start_context,
          uint32_t creation_flags);
  virtual ~XThread();

  static uint32_t GetCurrentThreadId(const uint8_t* thread_state_block);

  uint32_t thread_id();
  uint32_t last_error();
  void set_last_error(uint32_t error_code);

  X_STATUS Create();
  X_STATUS Exit(int exit_code);

  void Execute();

  virtual X_STATUS Wait(uint32_t wait_reason, uint32_t processor_mode,
                        uint32_t alertable, uint64_t* opt_timeout);

private:
  X_STATUS PlatformCreate();
  void PlatformDestroy();
  X_STATUS PlatformExit(int exit_code);

  struct {
    uint32_t    stack_size;
    uint32_t    xapi_thread_startup;
    uint32_t    start_address;
    uint32_t    start_context;
    uint32_t    creation_flags;
  } creation_params_;

  uint32_t      thread_id_;
  void*         thread_handle_;
  uint32_t      tls_address_;
  uint32_t      thread_state_address_;
  cpu::ThreadState* thread_state_;

  XEvent*       event_;
};


}  // namespace xboxkrnl
}  // namespace kernel
}  // namespace xe


#endif  // XENIA_KERNEL_MODULES_XBOXKRNL_XTHREAD_H_
