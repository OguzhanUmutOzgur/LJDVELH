#include<iostream>


typedef struct{
	char* texte = NULL; //texte possible sur le lien
	int destination; //contient l'id de l'article destination
}Lien;

typedef struct {
	int id; //identifiant de l'article
	char* texte = NULL; //texte de l'article
	int nbliens;
	Lien* tLiens = NULL; //tableau dynamique de liens vers les autres articles
}Article;

typedef struct {
	Article* article = NULL; //l'article lié au noeud du graphe
	int x = 1;
	int	y; //position du noeud dans la fenêtre
	int NbLignes;
}Noeud;

typedef struct {
	Noeud* origine = NULL; //pointeur sur le noeud origine du lien
	Noeud* destination = NULL; //pointeur sur le noeud destination du lien
}Arete;
