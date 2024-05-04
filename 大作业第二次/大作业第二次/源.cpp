//EasyX�����C++��ͼ�ο⣬���԰���C/C++��ѧ�߿�������ͼ�κ���Ϸ��̡�
//  ����,���Ի���EasyXͼ�ο�ܿ��ü���ͼ�λ�һ�����ӣ�����һ���ƶ���С�������Ա�д����˹���� ��̰���ߡ��ڰ����С��Ϸ��
#include <graphics.h>
//���ͷ�ļ�ͨ�������� C/C++ �н��м򵥵�ͼ�α��
//���ṩ��һЩ������ͼ�λ��ƺ������续�ߡ���Բ�������ɫ�ȣ��Լ�����ͼ�δ��ڵĺ������紴�����ڡ��رմ��ڵ�
#include <conio.h>
//���ͷ�ļ��ṩ��һЩ�����ڿ���̨�н�����������ĺ�������Ҫ������ַ����������������
//���а�����һЩ���ڿ��ƹ��λ�á������ı���ɫ���ӿ���̨�ж�ȡ�ַ��Ⱥ�����
#include<math.h>
//���� C/C++ ��׼���е���ѧ����ͷ�ļ����ṩ�˸�����ѧ�����������Ͷ��塣
//��������һϵ�г��õ���ѧ�����������Ǻ���������������ָ���������ݺ����ȡ�
//math.h �еĺ����������ڸ�����ѧ����Ϳ�ѧ���㣬����ֵ����������ѧ������ѧ������ļ��㡣

#define G 9.8                      //�������ٶ�
#define XSIZE 512                  //��Ļ��С
#define YSIZE 384
#define X 64                       //������ʼλ��
#define Y 192
#define W 32                       //���ǵĿ�͸�
#define H 32
#define STEP 4                     //������һ���������ظ���
#define HIGH (2*role.w+1)          //������Ծ�����߶�

