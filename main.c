
#include <stdio.h>
#include "syntx.h"



int main(int argc, char *argv[]){
    FILE *fich=fopen("C:\\Users\\toshiba\\CLionProjects\\compilation\\ex.txt", "r") ;
    setfichier(fich);
    if (fich==NULL)
        printf("error ");
    else{
        token Tab_tokens[100];
        int i=0;
        while(Sym_Cour.CODE != EOF){
            Tab_tokens[i]=lireFichier();
            afficherSymb(Tab_tokens[i].CODE);
            i++;

        }
    }
    lireFichier();
    printf("\nFin de l'analyse lexicale \n");
    fclose(fich);


    FILE *fich2=fopen("C:\\Users\\toshiba\\CLionProjects\\compilation\\ex.txt", "r") ;
    printf("\n************ANALYSEUR SYNTAXIQUE*********\n");
    setfichier(fich2);
    if (fich2==NULL)
        printf("error ");
    else{
        token Tab[100];
        int i=0;
        Sym_Cour.CODE=PT_TOKEN;
        while(Sym_Cour.CODE != EOF){
            Tab[i]=lireFichier();
            Sym_Cour.CODE=Tab[i].CODE;
            PROGRAM();
            i++;

        }
    }
    lireFichier();
    if(Sym_Cour.CODE == EOF)
        printf("\nFin de l'analyse syntaxique -- succes --\n");
    else printf("\nProgramme erronée");
    fclose(fich2);

    return 1;
}
