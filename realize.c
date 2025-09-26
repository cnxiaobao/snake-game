#include "realize.h"

//��behaviorΪ1ʱ����ʾ������������β��
//��behaviorΪ2ʱ����ʾ����ʳ������β��
void* Insert_Single_Bnake_Body_Node_At_Head(Maintain_Game_Information* game_info, int x, int y, int behavior)
{
	//ȷ�������ָ�벻Ϊ��
	assert(game_info);

	//��behaviorΪ1ʱ����ʾ������������β��
	if (behavior == 1)
	{
		//����һ���µ�����ڵ�
		Single_Bnake_Body_Node* new_node = (Single_Bnake_Body_Node*)malloc(sizeof(Single_Bnake_Body_Node));
		//ȷ���ڴ����ɹ�
		assert(new_node);
		new_node->x = x; //�����½ڵ��X����
		new_node->y = y; //�����½ڵ��Y����
		if (game_info->head == NULL)
		{
			game_info->head = new_node; //����ͷ�ڵ�Ϊ�½ڵ�
			new_node->next = NULL; //�½ڵ����һ���ڵ�Ϊ��
			game_info->tail = new_node; //����β�ڵ�Ϊ�½ڵ�
		}
		else
		{
			game_info->head->next = new_node; //����ǰβ�ڵ����һ���ڵ�ָ���½ڵ�
			game_info->head = new_node; //����ͷ�ڵ�Ϊ�½ڵ�
			new_node->next = NULL; //�½ڵ����һ���ڵ�Ϊ��
		}
		return new_node; //�����²���Ľڵ�
	}
	else if (behavior == 2) //��behaviorΪ2ʱ����ʾ����ʳ������β��
	{
		//����һ���µ�ʳ��ڵ�
		Food_Node* new_food = (Food_Node*)malloc(sizeof(Food_Node));
		//ȷ���ڴ����ɹ�
		assert(new_food);
		new_food->x = x; //�����½ڵ��X����
		new_food->y = y; //�����½ڵ��Y����
		if (game_info->food == NULL)
		{
			new_food->next = NULL; //�½ڵ����һ���ڵ�ָ��NULL
			game_info->food = new_food; //����ʳ������ͷΪ�½ڵ�
			game_info->food_tail = new_food; //����ʳ������βΪ�½ڵ�
		}
		else
		{
			game_info->food->next = new_food; //����ǰʳ������β�ڵ����һ���ڵ�ָ���½ڵ�
			game_info->food = new_food; //����ʳ������βΪ�½ڵ�
			new_food->next = NULL; //�½ڵ����һ���ڵ�ָ��NULL
		}
		
		return new_food; //�����²���Ľڵ�
	}
	else
	{
		//���behaviorֵ���Ϸ�������NULL
		return NULL;
	}
}

//����̨ˢ��
void Console_Refresh(Maintain_Game_Information* game_info)
{
	//ȷ�������ָ�벻Ϊ��
	assert(game_info);
	//����
	system("cls");
	//�ڿ���̨���Ͻ�ʹ�á��ء�����29*29�ĵ�ͼ�߽�
	for (int i = 0; i <= 29; i++)
	{
		for (int j = 0; j <= 29; j++)
		{
			if (i == 0 || i == 29 || j == 0 || j == 29)
			{
				Locate_Cursor_Position(j * 2, i, game_info->houtput); //ÿ���ַ����Ϊ2
				printf("��");
			}
		}
	}
	//��������
	Single_Bnake_Body_Node* current = game_info->tail;
	while (current)
	{
		Locate_Cursor_Position(current->x * 2, current->y, game_info->houtput); //ÿ���ַ����Ϊ2
		printf("��");
		current = current->next; //�ƶ�����һ���ڵ�
	}
	//����ʳ��
	Food_Node* food_current = game_info->food_tail;
	while (food_current)
	{
		Locate_Cursor_Position(food_current->x * 2, food_current->y, game_info->houtput); //ÿ���ַ����Ϊ2
		printf("��");
		food_current = food_current->next; //�ƶ�����һ���ڵ�
	}
	//���Ʒ�����������Ϣ
	Locate_Cursor_Position(60, 5, game_info->houtput);
	printf("����: %d", game_info->score);
	Locate_Cursor_Position(60, 7, game_info->houtput);
	printf("��ǰ�߳���: %d", game_info->length);
	Locate_Cursor_Position(60, 9, game_info->houtput);
	printf("��ǰʳ������: %d", game_info->food_count);
	Locate_Cursor_Position(60, 11, game_info->houtput);
	printf("��ǰ��Ϸ״̬: ");
	switch (game_info->state)
	{
	case NOT_START:
		printf("δ��ʼ");
		break;
	case NORMAL:
		printf("����");
		break;
	case PAUSE:
		printf("��ͣ");
		break;
	case KILL_BOUNDARY:
		printf("ײǽ");
	}
}

