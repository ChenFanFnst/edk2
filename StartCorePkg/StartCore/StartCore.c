/** @file
  * Implementation of the main function and some support functions for the StartCore application.
  *
  * ShellAppMain() is the entry point for the StartCore application and is the
  * only public function in this file.
  *
  * Copyright (c) 2009 - 2010, Intel Corporation. All rights reserved.<BR>
  * This program and the accompanying materials are licensed and made available
  * under the terms and conditions of the BSD License which accompanies this
  * distribution.  The full text of the license may be found at
  *   http://opensource.org/licenses/bsd-license.php.
  *
  * THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  * WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
  *
**/

#include <Pi/PiDxeCis.h>
#include <Library/UefiLib.h>  // Needed for Print()
#include <Library/MemoryAllocationLib.h>
#include <Library/ShellCEntryLib.h>

#include "StartCore.h"
#include "Utility.h"

/* ############################################################################
###                                                                         ###
###                Private Function and Data Definitions                    ###
###                                                                         ###
############################################################################ */

/** Pointer to the Task Status and Control structure for the target processor.
  * For this demo application it only allows a single task on a single processor core,
  * there is no need for anything more complex.
  *
  * For applications using multiple APs, "Tcb" could be an array of TCB structures,
  * one for each logical processor in the platform.
**/
STATIC TCB *mTcb = NULL;

#define DO_TEST_STARTAP(MpServiceArg, TcbArg)             \
  do {                                                    \
    Status = StartAP (MpServiceArg, TcbArg);              \
  } while (FALSE)

#define DO_TEST_STARTALLAPS(MpServiceArg, TcbArg)         \
  do {                                                    \
    Status = StartAllAPs (MpServiceArg, TcbArg);          \
  } while (FALSE)

#define DO_TEST_GETMPINFO(MpServiceArg, NumArg, TcbArg)   \
  do {                                                    \
    Status = GetMpInfo (MpServiceArg, NumArg, TcbArg);    \
  } while (FALSE)

#define DO_TEST_ENABLEDISABLEAP(MpServiceArg, TcbArg)     \
  do {                                                    \
    Status = EnableDisableAP (MpServiceArg, TcbArg);      \
  } while (FALSE)


/* ############################################################################
###                                                                         ###
###                     Public Function Definitions                         ###
###                                                                         ###
############################################################################ */

