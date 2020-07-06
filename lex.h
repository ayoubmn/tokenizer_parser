

#ifndef COMPILATION_LEX_H
#define COMPILATION_LEX_H

#include <stdbool.h>
#include <stdio.h>

#define IDFSIZE 20 // taille maximal d'un identificateur
#define NUMBERSIZE 11 // talle maximal d'un nombre


FILE *fichier ;

typedef enum{
    //other tokens
            ID_TOKEN, NUM_TOKEN, ERROR_TOKEN,EOF_TOKEN,
    //keyword tokens
            PROGRAM_TOKEN, CONST_TOKEN, VAR_TOKEN, BEGIN_TOKEN, END_TOKEN, IF_TOKEN, THEN_TOKEN, WHILE_TOKEN, DO_TOKEN, READ_TOKEN, WRITE_TOKEN,
    //symboles
            PV_TOKEN, PT_TOKEN, PLUS_TOKEN, MOINS_TOKEN, MULT_TOKEN, DIV_TOKEN, VIR_TOKEN, AFF_TOKEN, INF_TOKEN, INFEG_TOKEN, SUP_TOKEN, SUPEG_TOKEN, DIFF_TOKEN,
    PO_TOKEN, PF_TOKEN, FIN_TOKEN,EG_TOKEN,DP_TOKEN
}CODES_LEX;

//------------------------------------ERRORS----------------------------------------

typedef enum {IF_ER,DO_ER,END_ER,VAR_ER,THEN_ER,READ_ER,CONST_ER,WHILE_ER,
    BEGIN_ER,WRITE_ER,PROGRAM_ER,EG_ER,PV_ER,PT_ER,PLUS_ER,MOINS_ER,
    MULT_ER,DIV_ER,VIR_ER,SUP_ER,SUPEG_ER,INFEG_ER,DIFF_ER,
    PO_ER,PF_ER,INF_ER,AFF_ER,ERREUR_ER,ID_ER,NUM_ER,EOF_ER,FIN_ER
}ERREURS;

typedef struct token{
    CODES_LEX CODE;
     char NOM[20];
}token;




token Sym_Cour;



CODES_LEX estSpecial( char* c);//si la chaine courante est un special
CODES_LEX estMotcle(char* ch);//si la chaine courante est un mot cle
bool estAlphabet(char c); //si le caractere courant est un alphabet
bool estNumerique(char c);//si le caractere courant est un nombre
bool estSymbole(char c);//si le caractere courant est un symbole
bool estVide(char car);//si le caractere courant est une tabulation ou retour a la ligne
token lireFichier();//la fonction principale
char Lire_Car(FILE* fich);//caractere suivant
void afficherEr(ERREURS erreur);//affichage des erreurs
void setfichier(FILE *fich);//transferer le fichier a l'analyseur lexical

#endif //COMPILATION_LEX_H




