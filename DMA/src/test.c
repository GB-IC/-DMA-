#include "sys.h"
#include "usart.h"		
#include "delay.h"	
#include "led.h"
#include "timer.h"
#include "dma.h"
//char *name="hello world\n";
#define SEND_BUF_SIZE 72 //????,?? sizeof(TEXT_TO_SEND)+2 ????
u8 SendBuff[SEND_BUF_SIZE]; //???????
const u8 TEXT_TO_SEND[]={"hello world"};
u16 time=0;
int h;
void calculate(u32 iterations) {
    u32 result = 0;
    for (h = 0; h < iterations; h++) {
        result += h * h; // ִ��һЩ��������
    }
    //printf("������: %d\n", result);
}
int main(void)
{								  
	// u16 t;
	// u16 len;	
	// u16 count=0;
	 u16 wast_time=0;
	//u16 times=0;    

	// //LED0=0;
	// MYDMA_Config(DMA1_Channel4,(u32)&USART1->DR,(u32)SendBuff,SEND_BUF_SIZE);	
	// printf("hello world\n");
 	// while(1)
	// {
	// 	if(count!=240){
	// 		printf("hello world\n");
	// 		count+=12;
	// 	}else{
	// 		printf("Tranfer end\n");
	// 		wast_time=(TIM3->CNT-time)/10;
	// 		time=TIM3->CNT;
	// 		printf("time->%d ms\n",wast_time);
			
	// 		//LED0=!LED0;
	// 		count=0;
	// 	}	
		

	// }
	u16 i;
	u8 t=0;
	u8 j,mask=0;
	float pro=0;			//����	
	Stm32_Clock_Init(9);	//ϵͳʱ������
	uart_init(72,9600); 	//���ڳ�ʼ��Ϊ115200
	delay_init(72);	   	 	//��ʱ��ʼ�� 
	LED_Init();
	TIM3_Int_Init(19999,7199); 	
 	MYDMA_Config(DMA1_Channel4,(u32)&USART1->DR,(u32)SendBuff,SEND_BUF_SIZE);//DMA1ͨ��4,����Ϊ����1,�洢��ΪSendBuff,����SEND_BUF_SIZE.	
	j=sizeof(TEXT_TO_SEND);	   
	for(i=0;i<SEND_BUF_SIZE;i++)//������ݵ�SendBuff
    {
		if(t>=j)//���뻻�з�
		{
			if(mask)
			{
				SendBuff[i]=0x0a;
				t=0;
			}else 
			{
				SendBuff[i]=0x0d;
				mask++;
			}	
		}else//����TEXT_TO_SEND���
		{
			mask=0;
			SendBuff[i]=TEXT_TO_SEND[t];
			t++;
		}    	   
    }		  
	i=0;
	// MYDMA_Enable(DMA1_Channel4);//��ʼһ��DMA����?
	// USART1->CR3=1<<7;
	while(1)
	{
		time=TIM3->CNT;
		//printf("\r\nDMA DATA:\r\n");
		for(i=0;i<SEND_BUF_SIZE;i++){
			printf("%c",SendBuff[i]);
		}	
		// if(DMA1->ISR&(1<<13))//�ȴ�ͨ��4�������
		// {
		// 		DMA1->IFCR|=1<<13;//���ͨ��4������ɱ�־
		// 		//DMA1_Channel4->CCR&=~(1<<0);       
		// 	//USART1->CR3=0;				
		// 		break; 
		// }
		calculate(250000); 
		printf("Tranfer end\n");
		wast_time=(TIM3->CNT-time)/10;
		
		printf("time->%d ms\n",wast_time);
		    
	}
		   		 
}