/** Main entry point to StartCore.

  Load and run an application on a specified core.

  @param[in]  Argc   Number of arguments in Argv.
  @param[in]  Argv   Array of pointers to the tokenized command line arguments.

  @retval  0         The application exited normally.
  @retval  NonZero   An error occurred.

**/
INTN
EFIAPI
ShellAppMain (
  IN UINTN    Argc,
  IN CHAR16 **Argv
  )
{
  MP_SERVICE_UTILITIES       *MpService;  // Mp Service Utilities pointer
  UINTN                       NumProc;    // Number of logical CPUs in the system
  UINTN                       NumEnabled; // Number of enabled logical CPUs in the system
  UINTN                       Number;
  EFI_STATUS                  Status;

  /* The do-while loop is used as a poor-man's exception handling capability.
     The 'do-while' block can be viewed as a 'try' block.
     This allows the 'break' statement within the compound block to function as a
     primitive 'throw' -- The enclosing 'try' block is exited.
  */
  do
  {
    Status = UtilityConstructor();   // Create an instance of the Data for the MP Utilities
    if(EFI_ERROR (Status)) {
      Print(L"Failure allocating space for Utility Data: %r\n", Status);
      break;
    }

    // Create an instance of the Task Control Block and initialize it to ZERO
    mTcb = (TCB*)AllocateZeroPool( sizeof(TCB));
    if( mTcb == NULL) {
      Status = EFI_OUT_OF_RESOURCES;
      Print(L"Failure allocating space for the Task Control Block: %r\n", Status);
      break;
    }

    // locate Mp Protocol
    Status = LocateMpProtocol (&MpService, &NumProc, &NumEnabled);
    if (EFI_ERROR (Status)) break;

    mTcb->MpService = (VOID*) MpService;

    // WhoAmI ()
    Print(L"===================================\n");
    Print(L"Testing : WhoAmI\n");
    Print(L"===================================\n");
    for (Number = 0; Number < NumProc; Number++) {
      {
        mTcb->ProcNum = Number;
        mTcb->Blocked = TRUE;
        mTcb->Timeout = TRUE;
        mTcb->Delay = FALSE;
      }
      DO_TEST_STARTAP (MpService, mTcb);
      Print(L"  expected: %d, Result: %d\n", Number, mTcb->ExpectNum);
    }

    // GetProcessorInfo()
    for (Number = 0; Number < NumProc; Number++) {
      DO_TEST_GETMPINFO(MpService, Number, mTcb);
    }

    //
    // StartupThisAP ()
    //
    // Test Blocked status + timeout infinity.
    Print(L"===================================\n");
    Print(L"Testing StartupThisAP.\n");
    Print(L"===================================\n");
    Print(L"Testing 1: Block + AP reset after timeout\n");
    Print(L"  expected: Time out\n");
    {
      mTcb->ProcNum = 1;  // Processor 1
      mTcb->Blocked = TRUE;
      mTcb->Timeout = TRUE;
      mTcb->Delay = TRUE;
    }
    DO_TEST_STARTAP (MpService, mTcb);

    Print(L"Testing 2: Block + AP return before timeout\n");
    Print(L"  expected: Success\n");
    {
      mTcb->ProcNum = 2;  // Processor 2
      mTcb->Blocked = TRUE;
      mTcb->Timeout = TRUE;
      mTcb->Delay = FALSE;
    }
    DO_TEST_STARTAP (MpService, mTcb);

    // Test not Blocked status + timeout infinity.
    // Test not Blocked status + AP reset after timeout
    Print(L"Testing 3: non-Block + AP reset after timeout\n");
    Print(L"  expected: Time out\n");
    {
      mTcb->ProcNum = 1;
      mTcb->Blocked = FALSE;
      mTcb->Timeout = TRUE;
      mTcb->Delay = TRUE;
    }
    DO_TEST_STARTAP (MpService, mTcb);

    // Test not Blocked Status + AP return before timeout
    Print(L"Testing 4: non-Block + AP return before timeout\n");
    Print(L"  expected: Success\n");
    {
      mTcb->ProcNum = 2;
      mTcb->Blocked = FALSE;
      mTcb->Timeout = TRUE;
      mTcb->Delay = FALSE;
    }
    DO_TEST_STARTAP (MpService, mTcb);

    Print(L"Testing 5: ProcNum > maxcpu \n");
    Print(L"  expected: not found\n");
    {
      mTcb->ProcNum = NumProc;
      mTcb->Blocked = FALSE;
      mTcb->Timeout = TRUE;
      mTcb->Delay = FALSE;
    }
    DO_TEST_STARTAP (MpService, mTcb);

    //
    // StartupAllAPs ()
    //
    // Test Blocked status + timeout infinity.
    // Test Blocked status + APs reset after timeout
    Print(L"=======================================\n");
    Print(L"Testing StartupAllAPs.\n");
    Print(L"=======================================\n");
    Print(L"Testing 1: Block + APs reset after timeout\n");
    Print(L"  expected: Time out\n");
    {
      mTcb->SingleThread = FALSE;
      mTcb->Blocked = TRUE;
      mTcb->Timeout = TRUE;
      mTcb->Delay = TRUE;
    }
    DO_TEST_STARTALLAPS (MpService, mTcb);
    // SingleThread True
    {
      mTcb->SingleThread = TRUE;
      mTcb->Blocked = TRUE;
      mTcb->Timeout = TRUE;
      mTcb->Delay = TRUE;
    }
    DO_TEST_STARTALLAPS (MpService, mTcb);

    // Test Blocked Status + APs return before timeout
    Print(L"Testing 2: Block + APs return before timeout\n");
    Print(L"  expected: Success\n");
    {
      mTcb->SingleThread = FALSE;
      mTcb->Blocked = TRUE;
      mTcb->Timeout = TRUE;
      mTcb->Delay = FALSE;
    }
    DO_TEST_STARTALLAPS (MpService, mTcb);
    // SingleThread True
    {
      mTcb->SingleThread = TRUE;
      mTcb->Blocked = TRUE;
      mTcb->Timeout = TRUE;
      mTcb->Delay = FALSE;
    }
    DO_TEST_STARTALLAPS (MpService, mTcb);

    // Test not Blocked status + timeout infinity.
    // Test not Blocked status + APs reset excessed timeout
    Print(L"Testing 3: non-Block + APs reset after timeout\n");
    Print(L"  expected: Time out\n");
    {
      mTcb->SingleThread = FALSE;
      mTcb->Blocked = FALSE;
      mTcb->Timeout = TRUE;
      mTcb->Delay = TRUE;
    }
    DO_TEST_STARTALLAPS (MpService, mTcb);
    // SingleThread TRUE
    {
      mTcb->SingleThread = TRUE;
      mTcb->Blocked = FALSE;
      mTcb->Timeout = TRUE;
      mTcb->Delay = TRUE;
    }
    DO_TEST_STARTALLAPS (MpService, mTcb);

    Print(L"Testing 4: non-Block + APs return before timeout\n");
    Print(L"  expected: Success\n");
    {
      mTcb->SingleThread = FALSE;
      mTcb->Blocked = FALSE;
      mTcb->Timeout = TRUE;
      mTcb->Delay = FALSE;
    }
    DO_TEST_STARTALLAPS (MpService, mTcb);
    // SingleThread TRUE
    {
      mTcb->SingleThread = TRUE;
      mTcb->Blocked = FALSE;
      mTcb->Timeout = TRUE;
      mTcb->Delay = FALSE;
    }
    DO_TEST_STARTALLAPS (MpService, mTcb);

    //
    // EnableDisableAP
    //
    Print(L"===================================\n");
    Print(L"Testing EnableDisableAP\n");
    Print(L"===================================\n");
    Print(L"Testing 1: Disable BSP\n");
    Print(L"  expected: invalid parameter\n");
    {
      mTcb->ProcNum = 0;
      mTcb->Enabled = FALSE;
    }
    DO_TEST_ENABLEDISABLEAP (MpService, mTcb);
    Print(L"Testing 2: ProcNum > maxNum\n");
    Print(L"  expected: not found\n");
    {
      mTcb->ProcNum = NumProc;
      mTcb->Enabled = FALSE;
    }
    DO_TEST_ENABLEDISABLEAP (MpService, mTcb);

    Print(L"Testing 3: Disable AP 1\n");
    Print(L"  expected: success\n");
    {
      mTcb->ProcNum = 1;
      mTcb->Enabled = FALSE;
    }
    DO_TEST_ENABLEDISABLEAP (MpService, mTcb);
    {
      mTcb->ProcNum = 1;
      mTcb->Blocked = FALSE;
      mTcb->Timeout = FALSE;
      mTcb->Delay = FALSE;
    }
    DO_TEST_STARTAP (MpService, mTcb);
    {
      mTcb->ProcNum = 1;
      mTcb->Enabled = TRUE;
    }
    DO_TEST_ENABLEDISABLEAP (MpService, mTcb);

    Print(L"Tests end\n");

    FreePool( mTcb);        // Free the Task Control Block
    UtilityDestructor();    // Free any dynamic resources the Utility Functions consumed

  } while( FALSE );   // Guarantee we only execute the code once.

  return Status;
}
