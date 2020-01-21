/**********************************************************
/**
* @file	WRITE data TO sja1000(can controler) Register
*
* This file contains a example using gdr out and I/O functon to control outside register.
*
* 
*
*
* MODIFICATION HISTORY:
*
* Ver   Who		Date      Changes
* ---   ------	--------  --------------------------------
* 1.0	Kevin&Shan  12/7/17  First release
*
***********************************************************/

/****************** Include Files *************************/

#include "MCUIO.h"
#include "string.h"
#include "str.h"
#include "mcu.h"
#include "AFE.h"

#define SYS_GDR_REG		  0x1f800703  // gdr register
#define SYS_IOCTL_REG     0x1f800704  // 0=in; 1-out (16-bit), was IO config
#define SYS_GPIO0_REG     0x1f800705  // GPIO (16-bit) to pad content 
#define SYS_GPIO1_REG     0x1f800706  // GPIO (16_bit) from pad read 

#define SPI_CTL_REG             0x1f800d04
#define U1_CTL0_REG             0x1f800804
#define A_SDV2P_CTL_REG         0x1f800600

/*********************************************************/
/**
* This function is the main function
*
*
ale----GDR0
rd------GDR1
wr------GDR2
cs------GDR3
rst-------GDR4
ad0----ad7  INT5---INT0 A0N A0P
init-----IN0
**********************************************************/


WR_SJA_REG(volatile int ADD,volatile int DATA)
{


	MemoryWrite32(SPI_CTL_REG,0x8);        			 //disable spi 
	MemoryWrite32(U1_CTL0_REG,0x10);                //disable  uart1     
	MemoryWrite32(A_SDV2P_CTL_REG,0x0);             //disable sd
	RT_OPO_SetCh(0, 0, 0, 0);                          //Close OPO to enable io(7)-io(8)
	int p;
	int i;
	/*initial all GDR*/
	RT_GDR_BIT_OFF(0);    //SEG 20 ==GDR 0   ALE
	RT_GDR_BIT_ON(1);	  //SEG 21 ==GDR 1	RD
	RT_GDR_BIT_ON(2);	  //SEG 22 ==GDR 2	WR
	RT_GDR_BIT_ON(3);	  //SEG 23 ==GDR 3	CS
	

	RT_IOCTL_Set32(0xFFFF);					//set all gpio as output
	RT_GDR_BIT_ON(0);						//ALE HIGN
	for(i=0;i<5;i++);
	
    //ADD=ADD<<6;  
	RT_GPIO_Write32(ADD);		      		 //MCU SEND ADDRESS TO SJA1000
	for(i=0;i<5;i++);
										
	RT_GDR_BIT_OFF(0);						 //ALE LOW
	for(i=0;i<5;i++);
	
	RT_GDR_BIT_OFF(3);						 //CS LOW
	for(i=0;i<5;i++);
	
	RT_IOCTL_Set32(0xFFFF);	 				 //set all gpio as OUTPUT
	for(i=0;i<5;i++);
	
	RT_GDR_BIT_OFF(2);					   	 //WR LOW
	for(i=0;i<5;i++);
	
	//DATA=DATA<<6; 
	RT_GPIO_Write32(DATA);	    			 //MCU WRITE DATA TO SJA1000
	//puts(xtoa(RT_GPIO0_Read32())); 			//PRINT IT 
	
	p=RT_GPIO0_Read32();

	//p=p>>6;
	p=p&0Xff;								 //STAY THE LAST 8 BITS
	//putch('\n');
	for(i=0;i<5;i++);
	
	RT_GDR_BIT_ON(2);						 //WR HIGN
	for(i=0;i<5;i++);
	//RT_GPIO_Write32(0x1D);	
	RT_GDR_BIT_ON(3);						 //CS HIGN
	for(i=0;i<5;i++);
	
	return p;
	//STEP 4
	/*read*/
}

RD_SJA_REG(volatile int ADD)
{
	RT_OPO_SetCh(0, 0, 0, 0);                          //Close OPO to enable io(7)-io(8)
	MemoryWrite32(SPI_CTL_REG, 0x8);        			 //disable spi 
	MemoryWrite32(U1_CTL0_REG, 0x10);                 //disable  uart1     
	MemoryWrite32(A_SDV2P_CTL_REG, 0x0);              //disable sd
	int i;
	int p;

	RT_GDR_BIT_OFF(0);    //SEG 20 ==GDR 0   ALE
	RT_GDR_BIT_ON(1);	   //SEG 21 ==GDR 1	  RD
	RT_GDR_BIT_ON(2);	   //SEG 22 ==GDR 2   WR
	RT_GDR_BIT_ON(3);	   //SEG 23 ==GDR 3	  CS


	RT_IOCTL_Set32(0xFFFF);					//set all gpio as OUTPUT
	RT_GDR_BIT_ON(0);						//ALE HIGN
	for (i = 0;i<5;i++);

	//ADD=ADD<<6;
	RT_GPIO_Write32(ADD);		       //MCU SEND ADDRESS TO SJA1000
									   //puts(xtoa(ADD));
	for (i = 0;i<5;i++);

	RT_GDR_BIT_OFF(0);						//ALE LOW
	for (i = 0;i<5;i++);

	RT_GDR_BIT_OFF(3);						//CS LOW
	for (i = 0;i<5;i++);

	RT_IOCTL_Set32(0x0);					//set all gpio as INPUT
	for (i = 0;i<5;i++);

	RT_GDR_BIT_OFF(1);						//RD LOW
	for (i = 0;i<5;i++);

	//puts(xtoa(RT_GPIO1_Read8()));			//SJA1000 SEND DATA TO MCU AUTOMATICALLY AND PRINT IT 
	//putch('\n');
	//puts(xtoa(RT_GPIO1_Read()));
	//putch('\n');
	p = RT_GPIO1_Read();
	//p=p>>6;
	p &= 0xff;   								//STAY LAST 8 BITS
												//puts(xtoa(RT_GPIO1_Read16()));
												//putch('\n');
												//puts(xtoa(RT_GPIO1_Read32()));
												//putch('\n');
	for (i = 0;i<5;i++);

	RT_GDR_BIT_ON(1);						//RD HIGN
	for (i = 0;i<5;i++);

	RT_GDR_BIT_ON(3);						//CS HIGN
	for (i = 0;i<5;i++);

	return p;
}

