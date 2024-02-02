/************************************************************
*
*	Copyright(C) Satoshi Konno 1995
*
*	polhemus.cpp
*
************************************************************/

#include <stdlib.h>
#include "polhemus.h"
#include "serial.h"

void CPolhemus::UpdateData(int updateBit)
{
    int recvFlag = GetReceiverUpdateFlag();

#ifdef DEBUG
    printf("FASTRAK : Update data %2x %2x\n", recvFlag, updateBit);
#endif

    if (!(updateBit & recvFlag))
	ReadNewData();

    int newRecvFlag = GetReceiverUpdateFlag();
    newRecvFlag &= ~updateBit;
    SetReceiverUpdateFlag(newRecvFlag);	
}

void CPolhemus::GetPosition(int nReciver, Point3d p3Pos)
{
    int	bitFlag = 0x01 << (nReciver-1+4);
    UpdateData(bitFlag);

    p3Copy(p3FtPos[nReciver-1], p3Pos);
}

void CPolhemus::GetOrientation(int nReciver, Euler eOri)
{
    int	bitFlag = 0x01 << (nReciver-1);
    UpdateData(bitFlag);
    
    eCopy(eFtRot[nReciver-1], eOri);
}

int CPolhemus::GetMessage(int nMessage)
{
    int n = 0;

    while (n < nMessage)
	n += Read(buffer + n, nMessage - n);
    buffer[n] = '\0';
#ifdef DEBUG
    printf("FASTRAK : Received data(%d) is '%s'\n", n, buffer);
#endif
    return TRUE; 
}

void CPolhemus::ReadNewData(void)
{
    int msgn;

    for (int n=0; n<GetActiveReceiverN(); n++) {
        Write(GetRecord);

#ifdef ISOTRAK2
	msgn = 45;
#else
	msgn = 48;
#endif
	if (GetMessage(msgn)) {
	    p3FtPos[n][X] = atof(&buffer[3]);
	    p3FtPos[n][Y] = atof(&buffer[10]);
	    p3FtPos[n][Z] = atof(&buffer[17]);
	    eFtRot[n][X] = atof(&buffer[24]);
	    eFtRot[n][Y] = atof(&buffer[32]);
	    eFtRot[n][Z] = atof(&buffer[39]);
	}
    }

    SetReceiverUpdateFlag(0xff);
}

CPolhemus::CPolhemus(char *device, int speed) : CSerial(device, speed)
{
    int	    n;

    nReceiver = 0;

#ifdef ISOTRAK2
    Write("l\r");
    GetMessage(7);
#else
    Write("l1\r");
    GetMessage(9);
#endif
    for (n=0; n<4; n++) {
	if (buffer[n+3] == '1')
	    nReceiver++;	
    }

#ifdef DEBUG
    printf("FASTRAK : Active receiver is %d\n", nReceiver);
#endif

#ifdef ISOTRAK2 
	Write("O4,2\r");
#else
    char    commSetRecvN[32];
    for (n=1; n<=4; n++) {
	sprintf(commSetRecvN, "O%d,2,0,4,1\r", n);
	Write(commSetRecvN);
    }
#endif

    Write(toASCIICommand);
    Write(toNonContinuousCommand); 


    // ‰ñ“]Ši”[’l‚Ì‰Šú‰»
    for (n=0; n<4; n++) {
	p3Init(p3FtPos[n]);
	p3Init(eFtRot[n]);
    }

    SetReceiverUpdateFlag(0);
}

CPolhemus::~CPolhemus()
{
}
