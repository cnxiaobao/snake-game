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
			case NOT_START://δ��ʼ״̬
			case NORMAL://����״̬
			case KILL_BOUNDARY://ײǽ״̬
			case KILL_SELF://ײ�Լ�״̬
				Output_Information(&game_info);
				break;

			case PAUSE://��ͣ״̬

				if (GetAsyncKeyState(0x50)) //��P����ͣ
				{
					game_info.state = NORMAL;
					Sleep(300); //��ֹ�������쵼��״̬�л��쳣
				
					Console_Refresh(&game_info); //ˢ�¿���̨��ʾ
				}

				if (GetAsyncKeyState(VK_ESCAPE)) //��Esc���˳�
				{
					game_info.is_game_over = true;

					Free_All_Dynamic_Memory(&game_info);//�ͷ����ж�̬������ڴ�
					Locate_Cursor_Position((100 - 12) / 2, 15, game_info.houtput);
					printf("��Ϸ���˳�");
					Locate_Cursor_Position((100 - 21) / 2, 17, game_info.houtput);
					printf("��л�������棬��ӭ�´�����!");

					exit(0); //�˳�����
				}

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