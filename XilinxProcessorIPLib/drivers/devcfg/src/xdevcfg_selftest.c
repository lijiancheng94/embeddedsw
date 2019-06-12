/******************************************************************************
*
* Copyright (C) 2010 - 2015 Xilinx, Inc.  All rights reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMANGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
*
* 
*
******************************************************************************/
/****************************************************************************/
/**
*
* @file xdevcfg_selftest.c
* @addtogroup devcfg_v3_5
* @{
*
* Contains diagnostic self-test functions for the XDcfg driver.
*
* <pre>
* MODIFICATION HISTORY:
*
* Ver   Who Date     Changes
* ----- --- -------- ---------------------------------------------
* 1.00a hvm 02/07/11 First release
* 2.02a nm  02/27/13 Fixed CR# 701348.
*                    Peripheral test fails with  Running
* 		     DcfgSelfTestExample() in SECURE bootmode.
* </pre>
*
******************************************************************************/

/***************************** Include Files *********************************/

#include "xdevcfg.h"

/************************** Constant Definitions *****************************/

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/

/************************** Function Prototypes ******************************/

/************************** Variable Definitions *****************************/

/****************************************************************************/
/**
*
* Run a self-test on the Device Configuration Interface. This test does a
* control register write and reads back the same value.
*
* @param	InstancePtr is a pointer to the XDcfg instance.
*
* @return
*		- XST_SUCCESS if self-test was successful.
*		- XST_FAILURE if fails.
*
* @note		None.
*
******************************************************************************/
int XDcfg_SelfTest(XDcfg *InstancePtr)
{
	u32 OldCfgReg;
	u32 CfgReg;
	int Status = XST_SUCCESS;

	/*
	 * Assert to ensure the inputs are valid and the instance has been
	 * initialized.
	 */
	Xil_AssertNonvoid(InstancePtr != NULL);
	Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

	OldCfgReg = XDcfg_GetControlRegister(InstancePtr);

	XDcfg_SetControlRegister(InstancePtr, XDCFG_CTRL_NIDEN_MASK);

	CfgReg = XDcfg_GetControlRegister(InstancePtr);

	if ((CfgReg & XDCFG_CTRL_NIDEN_MASK) != XDCFG_CTRL_NIDEN_MASK) {

		Status = XST_FAILURE;
	}

	/*
	 * Restore the original values of the register
	 */
	XDcfg_SetControlRegister(InstancePtr, OldCfgReg);

	return Status;
}
/** @} */
