/*********************************************************************************************************************
* MM32F327X-G8P Opensourec Library 即（MM32F327X-G8P 开源库）是一个基于官方 SDK 接口的第三方开源库
* Copyright (c) 2022 SEEKFREE 逐飞科技
* 
* 本文件是 MM32F327X-G8P 开源库的一部分
* 
* MM32F327X-G8P 开源库 是免费软件
* 您可以根据自由软件基金会发布的 GPL（GNU General Public License，即 GNU通用公共许可证）的条款
* 即 GPL 的第3版（即 GPL3.0）或（您选择的）任何后来的版本，重新发布和/或修改它
* 
* 本开源库的发布是希望它能发挥作用，但并未对其作任何的保证
* 甚至没有隐含的适销性或适合特定用途的保证
* 更多细节请参见 GPL
* 
* 您应该在收到本开源库的同时收到一份 GPL 的副本
* 如果没有，请参阅<https://www.gnu.org/licenses/>
* 
* 额外注明：
* 本开源库使用 GPL3.0 开源许可证协议 以上许可申明为译文版本
* 许可申明英文版在 libraries/doc 文件夹下的 GPL3_permission_statement.txt 文件中
* 许可证副本在 libraries 文件夹下 即该文件夹下的 LICENSE 文件
* 欢迎各位使用并传播本程序 但修改内容时必须保留逐飞科技的版权声明（即本声明）
* 
* 文件名称          main
* 公司名称          成都逐飞科技有限公司
* 版本信息          查看 libraries/doc 文件夹内 version 文件 版本说明
* 开发环境          IAR 8.32.4 or MDK 5.37
* 适用平台          MM32F327X_G8P
* 店铺链接          https://seekfree.taobao.com/
* 
* 修改记录
* 日期              作者                备注
* 2022-08-10        Teternal            first version
********************************************************************************************************************/

#include "zf_common_headfile.h"
#include "PID.h"
#include "menu.h"

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
				
				
			
////图像显示*******************************************
//        if(mt9v03x_finish_flag)
//        {	
//					//原图像
//          ips200_displayimage03x((const uint8 *)mt9v03x_image, 240, 180);
//					//二值化后
//          ips200_show_string(0, 184,"After_Handle");
//					ips200_show_gray_image(0, 200, (const uint8 *)mt9v03x_image, MT9V03X_W, MT9V03X_H, 240, 180, BINARIZATION_THRESHOLD);
//          mt9v03x_finish_flag = 0;
//        }
////*************************************************

    }
}
// **************************** 代码区域 ****************************
