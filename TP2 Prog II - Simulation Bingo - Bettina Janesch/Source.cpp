#include <iostream>
#include <stdlib.h> // system cls
#include <conio.h> // getch

using namespace std;

struct BouleBingo_s
{
	string Lettre;
	int Numero;
};

string LettreBingo[5] = { "B", "I", "N", "G", "O" };

const int NumeroBoules = 75;

BouleBingo_s Boulier[NumeroBoules];
BouleBingo_s BoulesTirees[NumeroBoules];

void AffichageMenu();
void BoulierInitial(BouleBingo_s tab[], const int taille);
void AfficherBoulier(BouleBingo_s tab[], const int taille);

void main(void)
{
	setlocale(LC_CTYPE, "fr-CA");

	//AffichageMenu();
	BoulierInitial(Boulier, NumeroBoules);
	AfficherBoulier(Boulier, NumeroBoules);

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

void BoulierInitial(BouleBingo_s tab[], const int taille)
{
	for (int i = 0; i < taille; i++)
	{
		if (i < 15)
		{
			Boulier[i] = { LettreBingo[0], i + 1 };
		}
		else if (i >= 15 && i < 30)
		{
			Boulier[i] = { LettreBingo[1], i + 1 };
		}
		else if (i >= 30 && i < 46)
		{
			Boulier[i] = { LettreBingo[2], i + 1 };
		}
		else if (i >= 46 && i < 60)
		{
			Boulier[i] = { LettreBingo[3], i + 1 };
		}
		else if (i >= 60 && i <= 75)
		{
			Boulier[i] = { LettreBingo[4], i + 1 };
		}
	}
}

void AfficherBoulier(BouleBingo_s tab[], const int taille)
{
	cout << "\n\nBOULIER\n\n";
	for (int i = 0; i < taille; i++)
	{
		cout << Boulier[i].Lettre << Boulier[i].Numero << " ";
	}
}



//6.	Créez une fonction qui initialise le tableau de boules tirées jusqu’à maintenant : (75 bulles nulles au début)
//•	Accepte en paramètre un tableau de boules de bingo et une taille de tableau
//•	Ne retourne rien
//•	Insère une boule « nulle » dans tous les éléments du tableau(utilisez une boucle)
