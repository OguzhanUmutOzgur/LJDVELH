#include<SDL.h>
#include<SDL_ttf.h>
#include<SDL_image.h>
#include<SDL_mixer.h>
#include <iostream>
#include "structures.h"
#include <ctime>
#include <fstream>
#include <cstring>
#include <string>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

//----------------Constante-------------------//
const int FEN_LARGEUR = 1900;
const int FEN_HAUTEUR = 900;
const int NBArticle = 5;
const int TAILLE = 351;
int dest = 0;
int NbNoeud;
int NbCases;
int NbLiens;
int NbCol = 1;
int NbLignes = 1;
int* NomLignes;
int CurrentId;
bool AudioMod = true;
SDL_Renderer* render;
SDL_Rect rectnewpartie;
SDL_Rect rectmenu;
SDL_Rect GrapheParcouru;
SDL_Rect RectExportHTML;
SDL_Rect NewGameRect;
SDL_Rect ContinueRect;
SDL_Rect Audio;
SDL_Rect RectArticleContenu;
SDL_Rect rect;
SDL_Rect rectquit;
SDL_Rect RectGrapheTotale;
SDL_Rect RectDes;
SDL_Rect* RectLiensContenu;
SDL_Window* win;
TTF_Font* font;
SDL_Surface* SurfaceGrapheTotale;
SDL_Texture* TextureGrapheTotale;
SDL_Texture** TextureLiens;
Mix_Music* backgroundSound;
Article articles[TAILLE];
SDL_Color TextColorGrapheTotale = { 255, 0, 0 };

//------------------------------------------------//


//-------------	FONCTION-----------------//

void AnimLivre() {
	SDL_Surface* ImagesLivre[7];

	ImagesLivre[0] = IMG_Load(".\\ImagesLivre\\image_1.png");
	ImagesLivre[1] = IMG_Load(".\\ImagesLivre\\image_2.png");
	ImagesLivre[2] = IMG_Load(".\\ImagesLivre\\image_3.png");
	ImagesLivre[3] = IMG_Load(".\\ImagesLivre\\image_4.png");
	ImagesLivre[4] = IMG_Load(".\\ImagesLivre\\image_5.png");
	ImagesLivre[5] = IMG_Load(".\\ImagesLivre\\image_6.png");
	ImagesLivre[6] = IMG_Load(".\\ImagesLivre\\image_7.png");

	SDL_Texture* TextureLivre[7];

	TextureLivre[0] = SDL_CreateTextureFromSurface(render, ImagesLivre[0]);
	TextureLivre[1] = SDL_CreateTextureFromSurface(render, ImagesLivre[1]);
	TextureLivre[2] = SDL_CreateTextureFromSurface(render, ImagesLivre[2]);
	TextureLivre[3] = SDL_CreateTextureFromSurface(render, ImagesLivre[3]);
	TextureLivre[4] = SDL_CreateTextureFromSurface(render, ImagesLivre[4]);
	TextureLivre[5] = SDL_CreateTextureFromSurface(render, ImagesLivre[5]);
	TextureLivre[6] = SDL_CreateTextureFromSurface(render, ImagesLivre[6]);

	for (int i = 1; i < 7; i++) {

		SDL_RenderCopy(render, TextureLivre[i], NULL, NULL);
		SDL_RenderPresent(render);
		if (i != 6) {
			SDL_Delay(70);
		}
	}
	for (int z = 0; z < 7; z++)
	{
		SDL_FreeSurface(ImagesLivre[z]);
		SDL_DestroyTexture(TextureLivre[z]);
	}
	
}

int sauvegarde(int article, int option) {
	int rt = 0;
	if (option == 1) {
		ofstream sauvegarde("sauvegarde.txt", ios::app);
		sauvegarde << endl << article;
		sauvegarde.close();
	}

	if (option == 2) {
		ofstream sauvegarde("sauvegarde.txt", ios::trunc);
		sauvegarde << article;
		sauvegarde.close();
	}

	if (option == 3) {
		ifstream entree("sauvegarde.txt", ios::in);
		while (!entree.eof()) {
			entree >> rt;
		}
		entree.close();
		return rt;
	}
	return 0;
}


void InitializationSDL() {

	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
	{
		cout << "Echec à l’ouverture";
	}

	backgroundSound = Mix_LoadMUS(".\\Music\\Skyrim.mp3");
	

	win = SDL_CreateWindow("LDVELH", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, FEN_LARGEUR, FEN_HAUTEUR, SDL_WINDOW_SHOWN);
	render = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

	TTF_Init();
	font = TTF_OpenFont("C:\\Windows\\Fonts\\calibri.ttf", 18);

}


