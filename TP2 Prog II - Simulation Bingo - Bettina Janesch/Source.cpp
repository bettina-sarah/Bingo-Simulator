#include <iostream>
#include <stdlib.h> // system cls
#include <conio.h> // getch
#include <random> // rand fonc

using namespace std;

struct BouleBingo_s
{
	string Lettre;
	int Numero;
};


struct CaseCarte_s
{
	bool Etat;
	BouleBingo_s BouleCarte;
};

string LettreBingo[5] = { "B", "I", "N", "G", "O" };

const int NumeroBoules = 75;

BouleBingo_s Boulier[NumeroBoules];
BouleBingo_s BoulesApresTirage[NumeroBoules];

int BoulesRestantsBoulier = NumeroBoules;
int BoulesDejaTirees;

CaseCarte_s CarteBingo[5][5];

void AffichageMenu();
void BoulierInitial(BouleBingo_s tab[], const int taille); // boulier plein
void AfficherBoulier(BouleBingo_s tab[], const int taille); // affiche le boulier plein qui se vide avec chaquE tirage
void BoulesTirees(BouleBingo_s tab[], const int taille); // tableau initial vide qui se remplit avec chaque tirage
void CarteInitiale(CaseCarte_s matrice[5][5]); // carte initiale
void AfficherCarte(CaseCarte_s matrice[5][5]); // affiche matrice 5x5 nouvelle
int BoulierHasard(int &NombreMaximum); // pige numéro au hasard (max 75; apres ca descend)
BouleBingo_s RetirerBouleBingo(BouleBingo_s tab[], const int taille, int IndiceRandomtrouve); //Réarrange Boulier; boule est retirée; renvoyé a la fin du tableau et initialiser comme 0

void main(void)
{
	setlocale(LC_CTYPE, "fr-CA");

	//AffichageMenu();

	BoulierInitial(Boulier, NumeroBoules);
	AfficherBoulier(Boulier, NumeroBoules);
	RetirerBouleBingo(Boulier, NumeroBoules, BoulierHasard(BoulesRestantsBoulier));// indice random trouve = fonction Boulier Hasard
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
			"\n***********************************************************************************************************\n";
		BoulierInitial(Boulier, NumeroBoules);
		AfficherBoulier(Boulier, NumeroBoules);
		cout << "\n\n"
			"TIRAGE DE LA BOULE:\n";
		//cout << Boulier[]
			"\n\nBOULES DÈJÀ TIRÉES\n";
		CarteInitiale(CarteBingo);
		AfficherCarte(CarteBingo);

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
		cout << tab[i].Lettre << tab[i].Numero << " ";
	}
}

void BoulesTirees(BouleBingo_s tab[], const int taille)
{
	for (int i = 0; i < taille; i++)
	{
		tab[i].Lettre = " ";
		tab[i].Numero = 0;
	}
}

void CarteInitiale(CaseCarte_s matrice[5][5])
{
	int NumeroB = 11;
	int NumeroI = 16;
	int NumeroN = 31;
	int NumeroG = 46;
	int NumeroO = 61;
	for (int ligne = 0; ligne < 5; ligne++) // col 0: B, col 1: I, col 2: N, col 3: G, col 4: O
	{
		for (int colonne = 0; colonne < 5; colonne++) // ligne 0,1,2,3,4
		{
			if (colonne == 0) //B - 11-15 (tab 10-14)
			{
				matrice[colonne][ligne].BouleCarte.Lettre = LettreBingo[0];
				matrice[colonne][ligne].BouleCarte.Numero = NumeroB;
				matrice[colonne][ligne].Etat = false;
				NumeroB++;
			}
			else if (colonne == 1) //I - 16-20 (tab 15-19)
			{
				matrice[colonne][ligne].BouleCarte.Lettre = LettreBingo[1];
				matrice[colonne][ligne].BouleCarte.Numero = NumeroI;
				matrice[colonne][ligne].Etat = false;
				NumeroI++;
			}
			else if (colonne == 2) //N - 31-35 (tab 30-34)
			{
				matrice[colonne][ligne].BouleCarte.Lettre = LettreBingo[2];
				matrice[colonne][ligne].BouleCarte.Numero = NumeroN;
				matrice[colonne][ligne].Etat = false;
				NumeroN++;
			}
			else if (colonne == 3) //G - 46-50 (tab 45-49)
			{
				matrice[colonne][ligne].BouleCarte.Lettre = LettreBingo[3];
				matrice[colonne][ligne].BouleCarte.Numero = NumeroG;
				matrice[colonne][ligne].Etat = false;
				NumeroG++;
			}
			else if (colonne == 4) //O - 61-65 (tab 60-64)
			{
				matrice[colonne][ligne].BouleCarte.Lettre = LettreBingo[4];
				matrice[colonne][ligne].BouleCarte.Numero = NumeroO;
				matrice[colonne][ligne].Etat = false;
				NumeroO++;
			}
		}
	}
}

void AfficherCarte(CaseCarte_s matrice[5][5])
{
	cout << "\n\n\n=====================================\n"
		"||  B  ||  I  ||  N  ||  G  ||  O  ";
	for (int colonne = 0; colonne < 5; colonne++) // col 0: B, col 1: I, col 2: N, col 3: G, col 4: O
	{
		for (int ligne = 0; ligne < 5; ligne++) // ligne 0,1,2,3,4
		{
			if (ligne == 0)
			{
				cout << "||";
				cout<<"\n=====================================";
				cout << "\n";
				cout << "|| "<<matrice[colonne][ligne].BouleCarte.Numero << "  ";
			}
			else
			{
				cout << "|| " << matrice[colonne][ligne].BouleCarte.Numero << "  ";
			}
		}
	}
	cout << "||"
	"\n=====================================";

}

int BoulierHasard(int &NombreMaximum) // decrementer NombreMaximum pas ICI car tu veux conserver nbmax et decrementer dans une 
{
	int x = 0;
	srand(time(NULL));
	x = (rand() % (NombreMaximum + 1));
	return x;
}

BouleBingo_s RetirerBouleBingo(BouleBingo_s tab[], const int taille, int IndiceRandomtrouve)
{
	BouleBingo_s Temp = tab[IndiceRandomtrouve];
	tab[IndiceRandomtrouve] = tab[BoulesRestantsBoulier-1]; //-1 car tab[75] existe pas
	tab[BoulesRestantsBoulier-1].Lettre = " ";
	tab[BoulesRestantsBoulier-1].Numero = 0;
	cout << Temp.Lettre << Temp.Numero;
	return Temp;
}
