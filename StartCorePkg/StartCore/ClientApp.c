/** @file
  * Demo application to be run on a specified processor core (AP).
  *
  * This application may NOT call into or use
  * UEFI, PI, or other firmware functions or data; other than:
  *   - data specifically passed to the application by way of its parameter.
  *   - Library functions validated as being MP safe
  *   - Protocol member functions validated and specified as being MP safe
  *
  * An "Application" may be significantly larger than this sample, and may
  * consist of many supporting functions.  Think of the "Application" function
  * as if it were "main" in a normal application, except that it is for another processor.
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
#include <Pi/PiDxeCis.h>
#include <Library/BaseLib.h>      // BaseLib is MP safe
#include <Library/UefiLib.h>  // Needed for Print()
#include <Library/TimerLib.h>
#include <Protocol/MpService.h>
#include <Protocol/FrameworkMpService.h>

#include "StartCore.h"
#include "Utility.h"

/** Entry point function for the AP portion of the StartCore Application.
  *
  * This is the portion of the StartCore application that runs on one of the
  * Application Processors (APs).  It is extremely simple so that it is easier
  * to see what is happening.
  *
  * @param[in]  parameter Pointer to the TCB for this task.
  *
**/
VOID
EFIAPI
ClientTask (IN VOID* parameter)
{
  TCB *Tcb = (TCB*)parameter;         // Convert "parameter" to the correct type
  MP_SERVICE_UTILITIES *MpService;

  MpService = (VOID*)Tcb->MpService;

  MpService->WhoAmI (MpService, Tcb);

  // Count from 1 to LoopCount
  do {
    CpuPause ();
  } while(Tcb->Delay);       // Do our work LoopCount times
  // We have now done all of our work and could exit right now.

  // Send one more result so we can catch off-by-one errors in the Root Task
  Tcb->Ready = 1;              // This should be ignored

  // When the ClientTask exits, the firmware's MP infrastructure will mark
  // this processor as IDLE and place it in a quiescent state so that it can
  // be used again at a later time.
}
