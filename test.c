#include "realize.h"

int main() 
{

	//��������ʼ����Ϸ��Ϣ�ṹ��
	Maintain_Game_Information game_info = { 0 };

	//��Ϸ���γ�ʼ��
	First_Init(&game_info);

	//����̨�����Ϣ����ʾ
	Output_Information(&game_info);

	do
	{
		switch (game_info.state)
		{

			case NORMAL://����״̬

				break;

			case PAUSE://��ͣ״̬

				break;

			case KILL_BOUNDARY://ײǽ״̬

				break;

			case KILL_SELF://ײ�Լ�״̬

				break;

			default:
				//����δ����״̬��������Ϸ
				game_info.is_game_over = true;
				break;
		}
	} while (!game_info.is_game_over);

	//�ͷ����ж�̬������ڴ�
	Free_All_Dynamic_Memory(&game_info);

	return 0;
}