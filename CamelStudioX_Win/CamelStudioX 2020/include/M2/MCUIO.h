/*--------------------------------------------------------------------
 * TITLE: m2 Hardware Defines
 * AUTHOR: John & Jack 
 * DATE CREATED: 2013/10/10
 * FILENAME: m2.h
 * PROJECT: m2
 * COPYRIGHT: Small World, Inc.
 * DESCRIPTION:
 *    m2 Hardware Defines
 *
 *    2014-03-17: added sd adc, opo, v2p; sys reg modified
 *    2014-01-11: added sd adc, opo, v2p; sys reg modified
 *    2013-12-18: misc edit
 *    2013-12-15: uart reg back to m1
 *    2012-10-16: modified base on m2 new design
 *    2012-10-10: modified base on s0.h
 *--------------------------------------------------------------------*/
#include "mcu.h"
#include "SPI.h"


/*********** Hardware addesses ***********/
#define SYS_GDR_REG		  0x1f800703  // gdr register SEG OUTPUT[0:7] SEG[20]---SEG[27]
#define SYS_IOCTL_REG     0x1f800704  // 0=in; 1-out (16-bit), was IO config
#define SYS_GPIO0_REG     0x1f800705  // GPIO (16-bit) to pad content 
#define SYS_GPIO1_REG     0x1f800706  // GPIO (16_bit) from pad read 
#define SYS_SEGIN_REG     0x1f800c01  // SEG INPUT[0:7] SEG[12]---SEG[19] 

#define SET_GPIO0_BIT_ON(A) {MemoryOr32(SYS_IOCTL_REG, (1<<A)); MemoryOr32(SYS_GPIO0_REG, (1<<A)); }
#define SET_GPIO0_BIT_OFF(A) {MemoryOr32(SYS_IOCTL_REG, (1<<A)); MemoryAnd32(SYS_GPIO0_REG, ~(1<<A)); }
#define GET_GPIO1_BIT(A) MemoryBitAt(SYS_GPIO1_REG, A)

/*************** IO Setup***************/
#define RT_IOCTL_Set1(n, oe) 	MemoryOr16(SYS_IOCTL_REG, oe<<n);
						
#define RT_IOCTL_Set32(oe)		MemoryWrite32(SYS_IOCTL_REG, oe);

#define RT_IOCTL_Set16(oe)		MemoryWrite32(SYS_IOCTL_REG, oe);

#define RT_IOCTL_And16(oe)		MemoryAnd16(SYS_IOCTL_REG, oe);

#define RT_IOCTL_Or16(oe)		MemoryOr16(SYS_IOCTL_REG, oe);

#define RT_GPIO_Write1(n, v)	MemoryOr16(SYS_GPIO0_REG, v<<n);  
						
#define RT_GPIO_Write16(v)		MemoryWrite16(SYS_GPIO0_REG, v);	

#define RT_GPIO_Write32(v)		MemoryWrite32(SYS_GPIO0_REG, v);	

#define RT_GPIO_Read1(n)	((MemoryRead16(SYS_GPIO1_REG)&(1<<n))>>n)

#define RT_GPIO_Read32(n)	((MemoryRead32(SYS_GPIO1_REG)&(1<<n))>>n)

#define RT_GPIO1_Read()	    MemoryRead(SYS_GPIO1_REG)
#define RT_GPIO1_Read8()	MemoryRead8(SYS_GPIO1_REG)
#define RT_GPIO1_Read16()	MemoryRead16(SYS_GPIO1_REG)
#define RT_GPIO1_Read32()	MemoryRead32(SYS_GPIO1_REG)
#define RT_GPIO0_Read32()	MemoryRead32(SYS_GPIO0_REG)

#define RT_SEG_Read(n)   ((MemoryRead32(SYS_SEGIN_REG)&(1<<n))>>n)
/**************** IO End****************/

/******************gdr out***************/
#define RT_GDR_Write8(v)		MemoryWrite8(SYS_GDR_REG,v);

#define RT_GDR_BIT_ON(A)        MemoryOr32(SYS_GDR_REG,(1<<A));
#define RT_GDR_BIT_OFF(A)       MemoryAnd32(SYS_GDR_REG,~(1<<A));

#define RT_GDR_Write32(v)		MemoryWrite32(SYS_GDR_REG, v);


