#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <locale.h>
#include <stdbool.h>
#include <assert.h>
#include <time.h>

//定义方向枚举
enum Direction
{
	UP = 1,	//上
	DOWN,	//下
	LEFT,	//左
	RIGHT	//右
};

//定义游戏状态枚举
enum Game_State
{
	NOT_START = 0,	//未开始状态
	NORMAL,			//正常状态
	PAUSE,			//暂停状态
	KILL_BOUNDARY,	//撞墙状态
	KILL_SELF		//撞自己状态
};

//定义蛇身节点
typedef struct Single_Bnake_Body_Node
{
	//单一蛇身节点在控制台中的位置
	int x;
	int y;

	//指向下一个蛇身的节点
	struct Single_Bnake_Body_Node* next;
}Single_Bnake_Body_Node;

//定义食物节点
typedef struct Food_Node
{
	//食物在控制台中的位置
	int x;
	int y;

	//指向下一个食物节点
	struct Food_Node* next;
}Food_Node;

//定义维护游戏信息的结构体
typedef struct Maintain_Game_Information
{
	Single_Bnake_Body_Node* head;		//蛇头节点
	Single_Bnake_Body_Node* tail;		//蛇尾节点
	int length;							//初始蛇身长度
	enum Direction dir;					//蛇头方向
	Food_Node* food;					//食物头节点
	Food_Node* food_tail;				//食物尾节点
	int food_count;						//允许存在的食物数量
	int score;							//分数
	enum Game_State state;				//游戏状态
	int sleep_time;						//休息时间,单位毫秒,控制游戏速度,值越小速度越快,初始值75
	bool is_game_over;					//是否结束游戏
	HANDLE houtput;						//控制台句柄
	CONSOLE_CURSOR_INFO cursor_info;	//控制台光标信息
}Maintain_Game_Information;

//各种链表头尾插入
void* Insert_Single_Bnake_Body_Node_At_Head(Maintain_Game_Information* game_info, int x, int y,int behavior);

//控制台刷新
void Console_Refresh(Maintain_Game_Information* game_info);

//定位光标位置
void Locate_Cursor_Position(int x, int y, HANDLE houtput);

//初次初始化
void First_Init(Maintain_Game_Information* game_info);

//游戏初始化
void Game_Init(Maintain_Game_Information* game_info);

//控制台输出信息和提示
void Output_Information(Maintain_Game_Information* game_info);

//释放所有动态分配的内存
void Free_All_Dynamic_Memory(Maintain_Game_Information* game_info);