void menu(SDL_Renderer* render) {

	SDL_Surface* imagemenu = SDL_LoadBMP(".\\Images\\screenmenu.bmp");
	SDL_Surface* NewGame = SDL_LoadBMP(".\\Images\\NewGame.bmp");
	SDL_Surface* Continue = SDL_LoadBMP(".\\Images\\Continue.bmp");
	SDL_Surface* SurfGraphParcouru = SDL_LoadBMP(".\\Images\\GraphParcouru.bmp");
	SDL_Surface* Parcouru = IMG_Load(".\\Images\\Parcouru.png");
	SDL_Surface* SurfExportHTML = IMG_Load(".\\Images\\ExportHTML.png");
	SDL_Surface* GrapheTotale = IMG_Load(".\\Images\\Totale.png");
	SDL_Surface* Quit = IMG_Load(".\\Images\\Quit.png");
	

	SDL_Surface* SurfAudio;
	if (AudioMod)
	{
		SurfAudio = IMG_Load("VolumeOn.png");
	}
	else
	{
		SurfAudio = IMG_Load("VolumeOff.png");
	}


	SDL_Texture* texture = SDL_CreateTextureFromSurface(render, imagemenu);
	SDL_Texture* textureNewGame = SDL_CreateTextureFromSurface(render, NewGame);
	SDL_Texture* textureContinue = SDL_CreateTextureFromSurface(render, Continue);
	SDL_Texture* textureGraphParcouru = SDL_CreateTextureFromSurface(render, SurfGraphParcouru);
	SDL_Texture* textureParcouru = SDL_CreateTextureFromSurface(render, Parcouru);
	SDL_Texture* textureExportHTML = SDL_CreateTextureFromSurface(render, SurfExportHTML);
	SDL_Texture* textureVolume = SDL_CreateTextureFromSurface(render, SurfAudio);
	SDL_Texture* TexteGrapheTotale = SDL_CreateTextureFromSurface(render, GrapheTotale);
	SDL_Texture* textureQuit = SDL_CreateTextureFromSurface(render, Quit);

	SDL_Color PoliceColor = { 90, 90, 255 };

	Audio.w = 50;
	Audio.h = 50;
	Audio.x = FEN_LARGEUR - Audio.w - 5;
	Audio.y = 5;

	rectquit.w = 450;
	rectquit.h = 75;
	rectquit.x = FEN_LARGEUR / 2 - (rectquit.w / 2);
	rectquit.y = 710;

	GrapheParcouru.w = 200;
	GrapheParcouru.h = 30;
	GrapheParcouru.x = FEN_LARGEUR - (200 + 10);
	GrapheParcouru.y = 860;

	RectGrapheTotale.w = GrapheParcouru.w;
	RectGrapheTotale.h = GrapheParcouru.h;
	RectGrapheTotale.x = GrapheParcouru.x;
	RectGrapheTotale.y = GrapheParcouru.y - 80;

	RectExportHTML.w = GrapheParcouru.w;
	RectExportHTML.h = GrapheParcouru.h;
	RectExportHTML.x = GrapheParcouru.x;
	RectExportHTML.y = GrapheParcouru.y - (4 * GrapheParcouru.h / 3);

	rectnewpartie.w = 450;
	rectnewpartie.h = 75;
	rectnewpartie.x = FEN_LARGEUR / 2 - (rectnewpartie.w / 2);
	rectnewpartie.y = 475;

	NewGameRect.w = 450;
	NewGameRect.h = 75;
	NewGameRect.x = FEN_LARGEUR / 2 - (rectnewpartie.w / 2);
	NewGameRect.y = 475;

	ContinueRect.w = 450;
	ContinueRect.h = 75;
	ContinueRect.x = FEN_LARGEUR / 2 - (rectnewpartie.w / 2);
	ContinueRect.y = 594;

	SDL_RenderCopy(render, texture, NULL, NULL);
	SDL_RenderCopy(render, textureNewGame, NULL, &NewGameRect);
	SDL_RenderCopy(render, textureContinue, NULL, &ContinueRect);
	SDL_RenderCopy(render, textureParcouru, NULL, &GrapheParcouru);
	SDL_RenderCopy(render, textureExportHTML, NULL, &RectExportHTML);
	SDL_RenderCopy(render, textureVolume, NULL, &Audio);
	SDL_RenderCopy(render, TexteGrapheTotale, NULL, &RectGrapheTotale);
	SDL_RenderCopy(render, textureQuit, NULL, &rectquit);

	SDL_RenderPresent(render);


	SDL_FreeSurface(imagemenu);
	SDL_FreeSurface(NewGame);
	SDL_FreeSurface(Continue);
	SDL_FreeSurface(SurfGraphParcouru);
	SDL_FreeSurface(Parcouru);
	SDL_FreeSurface(SurfExportHTML);
	SDL_FreeSurface(GrapheTotale);
	SDL_FreeSurface(SurfAudio);
	SDL_FreeSurface(Quit);
	SDL_DestroyTexture(texture);
	SDL_DestroyTexture(textureNewGame);
	SDL_DestroyTexture(textureContinue);
	SDL_DestroyTexture(textureGraphParcouru);
	SDL_DestroyTexture(textureParcouru);
	SDL_DestroyTexture(textureExportHTML);
	SDL_DestroyTexture(textureVolume);
	SDL_DestroyTexture(TexteGrapheTotale);
	SDL_DestroyTexture(textureQuit);
}

