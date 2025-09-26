#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <locale.h>
#include <stdbool.h>
#include <assert.h>
#include <time.h>

//���巽��ö��
enum Direction
{
	UP = 1,	//��
	DOWN,	//��
	LEFT,	//��
	RIGHT	//��
};

//������Ϸ״̬ö��
enum Game_State
{
	NOT_START = 0,	//δ��ʼ״̬
	NORMAL,			//����״̬
	PAUSE,			//��ͣ״̬
	KILL_BOUNDARY,	//ײǽ״̬
	KILL_SELF		//ײ�Լ�״̬
};

//��������ڵ�
typedef struct Single_Bnake_Body_Node
{
	//��һ����ڵ��ڿ���̨�е�λ��
	int x;
	int y;

	//ָ����һ������Ľڵ�
	struct Single_Bnake_Body_Node* next;
}Single_Bnake_Body_Node;

//����ʳ��ڵ�
typedef struct Food_Node
{
	//ʳ���ڿ���̨�е�λ��
	int x;
	int y;

	//ָ����һ��ʳ��ڵ�
	struct Food_Node* next;
}Food_Node;

//����ά����Ϸ��Ϣ�Ľṹ��
typedef struct Maintain_Game_Information
{
	Single_Bnake_Body_Node* head;		//��ͷ�ڵ�
	Single_Bnake_Body_Node* tail;		//��β�ڵ�
	int length;							//��ʼ������
	enum Direction dir;					//��ͷ����
	Food_Node* food;					//ʳ��ͷ�ڵ�
	Food_Node* food_tail;				//ʳ��β�ڵ�
	int food_count;						//������ڵ�ʳ������
	int score;							//����
	enum Game_State state;				//��Ϸ״̬
	int sleep_time;						//��Ϣʱ��,��λ����,������Ϸ�ٶ�,ֵԽС�ٶ�Խ��,��ʼֵ75
	bool is_game_over;					//�Ƿ������Ϸ
	HANDLE houtput;						//����̨���
	CONSOLE_CURSOR_INFO cursor_info;	//����̨�����Ϣ
}Maintain_Game_Information;

//��������ͷβ����
void* Insert_Single_Bnake_Body_Node_At_Head(Maintain_Game_Information* game_info, int x, int y,int behavior);

//����̨ˢ��
void Console_Refresh(Maintain_Game_Information* game_info);

//��λ���λ��
void Locate_Cursor_Position(int x, int y, HANDLE houtput);

//���γ�ʼ��
void First_Init(Maintain_Game_Information* game_info);

//��Ϸ��ʼ��
void Game_Init(Maintain_Game_Information* game_info);

//����̨�����Ϣ����ʾ
void Output_Information(Maintain_Game_Information* game_info);

//�ͷ����ж�̬������ڴ�
void Free_All_Dynamic_Memory(Maintain_Game_Information* game_info);