//��λ���λ��
void Locate_Cursor_Position(int x, int y, HANDLE houtput)
{
	//ȷ������̨�����Ϊ��
	assert(houtput);
	//����һ��COORD�ṹ��������ڴ洢���λ��
	COORD pos;
	pos.X = x; //����X����
	pos.Y = y; //����Y����
	//Ӧ�ÿ���̨���λ��
	SetConsoleCursorPosition(houtput, pos);
}

//���γ�ʼ��
void First_Init(Maintain_Game_Information* game_info)
{
	//ȷ�������ָ�벻Ϊ��
	assert(game_info);

	//���ػ�����̨
	setlocale(LC_ALL, "");

	//�������뻺����
	fflush(stdin);

	//��ʼ������̨����
	//���ÿ���̨���ڴ�СΪ100��30��
	system("mode con cols=100 lines=33"); 

	//��ȡ����̨���
	game_info->houtput = GetStdHandle(STD_OUTPUT_HANDLE); 
	//���ÿ���̨����
	SetConsoleTitleA("̰����С��Ϸ");
	//��ȡ����̨�����Ϣ
	GetConsoleCursorInfo(game_info->houtput, &game_info->cursor_info);
	//���ÿ���̨��겻�ɼ�
	game_info->cursor_info.bVisible = FALSE;
	//Ӧ�ù����Ϣ����
	SetConsoleCursorInfo(game_info->houtput, &game_info->cursor_info);
	
	//��ʼ����������
	game_info->head = NULL;
	game_info->tail = NULL;
	//��ʼ��ʳ������
	game_info->food = NULL;

	//������Ϸ��ʼ״̬
	game_info->length = 5;				//��ʼ�߳���Ϊ5
	game_info->dir = RIGHT;				//��ʼ��������
	game_info->state = NOT_START;		//������ϷΪδ��ʼ״̬
	game_info->food_count = 1;			//��ʼ�������1��ʳ��
	game_info->score = 0;				//��ʼ����Ϊ0
	game_info->sleep_time = 75;			//��ʼ��Ϣʱ��Ϊ75����
	game_info->is_game_over = false;	//��ʼ��Ϸδ����
}

//��Ϸ��ʼ��
void Game_Init(Maintain_Game_Information* game_info)
{
	//ȷ�������ָ�벻Ϊ��
	assert(game_info); 

	//��������
	for (int i = 0; i < game_info->length; i++)
	{
		//��Insert_Single_Bnake_Body_Node_At_Head����NULLʱ����ʾ����ʧ��
		if (!Insert_Single_Bnake_Body_Node_At_Head(game_info, 15 - i, 10, 1))
		{
			exit(-1); //����ʧ�ܣ��˳�����
		}
	}

	//����ʳ��
	for (int i = 0; i < game_info->food_count; i++)
	{
		int food_x = rand() % 26 + 1; //����1��27֮������X����
		int food_y = rand() % 26 + 1; //����1��27֮������Y����

		//�ж�ʳ��λ���Ƿ��������غϣ����غ�����������λ��
		while (true)
		{
			bool is_overlap = false; //����Ƿ��غ�
			Single_Bnake_Body_Node* current = game_info->head;
			while (current)
			{
				if (current->x == food_x && current->y == food_y)
				{
					is_overlap = true; //λ���غ�
					break;
				}
				current = current->next; //�ƶ�����һ���ڵ�
			}
			if (!is_overlap)
			{
				break; //λ�ò��غϣ�����ѭ��
			}
			//��������ʳ��λ��
			food_x = rand() % 26 + 1;
			food_y = rand() % 26 + 1;
		}

		//��Insert_Single_Bnake_Body_Node_At_Head����NULLʱ����ʾ����ʧ��
		if (!Insert_Single_Bnake_Body_Node_At_Head(game_info, food_x, food_y, 2))
		{
			exit(-1); //����ʧ�ܣ��˳�����
		}
	}

	game_info->state = NORMAL; //����Ϸ״̬����Ϊ����

	//ˢ�¿���̨��ʾ
	Console_Refresh(game_info);
}