void WhiteScreen() {
	SDL_Rect Rectz;
	Rectz.x = 0;
	Rectz.y = 0;
	Rectz.h = FEN_HAUTEUR;
	Rectz.w = FEN_LARGEUR;
	SDL_SetRenderDrawColor(render, 255, 240, 240, 255);
	SDL_RenderFillRect(render, &Rectz);
	SDL_RenderPresent(render);
}

void blackscreen() {
	SDL_Rect Rectp;
	Rectp.x = 0;
	Rectp.y = 0;
	Rectp.h = FEN_HAUTEUR;
	Rectp.w = FEN_LARGEUR;
	SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
	SDL_RenderFillRect(render, &Rectp);
	SDL_RenderPresent(render);
}

void AffichageArticle(Article artic) {
	srand(time(NULL));
	char dest[5000];
	char id[5];
	char perdu[100] = "You lost the game, press \"M\" to return to menu and restart.";
	char gagne[100] = "You have completed quest. Congratulations, you won the game.";
	int RandomNumber = rand() % 6;
	SDL_Color Textcolor = { 0, 0, 0 };

	SDL_Surface* ImageLivreDebut = IMG_Load(".\\ImagesLivre\\image_1.png");
	SDL_Texture* TextureLivre = SDL_CreateTextureFromSurface(render, ImageLivreDebut);
	SDL_RenderCopy(render, TextureLivre, NULL, NULL);

	_itoa_s(artic.id, id, 10);
	TextureLiens = new SDL_Texture *[artic.nbliens];
	RectLiensContenu = new SDL_Rect[artic.nbliens];

	SDL_Surface* SurfAudio;
	if (AudioMod)
	{
		SurfAudio = IMG_Load("VolumeOn.png");
	}
	else
	{
		SurfAudio = IMG_Load("VolumeOff.png");
	}

	SDL_Texture* textureVolume = SDL_CreateTextureFromSurface(render, SurfAudio);
	SDL_RenderCopy(render, textureVolume, NULL, &Audio);

	SDL_Surface* SurfaceContenu = TTF_RenderText_Blended_Wrapped(font, artic.texte, Textcolor, 700);
	SDL_Texture* TextureMessage = SDL_CreateTextureFromSurface(render, SurfaceContenu);

	RectArticleContenu.x = 95;
	RectArticleContenu.y = 125;
	RectArticleContenu.w = 700;
	RectArticleContenu.h = 450;

	SDL_Surface* SurfIdArticle = TTF_RenderText_Blended_Wrapped(font, id, Textcolor, 200);
	SDL_Texture* TextureIdArticle = SDL_CreateTextureFromSurface(render, SurfIdArticle);
	SDL_Rect RectArticleId;
	RectArticleId.x = 95;
	RectArticleId.y = 100;
	RectArticleId.w = 200;
	RectArticleId.h = 30;

	SDL_QueryTexture(TextureMessage, NULL, NULL, &RectArticleContenu.w, &RectArticleContenu.h);
	SDL_QueryTexture(TextureIdArticle, NULL, NULL, &RectArticleId.w, &RectArticleId.h);

	SDL_RenderCopy(render, TextureMessage, NULL, &RectArticleContenu);
	SDL_RenderCopy(render, TextureIdArticle, NULL, &RectArticleId);

	SDL_Surface* Illustration[6];
	Illustration[0] = IMG_Load(".\\Images\\Dragon.png");
	Illustration[1] = IMG_Load(".\\Images\\LOTR.png");
	Illustration[2] = IMG_Load(".\\Images\\Wizard.png");
	Illustration[3] = IMG_Load(".\\Images\\Warrior.png");
	Illustration[4] = IMG_Load(".\\Images\\Tree.png");
	Illustration[5] = IMG_Load(".\\Images\\Sword.png");
	SDL_Texture* TextIllust = SDL_CreateTextureFromSurface(render, Illustration[RandomNumber]);
	SDL_Rect RectIllust;
	RectIllust.x = 1300;
	RectIllust.y = 400;
	RectIllust.w = 300;
	RectIllust.h = 400;
	SDL_RenderCopy(render, TextIllust, NULL, &RectIllust);

	SDL_Surface* SurfDes = IMG_Load(".\\Images\\dice.png");
	SDL_Texture* TextDes = SDL_CreateTextureFromSurface(render, SurfDes);

	RectDes.x = RectIllust.x + 350;
	RectDes.y = 700;
	RectDes.w = 100;
	RectDes.h = 100;

	SDL_RenderCopy(render, TextDes, NULL, &RectDes);

	if (artic.nbliens == 0)
	{
		if (artic.id != 349)
		{			
			SDL_Surface* SurfLost = TTF_RenderText_Blended_Wrapped(font, perdu, Textcolor, 1400);
			SDL_Texture* TextLost = SDL_CreateTextureFromSurface(render, SurfLost);
			SDL_Rect Lost;
			Lost.x = 85;
			Lost.y = 650;
			Lost.w = 1400;
			Lost.h = 50;
			SDL_QueryTexture(TextLost, NULL, NULL, &Lost.w, &Lost.h);
			SDL_RenderCopy(render, TextLost, NULL, &Lost);
			CurrentId = 1;
			sauvegarde(0, 3);
			SDL_FreeSurface(SurfLost);
			RectArticleContenu.w = 0;
			RectArticleContenu.h = 0;
			RectArticleContenu.y = 0;
			RectArticleContenu.x = 0;
		}
		else
		{
			if (artic.id == 349) {
				SDL_Surface* SurfWin = TTF_RenderText_Blended_Wrapped(font, gagne, Textcolor, 1400);
				SDL_Texture* TextWin = SDL_CreateTextureFromSurface(render, SurfWin);
				SDL_Rect Win;
				Win.x = 85;
				Win.y = 650;
				Win.w = 1400;
				Win.h = 50;
				SDL_QueryTexture(TextWin, NULL, NULL, &Win.w, &Win.h);
				SDL_RenderCopy(render, TextWin, NULL, &Win);
				sauvegarde(0, 3);
				SDL_FreeSurface(SurfWin);
				RectArticleContenu.w = 0;
				RectArticleContenu.h = 0;
				RectArticleContenu.y = 0;
				RectArticleContenu.x = 0;
			}
		}
	}
	else {

		for (int i = 0; i < artic.nbliens; i++)
		{

			_itoa_s(artic.tLiens[i].destination, dest, 10);
			strcat_s(dest, 1000, " ");
			strcat_s(dest, 1000, artic.tLiens[i].texte);
			SDL_Surface* SurfLiens = TTF_RenderText_Blended_Wrapped(font, dest, Textcolor, 700);
			TextureLiens[i] = SDL_CreateTextureFromSurface(render, SurfLiens);

			RectLiensContenu[i].x = 1000;
			RectLiensContenu[i].y = 125 + (i * 50);
			RectLiensContenu[i].w = 700;
			RectLiensContenu[i].h = 50;

			SDL_QueryTexture(TextureLiens[i], NULL, NULL, &RectLiensContenu[i].w, &RectLiensContenu[i].h);
			SDL_RenderCopy(render, TextureLiens[i], NULL, &RectLiensContenu[i]);

			SDL_FreeSurface(SurfLiens);
		}
	}



	SDL_FreeSurface(SurfaceContenu);
	SDL_FreeSurface(SurfIdArticle);
	SDL_FreeSurface(SurfDes);
	SDL_RenderPresent(render);

}

