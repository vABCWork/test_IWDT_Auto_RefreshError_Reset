#include	<machine.h>
#include	"iodefine.h"
#include	"misratypes.h"
#include	"delay.h"
#include	"iwdt.h"


// 動作確認用　LED出力ポート
// ALM3 :　PH3
#define ALM_3_PMR      (PORTH.PMR.BIT.B3)   //  汎用入出力ポート
#define ALM_3_PDR      (PORTH.PDR.BIT.B3)   //  出力または入力ポートポートに指定
#define ALM_3_PODR     (PORTH.PODR.BIT.B3)  //  出力データ

// ウオッチドックタイマによるリセット発生確認用 LED出力ポート
// ALM4: PH2
#define ALM_4_PMR      (PORTH.PMR.BIT.B2)   //  汎用入出力ポート
#define ALM_4_PDR      (PORTH.PDR.BIT.B2)   //  出力または入力ポートポートに指定
#define ALM_4_PODR     (PORTH.PODR.BIT.B2)  //  出力データ


void Task_Normal(void);
void Task_Early_Error(void);


//
// 独立ウオッチドックタイマの動作確認
//  ・オートスタートモード
//  ・タイムアウト時間 = 136.5[msec]
//  ・ウィンドウ終了=50%, ウィンドウ開始=100%
//  ・リフレッシュエラーでリセット
//

void main(void)
{
	ALM_3_PMR = 0;		// 汎用入出力ポート
	ALM_3_PDR = 1;		// 出力ポートに指定
	
	ALM_4_PMR = 0;		// 汎用入出力ポート
	ALM_4_PDR = 1;		// 出力ポートに指定
	
	
	if ( SYSTEM.RSTSR2.BIT.IWDTRF == 1 ) {	// 独立ウオッチドックタイマによるリセットを検出した場合
	    while(1){ 
		ALM_4_PODR = 1;	     // ALM_4 点灯
	    }
	}
	
	
	while(1){
	 
	   Task_Normal();	// 100msec待ち
	   
	   IWDT_Refresh();	// ウオッチドックタイマリフレッシュ
	
	  // Task_Normal();	// 100msec待ち (正常動作確認の場合 実施)
	   Task_Early_Error();	// 50msec待ち (異常動作確認の場合 実施)
	   
	   IWDT_Refresh();	// ウオッチドックタイマリフレッシュ

	}
	
	
}


//
//  タスク(正常時)
//
void Task_Normal(void)
{
	ALM_3_PODR ^= 1;      // ALM3 LED 反転	
	
	delay_msec(100);     // 100msec 待ち
}



//
//  タスク(早まり異常)
//
void Task_Early_Error(void)
{
	ALM_3_PODR ^= 1;      // ALM3 LED 反転	
	
	delay_msec(50);      // 50msec 待ち
}