/*RD_SJA_ID(volatile char ADD)
{

	MemoryWrite32(SPI_CTL_REG,0x8);        			 //disable spi 
	MemoryWrite32(U1_CTL0_REG,0x10);                 //disable  uart1     
	MemoryWrite32(A_SDV2P_CTL_REG,0x0);              //disable sd
	 int i;
	 int p;
	 int q;

	 RT_GDR_BIT_OFF(0);    //SEG 20 ==GDR 0   ALE
	 RT_GDR_BIT_ON(1);	   //SEG 21 ==GDR 1	  RD
	 RT_GDR_BIT_ON(2);	   //SEG 22 ==GDR 2   WR
	 RT_GDR_BIT_ON(3);	   //SEG 23 ==GDR 3	  CS


	RT_IOCTL_Set32(0xFFFF);					//set all gpio as OUTPUT
	RT_GDR_BIT_ON(0);						//ALE HIGN
	for(i=0;i<5;i++);
			
	RT_GPIO_Write32(ADD);		       //MCU SEND ADDRESS TO SJA1000
	for(i=0;i<5;i++);									
	
	RT_GDR_BIT_OFF(0);						//ALE LOW
	for(i=0;i<5;i++);
	
	RT_GDR_BIT_OFF(3);						//CS LOW
	for(i=0;i<5;i++);

	RT_IOCTL_Set32(0x0);					//set all gpio as INPUT
	for(i=0;i<5;i++);

	RT_GDR_BIT_OFF(1);						//RD LOW
	for(i=0;i<5;i++);

	//puts(xtoa(RT_GPIO1_Read8()));			//SJA1000 SEND DATA TO MCU AUTOMATICALLY AND PRINT IT 
	//putch('\n');
	//puts(xtoa(RT_GPIO1_Read()));
	//putch('\n');
	p=(RT_GPIO1_Read32());
	p&=0xff;   								//STAY LAST 8 BITS
	//puts(xtoa(RT_GPIO1_Read16()));
	//putch('\n');
	//puts(xtoa(RT_GPIO1_Read32()));
	//putch('\n');
	for(i=0;i<5;i++);
	
	RT_GDR_BIT_ON(1);						//RD HIGN
	for(i=0;i<5;i++);
	
	RT_GDR_BIT_ON(3);						//CS HIGN
	for(i=0;i<5;i++);

	return p;
}*/

WR_SJA_ID(unsigned char ADD,unsigned char DATA)
{
	RT_OPO_SetCh(0, 0, 0, 0);                          //Close OPO to enable io(7)-io(8)
	MemoryWrite32(SPI_CTL_REG,0x8);        			 //disable spi 
	MemoryWrite32(U1_CTL0_REG,0x10);                //disable  uart1     
	MemoryWrite32(A_SDV2P_CTL_REG,0x0);             //disable sd
	int p;
	int i;
	
	RT_GDR_BIT_OFF(0);    //SEG 20 ==GDR 0   ALE
	RT_GDR_BIT_ON(1);	  //SEG 21 ==GDR 1	RD
	RT_GDR_BIT_ON(2);	  //SEG 22 ==GDR 2	WR
	RT_GDR_BIT_ON(3);	  //SEG 23 ==GDR 3	CS
	

	RT_IOCTL_Set32(0xFFFF);					//set all gpio as output
	RT_GDR_BIT_ON(0);						//ALE HIGN
	for(i=0;i<5;i++);
	
      
	RT_GPIO_Write32(ADD);		      		 //MCU SEND ADDRESS TO SJA1000
	for(i=0;i<5;i++);
										
	RT_GDR_BIT_OFF(0);						 //ALE LOW
	for(i=0;i<5;i++);
	
	RT_GDR_BIT_OFF(3);						 //CS LOW
	for(i=0;i<5;i++);
	
	RT_IOCTL_Set32(0x00FF);	 				 //set all gpio as OUTPUT
	for(i=0;i<5;i++);
	
	RT_GDR_BIT_OFF(2);					   	 //WR LOW
	for(i=0;i<5;i++);
	
	
	RT_GPIO_Write32(DATA);	    			 //MCU WRITE DATA TO SJA1000
	//puts(xtoa(RT_GPIO0_Read32())); 			//PRINT IT 
	p=(RT_GPIO0_Read32()>>3);
	p=p&0Xff;								 //STAY THE LAST 8 BITS
	//putch('\n');
	for(i=0;i<5;i++);
	
	RT_GDR_BIT_ON(2);						 //WR HIGN
	for(i=0;i<5;i++);
	//RT_GPIO_Write32(0x1D);	
	RT_GDR_BIT_ON(3);						 //CS HIGN
	for(i=0;i<5;i++);
	
	return p;
	//STEP 4
	
}