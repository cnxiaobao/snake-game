#include "realize.h"

//当behavior为1时，表示插入蛇身链表头插
//当behavior为2时，表示插入食物链表尾插
//当behavior为3时，表示插入蛇身链表尾插
void* Insert_Single_Bnake_Body_Node_At_Head(Maintain_Game_Information* game_info, int x, int y, int behavior)
{
	//确保传入的指针不为空
	assert(game_info);

	//当behavior为1时，表示插入蛇身链表头插
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
			game_info->head = new_node; //更新蛇链表尾节点(蛇头)
			new_node->next = NULL; //新节点的下一个节点为空
			game_info->tail = new_node; //更新蛇链表头节点(蛇尾)
		}
		else
		{
			new_node->next = game_info->tail;
			game_info->tail = new_node; //更新蛇链表头节点(蛇尾)
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
	else if (behavior == 3) //当behavior为3时，表示插入蛇身链表尾插
	{
		//创建一个新的蛇身节点
		Single_Bnake_Body_Node* new_node = (Single_Bnake_Body_Node*)malloc(sizeof(Single_Bnake_Body_Node));
		//确保内存分配成功
		assert(new_node);
		new_node->x = x; //设置新节点的X坐标
		new_node->y = y; //设置新节点的Y坐标
		if (game_info->tail == NULL)
		{
			game_info->head = new_node; //更新蛇链表尾节点(蛇头)
			new_node->next = NULL; //新节点的下一个节点为空
			game_info->tail = new_node; //更新蛇链表头节点(蛇尾)
		}
		else
		{
			game_info->head->next = new_node; //将当前蛇链表尾节点(蛇头)的下一个节点指向新节点
			game_info->head = new_node; //更新蛇链表尾节点(蛇头)
			new_node->next = NULL; //新节点的下一个节点为空
		}
		return new_node; //返回新插入的节点
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
	
	//绘制食物
	Food_Node* food_current = game_info->food_tail;
	while (food_current)
	{
		Locate_Cursor_Position(food_current->x * 2, food_current->y, game_info->houtput); //每个字符宽度为2
		printf("※");
		food_current = food_current->next; //移动到下一个节点
	}

	//绘制蛇身蛇头为“○”蛇尾为“╳”
	Locate_Cursor_Position(game_info->head->x * 2, game_info->head->y, game_info->houtput); //每个字符宽度为2
	printf("○");
	Locate_Cursor_Position(game_info->tail->x * 2, game_info->tail->y, game_info->houtput); //每个字符宽度为2
	printf("╳");
	//绘制蛇身
	Single_Bnake_Body_Node* current = game_info->tail->next; //从蛇尾的下一个节点开始绘制
	while (current && current != game_info->head) //确保不绘制蛇头
	{
		Locate_Cursor_Position(current->x * 2, current->y, game_info->houtput); //每个字符宽度为2
		printf("◇");
		current = current->next; //移动到下一个节点
	}

	//绘制分数和其他信息
	Locate_Cursor_Position(60, 5, game_info->houtput);
	printf("分数: %d", game_info->score);
	Locate_Cursor_Position(60, 7, game_info->houtput);
	printf("当前蛇长度: %d", game_info->length);
	Locate_Cursor_Position(60, 9, game_info->houtput);
	printf("当前食物数量: %d", game_info->food_count);
	Locate_Cursor_Position(60, 11, game_info->houtput);
	printf("当前游戏速度: %dms", game_info->sleep_time);
	Locate_Cursor_Position(60, 13, game_info->houtput);
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
	Locate_Cursor_Position(60, 17, game_info->houtput);
	printf("使用f3加速,f4减速,速度越快分数越高");
	Locate_Cursor_Position(60, 19, game_info->houtput);
	printf("按 P 键暂停/继续游戏，按 Esc 键退出游戏");
	Locate_Cursor_Position(60, 23, game_info->houtput);
	printf("若输入无效,可尝试切换英文输入环境");
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

//蛇身移动
void Move_Snake_Body(Maintain_Game_Information* game_info)
{
	//确保传入的指针不为空
	assert(game_info);
	//创建一个新的蛇头节点，位置根据当前方向决定
	int new_head_x = game_info->head->x;
	int new_head_y = game_info->head->y;
	switch (game_info->dir)
	{
	case UP:
		new_head_y -= 1; //向上移动
		break;
	case DOWN:
		new_head_y += 1; //向下移动
		break;
	case LEFT:
		new_head_x -= 1; //向左移动
		break;
	case RIGHT:
		new_head_x += 1; //向右移动
		break;
	default:
		break;
	}
	//检查新蛇头位置是否撞墙
	if (new_head_x <= 0 || new_head_x >= 29 || new_head_y <= 0 || new_head_y >= 29)
	{
		game_info->state = KILL_BOUNDARY; //设置游戏状态为撞墙
		return;
	}
	//检查新蛇头位置是否撞到自己
	Single_Bnake_Body_Node* current = game_info->tail;
	while (current)
	{
		if (current->x == new_head_x && current->y == new_head_y)
		{
			game_info->state = KILL_SELF; //设置游戏状态为撞自己
			return;
		}
		current = current->next; //移动到下一个节点
	}
	
	//遍历食物链表，检查是否吃到食物
	Food_Node* food_current = game_info->food_tail;
	bool ate_food = false; //标记是否吃到食物
	while (food_current)
	{
		if (food_current->x == new_head_x && food_current->y == new_head_y)
		{
			ate_food = true; //标记吃到食物
			break;
		}
		food_current = food_current->next; //移动到下一个节点
	}

	//当ate_food为true时，表示吃到食物
	if (ate_food)
	{
		//更新分数
		game_info->score += 1; //每吃到一个食物，分数增加1

		if (!Insert_Single_Bnake_Body_Node_At_Head(game_info, new_head_x, new_head_y, 3)) //在蛇身链表头尾插新蛇头
		{
			Free_All_Dynamic_Memory(game_info); //释放所有动态分配的内存
			exit(-1); //插入失败，退出程序
		}

		//重新生成食物位置
		int food_x = rand() % 26 + 1; //生成1到27之间的随机X坐标
		int food_y = rand() % 26 + 1; //生成1到27之间的随机Y坐标
		//判断食物位置是否与蛇身重合，若重合则重新生成位置
		//判断食物位置是否与食物重合，若重合则重新生成位置
		while (true)
		{
			bool is_overlap = false; 

			//判断是否与蛇身重合
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

			//判断是否与食物重合
			Food_Node* food_current = game_info->food_tail;
			while (food_current)
			{
				if (food_current->x == food_x && food_current->y == food_y)
				{
					is_overlap = true; //位置重合
					break;
				}
				food_current = food_current->next; //移动到下一个节点
			}
			if (!is_overlap)
			{
				break; //位置不重合，跳出循环
			}
			//重新生成食物位置
			food_x = rand() % 26 + 1;
			food_y = rand() % 26 + 1;
		}
		//更新新食物位置
		food_current->x = food_x;
		food_current->y = food_y;
	}
	else//当ate_food为false时，表示未吃到食物
	{
		game_info->head->next = game_info->tail; //将当前蛇头的下一个节点指向蛇尾
		game_info->head = game_info->head->next; //更新蛇头为当前蛇头的下一个节点
		game_info->tail = game_info->tail->next; //更新蛇尾为当前蛇尾的下一个节点
		game_info->head->next = NULL;	 //将新的蛇头的下一个节点指向NULL

		game_info->head->x = new_head_x; //更新蛇头的X坐标
		game_info->head->y = new_head_y; //更新蛇头的Y坐标
	}
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

	//设置随机数种子
	srand((unsigned int)time(NULL));

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
	game_info->last_update_time = GetTickCount64();			//获取当前时间
	game_info->current_time = game_info->last_update_time;	//设置当前时间为上一次更新时间

	game_info->length = 5;				//初始蛇长度为5
	game_info->dir = RIGHT;				//初始方向向右
	game_info->next_dir = RIGHT;		//初始下次更新方向向右
	game_info->state = NOT_START;		//设置游戏为未开始状态
	game_info->food_count = 1;			//初始允许存在1个食物
	game_info->score = 0;				//初始分数为0
	game_info->sleep_time = 500;		//初始休息时间为500毫秒
	game_info->is_game_over = false;	//初始游戏未结束
}

//游戏初始化
void Game_Init(Maintain_Game_Information* game_info)
{
	//确保传入的指针不为空
	assert(game_info); 

	Free_All_Dynamic_Memory(game_info);//释放之前的动态内存，防止内存泄漏

	fflush(stdin);//清理输入缓冲区

	//创建蛇身
	for (int i = 0; i < game_info->length; i++)
	{
		//当Insert_Single_Bnake_Body_Node_At_Head返回NULL时，表示插入失败
		if (!Insert_Single_Bnake_Body_Node_At_Head(game_info, 15 - i, 10, 1))
		{
			Free_All_Dynamic_Memory(game_info);//释放所有动态分配的内存
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
			Free_All_Dynamic_Memory(game_info);//释放所有动态分配的内存
			exit(-1); //插入失败，退出程序
		}
	}

	//设置游始状态
	game_info->last_update_time = GetTickCount64();			//获取当前时间
	game_info->current_time = game_info->last_update_time;	//设置当前时间为上一次更新时间

	game_info->dir = RIGHT;				//初始方向向右
	game_info->next_dir = RIGHT;		//初始下次更新方向向右
	game_info->score = 0;				//初始分数为0
	game_info->sleep_time = 500;		//初始休息时间为500毫秒
	game_info->is_game_over = false;	//初始游戏未结束
	game_info->state = NORMAL;			//将游戏状态设置为正常

	GetAsyncKeyState(VK_ESCAPE);		//清理ESC键输入缓冲区

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
		printf("按 P 键暂停/继续游戏，按 Esc 键退出游戏。");
		Locate_Cursor_Position((100 - 19) / 2, 16, game_info->houtput);
		printf("按任意键开始游戏...");
		_getch(); //等待用户按键
		system("cls"); //清屏
		//询问用户是否需要自定义初始蛇长度与食物数量
		int choice = 0;
		while (choice != 1 && choice != 2)
		{

			Locate_Cursor_Position((100 - 32) / 2, 10, game_info->houtput);
			printf("是否自定义初始蛇长度与食物数量？");
			Locate_Cursor_Position((100 - 5) / 2, 12, game_info->houtput);
			printf("1. 是");
			Locate_Cursor_Position((100 - 5) / 2, 14, game_info->houtput);
			printf("2. 否");
			Locate_Cursor_Position((100 - 15) / 2, 16, game_info->houtput);
			printf("请输入 (1 / 2): ");
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
	//正常状态
	else if (game_info->state == NORMAL)
	{

		if (GetAsyncKeyState(0x50)) //按P键暂停
		{
			game_info->state = PAUSE;

			//刷新控制台显示	
			Console_Refresh(game_info);

			Locate_Cursor_Position(60, 27, game_info->houtput);
			printf("游戏已暂停");
			Locate_Cursor_Position(60, 28, game_info->houtput);
			printf("按 P 键继续游戏，按 Esc 键退出游戏");

			//延迟，防止按键过快导致状态切换错误
			Sleep(300);
			return;
		}
		
		if (GetAsyncKeyState(VK_ESCAPE)) //按Esc键退出
		{
			game_info->is_game_over = true;

			Free_All_Dynamic_Memory(game_info);//释放所有动态分配的内存
			Locate_Cursor_Position((100 - 12) / 2, 15, game_info->houtput);
			printf("游戏已退出");
			Locate_Cursor_Position((100 - 21) / 2, 17, game_info->houtput);
			printf("感谢您的游玩，欢迎下次再来!");
	
			exit(0); //退出程序
		}

		//蛇的下一次移动方向控制
		switch (game_info->dir)
		{
			case UP:
				if (GetAsyncKeyState(VK_LEFT))
				{
					game_info->next_dir = LEFT;
					//清理其他三个方向的按键缓存
					GetAsyncKeyState(VK_UP);
					GetAsyncKeyState(VK_DOWN);
					GetAsyncKeyState(VK_RIGHT);
				}
				if (GetAsyncKeyState(VK_RIGHT))
				{
					game_info->next_dir = RIGHT;
					//清理其他三个方向的按键缓存
					GetAsyncKeyState(VK_UP);
					GetAsyncKeyState(VK_DOWN);
					GetAsyncKeyState(VK_LEFT);
				}
				break;

			case DOWN:
				if (GetAsyncKeyState(VK_LEFT))
				{
					game_info->next_dir = LEFT;
					//清理其他三个方向的按键缓存
					GetAsyncKeyState(VK_UP);
					GetAsyncKeyState(VK_DOWN);
					GetAsyncKeyState(VK_RIGHT);
				}
				if (GetAsyncKeyState(VK_RIGHT))
				{
					game_info->next_dir = RIGHT;
					//清理其他三个方向的按键缓存
					GetAsyncKeyState(VK_UP);
					GetAsyncKeyState(VK_DOWN);
					GetAsyncKeyState(VK_LEFT);
				}
				break;

			case LEFT:
				if (GetAsyncKeyState(VK_UP))
				{
					game_info->next_dir = UP;
					//清理其他三个方向的按键缓存
					GetAsyncKeyState(VK_LEFT);
					GetAsyncKeyState(VK_DOWN);
					GetAsyncKeyState(VK_RIGHT);
				}
				else if (GetAsyncKeyState(VK_DOWN))
				{
					game_info->next_dir = DOWN;
					//清理其他三个方向的按键缓存
					GetAsyncKeyState(VK_LEFT);
					GetAsyncKeyState(VK_UP);
					GetAsyncKeyState(VK_RIGHT);
				}
				break;

			case RIGHT:
				if (GetAsyncKeyState(VK_UP))
				{
					game_info->next_dir = UP;
					//清理其他三个方向的按键缓存
					GetAsyncKeyState(VK_LEFT);
					GetAsyncKeyState(VK_DOWN);
					GetAsyncKeyState(VK_RIGHT);
				}
				else if (GetAsyncKeyState(VK_DOWN))
				{
					game_info->next_dir = DOWN;
					//清理其他三个方向的按键缓存
					GetAsyncKeyState(VK_LEFT);
					GetAsyncKeyState(VK_UP);
					GetAsyncKeyState(VK_RIGHT);
				}
				break;

		default:
			break;
		}

		game_info->current_time = GetTickCount64(); //获取当前时间

		//检查是否达到移动时间间隔
		if (game_info->current_time - game_info->last_update_time >= (ULONGLONG)game_info->sleep_time)
		{


			//速度控制
			if (GetAsyncKeyState(VK_F3)) //按F3加速
			{
				if (game_info->sleep_time > 100)
				{
					game_info->sleep_time -= 100;
				}
			}
			else if (GetAsyncKeyState(VK_F4)) //按F4减速
			{
				if (game_info->sleep_time < 1000)
				{
					game_info->sleep_time += 100;
				}
			}

			//更新蛇头方向
			game_info->dir = game_info->next_dir;
			//移动蛇身
			Move_Snake_Body(game_info);
			//更新时间
			game_info->last_update_time = game_info->current_time;
			//刷新控制台显示	
			Console_Refresh(game_info);
		}
	}
	//蛇撞墙或撞自己状态
	else if (game_info->state == KILL_BOUNDARY || game_info->state == KILL_SELF)
	{
		//提示游戏结束，并询问用户是否重新开始游戏
		Locate_Cursor_Position(26, 12, game_info->houtput);
		printf("游戏结束!");
		Locate_Cursor_Position(11, 15, game_info->houtput);
		printf("按 R 键重新开始游戏，按 Esc 键退出游戏");

		//清除按键缓存
		GetAsyncKeyState(0x52); 
		GetAsyncKeyState(VK_ESCAPE);

		while (true)
		{
			if (GetAsyncKeyState(0x52)) //按R键重新开始
			{
				game_info->state = NOT_START; //将游戏状态设置为未开始

				system("cls"); //清屏

				//清理输入缓冲区
				fflush(stdin);

				//清理所有输入缓存
				while (kbhit())
				{
					getch();
				}
				return;
			}
			if (GetAsyncKeyState(VK_ESCAPE)) //按Esc键退出
			{
				game_info->is_game_over = true;
				Free_All_Dynamic_Memory(game_info);//释放所有动态分配的内存
				Locate_Cursor_Position((100 - 10) / 2, 15, game_info->houtput);
				printf("游戏已退出");
				Locate_Cursor_Position((100 - 28) / 2, 17, game_info->houtput);
				printf("感谢您的游玩，欢迎下次再来!");
				Locate_Cursor_Position(0, 28, game_info->houtput);
				exit(0); //退出程序
			}
		}
	}
}

//释放所有动态分配的内存
void Free_All_Dynamic_Memory(Maintain_Game_Information* game_info)
{
	//确保传入的指针不为空
	assert(game_info);
	//释放蛇身节点内存
	Single_Bnake_Body_Node* current = game_info->tail;
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
	Food_Node* food_current = game_info->food_tail;
	while (food_current)
	{
		//保存当前节点，移动到下一个节点，释放当前节点
		Food_Node* temp = food_current;
		food_current = food_current->next;
		free(temp);
	}
	game_info->food = NULL;
	game_info->food_tail = NULL;

	//清屏
	system("cls");
}