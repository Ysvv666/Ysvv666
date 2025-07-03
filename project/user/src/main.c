#include "zf_common_headfile.h"
#include "PID.h"
#include "menu.h"
#include "image.h"
#define BINARIZATION_THRESHOLD ( 64 ) // 二值化阈值 默认 64 需要设置 DISPLAY_MODE 为 1 才使用
#define IPS200_TYPE (IPS200_TYPE_SPI) // 双排排针 并口两寸屏 这里宏定义填写 IPS200_TYPE_PARALLEL8
                                      // 单排排针 SPI 两寸屏 这里宏定义填写 IPS200_TYPE_SPI
PID_t Inner = {					//内环PID结构体变量，定义的时候同时给部分成员赋初值
	.Kp = 0,					    //比例项权重
	.Ki = 0,					    //积分项权重
	.Kd = 0,					    //微分项权重
	.OutMax = 100,				//输出限幅的最大值
	.OutMin = -100,				//输出限幅的最小值
	.Target=30,           //速度环控速
};

PID_t Outer = {					//外环PID结构体变量，定义的时候同时给部分成员赋初值
	.Kp = 0.5,					  //比例项权重
	.Ki = 0.001,					//积分项权重
	.Kd = 6,					    //微分项权重
	.OutMax = 50,				  //输出限幅的最大值
	.OutMin = -50,				//输出限幅的最小值
	.Target=64,           //差速环
};

// **************************** 变量区域 ****************************
uint8_t Best_thrsod;
// **************************** 代码区域 ****************************
int main(void)
{
    clock_init(SYSTEM_CLOCK_120M);                                              // 初始化芯片时钟 工作频率为 120MHz
    debug_init();                                                               // 初始化默认 Debug UART
    // 此处编写用户代码 例如外设初始化代码等
    mt9v03x_init();          //总钻风初始化
    ips200_init(IPS200_TYPE_SPI);//ips初始化
	  key_init (10);           //按键初始化//按键扫描周期 以毫秒为单位
		menu_init();                       

    // 此处编写用户代码 例如外设初始化代码等
	
    while(1)
    {
//按键处理*******************************************
				key_scanner();
				if(key_get_state     (KEY_1)){
						moveup();
            menu_display();
						key_clear_state  (KEY_1);
				}
				else if(key_get_state(KEY_2)){
						movedown();
            menu_display();
						key_clear_state  (KEY_2);
				}
				else if(key_get_state(KEY_3)){
						Sure();
            menu_display();
						key_clear_state  (KEY_3);
				}
				else if(key_get_state(KEY_4)){
						Back();
            menu_display();
						key_clear_state  (KEY_4);
				}			
//*************************************************
				
				
			
//图像显示*******************************************
        if(mt9v03x_finish_flag)
        {	
					//原图像
          ips200_displayimage03x((const uint8 *)mt9v03x_image, 240, 180);
					//二值化后
          ips200_show_string(0, 184,"After_Handle");
					Best_thrsod=OtsuThreshold(mt9v03x_image,MT9V03X_W,MT9V03X_H);//动态阈值	
					ips200_show_gray_image(0, Best_thrsod, (const uint8 *)mt9v03x_image, MT9V03X_W, MT9V03X_H, 240, 180, BINARIZATION_THRESHOLD);
          mt9v03x_finish_flag = 0;
        }
//*************************************************

    }
}