void importation(Article articles[], int TAILLE) {

	//variables fonction temporaires
	char tmp[100000];
	int NbArticle;

	ifstream livre("testExport.lb", ios::in);


	//test ifstream
	if (!livre)
	{
		cout << "Error";
	}

	else
	{
		//on saute la premiere ligne inutile"""
		livre.getline(tmp, 10000, '\n');

		for (int j = 0; j < TAILLE; j++) {
			//on stocke le numero de l'article
			livre.getline(tmp, 10000, ',');
			articles[j].id = atoi(tmp);
			
			//on stocke le texte associe a l'article dans un tableau dynamique
			articles[j].texte = new char[10000];
			livre.getline(tmp, 10000);
			strcpy_s(articles[j].texte, 10000, tmp);

			//on stocke le nombre de liens associes a l'article
			livre.getline(tmp, 10000, '\n');
			NbArticle = atoi(tmp);

			//pour le liens associes on a cree un tableau dynamique de type Lien de la taille du nombre de liens associes a l'article
			//qui stocke les liens
			articles[j].nbliens = NbArticle;
			articles[j].tLiens = new Lien[NbArticle];

			//on cree une boucle qui s'occupe de stocker les infos des liens dans le tableau
			for (int i = 0; i < NbArticle; i++) {
				//on stocke et attribue la valeur du lien 
				livre.getline(tmp, 10000, ',');
				articles[j].tLiens[i].destination = atoi(tmp);
				//on stocke le texte du lien dans un tableau dynamique
				livre.getline(tmp, 10000, '\n');
				articles[j].tLiens[i].texte = new char[10000];
				strcpy_s(articles[j].tLiens[i].texte, 10000, tmp);

			}
		}
	}
	livre.close();
}

