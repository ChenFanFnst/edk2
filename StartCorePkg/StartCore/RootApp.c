/*++ @file
  * Routine for interacting with the Demo application.
  *
  * This is the routine for interacting with the Demo application and
  * verifying that its behavior is as expected.
  *
  * The accompaning file, ClientApp1.c, contains the application, ClientTask(), which is to
  * be run on the target processor.
  *
  * Copyright (c) 2009 - 2013, Intel Corporation. All rights reserved.<BR>
  * This program and the accompanying materials are licensed and made available
  * under the terms and conditions of the BSD License which accompanies this
  * distribution.  The full text of the license may be found at
  *   http://opensource.org/licenses/bsd-license.php.
  *
  * THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  * WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
  *
--*/
#include <Library/UefiLib.h>
#include "StartCore.h"

/** Wait for the client to signal that data is available.
    A non-zero value in Tcb->Ready indicates that data is available.

    @param[in]    Tcb     Pointer to the Task control structure

    @retval     0       The client did not respond in the alloted time.
    @retval     !0      Any non-zero value indicates data is ready.  The value
                        returned is the number of microseconds remaining in the
                        wait time allotment.
**/
INT32
WaitForClient( IN TCB *Tcb)
{
  INT32   waitLimit;

  waitLimit = 1000;   // This is how long I am willing to wait
  while( (Tcb->Ready == 0) && (waitLimit > 0)) {
    --waitLimit;
    CpuPause();   // From BaseLib, provides hint to CPU that we are in a spin-loop
  }
  if( waitLimit <= 0 ) {
    // Timeout waiting for Client to provide the next value
    Print(L"Client task did not respond in the expected time!\n");
  }
  return waitLimit;
}

/** Procedure that interacts with the Client task.
  *
  * @param[in]  Tcb   Pointer to the TCB for the Client task.
  *
**/
VOID
EFIAPI
RootTask( IN TCB *Tcb)
{
  INTN  count;

  Print(L" #   Cpu# Max# Data Gate\n");
  Print(L"---: ---- ---- ---- ----\n");
  // The first line of data printed should be:  "-1: 1 100 0 1" if ProcNum=1 and NUMLOOPS=100

  // Retrieve and Display NUMLOOPS values from the Client Task
  for(count = NUMLOOPS; count > 0; --count) {
    // Wait until the ClientTask signals data is ready, or I time out
    if( WaitForClient(Tcb) != 0 ) {
      // Display what we received from the Client
      Print(L"%3d: %4d %4d %4d %4d\n", (INT32)NUMLOOPS-count,
                                       (UINT32)Tcb->ProcNum, (UINT32)Tcb->MaxCount,
                                       Tcb->Result, Tcb->Ready);
      Tcb->Ready = 0;           // Tell the Client Task she can run
    }
  }
  // Give the ClientTask a chance to signal she is done.
  (void)WaitForClient(Tcb);

  // Print the final state of the Tcb.
  Print(L"END: %4d %4d %4d %4d\n", (UINT32)Tcb->ProcNum, (UINT32)Tcb->MaxCount, Tcb->Result, Tcb->Ready);
}
