#include "realize.h"

//当behavior为1时，表示插入蛇身链表尾插
//当behavior为2时，表示插入食物链表尾插
void* Insert_Single_Bnake_Body_Node_At_Head(Maintain_Game_Information* game_info, int x, int y, int behavior)
{
	//确保传入的指针不为空
	assert(game_info);

	//当behavior为1时，表示插入蛇身链表尾插
	if (behavior == 1)
	{
		//创建一个新的蛇身节点
		Single_Bnake_Body_Node* new_node = (Single_Bnake_Body_Node*)malloc(sizeof(Single_Bnake_Body_Node));
		//确保内存分配成功
		assert(new_node);
		new_node->x = x; //设置新节点的X坐标
		new_node->y = y; //设置新节点的Y坐标
		if (game_info->head == NULL)
		{
			game_info->head = new_node; //更新头节点为新节点
			new_node->next = NULL; //新节点的下一个节点为空
			game_info->tail = new_node; //更新尾节点为新节点
		}
		else
		{
			game_info->head->next = new_node; //将当前尾节点的下一个节点指向新节点
			game_info->head = new_node; //更新头节点为新节点
			new_node->next = NULL; //新节点的下一个节点为空
		}
		return new_node; //返回新插入的节点
	}
	else if (behavior == 2) //当behavior为2时，表示插入食物链表尾插
	{
		//创建一个新的食物节点
		Food_Node* new_food = (Food_Node*)malloc(sizeof(Food_Node));
		//确保内存分配成功
		assert(new_food);
		new_food->x = x; //设置新节点的X坐标
		new_food->y = y; //设置新节点的Y坐标
		if (game_info->food == NULL)
		{
			new_food->next = NULL; //新节点的下一个节点指向NULL
			game_info->food = new_food; //更新食物链表头为新节点
			game_info->food_tail = new_food; //更新食物链表尾为新节点
		}
		else
		{
			game_info->food->next = new_food; //将当前食物链表尾节点的下一个节点指向新节点
			game_info->food = new_food; //更新食物链表尾为新节点
			new_food->next = NULL; //新节点的下一个节点指向NULL
		}
		
		return new_food; //返回新插入的节点
	}
	else
	{
		//如果behavior值不合法，返回NULL
		return NULL;
	}
}

//控制台刷新
void Console_Refresh(Maintain_Game_Information* game_info)
{
	//确保传入的指针不为空
	assert(game_info);
	//清屏
	system("cls");
	//在控制台左上角使用“回”绘制29*29的地图边界
	for (int i = 0; i <= 29; i++)
	{
		for (int j = 0; j <= 29; j++)
		{
			if (i == 0 || i == 29 || j == 0 || j == 29)
			{
				Locate_Cursor_Position(j * 2, i, game_info->houtput); //每个字符宽度为2
				printf("回");
			}
		}
	}
	//绘制蛇身
	Single_Bnake_Body_Node* current = game_info->tail;
	while (current)
	{
		Locate_Cursor_Position(current->x * 2, current->y, game_info->houtput); //每个字符宽度为2
		printf("口");
		current = current->next; //移动到下一个节点
	}
	//绘制食物
	Food_Node* food_current = game_info->food_tail;
	while (food_current)
	{
		Locate_Cursor_Position(food_current->x * 2, food_current->y, game_info->houtput); //每个字符宽度为2
		printf("※");
		food_current = food_current->next; //移动到下一个节点
	}
	//绘制分数和其他信息
	Locate_Cursor_Position(60, 5, game_info->houtput);
	printf("分数: %d", game_info->score);
	Locate_Cursor_Position(60, 7, game_info->houtput);
	printf("当前蛇长度: %d", game_info->length);
	Locate_Cursor_Position(60, 9, game_info->houtput);
	printf("当前食物数量: %d", game_info->food_count);
	Locate_Cursor_Position(60, 11, game_info->houtput);
	printf("当前游戏状态: ");
	switch (game_info->state)
	{
	case NOT_START:
		printf("未开始");
		break;
	case NORMAL:
		printf("正常");
		break;
	case PAUSE:
		printf("暂停");
		break;
	case KILL_BOUNDARY:
		printf("撞墙");
	}
}

