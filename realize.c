#include "realize.h"

//��behaviorΪ1ʱ����ʾ������������ͷ��
//��behaviorΪ2ʱ����ʾ����ʳ������β��
//��behaviorΪ3ʱ����ʾ������������β��
void* Insert_Single_Bnake_Body_Node_At_Head(Maintain_Game_Information* game_info, int x, int y, int behavior)
{
	//ȷ�������ָ�벻Ϊ��
	assert(game_info);

	//��behaviorΪ1ʱ����ʾ������������ͷ��
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
			game_info->head = new_node; //����������β�ڵ�(��ͷ)
			new_node->next = NULL; //�½ڵ����һ���ڵ�Ϊ��
			game_info->tail = new_node; //����������ͷ�ڵ�(��β)
		}
		else
		{
			new_node->next = game_info->tail;
			game_info->tail = new_node; //����������ͷ�ڵ�(��β)
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
	else if (behavior == 3) //��behaviorΪ3ʱ����ʾ������������β��
	{
		//����һ���µ�����ڵ�
		Single_Bnake_Body_Node* new_node = (Single_Bnake_Body_Node*)malloc(sizeof(Single_Bnake_Body_Node));
		//ȷ���ڴ����ɹ�
		assert(new_node);
		new_node->x = x; //�����½ڵ��X����
		new_node->y = y; //�����½ڵ��Y����
		if (game_info->tail == NULL)
		{
			game_info->head = new_node; //����������β�ڵ�(��ͷ)
			new_node->next = NULL; //�½ڵ����һ���ڵ�Ϊ��
			game_info->tail = new_node; //����������ͷ�ڵ�(��β)
		}
		else
		{
			game_info->head->next = new_node; //����ǰ������β�ڵ�(��ͷ)����һ���ڵ�ָ���½ڵ�
			game_info->head = new_node; //����������β�ڵ�(��ͷ)
			new_node->next = NULL; //�½ڵ����һ���ڵ�Ϊ��
		}
		return new_node; //�����²���Ľڵ�
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
	
	//����ʳ��
	Food_Node* food_current = game_info->food_tail;
	while (food_current)
	{
		Locate_Cursor_Position(food_current->x * 2, food_current->y, game_info->houtput); //ÿ���ַ����Ϊ2
		printf("��");
		food_current = food_current->next; //�ƶ�����һ���ڵ�
	}

	//����������ͷΪ������βΪ���w��
	Locate_Cursor_Position(game_info->head->x * 2, game_info->head->y, game_info->houtput); //ÿ���ַ����Ϊ2
	printf("��");
	Locate_Cursor_Position(game_info->tail->x * 2, game_info->tail->y, game_info->houtput); //ÿ���ַ����Ϊ2
	printf("�w");
	//��������
	Single_Bnake_Body_Node* current = game_info->tail->next; //����β����һ���ڵ㿪ʼ����
	while (current && current != game_info->head) //ȷ����������ͷ
	{
		Locate_Cursor_Position(current->x * 2, current->y, game_info->houtput); //ÿ���ַ����Ϊ2
		printf("��");
		current = current->next; //�ƶ�����һ���ڵ�
	}

	//���Ʒ�����������Ϣ
	Locate_Cursor_Position(60, 5, game_info->houtput);
	printf("����: %d", game_info->score);
	Locate_Cursor_Position(60, 7, game_info->houtput);
	printf("��ǰ�߳���: %d", game_info->length);
	Locate_Cursor_Position(60, 9, game_info->houtput);
	printf("��ǰʳ������: %d", game_info->food_count);
	Locate_Cursor_Position(60, 11, game_info->houtput);
	printf("��ǰ��Ϸ�ٶ�: %dms", game_info->sleep_time);
	Locate_Cursor_Position(60, 13, game_info->houtput);
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
	Locate_Cursor_Position(60, 17, game_info->houtput);
	printf("ʹ��f3����,f4����,�ٶ�Խ�����Խ��");
	Locate_Cursor_Position(60, 19, game_info->houtput);
	printf("�� P ����ͣ/������Ϸ���� Esc ���˳���Ϸ");
	Locate_Cursor_Position(60, 23, game_info->houtput);
	printf("��������Ч,�ɳ����л�Ӣ�����뻷��");
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

//�����ƶ�
void Move_Snake_Body(Maintain_Game_Information* game_info)
{
	//ȷ�������ָ�벻Ϊ��
	assert(game_info);
	//����һ���µ���ͷ�ڵ㣬λ�ø��ݵ�ǰ�������
	int new_head_x = game_info->head->x;
	int new_head_y = game_info->head->y;
	switch (game_info->dir)
	{
	case UP:
		new_head_y -= 1; //�����ƶ�
		break;
	case DOWN:
		new_head_y += 1; //�����ƶ�
		break;
	case LEFT:
		new_head_x -= 1; //�����ƶ�
		break;
	case RIGHT:
		new_head_x += 1; //�����ƶ�
		break;
	default:
		break;
	}
	//�������ͷλ���Ƿ�ײǽ
	if (new_head_x <= 0 || new_head_x >= 29 || new_head_y <= 0 || new_head_y >= 29)
	{
		game_info->state = KILL_BOUNDARY; //������Ϸ״̬Ϊײǽ
		return;
	}
	//�������ͷλ���Ƿ�ײ���Լ�
	Single_Bnake_Body_Node* current = game_info->tail;
	while (current)
	{
		if (current->x == new_head_x && current->y == new_head_y)
		{
			game_info->state = KILL_SELF; //������Ϸ״̬Ϊײ�Լ�
			return;
		}
		current = current->next; //�ƶ�����һ���ڵ�
	}
	
	//����ʳ����������Ƿ�Ե�ʳ��
	Food_Node* food_current = game_info->food_tail;
	bool ate_food = false; //����Ƿ�Ե�ʳ��
	while (food_current)
	{
		if (food_current->x == new_head_x && food_current->y == new_head_y)
		{
			ate_food = true; //��ǳԵ�ʳ��
			break;
		}
		food_current = food_current->next; //�ƶ�����һ���ڵ�
	}

	//��ate_foodΪtrueʱ����ʾ�Ե�ʳ��
	if (ate_food)
	{
		//���·���
		game_info->score += 1; //ÿ�Ե�һ��ʳ���������1

		if (!Insert_Single_Bnake_Body_Node_At_Head(game_info, new_head_x, new_head_y, 3)) //����������ͷβ������ͷ
		{
			Free_All_Dynamic_Memory(game_info); //�ͷ����ж�̬������ڴ�
			exit(-1); //����ʧ�ܣ��˳�����
		}

		//��������ʳ��λ��
		int food_x = rand() % 26 + 1; //����1��27֮������X����
		int food_y = rand() % 26 + 1; //����1��27֮������Y����
		//�ж�ʳ��λ���Ƿ��������غϣ����غ�����������λ��
		//�ж�ʳ��λ���Ƿ���ʳ���غϣ����غ�����������λ��
		while (true)
		{
			bool is_overlap = false; 

			//�ж��Ƿ��������غ�
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

			//�ж��Ƿ���ʳ���غ�
			Food_Node* food_current = game_info->food_tail;
			while (food_current)
			{
				if (food_current->x == food_x && food_current->y == food_y)
				{
					is_overlap = true; //λ���غ�
					break;
				}
				food_current = food_current->next; //�ƶ�����һ���ڵ�
			}
			if (!is_overlap)
			{
				break; //λ�ò��غϣ�����ѭ��
			}
			//��������ʳ��λ��
			food_x = rand() % 26 + 1;
			food_y = rand() % 26 + 1;
		}
		//������ʳ��λ��
		food_current->x = food_x;
		food_current->y = food_y;
	}
	else//��ate_foodΪfalseʱ����ʾδ�Ե�ʳ��
	{
		game_info->head->next = game_info->tail; //����ǰ��ͷ����һ���ڵ�ָ����β
		game_info->head = game_info->head->next; //������ͷΪ��ǰ��ͷ����һ���ڵ�
		game_info->tail = game_info->tail->next; //������βΪ��ǰ��β����һ���ڵ�
		game_info->head->next = NULL;	 //���µ���ͷ����һ���ڵ�ָ��NULL

		game_info->head->x = new_head_x; //������ͷ��X����
		game_info->head->y = new_head_y; //������ͷ��Y����
	}
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

	//�������������
	srand((unsigned int)time(NULL));

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
	game_info->last_update_time = GetTickCount64();			//��ȡ��ǰʱ��
	game_info->current_time = game_info->last_update_time;	//���õ�ǰʱ��Ϊ��һ�θ���ʱ��

	game_info->length = 5;				//��ʼ�߳���Ϊ5
	game_info->dir = RIGHT;				//��ʼ��������
	game_info->next_dir = RIGHT;		//��ʼ�´θ��·�������
	game_info->state = NOT_START;		//������ϷΪδ��ʼ״̬
	game_info->food_count = 1;			//��ʼ�������1��ʳ��
	game_info->score = 0;				//��ʼ����Ϊ0
	game_info->sleep_time = 500;		//��ʼ��Ϣʱ��Ϊ500����
	game_info->is_game_over = false;	//��ʼ��Ϸδ����
}

//��Ϸ��ʼ��
void Game_Init(Maintain_Game_Information* game_info)
{
	//ȷ�������ָ�벻Ϊ��
	assert(game_info); 

	Free_All_Dynamic_Memory(game_info);//�ͷ�֮ǰ�Ķ�̬�ڴ棬��ֹ�ڴ�й©

	fflush(stdin);//�������뻺����

	//��������
	for (int i = 0; i < game_info->length; i++)
	{
		//��Insert_Single_Bnake_Body_Node_At_Head����NULLʱ����ʾ����ʧ��
		if (!Insert_Single_Bnake_Body_Node_At_Head(game_info, 15 - i, 10, 1))
		{
			Free_All_Dynamic_Memory(game_info);//�ͷ����ж�̬������ڴ�
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
			Free_All_Dynamic_Memory(game_info);//�ͷ����ж�̬������ڴ�
			exit(-1); //����ʧ�ܣ��˳�����
		}
	}

	//������ʼ״̬
	game_info->last_update_time = GetTickCount64();			//��ȡ��ǰʱ��
	game_info->current_time = game_info->last_update_time;	//���õ�ǰʱ��Ϊ��һ�θ���ʱ��

	game_info->dir = RIGHT;				//��ʼ��������
	game_info->next_dir = RIGHT;		//��ʼ�´θ��·�������
	game_info->score = 0;				//��ʼ����Ϊ0
	game_info->sleep_time = 500;		//��ʼ��Ϣʱ��Ϊ500����
	game_info->is_game_over = false;	//��ʼ��Ϸδ����
	game_info->state = NORMAL;			//����Ϸ״̬����Ϊ����

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
		printf("�� P ����ͣ/������Ϸ���� Esc ���˳���Ϸ��");
		Locate_Cursor_Position((100 - 19) / 2, 16, game_info->houtput);
		printf("���������ʼ��Ϸ...");
		_getch(); //�ȴ��û�����
		system("cls"); //����
		//ѯ���û��Ƿ���Ҫ�Զ����ʼ�߳�����ʳ������
		int choice = 0;
		while (choice != 1 && choice != 2)
		{

			Locate_Cursor_Position((100 - 32) / 2, 10, game_info->houtput);
			printf("�Ƿ��Զ����ʼ�߳�����ʳ��������");
			Locate_Cursor_Position((100 - 5) / 2, 12, game_info->houtput);
			printf("1. ��");
			Locate_Cursor_Position((100 - 5) / 2, 14, game_info->houtput);
			printf("2. ��");
			Locate_Cursor_Position((100 - 15) / 2, 16, game_info->houtput);
			printf("������ (1 / 2): ");
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
	else if (game_info->state == NORMAL)//����״̬
	{

		if (GetAsyncKeyState(0x50)) //��P����ͣ
		{
			game_info->state = PAUSE;

			//ˢ�¿���̨��ʾ	
			Console_Refresh(game_info);

			Locate_Cursor_Position(60, 27, game_info->houtput);
			printf("��Ϸ����ͣ");
			Locate_Cursor_Position(60, 28, game_info->houtput);
			printf("�� P ��������Ϸ���� Esc ���˳���Ϸ");

			//�ӳ٣���ֹ�������쵼��״̬�л�����
			Sleep(300);
			return;
		}
		
		if (GetAsyncKeyState(VK_ESCAPE)) //��Esc���˳�
		{
			game_info->is_game_over = true;

			Free_All_Dynamic_Memory(game_info);//�ͷ����ж�̬������ڴ�
			Locate_Cursor_Position((100 - 12) / 2, 15, game_info->houtput);
			printf("��Ϸ���˳�");
			Locate_Cursor_Position((100 - 21) / 2, 17, game_info->houtput);
			printf("��л�������棬��ӭ�´�����!");
	
			exit(0); //�˳�����
		}

		//�ߵ���һ���ƶ��������
		switch (game_info->dir)
		{
			case UP:
				if (GetAsyncKeyState(VK_LEFT))
				{
					game_info->next_dir = LEFT;
					//����������������İ�������
					GetAsyncKeyState(VK_UP);
					GetAsyncKeyState(VK_DOWN);
					GetAsyncKeyState(VK_RIGHT);
				}
				if (GetAsyncKeyState(VK_RIGHT))
				{
					game_info->next_dir = RIGHT;
					//����������������İ�������
					GetAsyncKeyState(VK_UP);
					GetAsyncKeyState(VK_DOWN);
					GetAsyncKeyState(VK_LEFT);
				}
				break;

			case DOWN:
				if (GetAsyncKeyState(VK_LEFT))
				{
					game_info->next_dir = LEFT;
					//����������������İ�������
					GetAsyncKeyState(VK_UP);
					GetAsyncKeyState(VK_DOWN);
					GetAsyncKeyState(VK_RIGHT);
				}
				if (GetAsyncKeyState(VK_RIGHT))
				{
					game_info->next_dir = RIGHT;
					//����������������İ�������
					GetAsyncKeyState(VK_UP);
					GetAsyncKeyState(VK_DOWN);
					GetAsyncKeyState(VK_LEFT);
				}
				break;

			case LEFT:
				if (GetAsyncKeyState(VK_UP))
				{
					game_info->next_dir = UP;
					//����������������İ�������
					GetAsyncKeyState(VK_LEFT);
					GetAsyncKeyState(VK_DOWN);
					GetAsyncKeyState(VK_RIGHT);
				}
				else if (GetAsyncKeyState(VK_DOWN))
				{
					game_info->next_dir = DOWN;
					//����������������İ�������
					GetAsyncKeyState(VK_LEFT);
					GetAsyncKeyState(VK_UP);
					GetAsyncKeyState(VK_RIGHT);
				}
				break;

			case RIGHT:
				if (GetAsyncKeyState(VK_UP))
				{
					game_info->next_dir = UP;
					//����������������İ�������
					GetAsyncKeyState(VK_LEFT);
					GetAsyncKeyState(VK_DOWN);
					GetAsyncKeyState(VK_RIGHT);
				}
				else if (GetAsyncKeyState(VK_DOWN))
				{
					game_info->next_dir = DOWN;
					//����������������İ�������
					GetAsyncKeyState(VK_LEFT);
					GetAsyncKeyState(VK_UP);
					GetAsyncKeyState(VK_RIGHT);
				}
				break;

		default:
			break;
		}

		game_info->current_time = GetTickCount64(); //��ȡ��ǰʱ��

		//����Ƿ�ﵽ�ƶ�ʱ����
		if (game_info->current_time - game_info->last_update_time >= (ULONGLONG)game_info->sleep_time)
		{
			//�ٶȿ���
			if (GetAsyncKeyState(VK_F3)) //��F3����
			{
				if (game_info->sleep_time > 100)
				{
					game_info->sleep_time -= 100;
				}
			}
			else if (GetAsyncKeyState(VK_F4)) //��F4����
			{
				if (game_info->sleep_time < 1000)
				{
					game_info->sleep_time += 100;
				}
			}

			//������ͷ����
			game_info->dir = game_info->next_dir;
			//�ƶ�����
			Move_Snake_Body(game_info);
			//����ʱ��
			game_info->last_update_time = game_info->current_time;
			//ˢ�¿���̨��ʾ	
			Console_Refresh(game_info);
		}
	}
	else if (game_info->state == KILL_BOUNDARY || game_info->state == KILL_SELF)//��ײǽ��ײ�Լ�״̬
	{
		//��ʾ��Ϸ��������ѯ���û��Ƿ����¿�ʼ��Ϸ
		Locate_Cursor_Position(26, 12, game_info->houtput);
		printf("��Ϸ����!");
		Locate_Cursor_Position(11, 15, game_info->houtput);
		printf("�� R �����¿�ʼ��Ϸ���� Esc ���˳���Ϸ");

		//�����������
		GetAsyncKeyState(0x52); 
		GetAsyncKeyState(VK_ESCAPE);

		while (true)
		{
			if (GetAsyncKeyState(0x52)) //��R�����¿�ʼ
			{
				game_info->state = NOT_START; //����Ϸ״̬����Ϊδ��ʼ

				system("cls"); //����

				//�������뻺����
				fflush(stdin);

				//�����������뻺��
				while (kbhit())
				{
					getch();
				}
				return;
			}
			if (GetAsyncKeyState(VK_ESCAPE)) //��Esc���˳�
			{
				game_info->is_game_over = true;
				Free_All_Dynamic_Memory(game_info);//�ͷ����ж�̬������ڴ�
				Locate_Cursor_Position((100 - 10) / 2, 15, game_info->houtput);
				printf("��Ϸ���˳�");
				Locate_Cursor_Position((100 - 28) / 2, 17, game_info->houtput);
				printf("��л�������棬��ӭ�´�����!");
				Locate_Cursor_Position(0, 28, game_info->houtput);
				exit(0); //�˳�����
			}
		}
	}
}

//�ͷ����ж�̬������ڴ�
void Free_All_Dynamic_Memory(Maintain_Game_Information* game_info)
{
	//ȷ�������ָ�벻Ϊ��
	assert(game_info);
	//�ͷ�����ڵ��ڴ�
	Single_Bnake_Body_Node* current = game_info->tail;
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
	Food_Node* food_current = game_info->food_tail;
	while (food_current)
	{
		//���浱ǰ�ڵ㣬�ƶ�����һ���ڵ㣬�ͷŵ�ǰ�ڵ�
		Food_Node* temp = food_current;
		food_current = food_current->next;
		free(temp);
	}
	game_info->food = NULL;
	game_info->food_tail = NULL;

	//����
	system("cls");
}