void exportHTML() {
	ofstream page("page.html", ios::out);

	page << "<!DOCTYPE html>" << endl << "<html>" << endl << "<head>" << endl << "<link href=\"Style.css\" rel=\"stylesheet\">" << endl << "<meta charset = \"utf-8\">" << endl << "<title>LJDVELH</title>" << endl << "</head>" << endl << "<body>" << endl;
	for (int j = 0; j < TAILLE; j++) {
		//on stocke le numero de l'article

		page << "<div class=\"" << "ch" << articles[j].id << "\"></div>" << endl;
		page << "<p id = \"ArticleID" << articles[j].id << "\">" << "</p>" << endl;

		//on stocke le texte associe a l'article dans un tableau dynamique

		page << "<p class = \"ContenuArticle" << articles[j].id << "\">" << articles[j].id << " : " << articles[j].texte << "</p><br>" << endl;

		//on stocke le nombre de liens associes a l'article

		//pour le liens associes on a cree un tableau dynamique de type Lien de la taille du nombre de liens associes a l'article
		//qui stocke les liens

		//on cree une boucle qui s'occupe de stocker les infos des liens dans le tableau
		for (int i = 0; i < articles[j].nbliens; i++) {

			page << "<h4><a href=\"#ArticleID" << articles[j].tLiens[i].destination << "\">" << articles[j].tLiens[i].destination << " , " << articles[j].tLiens[i].texte << "</a></h4>" << endl << "<br>" << endl;

		}
	}

	page << "<style type = \"text/css\">" << endl << "<style type = \"text/css\">";
	for (int z = 0; z < TAILLE; z++) {
		page << "div.ch" << articles[z].id << "{ height : " << 1080 << "px; }" << endl;
		page << "body{ height: " << 1080 * TAILLE << "px; }" << endl;
	}


	page << "</style>" << endl << "</body>" << endl << "</html>" << endl;
	page.close();


}

void SupprimeAlloc() {
	//on ferme les tableaux dynamiques crées
	for (int a = 0; a < TAILLE; a++) {
		delete[] articles[a].texte;
		for (int b = 0; b < articles[a].nbliens; b++) {
			delete[] articles[a].tLiens[b].texte;
		}
		delete articles[a].tLiens;
	}
	delete[] RectLiensContenu;
	delete[] TextureLiens;
}


void reptab(Article source[], Noeud noeuds[]) {
	int taillei;
	int compt = 2;

	int SourceSur[50];
	int comptsur = 1;

	

	NomLignes = new int[1];
	for (int i = 0; i < TAILLE; i++) {
		noeuds[i].article = &source[i];

	}

	NomLignes[0] = 1;
	NbLiens = source[0].nbliens;
	noeuds[0].x = 5;
	noeuds[0].y = (FEN_HAUTEUR / 2);


	SourceSur[0] = 1;

	do {

		taillei = NbLiens;
		NbLiens = 0;

		for (int le = 0; le < comptsur; le++) {
			NbLiens = NbLiens + source[SourceSur[le] - 1].nbliens;
		}

		if (NbLiens > 0) {
			int* TabDest = new int[NbLiens];
			int compteur = 0;

			for (int tn = 0; tn < comptsur; tn++) {
				for (int nl = 0; nl < source[SourceSur[tn] - 1].nbliens; nl++) {
					cout << source[NomLignes[tn] - 1].tLiens[nl].destination << endl;
					TabDest[compteur] = source[SourceSur[tn] - 1].tLiens[nl].destination;
					compteur++;
				}
			}

			NomLignes = TabDest;
			comptsur = 0;
			for (int a = 0; a < NbLiens; a++) {

				if (noeuds[NomLignes[a] - 1].x == 1) {
					noeuds[NomLignes[a] - 1].x = 9 * 2 * compt;

					cout << NomLignes[a] << "   :    " << noeuds[NomLignes[a] - 1].x << endl;
					SourceSur[comptsur] = NomLignes[a];

					comptsur++;
				}

			}

			SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
			for (int d = 0; d < comptsur; d++) {
				noeuds[SourceSur[d] - 1].y = (((FEN_HAUTEUR / 2) - 10) - (40 * d)) + (((comptsur + comptsur - 1) * 20) / 2);
				cout << "y" << "    -    " << noeuds[SourceSur[d] - 1].y << endl;
				
			};

			compt++;
		}
	} while (NbLiens >= 1);
	SDL_RenderPresent(render);
	cout << "ok" << endl;
}