//����̨�����Ϣ����ʾ
void Output_Information(Maintain_Game_Information* game_info)
{
	//ȷ�������ָ�벻Ϊ��
	assert(game_info);

	//����һ����Ϸʱ�������Ϸ˵��
	if (game_info->state == NOT_START)
	{
		Locate_Cursor_Position((100 - 22) / 2, 10, game_info->houtput);
		printf("��ӭ����̰����С��Ϸ!");
		Locate_Cursor_Position((100 - 68) / 2, 12, game_info->houtput);
		printf("��Ϸ˵��: ʹ�÷���������ߵ��ƶ����򣬳Ե�ʳ��������ӳ��Ⱥͷ�����");
		Locate_Cursor_Position((100 - 44) / 2, 14, game_info->houtput);
		printf("�� 'P' ����ͣ/������Ϸ���� 'Esc' ���˳���Ϸ��");
		Locate_Cursor_Position((100 - 19) / 2, 16, game_info->houtput);
		printf("���������ʼ��Ϸ...");
		_getch(); //�ȴ��û�����
		system("cls"); //����
		//ѯ���û��Ƿ���Ҫ�Զ����ʼ�߳�����ʳ������
		int choice = 0;
		while (choice != 1 && choice != 2)
		{
			
			Locate_Cursor_Position((100 - 36) / 2, 10, game_info->houtput);
			printf("�Ƿ��Զ����ʼ�߳�����ʳ��������");
			Locate_Cursor_Position((100 - 20) / 2, 12, game_info->houtput);
			printf("1. �� (Y / N)");
			Locate_Cursor_Position((100 - 20) / 2, 14, game_info->houtput);
			printf("2. �� (N / N)");
			Locate_Cursor_Position((100 - 21) / 2, 16, game_info->houtput);
			printf("��ѡ�� (1 / 2): ");
			scanf("%d", &choice);

			if (choice < 1 || choice>2)
			{
				system("cls"); //����
				Locate_Cursor_Position((100 - 25) / 2, 12, game_info->houtput);
				printf("������Ч��������ѡ�� (1 / 2): ");
				Locate_Cursor_Position((100 - 17) / 2, 14, game_info->houtput);
				system("pause");
				system("cls"); //����
			}
			
		}
		if (choice == 1)
		{
			system("cls"); //����

			int custom_length = 0;
			int custom_food_count = 0;
			//��ȡ�û��Զ���ĳ�ʼ�߳���
			while (custom_length < 3 || custom_length > 10)
			{
				Locate_Cursor_Position((100 - 25) / 2, 10, game_info->houtput);
				printf("�������ʼ�߳��� (3-10): ");
				scanf("%d", &custom_length);
				if (custom_length < 3 || custom_length > 10)
				{
					system("cls"); //����
					Locate_Cursor_Position((100 - 21) / 2, 12, game_info->houtput);
					printf("������Ч������������!");
					Locate_Cursor_Position((100 - 17) / 2, 14, game_info->houtput);
					system("pause");
					system("cls"); //����
				}
			}
			game_info->length = custom_length; //�����Զ����߳���

			system("cls"); //����

			//��ȡ�û��Զ����ʳ������
			while (custom_food_count < 1 || custom_food_count > 10)
			{
				Locate_Cursor_Position((100 - 23) / 2, 10, game_info->houtput);
				printf("������ʳ������ (1-10): ");
				scanf("%d", &custom_food_count);
				if (custom_food_count < 1 || custom_food_count > 10)
				{
					system("cls"); //����
					Locate_Cursor_Position((100 - 21) / 2, 12, game_info->houtput);
					printf("������Ч������������!");
					Locate_Cursor_Position((100 - 17) / 2, 14, game_info->houtput);
					system("pause");
					system("cls"); //����
				}
			}
			game_info->food_count = custom_food_count; //�����Զ���ʳ������

			Game_Init(game_info); //��Ϸ��ʼ��
		}
		else
		{
			Game_Init(game_info); //��Ϸ��ʼ��
		}
	}
	

	//���������Ϣ����ʾ���������
}

//�ͷ����ж�̬������ڴ�
void Free_All_Dynamic_Memory(Maintain_Game_Information* game_info)
{
	//ȷ�������ָ�벻Ϊ��
	assert(game_info);
	//�ͷ�����ڵ��ڴ�
	Single_Bnake_Body_Node* current = game_info->head;
	while (current)
	{
		//���浱ǰ�ڵ㣬�ƶ�����һ���ڵ㣬�ͷŵ�ǰ�ڵ�
		Single_Bnake_Body_Node* temp = current;
		current = current->next;
		free(temp);
	}
	game_info->head = NULL;
	game_info->tail = NULL;
	//�ͷ�ʳ��ڵ��ڴ�
	Food_Node* food_current = game_info->food;
	while (food_current)
	{
		//���浱ǰ�ڵ㣬�ƶ�����һ���ڵ㣬�ͷŵ�ǰ�ڵ�
		Food_Node* temp = food_current;
		food_current = food_current->next;
		free(temp);
	}
	game_info->food = NULL;
	//�ָ�����̨���ɼ�
	game_info->cursor_info.bVisible = TRUE;
	//Ӧ�ù����Ϣ����
	SetConsoleCursorInfo(game_info->houtput, &game_info->cursor_info);
	//����
	system("cls");
}