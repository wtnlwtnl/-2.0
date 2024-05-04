//EasyX是针对C++的图形库，可以帮助C/C++初学者快速上手图形和游戏编程。
//  比如,可以基于EasyX图形库很快用几何图形画一个房子，或者一辆移动的小车，可以编写俄罗斯方块 、贪吃蛇、黑白棋等小游戏。
#include <graphics.h>
//这个头文件通常用于在 C/C++ 中进行简单的图形编程
//它提供了一些基本的图形绘制函数，如画线、画圆、填充颜色等，以及控制图形窗口的函数，如创建窗口、关闭窗口等
#include <conio.h>
//这个头文件提供了一些用于在控制台中进行输入输出的函数，主要是针对字符的输入输出操作。
//其中包括了一些用于控制光标位置、设置文本颜色、从控制台中读取字符等函数。
#include<math.h>
//这是 C/C++ 标准库中的数学函数头文件，提供了各种数学函数的声明和定义。
//它包含了一系列常用的数学函数，如三角函数、对数函数、指数函数、幂函数等。
//math.h 中的函数可以用于各种数学计算和科学计算，如数值分析、物理学、工程学等领域的计算。

#define G 9.8                      //重力加速度
#define XSIZE 512                  //屏幕大小
#define YSIZE 384
#define X 64                       //主角起始位置
#define Y 192
#define W 32                       //主角的宽和高
#define H 32
#define STEP 4                     //主角走一步相距的像素个数
#define HIGH (2*role.w+1)          //主角跳跃的最大高度

