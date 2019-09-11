#include "sl.h"
#include <string>
using namespace std;

int main(int args, char *argv[])
{
	const int screenWidth = 700;
	const int screenHeight = 600;

	bool game = false;
	int posBolaX = screenWidth/2;
	int posBolaY = screenHeight/2;
	int incrementoY = 7;
	int incrementoX = 6;
	int contadorP1 = 0;
	int contadorP2 = 0;
	const float speed = 8;
	const float IAspeed = 5;
	int playerHeight = 150;
	int playerWidth = 30;

	bool keyPressed = false;
	bool ia = false;
	bool gameOver = false;

	float p1X = 35;
	float p1Y = screenHeight / 2;
	float p1Top;
	float p1Bot;
	float p1Edge;

	bool movAbajo = false;
	bool movArriba = false; // NO USADO POR AHORA

	float p2X = screenWidth - 35;
	float p2Y = screenHeight / 2;
	float p2Top;
	float p2Bot;
	float p2Edge;
	
	int colorSel = 0;

	int radio = 20;

	slWindow(screenWidth, screenHeight, "Bad Pong 2: Electric Boogaloo", false);
	slSetFont(slLoadFont("ttf/white_rabbit.ttf"), 24);

	slSetTextAlign(SL_ALIGN_CENTER);
	slSetBackColor(0, 0, 0);//COLOR FONDO
	slSetForeColor(0, 2.5, 0, 1.0); //COLOR DE LOS OBJETOS

	while (!slShouldClose() && !slGetKey(SL_KEY_ESCAPE))
	{
		string textP1 = "" + to_string(contadorP1);//DECLARADO ACA PARA QUE SE CAMBIE CON EL UPDATE
		string textP2 = "" + to_string(contadorP2);

		p1Top = p1Y + playerHeight / 2;
		p1Bot = p1Y - playerHeight / 2;
		p1Edge = p1X + playerWidth;
		p2Top = p2Y + playerHeight / 2;
		p2Bot = p2Y - playerHeight / 2;
		p2Edge = p2X + playerWidth;

		if (game)
		{
			if (slGetKey('P'))
			{
				game = false;
			}

			if (slGetKey('W') && p1Y + 75 < screenHeight)
			{
				p1Y += speed;
				movArriba = true;
				movAbajo = false;
			}
			if (slGetKey('S') && p1Y - 75 > 0)
			{
				p1Y -= speed;
				movAbajo = true;
				movArriba = false;
			}

			if (slGetKey(SL_KEY_UP) && p2Y + 75 < screenHeight && !ia)
			{
				p2Y += speed;
			}
			if (slGetKey(SL_KEY_DOWN) && p2Y - 75 > 0 && !ia)
			{
				p2Y -= speed;
			}

			if (ia)
			{
				if (posBolaY > p2Y)
				{
					p2Y += IAspeed;
				}
				else if (posBolaY < p2Y)
				{
					p2Y -= IAspeed;
				}
			}

			if (posBolaY - radio <= 0 || posBolaY + radio >= screenHeight)
			{
				incrementoY *= -1;
			}

			if (posBolaX - radio <= 0 || posBolaX + radio >= screenWidth)
			{
				if (incrementoX < 0)
				{
					contadorP2++;
				}
				else
				{
					contadorP1++;
				}
				posBolaX = screenWidth / 2;
				posBolaX = screenHeight / 2;
				incrementoX *= -1;
			}

			if ((posBolaX <= p1Edge && (posBolaY >= p1Bot && posBolaY <= p1Top))
				|| (posBolaX + 2 * radio >= p2X && (posBolaY >= p2Bot && posBolaY <= p2Top)))
			{
				if (movAbajo)
				{
					incrementoY *= -1;
				}
				incrementoX *= -1;
				posBolaX += incrementoX;
			}

			posBolaX += incrementoX;
			posBolaY += incrementoY;

			if (contadorP1 == 5 || contadorP2 == 5)
			{
				game = false;
				gameOver = true;
			}

			slText(60, screenHeight - 40, textP1.c_str());
			slText(screenWidth - 60, screenHeight - 40, textP2.c_str());

			slRectangleOutline(p1X, p1Y, playerWidth, playerHeight);

			slRectangleOutline(p2X, p2Y, playerWidth, playerHeight);

			slCircleOutline(posBolaX, posBolaY, radio, 99);
		}
		else if(!game && !gameOver)
		{
			if (slGetKey(SL_KEY_ENTER))
			{
				game = true;
				ia = true;
			}

			if (slGetKey('A') && !keyPressed)
			{
				keyPressed = true;
				if (colorSel == 0)
				{
					colorSel = 4;
				}
				else
				{
					colorSel--;
				}
			}
			else if (!slGetKey('A') && !slGetKey('D'))
			{
				keyPressed = false;
			}
			if (slGetKey('D') && !keyPressed)
			{
				keyPressed = true;
				if (colorSel == 4)
				{
					colorSel = 0;
				}
				else
				{
					colorSel++;
				}
			}

			switch (colorSel)
			{
			case 0:
				slSetForeColor(0, 2.5, 0, 1.0);
				break;
			case 1:
				slSetForeColor(2.01, 1.05, 0.30, 1.0);
				break;
			case 2:
				slSetForeColor(2.5, 0.20, 1.47, 1.0);
				break;
			case 3:
				slSetForeColor(0, 0, 2.5, 1.0);
				break;
			case 4:
				slSetForeColor(2.5, 0, 0, 1.0);
				break;
			default:
				break;
			}

			slText(screenWidth / 2, screenHeight / 2 + 120, "Bad Pong 2");
			slText(screenWidth / 2, (screenHeight / 2) + 80, "Electric Boogaloo");
			slText(screenWidth / 2, 190, "Controles: W y S para mover P para pausar");
			slText(screenWidth / 2, 170, "Cambiar Colores (con A y D)");
			slRectangleOutline(screenWidth / 2, 130, playerHeight, playerWidth);
			slText(screenWidth / 2, 70, "Presione Enter para jugar");
			slText(screenWidth / 2, 30, "Presione Esc para salir");
		}
		else if (!game && gameOver)
		{
			if (slGetKey('P'))
			{
				gameOver = false;
				contadorP1 = 0;
				contadorP2 = 0;
			}

			if (contadorP2 >= 5)
			{
				slSetForeColor(2.5, 0, 0, 1.0);
				slText(screenWidth / 2, screenHeight / 2, "YOU DIED");
			}
			else if (contadorP1 >= 5)
			{
				slSetForeColor(0, 2.5, 0, 1.0);
				slText(screenWidth / 2, screenHeight / 2, "YOU WIN");
			}
			slText(screenWidth / 2, 40, "PRESS P TO REPLAY");
		}		
		slRender();
	}
	slClose();
	return 0;
}