void descarre(Noeud noeuds[]) {
	char NumCase[500];
	
	rect.w = 9;
	rect.h = 20;
	rect.x = noeuds[0].x;
	rect.y = noeuds[0].y;
	SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
	SDL_RenderDrawRect(render, &rect);
	SurfaceGrapheTotale = TTF_RenderText_Solid(font, "1", TextColorGrapheTotale);
	TextureGrapheTotale = SDL_CreateTextureFromSurface(render, SurfaceGrapheTotale);

	SDL_QueryTexture(TextureGrapheTotale, NULL, NULL, &rect.w, &rect.h);
	SDL_RenderCopy(render, TextureGrapheTotale, NULL, &rect);

	for(int i = 0; i < 350; i++) {
		rect.x = noeuds[i].x;
		cout << endl << "ex   =    " << rect.x << endl;
		rect.y = noeuds[i].y;
		cout << endl << "ey   =    " << rect.y << endl;

		SDL_RenderFillRect(render, &rect);
		_itoa_s(i+1, NumCase, 10);
		SurfaceGrapheTotale = TTF_RenderText_Solid(font, NumCase, TextColorGrapheTotale);
		TextureGrapheTotale = SDL_CreateTextureFromSurface(render, SurfaceGrapheTotale);

		SDL_QueryTexture(TextureGrapheTotale, NULL, NULL, &rect.w, &rect.h);
		SDL_RenderCopy(render, TextureGrapheTotale, NULL, &rect);

	}
	SDL_RenderPresent(render);
}

void cheminfait(Noeud noeuds[]) {
	char bin[5000];
	int i = 0;
	ifstream entree("sauvegarde.txt", ios::in);
	if (!entree) {
		cout << "erreur ouverture sauvgarde.txt" << endl;
	}
	else {
		while (!entree.eof()) {
			entree.getline(bin, 500);
			i = atoi(bin);
			rect.x = noeuds[i-1].x;
			rect.y = noeuds[i-1].y;
			SDL_SetRenderDrawColor(render, 0, 255, 0, 255);
			SDL_RenderFillRect(render, &rect);
			
			SurfaceGrapheTotale = TTF_RenderText_Solid(font, bin, TextColorGrapheTotale);
			TextureGrapheTotale = SDL_CreateTextureFromSurface(render, SurfaceGrapheTotale);

			SDL_QueryTexture(TextureGrapheTotale, NULL, NULL, &rect.w, &rect.h);
			SDL_RenderCopy(render, TextureGrapheTotale, NULL, &rect);
		
			SDL_RenderPresent(render);
		}
	}
}

void dessarete(Article articles[], Noeud tab[]) {
	Arete* trait;
	SDL_SetRenderDrawColor(render, 255, 255, 255, 255);

	for (int i = 0; i < TAILLE; i++) {
		Arete Trait;
		Trait.origine = &tab[i];
		for (int a = 0; a < articles[i].nbliens; a++) {
			Trait.destination = &tab[(articles[i].tLiens[a].destination) - 1];
			SDL_RenderDrawLine(render, Trait.destination->x + 4, Trait.destination->y + 10, Trait.origine->x + 4, Trait.origine->y + 10);

		};

	};
	//SDL_RenderPresent(render);
}


int comptlignesauvegarde(int& cpt, int tab[]) {
	char bin[5000];
	int i = 0;
	ifstream entree("sauvegarde.txt", ios::in);
	if (!entree) {
		cout << "erreur ouverture sauvgarde.txt" << endl;
	}
	else {
		while (!entree.eof()) {
			entree.getline(bin, 500);
			cout << bin << endl;
			tab[i] = atoi(bin);
			cout << tab[i] << endl;
			cpt++;
			i++;
		}
	}
	return cpt;
}

void AudioAffichage() {
	SDL_Surface* SurfAudio;
	if (AudioMod)
	{
		SurfAudio = IMG_Load("VolumeOn.png");
	}
	else
	{
		SurfAudio = IMG_Load("VolumeOff.png");
	}
	SDL_Texture* textureVolume = SDL_CreateTextureFromSurface(render, SurfAudio);
	SDL_RenderCopy(render, textureVolume, NULL, &Audio);
	SDL_RenderPresent(render);
}