#define	CMD_LEFT 1                 //方向键的宏定义
#define	CMD_RIGHT 2	
#define	CMD_UP 4
#define CMD_DOWN 8
#define CMD_SHOOT 16
#define CMD_ESC 32
int life;                          //全局变量，主角共有多少条生命
int score;                         //全局变量，主角获得的分数
struct ROLE
{
	int id;
	int x;//横坐标
	int y;//纵坐标
	int w;//图片宽度
	int h;//图片高度
	int xleft;//水平运动的左界限 
	int xright;//水平运动的右界限
	int turn;//精灵的运动方向
	int jump;//精灵是否跳跃
	int iframe;//加载第几副精灵图，这样就能让精灵看上去动起来了
};
struct MAP        //储存地图的结构体
{
	int id;
	int x;
	int y;
};
struct BULLET      //子弹的结构体
{
	int x;
	int y;
	int turn;
	int iframe;
	int id;
};
struct COINT      //硬币的结构体
{
	int x;
	int y;
	double iframe;
};
struct ENEMY      //敌人的结构体
{
	int id;
	int x;
	int y;
	int turn;
	int iframe;
};
class game        //整个游戏只设置了这一个类
{
private:
	ROLE role;
	MAP map[350];
	BULLET bullet[20];
	COINT coint[50];
	ENEMY enemy[20];
	IMAGE img_mapsky, img_p, img_map, img_ani, img_mapbk, img_home;
	int xmapsky;           //背景天空的起始横坐标
	int xmap;              //地图的起始坐标
	double v0;             //精灵跳跃的初速度             
	double h;              //精灵跳跃的高度
	double t;              //精灵跳跃的时间
	int ibullet;           //第几颗子弹
	int xbullet;           //子弹的x坐标
	int ybullet;           //子弹的y坐标
	int get_bullet;        //是否获得武器，0表示没有获得，1表示已获得
	POINT icoint;          //储存硬币的坐标
	POINT bomb[20];        //储存哪些地方爆炸了的坐标
	POINT temp;            //临时坐标。储存哪些地方爆炸了的坐标
	double score_frame;    //下面3个double型的变量用于控制各自图片的帧，以实现动画的效果。如画面中的流水
	double bomb_frame;
	double mapbk_frame;
	int win;               //玩家是否过关
	int pause;             //玩家是否按Esc（暂停键）
public:
	game();
	~game();
	void start();          //处理游戏开始的界面，和按暂停键后的界面
	void init();           //初始化各项变量
	void move();           //控制主角移动
	void show();           //显示画面
	int isdie();           //判断主角是否已死
	int  GetCommand();	   // 获取控制命令。
	void left();           //主角向左运动
	void right();          //主角向右运动
	void up();             //主角跳跃
	void init_shoot();     //初始化发射子弹
	void fall();	       //主角自由落体或者向上跳跃
	int is_l_touch(int id);//主角的左边是否碰到墙或敌人，以及敌人是否碰到陆地的左边界
	int is_r_touch(int id);//主角的右边是否碰到墙或敌人，以及敌人是否碰到陆地的右边界
	int is_t_touch();      //主角的头是否碰到墙
	int is_b_touch(int id);//主角是否踩到敌人。
	int is_touch();        //主角是否吃到金币
	int is_land(ENEMY e);  //敌人是否站在陆地上
	void getbullet();      //获取子弹
	void shoot();          //发射子弹
	int eat(BULLET b);     //子弹是否打到敌人或者墙壁
	void end();            //处理游戏结束
};
game::game()
{
	initgraph(XSIZE, YSIZE);//XSIZE,YSIZE为前面宏定义得到的数据
}
//构造函数 game::game() 在对象被创建时调用
// 它的作用是初始化游戏的图形窗口
// 通过 initgraph(XSIZE, YSIZE) 创建一个指定大小的图形窗口，用于显示游戏画面
game::~game()
{
	closegraph();
}
//析构函数 game::~game() 在对象被销毁时调用，它的作用是关闭游戏的图形窗口
// 通过 closegraph() 关闭游戏的图形环境，释放相关资源，确保游戏结束时资源能够被正确释放。
void game::start()
{
	if (pause == 1)//如果按了暂停键
	{
		BeginBatchDraw(); //开始批量绘制，以提高绘制效率
		int points[8] = { XSIZE / 2 - 45,YSIZE / 3,XSIZE / 2 + 45,YSIZE / 3,XSIZE / 2 + 45,YSIZE / 3 + 90,XSIZE / 2 - 45,YSIZE / 3 + 90 };
		setfillstyle(GREEN);//定义一个包含菜单框架四个顶点坐标的数组
		fillpoly(4, points);//使用指定的顶点坐标数组绘制一个填充的四边形，即暂停菜单的背景框
		setbkmode(TRANSPARENT);//设置文本背景模式为透明，这样绘制的文字背景就会透明，不会覆盖背景框。
		setfont(20, 0, "黑体"); //设置字体大小为 20，字体样式为正常，字体类型为黑体
		RECT r2 = { XSIZE / 2 - 45,YSIZE / 3,XSIZE / 2 + 45,YSIZE / 3 + 30 }; rectangle(XSIZE / 2 - 45, YSIZE / 3, XSIZE / 2 + 45, YSIZE / 3 + 30);
		drawtext("回到游戏", &r2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		//定义一个矩形 r2，用于包裹“回到游戏”文字，并绘制一个矩形框。
		RECT r3 = { XSIZE / 2 - 45,YSIZE / 3 + 30,XSIZE / 2 + 45,YSIZE / 3 + 60 }; rectangle(XSIZE / 2 - 45, YSIZE / 3 + 30, XSIZE / 2 + 45, YSIZE / 3 + 60);
		drawtext("重新开始", &r3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		//定义一个矩形 r3，用于包裹“重新开始”文字，并绘制一个矩形框。
		RECT r4 = { XSIZE / 2 - 45,YSIZE / 3 + 60,XSIZE / 2 + 45,YSIZE / 3 + 90 }; rectangle(XSIZE / 2 - 45, YSIZE / 3 + 60, XSIZE / 2 + 45, YSIZE / 3 + 90);
		drawtext(" 主 菜 单 ", &r4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		//定义一个矩形 r4，用于包裹“主菜单”文字，并绘制一个矩形框。
		FlushBatchDraw();
		//刷新批量绘制的结果，将绘制的图形和文字显示在屏幕上
		MOUSEMSG m;//定义一个 MOUSEMSG 结构体变量 m，用于接收鼠标消息。
		while (true)// 进入一个无限循环，不断监听鼠标事件
		{
			BeginBatchDraw();//开始批量绘制，以提高绘制效率
			m = GetMouseMsg();//获取鼠标消息
			switch (m.uMsg)//根据鼠标消息类型进行分支处理
			{
			case WM_LBUTTONDOWN://当鼠标左键被按下时执行以下操作。
				EndBatchDraw();//结束批量绘制，绘制的图形和文字显示在屏幕上
				if (m.x > XSIZE / 2 - 45 && m.x<XSIZE / 2 + 45 && m.y>YSIZE / 3 && m.y < YSIZE / 3 + 30)
					return;//如果鼠标点击位置在“回到游戏”按钮范围内，函数返回。
				else if (m.x > XSIZE / 2 - 45 && m.x<XSIZE / 2 + 45 && m.y>YSIZE / 3 + 30 && m.y < YSIZE / 3 + 60)
				{
					mciSendString("close all", NULL, 0, NULL);
					pause = 0;
					score = 0;
					return;
				}//如果鼠标点击位置在“重新开始”按钮范围内，执行关闭所有音频、取消暂停、重置得分，然后返回。
				else if (m.x > XSIZE / 2 - 45 && m.x<XSIZE / 2 + 45 && m.y>YSIZE / 3 + 60 && m.y < YSIZE / 3 + 90)
				{
					mciSendString("close all", NULL, 0, NULL);
					pause = 0;
					score = 0;
					life = 0;
					cleardevice();
					break;
				}
				//如果鼠标点击位置在“主菜单”按钮范围内
				// 执行关闭所有音频、取消暂停、重置得分、生命为0，清除屏幕内容，然后跳出循环。
				else
					break;
				//如果鼠标点击位置不在任何按钮范围内，跳出 switch 分支，然后继续下一次循环。
			case WM_MOUSEMOVE://当鼠标移动时执行以下操作
				RECT r;//定义一个矩形结构体变量 r，用于表示按钮的区域
				int i; //定义一个整型变量 i，用于循环控制
				for (i = 0; i < 3; i++)//循环遍历三个按钮
				{
					if (m.x > XSIZE / 2 - 45 && m.x<XSIZE / 2 + 45 && m.y>YSIZE / 3 + i * 30 && m.y < YSIZE / 3 + 30 + i * 30)
					{
						r.left = XSIZE / 2 - 45;
						r.top = YSIZE / 3 + i * 30;
						r.right = XSIZE / 2 + 45;
						r.bottom = YSIZE / 3 + 30 + i * 30;
						int points[8] = { r.left,r.top,r.right,r.top,r.right,r.bottom,r.left,r.bottom };
						//循环遍历三个按钮
						setfillstyle(RED);
						//使用 setfillstyle() 设置填充颜色为红色
						fillpoly(4, points);
						//使用 fillpoly() 函数绘制一个四边形，四个顶点坐标由数组 points 提供
						setbkmode(TRANSPARENT);
						//使用 setbkmode() 函数将文本背景模式设置为透明，以便文本可以在不受背景色影响的情况下显示
						switch (i)//根据变量 i 的值进行不同的操作
						{
						case 0:
							drawtext("回到游戏", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
							break;
							//使用 drawtext() 函数在矩形 r 的中心绘制文本 "回到游戏"，文本水平和垂直居中，单行显示。
						case 1:
							drawtext("重新开始", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
							break;
							//使用 drawtext() 函数在矩形 r 的中心绘制文本 "重新开始"，文本水平和垂直居中，单行显示。
						case 2:
							drawtext(" 主 菜 单 ", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
							break;
							//使用 drawtext() 函数在矩形 r 的中心绘制文本 " 主 菜 单 "，文本水平和垂直居中，单行显示。
						}
					}
					else
					{
						if (getpixel(XSIZE / 2 - 45 + 1, YSIZE / 3 + i * 30 + 1) == RED)
							//检查按钮区域内的像素颜色是否为红色。 getpixel函数用于获取指定位置的像素颜色
							//(XSIZE/2-45+1,YSIZE/3+i*30+1) 是按钮区域内的一个点，通过向右和向下移动一个像素，以确保检查的点在按钮内部。
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
								drawtext("回到游戏", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
								break;
							case 1:
								drawtext("重新开始", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
								break;
							case 2:
								drawtext(" 主 菜 单 ", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
								break;
							}
							//设置矩形 r 的位置。
							//使用 setfillstyle() 设置填充颜色为绿色。
							//fillpoly() 函数绘制绿色按钮。
							//使用 setbkmode() 函数将文本背景模式设置为透明。
							//根据按钮的索引选择不同的文本内容，使用 drawtext() 函数重新绘制按钮上的文本。
						}
						FlushBatchDraw();//刷新绘制结果，将变化后的按钮显示在屏幕上
					}
				}
			}
			if (pause == 0)
				break;
			//if(pause==0) break;：如果游戏暂停状态为 0（未暂停），则跳出循环
		}
	}
	if (life == 1 || life == 2)
		return;
	life = 3;
	score = 0;
	setfont(40, 0, "方正舒体");	// 设置字体大小为40，字体样式为“方正舒体”
	RECT r1 = { 0, 0, XSIZE, YSIZE / 3 };//定义一个矩形结构体变量 r1，用于显示标题区域
	drawtext("超级蘑菇", &r1, DT_CENTER | DT_VCENTER | DT_SINGLELINE); //在标题区域中心绘制文本“超级蘑菇”。
	setfont(20, 0, "宋体");//设置字体大小为20，字体样式为“宋体”
	RECT r2 = { XSIZE / 2 - 45,YSIZE / 3,XSIZE / 2 + 45,YSIZE / 3 + 30 }; rectangle(XSIZE / 2 - 45, YSIZE / 3, XSIZE / 2 + 45, YSIZE / 3 + 30);
	drawtext("开始游戏", &r2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	RECT r3 = { XSIZE / 2 - 45,YSIZE / 3 + 30,XSIZE / 2 + 45,YSIZE / 3 + 60 }; rectangle(XSIZE / 2 - 45, YSIZE / 3 + 30, XSIZE / 2 + 45, YSIZE / 3 + 60);
	drawtext("游戏介绍", &r3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	RECT r4 = { XSIZE / 2 - 45,YSIZE / 3 + 60,XSIZE / 2 + 45,YSIZE / 3 + 90 }; rectangle(XSIZE / 2 - 45, YSIZE / 3 + 60, XSIZE / 2 + 45, YSIZE / 3 + 90);
	drawtext("操作说明", &r4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	RECT r5 = { XSIZE / 2 - 45,YSIZE / 3 + 90,XSIZE / 2 + 45,YSIZE / 3 + 120 }; rectangle(XSIZE / 2 - 45, YSIZE / 3 + 90, XSIZE / 2 + 45, YSIZE / 3 + 120);
	drawtext("退出游戏", &r5, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	//定义并绘制四个按钮及其文本：
	//  开始游戏按钮
	//	游戏介绍按钮
	//	操作说明按钮
	//	退出游戏按钮
	int flag1 = 1, flag2 = 0, flag3 = 0;
	//定义并初始化标志变量 flag1=1,flag2=0,flag3=0，用于控制界面的状态
	MOUSEMSG m;
	while (flag1 == 1)//进入循环，监听鼠标消息
	{
		BeginBatchDraw();
		m = GetMouseMsg();
		switch (m.uMsg)
		{
		case WM_LBUTTONDOWN:// 如果是鼠标左键点击事件
			EndBatchDraw();//根据鼠标点击位置和按钮状态执行相应的操作：
			if (m.x > XSIZE / 2 - 45 && m.x<XSIZE / 2 + 45 && m.y>YSIZE / 3 && m.y < YSIZE / 3 + 30 && flag1 == 1 && flag2 == 0 && flag3 == 0)
			{
				flag1 = 0;
				break;
			}//如果点击的是开始游戏按钮，则进入游戏
			else if (m.x > XSIZE / 2 - 45 && m.x<XSIZE / 2 + 45 && m.y>YSIZE / 3 + 30 && m.y < YSIZE / 3 + 60 && flag1 == 1 && flag3 == 0)
			{
				flag2 = 1;
				cleardevice();
				rectangle(50, 50, 213, 220);
				outtextxy(52, 52, "游戏介绍：");
				outtextxy(52, 82, "超级玛丽变");
				outtextxy(52, 102, "身超级蘑菇");
				outtextxy(52, 132, "开发者：");
				outtextxy(52, 152, "czxczx");
				RECT R1 = { XSIZE - 46,YSIZE - 26,XSIZE - 2,YSIZE - 2 }; rectangle(XSIZE - 46, YSIZE - 26, XSIZE - 2, YSIZE - 2);
				drawtext("返回", &R1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				break;
			}//如果点击的是游戏介绍按钮，则显示游戏介绍
			else if (m.x > XSIZE / 2 - 45 && m.x<XSIZE / 2 + 45 && m.y>YSIZE / 3 + 60 && m.y < YSIZE / 3 + 90 && flag1 == 1 && flag2 == 0)
			{
				flag3 = 1;
				cleardevice();
				rectangle(50, 50, 213, 220);
				outtextxy(52, 52, "操作说明：");
				outtextxy(52, 72, "左移：A键");
				outtextxy(52, 92, "右移：D键");
				outtextxy(52, 112, "发射：J键");
				outtextxy(52, 132, "跳跃：W键/K键");
				outtextxy(52, 152, "暂停：Esc键");
				RECT R2 = { XSIZE - 46,YSIZE - 26,XSIZE - 2,YSIZE - 2 }; rectangle(XSIZE - 46, YSIZE - 26, XSIZE - 2, YSIZE - 2);
				drawtext("返回", &R2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				break;//如果点击的是操作说明按钮，则显示游戏操作说明
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
				break;//如果点击的是退出游戏按钮，则退出游戏
		case WM_MOUSEMOVE://如果是鼠标移动事件，根据鼠标移动位置和按钮状态改变按钮的颜色以及显示状态
			RECT r;//定义矩形结构体变量 r 用于表示按钮的区域
			if (flag2 == 1 || flag3 == 1)//检查当前界面的状态，如果处于游戏介绍或操作说明状态，则处理返回按钮的颜色和显示状态
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
					drawtext("返回", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				}//如果鼠标位于返回按钮的区域内，将按钮填充为红色，显示文本“返回”
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
						drawtext("返回", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
					}
				}//否则，如果返回按钮之前已经被绘制为红色，将其填充为黑色，以清除红色背景，然后显示文本“返回”
			}
			else//如果不处于游戏介绍或操作说明状态，则处理开始游戏、游戏介绍、操作说明和退出游戏按钮的颜色和显示状态。
			{
				for (int i = 0; i < 4; i++)
				{
					//对于每个按钮，如果鼠标位于按钮的区域内，将按钮填充为红色，显示相应的文本。
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
							drawtext("开始游戏", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
							break;
						case 1:
							drawtext("游戏介绍", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
							break;
						case 2:
							drawtext("操作说明", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
							break;
						case 3:
							drawtext("退出游戏", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
							break;
						}
					}
					//否则，如果按钮之前已经被绘制为红色，将其填充为黑色，以清除红色背景，然后显示相应的文本
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
								drawtext("开始游戏", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
								break;
							case 1:
								drawtext("游戏介绍", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
								break;
							case 2:
								drawtext("操作说明", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
								break;
							case 3:
								drawtext("退出游戏", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
								break;
							}
						}
					}
				}
			}
			FlushBatchDraw(); //刷新绘图结果，将按钮的变化显示在屏幕上
			break;
		default:
			break;
		}
	}
}