//定位光标位置
void Locate_Cursor_Position(int x, int y, HANDLE houtput)
{
	//确保控制台句柄不为空
	assert(houtput);
	//创建一个COORD结构体变量用于存储光标位置
	COORD pos;
	pos.X = x; //设置X坐标
	pos.Y = y; //设置Y坐标
	//应用控制台光标位置
	SetConsoleCursorPosition(houtput, pos);
}

//初次初始化
void First_Init(Maintain_Game_Information* game_info)
{
	//确保传入的指针不为空
	assert(game_info);

	//本地化控制台
	setlocale(LC_ALL, "");

	//清理输入缓冲区
	fflush(stdin);

	//初始化控制台窗口
	//设置控制台窗口大小为100列30行
	system("mode con cols=100 lines=33"); 

	//获取控制台句柄
	game_info->houtput = GetStdHandle(STD_OUTPUT_HANDLE); 
	//设置控制台标题
	SetConsoleTitleA("贪吃蛇小游戏");
	//获取控制台光标信息
	GetConsoleCursorInfo(game_info->houtput, &game_info->cursor_info);
	//设置控制台光标不可见
	game_info->cursor_info.bVisible = FALSE;
	//应用光标信息设置
	SetConsoleCursorInfo(game_info->houtput, &game_info->cursor_info);
	
	//初始化蛇身链表
	game_info->head = NULL;
	game_info->tail = NULL;
	//初始化食物链表
	game_info->food = NULL;

	//设置游戏初始状态
	game_info->length = 5;				//初始蛇长度为5
	game_info->dir = RIGHT;				//初始方向向右
	game_info->state = NOT_START;		//设置游戏为未开始状态
	game_info->food_count = 1;			//初始允许存在1个食物
	game_info->score = 0;				//初始分数为0
	game_info->sleep_time = 75;			//初始休息时间为75毫秒
	game_info->is_game_over = false;	//初始游戏未结束
}

//游戏初始化
void Game_Init(Maintain_Game_Information* game_info)
{
	//确保传入的指针不为空
	assert(game_info); 

	//创建蛇身
	for (int i = 0; i < game_info->length; i++)
	{
		//当Insert_Single_Bnake_Body_Node_At_Head返回NULL时，表示插入失败
		if (!Insert_Single_Bnake_Body_Node_At_Head(game_info, 15 - i, 10, 1))
		{
			exit(-1); //插入失败，退出程序
		}
	}

	//生成食物
	for (int i = 0; i < game_info->food_count; i++)
	{
		int food_x = rand() % 26 + 1; //生成1到27之间的随机X坐标
		int food_y = rand() % 26 + 1; //生成1到27之间的随机Y坐标

		//判断食物位置是否与蛇身重合，若重合则重新生成位置
		while (true)
		{
			bool is_overlap = false; //标记是否重合
			Single_Bnake_Body_Node* current = game_info->head;
			while (current)
			{
				if (current->x == food_x && current->y == food_y)
				{
					is_overlap = true; //位置重合
					break;
				}
				current = current->next; //移动到下一个节点
			}
			if (!is_overlap)
			{
				break; //位置不重合，跳出循环
			}
			//重新生成食物位置
			food_x = rand() % 26 + 1;
			food_y = rand() % 26 + 1;
		}

		//当Insert_Single_Bnake_Body_Node_At_Head返回NULL时，表示插入失败
		if (!Insert_Single_Bnake_Body_Node_At_Head(game_info, food_x, food_y, 2))
		{
			exit(-1); //插入失败，退出程序
		}
	}

	game_info->state = NORMAL; //将游戏状态设置为正常

	//刷新控制台显示
	Console_Refresh(game_info);
}

