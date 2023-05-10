

//   N [msec] 待つ関数 (ICLK = 32MHz)
//   命令語は、 RX V2 アーキテクチャ
//    コンパイル時　最適化レベル = 2   (-optimize = 2 )
//   n_msec=  1:  1msec
//      

#pragma instalign4 delay_msec

void  delay_msec( unsigned long  n_msec )
{
	unsigned long delay_cnt;

	while( n_msec-- ) {

	   delay_cnt = 10656;
		
 	   while(delay_cnt --) 
	   { 			 
	   }

	}
}




//   
//    50[usec}待つ   
//  IWDT専用クロック発振安定時間 用
//

#pragma instalign4 delay_50usec

void  delay_50usec(void)
{
	unsigned long delay_cnt;

	   delay_cnt = 530;
		
	   while(delay_cnt --) 
	   { 			 
	   }

}

