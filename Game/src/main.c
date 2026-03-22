#include "uart.h"
#include "mbox.h"
#include "framebf.h"
#include "display_img.h"
#include "display_video.h"
#include "game.h"

void menu();
void main()
{
	// set up serial console
	uart_init();
	// Initialize frame buffer
	framebf_init();

	while (1)
	{
		menu();
		char command = uart_getc();

		uart_sendc(command);
		uart_sendc('\n');
		if (command == '1')
		{
			clearscreen(1920, 1080);
		    controlImage(0, 300);
		}
		else if (command == '2')
		{
			clearscreen(1920, 1080);
			switchImage();
		}
		else if (command == '3')
		{
			clearscreen(1920, 1080);
			drawString((1024 / 2)- 200, 100, "GROUP 10", 0x6);
		    drawString((1024 / 2) - 350, 150, "Tran Manh Hung", 0xc);
		    drawString((1024 / 2) - 200, 200, "s3836286", 0xb);

		    drawString((1024 / 2) - 350, 250, "Nguyen Quoc Binh", 0xa);
		    drawString((1024 / 2) - 200, 300, "s3818140", 0x7);

			drawString((1024 / 2) - 350, 350, "Chau Huu Nghia", 0xd);
		    drawString((1024 / 2) - 200, 400, "s3817841", 0xe);

			drawString((1024 / 2) - 350, 450, "To Hung Phuoc", 0x2);
		    drawString((1024 / 2) - 200, 500, "s3878094", 0x3);
		}
		else if (command == '4')
		{
			clearscreen(1920,1080);
			displayVideo(0,0);
		}

		else if (command == '5')
		{
			while (1)
			{
				framebf_init1();

				start_game();

				int win = playGame1();
				if (win == 1)
				{
					uart_puts("You win first round!!! LET'S MOVE TO SECOND ONE !!!\n");
					uart_puts("Type \"s\" to out the game, or other keys to continue second round !!!");
					char c = uart_getc();
					if (c == 's')
					{
						break;
						uart_puts("BYE !!");
					}
					else
					{
						clearscreen(1024, 768);
						win = playGame2();
						if (win == 1)
							uart_puts("CONGRATULATIONS !! YOU ARE WINNER !!!");
						else if (win == 0)
						{
							uart_puts("You loose in round 2!!!\n");
							uart_puts("Wanna play round 2 again ???\n You have 1 more chance left to try !!!\n");
							uart_puts("Type \"s\" to out the game, or other keys to restart !!!");
							char c = uart_getc();
							if (c == 's')
							{
								break;
								uart_puts("BYE !!");
							}
							else
							{
								win = playGame2();
								if (win == 1)
									uart_puts("CONGRATULATIONS !! YOU ARE WINNER !!!");
								else
								{
									uart_puts("sorry, you loose !! Try harder next time !!\n");
									continue;
								}
							}
						}
					}
				}
				else if (win == 0)
				{
					uart_puts("You loose !!!\n");
					uart_puts("Let's try harder next time !!\n");
				}
				uart_puts("Type \"s\" to out the game, or \"enter\" to restart !!!");
				uart_puts("\n");
				char c = uart_getc();
				if (c == 's')
					break;
				else
					continue;
			}
		}
	}
}

void menu()
{
	uart_puts(
		"\nPress key number to choose command:\n"
		"1.Display scrollable image\n"
		"2.Display switchable image\n"
		"3.Display team members name\n"
		"4.Display video\n"
		"5.Play Game\n");
}
