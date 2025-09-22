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

			case NORMAL://正常状态

				break;

			case PAUSE://暂停状态

				break;

			case KILL_BOUNDARY://撞墙状态

				break;

			case KILL_SELF://撞自己状态

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