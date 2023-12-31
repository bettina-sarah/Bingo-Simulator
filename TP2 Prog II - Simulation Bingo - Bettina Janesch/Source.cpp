#include <iostream>
#include <stdlib.h> // system cls
#include <conio.h>	// getch
#include <random>	// rand fonc

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

string LettreBingo[5] = {"B", "I", "N", "G", "O"};

const int NumeroBoules = 75; // const size de mon tableau
int BoulesRestantsBoulier = NumeroBoules; // variable qui change apres chaque tirage (75,74, ... )
int BoulesDejaTirees = 0;				  // variable qui augmente chaque tirage - 0,1,2)

BouleBingo_s Boulier[NumeroBoules];
BouleBingo_s BoulesApresTirage[NumeroBoules];
BouleBingo_s BouleChoisi;

CaseCarte_s CarteBingo[5][5];

void AffichageMenu();
void BoulierInitial(BouleBingo_s tab[], const int taille);									  // boulier plein
void AfficherBoulier(BouleBingo_s tab[], const int taille);									  // affiche le boulier plein qui se vide avec chaquE tirage
void BoulesTirees(BouleBingo_s tab[], const int taille);									  // tableau initial vide qui se remplit avec chaque tirage
void CarteInitiale(CaseCarte_s matrice[5][5]);												  // carte initiale
void AfficherCarte(CaseCarte_s matrice[5][5]);												  // affiche matrice 5x5 nouvelle
int BoulierHasard(int &NombreMaximum);														  // pige numero au hasard (max 75; apres ca descend)
BouleBingo_s RetirerBouleBingo(BouleBingo_s tab[], const int taille, int IndiceRandomtrouve); // Rearrange Boulier; boule est retir�e; renvoy� a la fin du tableau et initialiser comme 0
void AjouterBouleBingo(BouleBingo_s tab[], int &DejaTire, BouleBingo_s BingoPourAjouter);
void TrouverBouleSurCarte(BouleBingo_s BouleVraie, CaseCarte_s matrice[5][5]);

void main(void)
{
	char OptionMenu;
	BoulierInitial(Boulier, NumeroBoules);
	BoulesTirees(BoulesApresTirage, NumeroBoules);
	CarteInitiale(CarteBingo);
	do
	{
		AffichageMenu();
		OptionMenu = _getche();
		OptionMenu = toupper(OptionMenu);
		switch (OptionMenu)
		{
		case 'T':
			BouleChoisi = RetirerBouleBingo(Boulier, NumeroBoules, BoulierHasard(BoulesRestantsBoulier));
			AjouterBouleBingo(BoulesApresTirage, BoulesDejaTirees, BouleChoisi);
			TrouverBouleSurCarte(BouleChoisi, CarteBingo);
			if (BoulesRestantsBoulier < 0) // pour pas afficher des cartes "fausses" dans un boulier maintenant vide, quite le programme
			{
				OptionMenu = 'Q';
			}
			break;
		case 'B':
			system("cls");
			cout << "\n\n*****************"
					"\n*** BINGO !!! ***"
					"\n*****************";
			_getch();
			break;
		case 'Q':
			system("cls");
			cout << "\n\n\n\n\t\t\t" << "\033[30;44m" << char(178) << char(178) << char(178) << char(178) << char(178) << char(178) << char(178) << char(178)<<char(178) << char(178) << char(178) << char(178);;
			cout<<"\n\t\t\t"<< char(178)<<"\033[36;40m"<<"FIN DU JEU" << "\033[30;44m"<< char(178);
			cout << "\n\t\t\t"<<"\033[30;44m" << char(178) << char(178) << char(178) << char(178) << char(178) << char(178) << char(178) << char(178) << char(178) << char(178) << char(178) << char(178);

			_getch();
		}
	} while (OptionMenu != 'Q');
}

void AffichageMenu()