void menuGraphe() {
	int cpt = 0;
	int nbblocparligne = 24;
	int CharStock[1000];
	int NbDeLigne;
	blackscreen();
	SDL_Color PoliceColor = { 41, 128, 185 };
	SDL_Rect TextePositionGraphe;
	SDL_Rect* GrapheRect;
	GrapheRect = new SDL_Rect[comptlignesauvegarde(cpt, CharStock)];
	NbDeLigne = (cpt / (nbblocparligne + 1)) + 2;
	if (NbDeLigne == 1 || NbDeLigne == 0)
	{
		NbDeLigne = 2;
	}
	SDL_SetRenderDrawColor(render, 236, 240, 241, 255);
	char bin2[10];
	char tab2char[20];


	for (int z = 0; z < NbDeLigne * 2; z++)
	{
		SDL_RenderDrawLine(render, 20, (FEN_HAUTEUR / NbDeLigne) * z, 1880, (FEN_HAUTEUR / NbDeLigne) * z);
	}

	for (int i = 0; i < cpt; i++) {
		_itoa_s(articles[i].id, bin2, 10);
		_itoa_s(CharStock[i], tab2char, 10);

		GrapheRect[i].h = 50;
		GrapheRect[i].w = 50;
		GrapheRect[i].y = FEN_HAUTEUR / NbDeLigne * ((i / nbblocparligne) + 1) - (GrapheRect[i].h / 2);

		if (i < nbblocparligne)
		{
			GrapheRect[i].x = i * 75 + 50;
		}
		else
		{
			GrapheRect[i].x = (i - ((i / nbblocparligne) * nbblocparligne)) * 75 + 50;
		}

		TextePositionGraphe.h = GrapheRect[i].h - 20;
		TextePositionGraphe.w = GrapheRect[i].w - 25;
		TextePositionGraphe.y = GrapheRect[i].y + (25 / 2);
		TextePositionGraphe.x = GrapheRect[i].x + (25 / 2);

		SDL_RenderFillRect(render, &GrapheRect[i]);
		SDL_Surface* surfaceMessage = TTF_RenderText_Blended(font, tab2char, PoliceColor);
		SDL_Texture* Message = SDL_CreateTextureFromSurface(render, surfaceMessage);
		SDL_RenderCopy(render, Message, NULL, &TextePositionGraphe);
	}

	SDL_RenderPresent(render);
	
	delete[]GrapheRect;
}

void des() {
	int tirage = (rand() % 11) + 1;
	char de[3];
	cout << tirage << endl;
	_itoa_s(tirage, de, 10);
	SDL_Color noir = { 0,0,0 };
	SDL_Surface* SurfaceTexte = TTF_RenderText_Blended_Wrapped(font, de, noir, 30);
	SDL_Texture* TextureTexte = SDL_CreateTextureFromSurface(render, SurfaceTexte);
	SDL_Rect Texte;
	Texte.x = RectDes.x + 42;
	Texte.y = RectDes.y - 20;
	Texte.h = 22;
	Texte.w = 50;
	SDL_SetRenderDrawColor(render, 240, 225, 178, 255);
	SDL_RenderFillRect(render, &Texte);
	SDL_QueryTexture(TextureTexte, NULL, NULL, &Texte.w, &Texte.h);
	SDL_RenderCopy(render, TextureTexte, NULL, &Texte);
	SDL_FreeSurface(SurfaceTexte);
	SDL_RenderPresent(render);
}

