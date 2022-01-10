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

/*Error Code defination*/
typedef short err_Cj;
#define ERR_OK (0)
#define ERR_ERR (-1)

/*Message type defination*/
#define LM_TYPE (1)
#define RSM_TYPE (0)

/*ChaoJi communication states defination*/
enum Cj_Com_state{
	RSM_S0=0,
	RSM_S1,
	RSM_S2,
	LM_S0=10,
	LM_S1,
	LM_S2,
	URSM_S0=100,
	URSM_S1,
	URSM_S2	
};

/* Data structure of reliable Message*/  
struct ChaoJi_RM_Mcb
{
	enum Cj_Com_state cj_rm_com_state;
	u8 MsgType; //0: RSM_TYPE, 1: LM_TYPE
	u8 port;
	u8 pgi;
	u8 len;
	u8 *recv_buf;
	u16 tfs;			//total fram size: ACK's total frame size 
	u16 crt_seq;		//current sequence no: ACK's start sequence number included
	u16 rst_seq;		//request seq no 
	u8 *recved_flag;	//received flag: include all ACK, NACK and ANDACK, number of pending data frames and its initial sequence number
	u8 pause_flag;	//transfer pause 
	u8 trans_fin_flag;//transfer finish flag 
	err_Cj (* recv)(struct ChaoJi_RM_Mcb *rm_Mcb);// call back function to notify appliacation layer recv have been made
	u8* snd_buf;	//send the data buffer. 
    u32	snd_len;	//send the byte size of data	
    u32 snd_state;	//send states
	u32 snd_currSN; //send the current serial number	
	u32 snd_time_out; //send the timeout
	u32 snd_max_timer; //send the maxium timer round	
	err_Cj (* sent)(struct ChaoJi_RM_Mcb *rm_Mcb) // call back func to notify application layer
};

/* Data structure of unreliable Message*/  
struct ChaoJi_Urm_Mcb
{
	enum Cj_Com_state cj_urm_com_state;//connect(s0) data transfer(s1) wait ack(s2) wait end(s3) connection close(s4)
	u8 port;
	u8 pgi;
	u8 len;
	u8 *recv_buf;
	u16 tfs;			//total fram size 
	u16 crt_seq;		//current sequence no 
	u16 rst_seq;		//request seq no 
	u8 *recved_flag;	//received flag
	u8 pause_flag;	//transfer pause flag
	u8 trans_fin_flag;//transter finish flag 
	err_Cj (* recv)(struct ChaoJi_URM_Mcb *urm_Mcb);// call back function to notify application layer recv have been made
	u8* snd_buf;	//send procedure data buffer	
	u32	snd_len;	//send the byte size of data	
	u32 snd_state;	//Send the status	
	u32 snd_currSN; //send the current serial number
	u32 snd_time_out; //send the timeout
	u32 snd_max_timer; //send the maxium timer round	
	err_Cj (* sent)(struct ChaoJi_URM_Mcb *urm_Mcb) // call back func to notify application layer
};

//CAN ID
typedef union
{
	u32 u32Word;
	struct
	{
		u32 sa	 :8;//source address
		u32 ps	 :8;//Destination address
		u32 pf	 :8;//PDU type
		u32 dp	 :1;//Data Page
		u32 edp  :1;//expension data page
		u32 p 	 :3;//Priority
		u32 rev    :3;//Reserv
	}Bits;
}CanId_t;

//CAN PDU defination
struct Can_Pdu
{
	CanId_t    can_id;
    u8_t       can_dlc;
    u8_t       data[8];
};
