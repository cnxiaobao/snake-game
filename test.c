#include "realize.h"

int main() 
{

	//创建并初始化游戏信息结构体
	Maintain_Game_Information game_info = { 0 };

	//游戏初次初始化
	First_Init(&game_info);

	//控制台输出信息和提示
	Output_Information(&game_info);

	do
	{
		switch (game_info.state)
		{
			case NOT_START://未开始状态
			case NORMAL://正常状态
			case KILL_BOUNDARY://撞墙状态
			case KILL_SELF://撞自己状态
				Output_Information(&game_info);
				break;

			case PAUSE://暂停状态

				if (GetAsyncKeyState(0x50)) //按P键暂停
				{
					game_info.state = NORMAL;
					Sleep(300); //防止按键过快导致状态切换异常
				
					Console_Refresh(&game_info); //刷新控制台显示
				}

				if (GetAsyncKeyState(VK_ESCAPE)) //按Esc键退出
				{
					game_info.is_game_over = true;

					Free_All_Dynamic_Memory(&game_info);//释放所有动态分配的内存
					Locate_Cursor_Position((100 - 12) / 2, 15, game_info.houtput);
					printf("游戏已退出");
					Locate_Cursor_Position((100 - 21) / 2, 17, game_info.houtput);
					printf("感谢您的游玩，欢迎下次再来!");

					exit(0); //退出程序
				}

				break;

			default:
				//出现未定义状态，结束游戏
				game_info.is_game_over = true;
				break;
		}
	} while (!game_info.is_game_over);

	//释放所有动态分配的内存
	Free_All_Dynamic_Memory(&game_info);

	return 0;
}