//------------------Main--------------------//
int main(int argc, char* argv[]) {
	srand(time(NULL));

	bool Modmenu = true;
	bool continuer = true;
	bool GameMod = false;
	bool GrapheCouru = false;
	bool GrapheTotale = false;
	CurrentId = 1;
	int tab[NBArticle];
	SDL_Event event;
	Noeud tabNoeud[TAILLE];

	importation(articles, TAILLE);
	InitializationSDL();
	Mix_PlayMusic(backgroundSound, -1);
	Mix_VolumeMusic(5);
	menu(render);

	cout << articles[0].nbliens;

	if (win == NULL) {
		cout << "erreur ouverture fenetre";
	}

	//---------------------Boucle Principale------------------------//
	while (continuer) {

		SDL_WaitEvent(&event);//attente d’un évènement
		switch (event.type) {

		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_m) {
				menu(render);
				Modmenu = true;
			}
			break;

		case SDL_MOUSEBUTTONUP://appui souris

			if (event.button.button == SDL_BUTTON_LEFT) {//si on clique bouton gauche
				if (Modmenu)
				{
					if (event.button.x > rectnewpartie.x&& event.button.x < rectnewpartie.x + rectnewpartie.w && event.button.y > rectnewpartie.y&& event.button.y < rectnewpartie.y + rectnewpartie.h) { //dans 	le rectangle
						cout << "ca marche";
						Modmenu = false;
						GameMod = true;
						sauvegarde(1, 2);
						AffichageArticle(articles[CurrentId - 1]);

					}
					if (event.button.x > rectquit.x&& event.button.x < rectquit.x + rectquit.w && event.button.y > rectquit.y&& event.button.y < rectquit.y + rectquit.h) {
						continuer = false;
					}
					if (event.button.x > ContinueRect.x && event.button.x < ContinueRect.x + +ContinueRect.w && event.button.y > ContinueRect.y && event.button.y < ContinueRect.y + ContinueRect.h) {

						Modmenu = false;
						GameMod = true;
						CurrentId = sauvegarde(0, 3);
						AffichageArticle(articles[CurrentId - 1]);

					}
					if (event.button.x > GrapheParcouru.x&& event.button.x < GrapheParcouru.x + GrapheParcouru.w && event.button.y > GrapheParcouru.y&& event.button.y < GrapheParcouru.y + GrapheParcouru.h) {
						menuGraphe();

						GrapheCouru = true;
						while (GrapheCouru)
						{
							SDL_WaitEvent(&event);
							switch (event.type) {
							case SDL_KEYDOWN:
								if (event.key.keysym.sym == SDLK_m) {
									menu(render);
									Modmenu = true;
									GrapheCouru = false;
								}
								break;
							case SDL_QUIT:
								continuer = false;
								GrapheCouru = false;
								break;
							}
						}
					}
					if (event.button.x > RectGrapheTotale.x&& event.button.x < RectGrapheTotale.x + RectGrapheTotale.w && event.button.y > RectGrapheTotale.y&& event.button.y < RectGrapheTotale.y + RectGrapheTotale.h) {
						blackscreen();
						reptab(articles, tabNoeud);
						
						dessarete(articles, tabNoeud);
						descarre(tabNoeud);

						cheminfait(tabNoeud);

						GrapheTotale = true;
						while (GrapheTotale)
						{
							SDL_WaitEvent(&event);
							switch (event.type) {
							case SDL_KEYDOWN:
								if (event.key.keysym.sym == SDLK_m) {
									menu(render);
									Modmenu = true;
									GrapheTotale = false;
								}
								break;
							case SDL_QUIT:
								continuer = false;
								GrapheTotale = false;
								break;
							}
						}
					}
					if (event.button.x > Audio.x&& event.button.x < Audio.x + Audio.w && event.button.y > Audio.y&& event.button.y < Audio.y + Audio.h) {
						if (AudioMod)
						{
							AudioMod = false;
							Mix_VolumeMusic(0);
						}
						else
						{
							AudioMod = true;
							Mix_VolumeMusic(5);
						}
						AudioAffichage();
						break;
					}
					if (event.button.x > RectExportHTML.x&& event.button.x < RectExportHTML.x + RectExportHTML.w && event.button.y > RectExportHTML.y&& event.button.y < RectExportHTML.y + RectExportHTML.h) {
						exportHTML();
						break;
					}
				}

				SDL_RenderPresent(render);//on rafraichit
			}
			break;
		case SDL_QUIT:
			continuer = false;
			break;

		}

		while (GameMod)
		{

			SDL_WaitEvent(&event);
			switch (event.type) {
			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_m) {
					menu(render);
					Modmenu = true;
					GameMod = false;
					CurrentId = 1;
				}
				break;

			case SDL_MOUSEBUTTONUP://appui souris

				if (event.button.button == SDL_BUTTON_LEFT) {//si on clique bouton gauche

					if (event.button.x > 1000 && event.button.x < 1000 + 700 && event.button.y > 125 && event.button.y < 125 + (articles[CurrentId - 1].nbliens * 50)) {

						int clicy = event.button.y - 125;
						int destina = clicy / 50;
						CurrentId = articles[CurrentId - 1].tLiens[destina].destination;
						sauvegarde(CurrentId, 1);
						AnimLivre();
						AffichageArticle(articles[CurrentId - 1]);
					}
					if (event.button.x > Audio.x&& event.button.x < Audio.x + Audio.w && event.button.y > Audio.y&& event.button.y < Audio.y + Audio.h) {
						if (AudioMod)
						{
							AudioMod = false;
							Mix_VolumeMusic(0);
						}
						else
						{
							AudioMod = true;
							Mix_VolumeMusic(5);
						}
						AudioAffichage();
						break;
					}
					if (event.button.x > RectDes.x && event.button.x< RectDes.x + RectDes.w && event.button.y > RectDes.y && event.button.y < RectDes.y + RectDes.h) {
						des();
					}
				}

			case SDL_MOUSEMOTION:


				if (event.motion.x > 1000 && event.motion.x < 1000 + 700 && event.motion.y > 125 && event.motion.y < 125 + (articles[CurrentId - 1].nbliens * 50))
				{
					SDL_SetRenderDrawColor(render, 240, 225, 178, 0);
					SDL_RenderDrawRect(render, &RectLiensContenu[dest]);
					dest = (event.motion.y - 125) / 50;
					SDL_SetRenderDrawColor(render, 0, 0, 255, 255);
					SDL_RenderDrawRect(render, &RectLiensContenu[dest]);
					SDL_RenderPresent(render);
				}
				else {		
					SDL_SetRenderDrawColor(render, 240, 225, 178, 0);
					SDL_RenderDrawRect(render, &RectLiensContenu[dest]);
					SDL_RenderPresent(render);
				}
				break;

			case SDL_QUIT:
				GameMod = false;
				continuer = false;
				break;

			}
		}
	}

	//------------------FIN Boucle Principale-----------------------//
	SupprimeAlloc();
	TTF_CloseFont(font);
	TTF_Quit();
	SDL_DestroyRenderer(render);
	SDL_DestroyWindow(win);//equivalent du delete
	Mix_CloseAudio();
	Mix_FreeMusic(backgroundSound);
	SDL_Quit();
	return 0;
}
