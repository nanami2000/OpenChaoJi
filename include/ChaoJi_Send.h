/*
 *  Copyright (c) 2022 OpenChaoJi Org
 *
 *  Use of this source code is governed by an MIT-style
 *  license that can be found in the LICENSE file or at
 *  https://opensource.org/licenses/MIT.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy of
 *  this software and associated documentation files (the "Software"), to deal in
 *  the Software without restriction, including without limitation the rights to
 *  use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 *  the Software, and to permit persons to whom the Software is furnished to do so,
 *  subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all
 *  copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 *  FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 *  COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 *  IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 *  CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 *
 */

/*after Reliable Message send all procedure is done call back to notify application layer*/
void ChaoJi_RM_Send_Notify(struct ChaoJi_RM_Mcb *Msgcb)

/*after unreliable Reliable Message send all procedure is done call back to notify application layer*/
void ChaoJi_URM_Send_Notify(struct ChaoJi_URM_Mcb *Msgcb)

/*reliable message send, Deal with application data buffer and request Msgcb according to data buffer length then call ChaoJi_RM_SendProcess*/
err_Cj ChaoJi_RM_write(struct ChaoJi_RM_Mcb *Msgcb, u8* data, u32 length, err_Cj err)

/*unreliable message send, Deal with application data buffer and request Msgcb according to data buffer then call ChaoJi_Output*/
err_Cj ChaoJi_URSM_write(struct ChaoJi_Urm_Mcb *Msgcb, u8* data, u32 length, struct Can_Pdu *pdu)

/* relaible message send state machine, connection established, sending data, pause, ending states transient, after execute finished call back 
 ChaoJi_RM_Send_Notify to notify application layer;
 Periodic call ChaoJi_RM_TxProcess(lm_Msgcb)、ChaoJi_RM_TxProcess(rsm_Msgcb)
 call back by RSM ACK, LM ACK, NACK to update the Cj_state*/
Cj_state ChaoJi_RM_SendProcess(struct ChaoJi_RM_Mcb *Msgcb, struct Can_Pdu *pdu)

/*Deal with data link layer to make real traffic by using CAN PDU
usage:
After ChaoJi_URSM_write, ChaoJi_RM_TxProcess
or
rferenced by receiv procedure*/
err_Cj ChaoJi_Output(struct Can_Pdu *pdu)


/*Polling method to get the sending procedure status for application layer
  return Cj_state*/
Cj_state ChaoJi_RM_GetSendState(struct ChaoJi_RM_Mcb *Msgcb)


/*some example for how to use send*/
void example()
{
	//-----------------Init--------------------------------------------------
	struct ChaoJi_RM_Mcb lm_Mcb = *ChaoJi_RM_new(void);
	//...
	struct ChaoJi_RM_Mcb rsm_Mcb = *ChaoJi_RM_new(void);
	//...
	struct ChaoJi_URSM_Mcb ursm_Mcb = *ChaoJi_URSM_new(void);
	//...

	//发送
	u8_t data1[] = {1, 2, 3, 4, 5,6,7,8,9};
	ChaoJi_RM_write(lm_Mcb,data1, sizeof(data1),);
	ChaoJi_RM_TxProcess(lm_Mcb, pdu);
	ChaoJi_Output(pdu);
	
	u8_t data2[] = {1, 2, 3, 4, 5};
	ChaoJi_RM_write(rsm_Mcb,data2, sizeof(data2),);
	ChaoJi_RM_TxProcess(rsm_Mcb, pdu);
	ChaoJi_Output(pdu);
	
	u8_t data3[] = {1, 2, 3, 4, 5,6,7};
	ChaoJi_URSM_write(ursm_Mcb, data3, sizeof(data3), pdu);
	ChaoJi_Output(pdu);
}

	
