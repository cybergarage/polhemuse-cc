/************************************************************
*
*	Copyright(C) Satoshi Konno 1995
*
*	polhemus.h
*
************************************************************/

#ifndef _FASTRAK_H_
#define _FASTRAK_H_

#include <stdio.h>
#include <math.h>
#include "serial.h"

#define TRUE	1
#define FALSE	0

#define X	0
#define Y	1
#define Z	2

#define toBinaryCommand			"f"
#define toASCIICommand			"F"
#define toContinuousCommand	 	"C"
#define toNonContinuousCommand		"c"
#define retrieveStatusCommand		"S"
#define PCommand		       	"P"
#define GetRecord		       	"P"
#define SystemReset		       	"W"
#define PerformBoresight		"B1\r" 

#define MIN	0
#define MAX	1

typedef float    Euler[3];
typedef float    Point3d[3];

inline void p3Copy(
Point3d pin,
Point3d pout)
{
    pout[0] = pin[0];
    pout[1] = pin[1];
    pout[2] = pin[2];
}

inline void eCopy(
Euler ein,
Euler eout)
{
    eout[0] = ein[0];
    eout[1] = ein[1];
    eout[2] = ein[2];
}

inline void p3Subtract(
Point3d p1, 
Point3d p2, 
Point3d pout)
{
    pout[0] = p1[0] - p2[0];
    pout[1] = p1[1] - p2[1];
    pout[2] = p1[2] - p2[2];
}

inline void p3Init(Point3d p)
{
    p[0] = p[1] = p[2] = 0.0;
}

#define FASTRAK_MAXIMUM_RECEIVERN   4

#define FASTRAK_RECEIVER1	    1
#define FASTRAK_RECEIVER2	    2
#define FASTRAK_RECEIVER3	    3
#define FASTRAK_RECEIVER4	    4

class CPolhemus : public CSerial
{
    int		nReceiver;
    Point3d	p3FtPos[FASTRAK_MAXIMUM_RECEIVERN];	    //磁気センサーの位置情報
    Euler	eFtRot[FASTRAK_MAXIMUM_RECEIVERN];	    //磁気センサーの回転情報
    char	buffer[256];				    //通信読み込みバファ
    int		updateFlag;				    // 8bit (p1|p2|p3|p4|r1|r2|r3|r4)
public:
    CPolhemus(char *device, int speed);			    //コンストラクタ
    ~CPolhemus();					    //デストラクタ
    int	    GetActiveReceiverN(void)	    {return nReceiver;}
    void    SetReceiverUpdateFlag(int flag) {updateFlag = flag;}
    int	    GetReceiverUpdateFlag(void)	    {return updateFlag;}
    int	    GetMessage(int n);				    //磁気センサーからのデータ読み込み
    void    UpdateData(int updateBit);     		    
    void    ReadNewData(void);				    //磁気センサーへのデータ要求
    void    GetPosition(int nReciver, Point3d p3Pos);	    //磁気サンサー位置の取得
    void    GetOrientation(int nReciver, Euler eOri);	    //磁気サンサー回転の取得
};

#endif