//控制台输出信息和提示
void Output_Information(Maintain_Game_Information* game_info)
{
	//确保传入的指针不为空
	assert(game_info);

	//当第一次游戏时，输出游戏说明
	if (game_info->state == NOT_START)
	{
		Locate_Cursor_Position((100 - 22) / 2, 10, game_info->houtput);
		printf("欢迎来到贪吃蛇小游戏!");
		Locate_Cursor_Position((100 - 68) / 2, 12, game_info->houtput);
		printf("游戏说明: 使用方向键控制蛇的移动方向，吃到食物可以增加长度和分数。");
		Locate_Cursor_Position((100 - 44) / 2, 14, game_info->houtput);
		printf("按 'P' 键暂停/继续游戏，按 'Esc' 键退出游戏。");
		Locate_Cursor_Position((100 - 19) / 2, 16, game_info->houtput);
		printf("按任意键开始游戏...");
		_getch(); //等待用户按键
		system("cls"); //清屏
		//询问用户是否需要自定义初始蛇长度与食物数量
		int choice = 0;
		while (choice != 1 && choice != 2)
		{
			
			Locate_Cursor_Position((100 - 36) / 2, 10, game_info->houtput);
			printf("是否自定义初始蛇长度与食物数量？");
			Locate_Cursor_Position((100 - 20) / 2, 12, game_info->houtput);
			printf("1. 是 (Y / N)");
			Locate_Cursor_Position((100 - 20) / 2, 14, game_info->houtput);
			printf("2. 否 (N / N)");
			Locate_Cursor_Position((100 - 21) / 2, 16, game_info->houtput);
			printf("请选择 (1 / 2): ");
			scanf("%d", &choice);

			if (choice < 1 || choice>2)
			{
				system("cls"); //清屏
				Locate_Cursor_Position((100 - 25) / 2, 12, game_info->houtput);
				printf("输入无效，请重新选择 (1 / 2): ");
				Locate_Cursor_Position((100 - 17) / 2, 14, game_info->houtput);
				system("pause");
				system("cls"); //清屏
			}
			
		}
		if (choice == 1)
		{
			system("cls"); //清屏

			int custom_length = 0;
			int custom_food_count = 0;
			//获取用户自定义的初始蛇长度
			while (custom_length < 3 || custom_length > 10)
			{
				Locate_Cursor_Position((100 - 25) / 2, 10, game_info->houtput);
				printf("请输入初始蛇长度 (3-10): ");
				scanf("%d", &custom_length);
				if (custom_length < 3 || custom_length > 10)
				{
					system("cls"); //清屏
					Locate_Cursor_Position((100 - 21) / 2, 12, game_info->houtput);
					printf("输入无效，请重新输入!");
					Locate_Cursor_Position((100 - 17) / 2, 14, game_info->houtput);
					system("pause");
					system("cls"); //清屏
				}
			}
			game_info->length = custom_length; //设置自定义蛇长度

			system("cls"); //清屏

			//获取用户自定义的食物数量
			while (custom_food_count < 1 || custom_food_count > 10)
			{
				Locate_Cursor_Position((100 - 23) / 2, 10, game_info->houtput);
				printf("请输入食物数量 (1-10): ");
				scanf("%d", &custom_food_count);
				if (custom_food_count < 1 || custom_food_count > 10)
				{
					system("cls"); //清屏
					Locate_Cursor_Position((100 - 21) / 2, 12, game_info->houtput);
					printf("输入无效，请重新输入!");
					Locate_Cursor_Position((100 - 17) / 2, 14, game_info->houtput);
					system("pause");
					system("cls"); //清屏
				}
			}
			game_info->food_count = custom_food_count; //设置自定义食物数量

			Game_Init(game_info); //游戏初始化
		}
		else
		{
			Game_Init(game_info); //游戏初始化
		}
	}
	

	//后续输出信息和提示代码待补充
}

//释放所有动态分配的内存
void Free_All_Dynamic_Memory(Maintain_Game_Information* game_info)
{
	//确保传入的指针不为空
	assert(game_info);
	//释放蛇身节点内存
	Single_Bnake_Body_Node* current = game_info->head;
	while (current)
	{
		//保存当前节点，移动到下一个节点，释放当前节点
		Single_Bnake_Body_Node* temp = current;
		current = current->next;
		free(temp);
	}
	game_info->head = NULL;
	game_info->tail = NULL;
	//释放食物节点内存
	Food_Node* food_current = game_info->food;
	while (food_current)
	{
		//保存当前节点，移动到下一个节点，释放当前节点
		Food_Node* temp = food_current;
		food_current = food_current->next;
		free(temp);
	}
	game_info->food = NULL;
	//恢复控制台光标可见
	game_info->cursor_info.bVisible = TRUE;
	//应用光标信息设置
	SetConsoleCursorInfo(game_info->houtput, &game_info->cursor_info);
	//清屏
	system("cls");
}