#define	CMD_LEFT 1                 //������ĺ궨��
#define	CMD_RIGHT 2	
#define	CMD_UP 4
#define CMD_DOWN 8
#define CMD_SHOOT 16
#define CMD_ESC 32
int life;                          //ȫ�ֱ��������ǹ��ж���������
int score;                         //ȫ�ֱ��������ǻ�õķ���
struct ROLE
{
	int id;
	int x;//������
	int y;//������
	int w;//ͼƬ���
	int h;//ͼƬ�߶�
	int xleft;//ˮƽ�˶�������� 
	int xright;//ˮƽ�˶����ҽ���
	int turn;//������˶�����
	int jump;//�����Ƿ���Ծ
	int iframe;//���صڼ�������ͼ�����������þ��鿴��ȥ��������
};
struct MAP        //�����ͼ�Ľṹ��
{
	int id;
	int x;
	int y;
};
struct BULLET      //�ӵ��Ľṹ��
{
	int x;
	int y;
	int turn;
	int iframe;
	int id;
};
struct COINT      //Ӳ�ҵĽṹ��
{
	int x;
	int y;
	double iframe;
};
struct ENEMY      //���˵Ľṹ��
{
	int id;
	int x;
	int y;
	int turn;
	int iframe;
};
class game        //������Ϸֻ��������һ����
{
private:
	ROLE role;
	MAP map[350];
	BULLET bullet[20];
	COINT coint[50];
	ENEMY enemy[20];
	IMAGE img_mapsky, img_p, img_map, img_ani, img_mapbk, img_home;
	int xmapsky;           //������յ���ʼ������
	int xmap;              //��ͼ����ʼ����
	double v0;             //������Ծ�ĳ��ٶ�             
	double h;              //������Ծ�ĸ߶�
	double t;              //������Ծ��ʱ��
	int ibullet;           //�ڼ����ӵ�
	int xbullet;           //�ӵ���x����
	int ybullet;           //�ӵ���y����
	int get_bullet;        //�Ƿ���������0��ʾû�л�ã�1��ʾ�ѻ��
	POINT icoint;          //����Ӳ�ҵ�����
	POINT bomb[20];        //������Щ�ط���ը�˵�����
	POINT temp;            //��ʱ���ꡣ������Щ�ط���ը�˵�����
	double score_frame;    //����3��double�͵ı������ڿ��Ƹ���ͼƬ��֡����ʵ�ֶ�����Ч�����续���е���ˮ
	double bomb_frame;
	double mapbk_frame;
	int win;               //����Ƿ����
	int pause;             //����Ƿ�Esc����ͣ����
public:
	game();
	~game();
	void start();          //������Ϸ��ʼ�Ľ��棬�Ͱ���ͣ����Ľ���
	void init();           //��ʼ���������
	void move();           //���������ƶ�
	void show();           //��ʾ����
	int isdie();           //�ж������Ƿ�����
	int  GetCommand();	   // ��ȡ�������
	void left();           //���������˶�
	void right();          //���������˶�
	void up();             //������Ծ
	void init_shoot();     //��ʼ�������ӵ�
	void fall();	       //���������������������Ծ
	int is_l_touch(int id);//���ǵ�����Ƿ�����ǽ����ˣ��Լ������Ƿ�����½�ص���߽�
	int is_r_touch(int id);//���ǵ��ұ��Ƿ�����ǽ����ˣ��Լ������Ƿ�����½�ص��ұ߽�
	int is_t_touch();      //���ǵ�ͷ�Ƿ�����ǽ
	int is_b_touch(int id);//�����Ƿ�ȵ����ˡ�
	int is_touch();        //�����Ƿ�Ե����
	int is_land(ENEMY e);  //�����Ƿ�վ��½����
	void getbullet();      //��ȡ�ӵ�
	void shoot();          //�����ӵ�
	int eat(BULLET b);     //�ӵ��Ƿ�򵽵��˻���ǽ��
	void end();            //������Ϸ����
};
game::game()
{
	initgraph(XSIZE, YSIZE);//XSIZE,YSIZEΪǰ��궨��õ�������
}
//���캯�� game::game() �ڶ��󱻴���ʱ����
// ���������ǳ�ʼ����Ϸ��ͼ�δ���
// ͨ�� initgraph(XSIZE, YSIZE) ����һ��ָ����С��ͼ�δ��ڣ�������ʾ��Ϸ����
game::~game()
{
	closegraph();
}
//�������� game::~game() �ڶ�������ʱ���ã����������ǹر���Ϸ��ͼ�δ���
// ͨ�� closegraph() �ر���Ϸ��ͼ�λ������ͷ������Դ��ȷ����Ϸ����ʱ��Դ�ܹ�����ȷ�ͷš�
void game::start()
{
	if (pause == 1)//���������ͣ��
	{
		BeginBatchDraw(); //��ʼ�������ƣ�����߻���Ч��
		int points[8] = { XSIZE / 2 - 45,YSIZE / 3,XSIZE / 2 + 45,YSIZE / 3,XSIZE / 2 + 45,YSIZE / 3 + 90,XSIZE / 2 - 45,YSIZE / 3 + 90 };
		setfillstyle(GREEN);//����һ�������˵�����ĸ��������������
		fillpoly(4, points);//ʹ��ָ���Ķ��������������һ�������ı��Σ�����ͣ�˵��ı�����
		setbkmode(TRANSPARENT);//�����ı�����ģʽΪ͸�����������Ƶ����ֱ����ͻ�͸�������Ḳ�Ǳ�����
		setfont(20, 0, "����"); //���������СΪ 20��������ʽΪ��������������Ϊ����
		RECT r2 = { XSIZE / 2 - 45,YSIZE / 3,XSIZE / 2 + 45,YSIZE / 3 + 30 }; rectangle(XSIZE / 2 - 45, YSIZE / 3, XSIZE / 2 + 45, YSIZE / 3 + 30);
		drawtext("�ص���Ϸ", &r2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		//����һ������ r2�����ڰ������ص���Ϸ�����֣�������һ�����ο�
		RECT r3 = { XSIZE / 2 - 45,YSIZE / 3 + 30,XSIZE / 2 + 45,YSIZE / 3 + 60 }; rectangle(XSIZE / 2 - 45, YSIZE / 3 + 30, XSIZE / 2 + 45, YSIZE / 3 + 60);
		drawtext("���¿�ʼ", &r3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		//����һ������ r3�����ڰ��������¿�ʼ�����֣�������һ�����ο�
		RECT r4 = { XSIZE / 2 - 45,YSIZE / 3 + 60,XSIZE / 2 + 45,YSIZE / 3 + 90 }; rectangle(XSIZE / 2 - 45, YSIZE / 3 + 60, XSIZE / 2 + 45, YSIZE / 3 + 90);
		drawtext(" �� �� �� ", &r4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		//����һ������ r4�����ڰ��������˵������֣�������һ�����ο�
		FlushBatchDraw();
		//ˢ���������ƵĽ���������Ƶ�ͼ�κ�������ʾ����Ļ��
		MOUSEMSG m;//����һ�� MOUSEMSG �ṹ����� m�����ڽ��������Ϣ��
		while (true)// ����һ������ѭ�������ϼ�������¼�
		{
			BeginBatchDraw();//��ʼ�������ƣ�����߻���Ч��
			m = GetMouseMsg();//��ȡ�����Ϣ
			switch (m.uMsg)//���������Ϣ���ͽ��з�֧����
			{
			case WM_LBUTTONDOWN://��������������ʱִ�����²�����
				EndBatchDraw();//�����������ƣ����Ƶ�ͼ�κ�������ʾ����Ļ��
				if (m.x > XSIZE / 2 - 45 && m.x<XSIZE / 2 + 45 && m.y>YSIZE / 3 && m.y < YSIZE / 3 + 30)
					return;//��������λ���ڡ��ص���Ϸ����ť��Χ�ڣ��������ء�
				else if (m.x > XSIZE / 2 - 45 && m.x<XSIZE / 2 + 45 && m.y>YSIZE / 3 + 30 && m.y < YSIZE / 3 + 60)
				{
					mciSendString("close all", NULL, 0, NULL);
					pause = 0;
					score = 0;
					return;
				}//��������λ���ڡ����¿�ʼ����ť��Χ�ڣ�ִ�йر�������Ƶ��ȡ����ͣ�����õ÷֣�Ȼ�󷵻ء�
				else if (m.x > XSIZE / 2 - 45 && m.x<XSIZE / 2 + 45 && m.y>YSIZE / 3 + 60 && m.y < YSIZE / 3 + 90)
				{
					mciSendString("close all", NULL, 0, NULL);
					pause = 0;
					score = 0;
					life = 0;
					cleardevice();
					break;
				}
				//��������λ���ڡ����˵�����ť��Χ��
				// ִ�йر�������Ƶ��ȡ����ͣ�����õ÷֡�����Ϊ0�������Ļ���ݣ�Ȼ������ѭ����
				else
					break;
				//��������λ�ò����κΰ�ť��Χ�ڣ����� switch ��֧��Ȼ�������һ��ѭ����
			case WM_MOUSEMOVE://������ƶ�ʱִ�����²���
				RECT r;//����һ�����νṹ����� r�����ڱ�ʾ��ť������
				int i; //����һ�����ͱ��� i������ѭ������
				for (i = 0; i < 3; i++)//ѭ������������ť
				{
					if (m.x > XSIZE / 2 - 45 && m.x<XSIZE / 2 + 45 && m.y>YSIZE / 3 + i * 30 && m.y < YSIZE / 3 + 30 + i * 30)
					{
						r.left = XSIZE / 2 - 45;
						r.top = YSIZE / 3 + i * 30;
						r.right = XSIZE / 2 + 45;
						r.bottom = YSIZE / 3 + 30 + i * 30;
						int points[8] = { r.left,r.top,r.right,r.top,r.right,r.bottom,r.left,r.bottom };
						//ѭ������������ť
						setfillstyle(RED);
						//ʹ�� setfillstyle() ���������ɫΪ��ɫ
						fillpoly(4, points);
						//ʹ�� fillpoly() ��������һ���ı��Σ��ĸ��������������� points �ṩ
						setbkmode(TRANSPARENT);
						//ʹ�� setbkmode() �������ı�����ģʽ����Ϊ͸�����Ա��ı������ڲ��ܱ���ɫӰ����������ʾ
						switch (i)//���ݱ��� i ��ֵ���в�ͬ�Ĳ���
						{
						case 0:
							drawtext("�ص���Ϸ", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
							break;
							//ʹ�� drawtext() �����ھ��� r �����Ļ����ı� "�ص���Ϸ"���ı�ˮƽ�ʹ�ֱ���У�������ʾ��
						case 1:
							drawtext("���¿�ʼ", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
							break;
							//ʹ�� drawtext() �����ھ��� r �����Ļ����ı� "���¿�ʼ"���ı�ˮƽ�ʹ�ֱ���У�������ʾ��
						case 2:
							drawtext(" �� �� �� ", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
							break;
							//ʹ�� drawtext() �����ھ��� r �����Ļ����ı� " �� �� �� "���ı�ˮƽ�ʹ�ֱ���У�������ʾ��
						}
					}
					else
					{
						if (getpixel(XSIZE / 2 - 45 + 1, YSIZE / 3 + i * 30 + 1) == RED)
							//��鰴ť�����ڵ�������ɫ�Ƿ�Ϊ��ɫ�� getpixel�������ڻ�ȡָ��λ�õ�������ɫ
							//(XSIZE/2-45+1,YSIZE/3+i*30+1) �ǰ�ť�����ڵ�һ���㣬ͨ�����Һ������ƶ�һ�����أ���ȷ�����ĵ��ڰ�ť�ڲ���
						{
							r.left = XSIZE / 2 - 45;
							r.top = YSIZE / 3 + i * 30;
							r.right = XSIZE / 2 + 45;
							r.bottom = YSIZE / 3 + 30 + i * 30;
							int points[8] = { r.left,r.top,r.right,r.top,r.right,r.bottom,r.left,r.bottom };
							setfillstyle(GREEN);
							fillpoly(4, points);
							setbkmode(TRANSPARENT);
							switch (i)
							{
							case 0:
								drawtext("�ص���Ϸ", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
								break;
							case 1:
								drawtext("���¿�ʼ", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
								break;
							case 2:
								drawtext(" �� �� �� ", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
								break;
							}
							//���þ��� r ��λ�á�
							//ʹ�� setfillstyle() ���������ɫΪ��ɫ��
							//fillpoly() ����������ɫ��ť��
							//ʹ�� setbkmode() �������ı�����ģʽ����Ϊ͸����
							//���ݰ�ť������ѡ��ͬ���ı����ݣ�ʹ�� drawtext() �������»��ư�ť�ϵ��ı���
						}
						FlushBatchDraw();//ˢ�»��ƽ�������仯��İ�ť��ʾ����Ļ��
					}
				}
			}
			if (pause == 0)
				break;
			//if(pause==0) break;�������Ϸ��ͣ״̬Ϊ 0��δ��ͣ����������ѭ��
		}
	}
	if (life == 1 || life == 2)
		return;
	life = 3;
	score = 0;
	setfont(40, 0, "��������");	// ���������СΪ40��������ʽΪ���������塱
	RECT r1 = { 0, 0, XSIZE, YSIZE / 3 };//����һ�����νṹ����� r1��������ʾ��������
	drawtext("����Ģ��", &r1, DT_CENTER | DT_VCENTER | DT_SINGLELINE); //�ڱ����������Ļ����ı�������Ģ������
	setfont(20, 0, "����");//���������СΪ20��������ʽΪ�����塱
	RECT r2 = { XSIZE / 2 - 45,YSIZE / 3,XSIZE / 2 + 45,YSIZE / 3 + 30 }; rectangle(XSIZE / 2 - 45, YSIZE / 3, XSIZE / 2 + 45, YSIZE / 3 + 30);
	drawtext("��ʼ��Ϸ", &r2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	RECT r3 = { XSIZE / 2 - 45,YSIZE / 3 + 30,XSIZE / 2 + 45,YSIZE / 3 + 60 }; rectangle(XSIZE / 2 - 45, YSIZE / 3 + 30, XSIZE / 2 + 45, YSIZE / 3 + 60);
	drawtext("��Ϸ����", &r3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	RECT r4 = { XSIZE / 2 - 45,YSIZE / 3 + 60,XSIZE / 2 + 45,YSIZE / 3 + 90 }; rectangle(XSIZE / 2 - 45, YSIZE / 3 + 60, XSIZE / 2 + 45, YSIZE / 3 + 90);
	drawtext("����˵��", &r4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	RECT r5 = { XSIZE / 2 - 45,YSIZE / 3 + 90,XSIZE / 2 + 45,YSIZE / 3 + 120 }; rectangle(XSIZE / 2 - 45, YSIZE / 3 + 90, XSIZE / 2 + 45, YSIZE / 3 + 120);
	drawtext("�˳���Ϸ", &r5, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	//���岢�����ĸ���ť�����ı���
	//  ��ʼ��Ϸ��ť
	//	��Ϸ���ܰ�ť
	//	����˵����ť
	//	�˳���Ϸ��ť
	int flag1 = 1, flag2 = 0, flag3 = 0;
	//���岢��ʼ����־���� flag1=1,flag2=0,flag3=0�����ڿ��ƽ����״̬
	MOUSEMSG m;
	while (flag1 == 1)//����ѭ�������������Ϣ
	{
		BeginBatchDraw();
		m = GetMouseMsg();
		switch (m.uMsg)
		{
		case WM_LBUTTONDOWN:// ���������������¼�
			EndBatchDraw();//���������λ�úͰ�ť״ִ̬����Ӧ�Ĳ�����
			if (m.x > XSIZE / 2 - 45 && m.x<XSIZE / 2 + 45 && m.y>YSIZE / 3 && m.y < YSIZE / 3 + 30 && flag1 == 1 && flag2 == 0 && flag3 == 0)
			{
				flag1 = 0;
				break;
			}//���������ǿ�ʼ��Ϸ��ť���������Ϸ
			else if (m.x > XSIZE / 2 - 45 && m.x<XSIZE / 2 + 45 && m.y>YSIZE / 3 + 30 && m.y < YSIZE / 3 + 60 && flag1 == 1 && flag3 == 0)
			{
				flag2 = 1;
				cleardevice();
				rectangle(50, 50, 213, 220);
				outtextxy(52, 52, "��Ϸ���ܣ�");
				outtextxy(52, 82, "����������");
				outtextxy(52, 102, "����Ģ��");
				outtextxy(52, 132, "�����ߣ�");
				outtextxy(52, 152, "czxczx");
				RECT R1 = { XSIZE - 46,YSIZE - 26,XSIZE - 2,YSIZE - 2 }; rectangle(XSIZE - 46, YSIZE - 26, XSIZE - 2, YSIZE - 2);
				drawtext("����", &R1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				break;
			}//������������Ϸ���ܰ�ť������ʾ��Ϸ����
			else if (m.x > XSIZE / 2 - 45 && m.x<XSIZE / 2 + 45 && m.y>YSIZE / 3 + 60 && m.y < YSIZE / 3 + 90 && flag1 == 1 && flag2 == 0)
			{
				flag3 = 1;
				cleardevice();
				rectangle(50, 50, 213, 220);
				outtextxy(52, 52, "����˵����");
				outtextxy(52, 72, "���ƣ�A��");
				outtextxy(52, 92, "���ƣ�D��");
				outtextxy(52, 112, "���䣺J��");
				outtextxy(52, 132, "��Ծ��W��/K��");
				outtextxy(52, 152, "��ͣ��Esc��");
				RECT R2 = { XSIZE - 46,YSIZE - 26,XSIZE - 2,YSIZE - 2 }; rectangle(XSIZE - 46, YSIZE - 26, XSIZE - 2, YSIZE - 2);
				drawtext("����", &R2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				break;//���������ǲ���˵����ť������ʾ��Ϸ����˵��
			}
			else if (m.x > XSIZE / 2 - 45 && m.x<XSIZE / 2 + 45 && m.y>YSIZE / 3 + 90 && m.y < YSIZE / 3 + 120 && flag1 == 1 && flag2 == 0 && flag3 == 0)
				exit(0);
			else if (m.x > XSIZE - 46 && m.x<XSIZE - 3 && m.y>YSIZE - 26 && m.y < YSIZE - 3 && (flag2 == 1 || flag3 == 1))
			{
				cleardevice();
				flag1 = 0, flag2 = 0, flag3 = 0;
				start();
			}
			else
				break;//�����������˳���Ϸ��ť�����˳���Ϸ
		case WM_MOUSEMOVE://���������ƶ��¼�����������ƶ�λ�úͰ�ť״̬�ı䰴ť����ɫ�Լ���ʾ״̬
			RECT r;//������νṹ����� r ���ڱ�ʾ��ť������
			if (flag2 == 1 || flag3 == 1)//��鵱ǰ�����״̬�����������Ϸ���ܻ����˵��״̬�������ذ�ť����ɫ����ʾ״̬
			{
				if (m.x > XSIZE - 46 && m.x<XSIZE - 3 && m.y>YSIZE - 26 && m.y < YSIZE - 3)
				{
					r.left = XSIZE - 46;
					r.top = YSIZE - 26;
					r.right = XSIZE - 2;
					r.bottom = YSIZE - 2;
					int points[8] = { r.left,r.top,r.right,r.top,r.right,r.bottom,r.left,r.bottom };
					setfillstyle(RED);
					fillpoly(4, points);
					setbkmode(TRANSPARENT);
					drawtext("����", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				}//������λ�ڷ��ذ�ť�������ڣ�����ť���Ϊ��ɫ����ʾ�ı������ء�
				else
				{
					if (getpixel(XSIZE - 46 + 1, YSIZE - 26 + 1) == RED)
					{
						r.left = XSIZE - 46;
						r.top = YSIZE - 26;
						r.right = XSIZE - 2;
						r.bottom = YSIZE - 2;
						int points[8] = { r.left,r.top,r.right,r.top,r.right,r.bottom,r.left,r.bottom };
						setfillstyle(BLACK);
						fillpoly(4, points);
						setbkmode(TRANSPARENT);
						drawtext("����", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
					}
				}//����������ذ�ť֮ǰ�Ѿ�������Ϊ��ɫ���������Ϊ��ɫ���������ɫ������Ȼ����ʾ�ı������ء�
			}
			else//�����������Ϸ���ܻ����˵��״̬������ʼ��Ϸ����Ϸ���ܡ�����˵�����˳���Ϸ��ť����ɫ����ʾ״̬��
			{
				for (int i = 0; i < 4; i++)
				{
					//����ÿ����ť��������λ�ڰ�ť�������ڣ�����ť���Ϊ��ɫ����ʾ��Ӧ���ı���
					if (m.x > XSIZE / 2 - 45 && m.x<XSIZE / 2 + 45 && m.y>YSIZE / 3 + i * 30 && m.y < YSIZE / 3 + 30 + i * 30)
					{
						r.left = XSIZE / 2 - 45;
						r.top = YSIZE / 3 + i * 30;
						r.right = XSIZE / 2 + 45;
						r.bottom = YSIZE / 3 + 30 + i * 30;
						int points[8] = { r.left,r.top,r.right,r.top,r.right,r.bottom,r.left,r.bottom };
						setfillstyle(RED);
						fillpoly(4, points);
						setbkmode(TRANSPARENT);
						switch (i)
						{
						case 0:
							drawtext("��ʼ��Ϸ", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
							break;
						case 1:
							drawtext("��Ϸ����", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
							break;
						case 2:
							drawtext("����˵��", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
							break;
						case 3:
							drawtext("�˳���Ϸ", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
							break;
						}
					}
					//���������ť֮ǰ�Ѿ�������Ϊ��ɫ���������Ϊ��ɫ���������ɫ������Ȼ����ʾ��Ӧ���ı�
					else
					{
						if (getpixel(XSIZE / 2 - 45 + 1, YSIZE / 3 + i * 30 + 1) == RED)
						{
							r.left = XSIZE / 2 - 45;
							r.top = YSIZE / 3 + i * 30;
							r.right = XSIZE / 2 + 45;
							r.bottom = YSIZE / 3 + 30 + i * 30;
							int points[8] = { r.left,r.top,r.right,r.top,r.right,r.bottom,r.left,r.bottom };
							setfillstyle(BLACK);
							fillpoly(4, points);
							setbkmode(TRANSPARENT);
							switch (i)
							{
							case 0:
								drawtext("��ʼ��Ϸ", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
								break;
							case 1:
								drawtext("��Ϸ����", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
								break;
							case 2:
								drawtext("����˵��", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
								break;
							case 3:
								drawtext("�˳���Ϸ", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
								break;
							}
						}
					}
				}
			}
			FlushBatchDraw(); //ˢ�»�ͼ���������ť�ı仯��ʾ����Ļ��
			break;
		default:
			break;
		}
	}
}