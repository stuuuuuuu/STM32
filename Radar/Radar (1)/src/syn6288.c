#include "syn6288.h"
#include "time0.h"



void SYN_FrameInfo(uint8_t Music,uint8_t *HZdata)
{
/****************��Ҫ���͵��ı�**********************************/ 
		 unsigned  char  Frame_Info[50];
         unsigned  char  HZ_Length;  
		 unsigned  char  ecc  = 0;  			//����У���ֽ�
	     unsigned  int i=0; 
		 HZ_Length =strlen(HZdata); 			//��Ҫ�����ı��ĳ���
 
/*****************֡�̶�������Ϣ**************************************/           
		 Frame_Info[0] = 0xFD ; 			//����֡ͷFD
		 Frame_Info[1] = 0x00 ; 			//�������������ȵĸ��ֽ�
		 Frame_Info[2] = HZ_Length + 3; 		//�������������ȵĵ��ֽ�
		 Frame_Info[3] = 0x01 ; 			//���������֣��ϳɲ�������		 		 
		 Frame_Info[4] = 0x01 | Music<<4 ;  //����������������������趨

/*******************У�������***************************************/		 
		 for(i = 0; i<5; i++)   				//���η��͹���õ�5��֡ͷ�ֽ�
	     {  
	         ecc=ecc^(Frame_Info[i]);		//�Է��͵��ֽڽ������У��	
	     }

	   	 for(i= 0; i<HZ_Length; i++)   		//���η��ʹ��ϳɵ��ı�����
	     {  
	         ecc=ecc^(HZdata[i]); 				//�Է��͵��ֽڽ������У��		
	     }		 
/*******************����֡��Ϣ***************************************/		  
		  memcpy(&Frame_Info[5], HZdata, HZ_Length);
		  Frame_Info[5+HZ_Length]=ecc;
		  PrintCom(Frame_Info,5+HZ_Length+1);
		  flag_2s = 1;
}
