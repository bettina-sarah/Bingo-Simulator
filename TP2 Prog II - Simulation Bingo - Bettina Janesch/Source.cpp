#include <iostream>
#include <stdlib.h> // system cls
#include <conio.h> // getch

using namespace std;

void AffichageMenu();

void main(void)
{

	setlocale(LC_CTYPE, "fr-CA");

	AffichageMenu();

}
	


void AffichageMenu()
{
	char OptionMenu;
	do
	{
		system("cls");
		cout << "*********************************************    MENU    **************************************************"
			"\n***\t\t\tT - Tirer un numéro\tB - BINGO!\tQ - Quitter le menu\t\t\t***"
			"\n***********************************************************************************************************";
		cin >> OptionMenu;
		OptionMenu = toupper(OptionMenu);
		switch (OptionMenu)
		{
		case 'T': 
			// call fonc tirage
			system("cls");
			cout << "Tirage";
			_getch();
			break;
		case 'B':
			system("cls");
			cout << "\n\n*****************"
				"\n*** BINGO !!! ***"
				"\n*****************";
			_getch();
			break;
		case 'Q':
			_getch();
		}

	}
	while (OptionMenu != 'Q');
}	