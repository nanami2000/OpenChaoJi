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


/*after Reliable Message connection have been made call back to notify application layer*/
void ChaoJi_RM_Connect_Notify(struct ChaoJi_RM_Mcb *Msgcb)

/*ChaoJi connection setup, initializ a ChaoJi RM Mcb structure, return address of Memory*/
struct ChaoJi_RM_Mcb *ChaoJi_RM_new(void)

/*Bind the connection(with LM and RSM) with local CAN port. If the CAN port is invalid, return error code*/
err_Cj ChaoJi_RM_bind(struct ChaoJi_RM_Mcb *Msgcb, u16 port)


/*The Client(EVSE Master) connects to the Server(EV Slave)*/
err_Cj ChaoJi_RM_connect(struct ChaoJi_RM_Mcb *Msgcb,  u16 port, void (* connected)(struct ChaoJi_RM_Mcb *Msgcb));


/*The server(Slave) listen port before receiving the connection from the Client(Master). The server(Slave) will not trigger ChaoJi_RM_accept() until it received the connection from the client(master). 
it return success by default (ChaoJi based on CAN2.0B only allow one conection at the time*/
struct ChaoJi_RM_Mcb *ChaoJi_RM_listen(struct ChaoJi_RM_Mcb *Msgcb)


/*The server(Slave) responses to return success when it receives the connection from the Client(Master), default succeed.*/
void ChaoJi_RM_accept(struct ChaoJi_RM_Mcb *Msgcb, void (* accept)(struct ChaoJi_RM_Mcb *Msgcb))

/*close the connection and free the memory.*/
void ChaoJi_RM_Close(struct ChaoJi_RM_Mcb *Msgcb);