{
	system("cls");
	cout <<"*********************************************    MENU    **************************************************"
			"\n***\t\t\tT - Tirer un num"<<char(130)<<"ro\tB - BINGO!\tQ - Quitter le menu\t\t\t***"
			"\n***********************************************************************************************************\n";

	cout << "\nBOULIER\n\n";
	AfficherBoulier(Boulier, BoulesRestantsBoulier);
	cout << "\n\n"
			"TIRAGE DE LA BOULE:\n";
	cout << BouleChoisi.Lettre << BouleChoisi.Numero;
	cout << "\n\nBOULES DEJA TIR"<<char(144)<<"ES\n"; // mon setlocale langue FR marchait plus; donc je suis allé avec code ASCII

	AfficherBoulier(BoulesApresTirage, BoulesDejaTirees);
	AfficherCarte(CarteBingo);
}

void BoulierInitial(BouleBingo_s tab[], const int taille)
{
	for (int i = 0; i < taille; i++)
	{
		if (i < 15)
		{
			Boulier[i] = {LettreBingo[0], i + 1};
		}
		else if (i >= 15 && i < 30)
		{
			Boulier[i] = {LettreBingo[1], i + 1};
		}
		else if (i >= 30 && i < 46)
		{
			Boulier[i] = {LettreBingo[2], i + 1};
		}
		else if (i >= 46 && i < 60)
		{
			Boulier[i] = {LettreBingo[3], i + 1};
		}
		else if (i >= 60 && i <= 75)
		{
			Boulier[i] = {LettreBingo[4], i + 1};
		}
	}
}

void AfficherBoulier(BouleBingo_s tab[], const int taille)
{
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
	for (int colonne = 0; colonne < 5; colonne++) // col 0: B, col 1: I, col 2: N, col 3: G, col 4: O
	{
		for (int ligne = 0; ligne < 5; ligne++) // ligne 0,1,2,3,4
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
			}
			if (matrice[ligne][colonne].Etat == true)
			{
				cout << "|| "<<"\033[30;47m" << matrice[ligne][colonne].BouleCarte.Numero <<"\033[0m"<< "  ";
				// les couleurs marchent pas comme dans l'enoncé, celui-la l'affice en fond blanc avec écriture noire pour ma console
			}

			else
			{
				cout << "|| " << matrice[ligne][colonne].BouleCarte.Numero << "  ";
			}
		}
	}
	cout << "||"
		"\n=====================================";
}

int BoulierHasard(int &NombreMaximum)
{
	int x = 0;
	srand(time(NULL));
	x = (rand() % (NombreMaximum));
	return x;
}

BouleBingo_s RetirerBouleBingo(BouleBingo_s tab[], const int taille, int IndiceRandomtrouve)
{
	BouleBingo_s Temp = tab[IndiceRandomtrouve];
	for (int i = IndiceRandomtrouve; i < BoulesRestantsBoulier; i++)
	{
		if (i == (BoulesRestantsBoulier - 1)) // 75-1 - 74 - dernier element du tableau devient 0
		{
			tab[i].Lettre = " ";
			tab[i].Numero = 0;
		}
		else
		{
			tab[i] = tab[i + 1];
		}
	}
	BoulesRestantsBoulier--; // decrementer a 74, 73 ... etc
	return Temp;
}

void AjouterBouleBingo(BouleBingo_s tab[], int &DejaTire, BouleBingo_s BingoPourAjouter)
{
	tab[DejaTire] = BingoPourAjouter;
	DejaTire++; // commence a 0, incremente
}

void TrouverBouleSurCarte(BouleBingo_s BouleVraie, CaseCarte_s matrice[5][5]) // A TESTER
{
	for (int ligne = 0; ligne < 5; ligne++) // line 0 - col 0,1,2,3,4 .. line 1-col 0,1,2,3,4...
	{
		for (int colonne = 0; colonne < 5; colonne++)
		{
			if (matrice[ligne][colonne].BouleCarte.Lettre == BouleVraie.Lettre && matrice[ligne][colonne].BouleCarte.Numero == BouleVraie.Numero) // si item trouve dans matrice, tamponner
			{
				matrice[ligne][colonne].Etat = true;
			}
		}
	}
}