#include "sl.h"

int main(int args, char *argv[])
{
	const int screenWidth = 700;
	const int screenHeight = 600;

	bool game = true;
	int posBolaX = screenWidth/2;
	int posBolaY = screenHeight/2;
	int incrementoY = 8;
	int incrementoX = 7;
	int contadorP1 = 0;
	int contadorP2 = 0;
	const float speed = 10;
	int playerHeight = 150;
	int playerWidth = 30;

	bool IA = false;

	float P1X = 35;
	float P1Y = screenHeight / 2;
	float P1Top;
	float P1Bot;
	float P1Edge;

	float P2X = screenWidth - 35;
	float P2Y = screenHeight / 2;
	float P2Top;
	float P2Bot;
	float P2Edge;

	int radio = 20;

	slWindow(screenWidth, screenHeight, "Bad Pong 2: Electric Boogaloo", false);

	slSetFont(slLoadFont("ttf/white_rabbit.ttf"), 24);

	slSetTextAlign(SL_ALIGN_CENTER);
	slSetBackColor(0, 0, 0);//COLOR FONDO
	slSetForeColor(1.0, 0.5, 0.5, 1.0); //COLOR DE LOS OBJETOS

	while (!slShouldClose() && !slGetKey(SL_KEY_ESCAPE))
	{
		P1Top = P1Y + playerHeight / 2;
		P1Bot = P1Y - playerHeight / 2;
		P1Edge = P1X + playerWidth;
		P2Top = P2Y + playerHeight / 2;
		P2Bot = P2Y - playerHeight / 2;
		P2Edge = P2X + playerWidth;



		if (slGetKey('W') && P1Y + 75 < screenHeight)
		{
			P1Y += speed;
		}
		if (slGetKey('S') && P1Y - 75 > 0)
		{
			P1Y -= speed;
		}
		if (slGetKey(SL_KEY_UP) && P2Y + 75 < screenHeight)
		{
			P2Y += speed;
		}
		if (slGetKey(SL_KEY_DOWN) && P2Y - 75 > 0)
		{
			P2Y -= speed;
		}

		if(posBolaY - radio <= 0 || posBolaY + radio >= screenHeight)
		{
			incrementoY *= -1;
		}

		if (posBolaX - radio <= 0 || posBolaX + radio >= screenWidth)
		{
			incrementoX *= -1;
		}

		if ((posBolaX <= P1Edge && (posBolaY >= P1Bot && posBolaY <= P1Top))
			|| (posBolaX + 2*radio >= P2X && (posBolaY >= P2Bot && posBolaY <= P2Top)))
		{
			if (posBolaY >= P1Y || posBolaY >= P2Y)
			{
				incrementoY *= -1;
			}
			incrementoX *= -1;
		}

		posBolaX += incrementoX;
		posBolaY += incrementoY;

		slRectangleOutline(P1X, P1Y, playerWidth, playerHeight);

		slRectangleOutline(P2X, P2Y, playerWidth, playerHeight);

		slCircleOutline(posBolaX, posBolaY, radio, 99);

		slRender();
	}
	slClose();
	return 0;
}