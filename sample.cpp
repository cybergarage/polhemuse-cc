/************************************************************
*
*	Copyright(C) Satoshi Konno 1995
*
*	sample.cpp
*
************************************************************/

#include <stdio.h>
#include "polhemus.h"

void main(int argc, char **argv)
{
    CPolhemus frak(SERIAL1, B19200);
    Point3d p3;

	printf("Receiver n : %d\n", frak.GetActiveReceiverN());
    while(1) {
		frak.GetPosition(1, p3);
		printf("R1 : %f %f %f ", p3[0], p3[1], p3[2]);
		frak.GetOrientation(1, p3);
		printf("%f %f %f\n", p3[0], p3[1], p3[2]);
    };
}
