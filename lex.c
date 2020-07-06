#include<stdio.h>
#include<string.h>
#include<errno.h>
#include<stdlib.h>
#include "lex.h"

#define IDFSIZE 20 // taille maximal d'un identificateur
#define NUMBERSIZE 11 // talle maximal d'un nombre

token nomToken[] = {{PROGRAM_TOKEN,"program"},{CONST_TOKEN,"const"},{VAR_TOKEN,"var"},{BEGIN_TOKEN, "begin"},
                    {END_TOKEN,"end"}, {IF_TOKEN,"if"}, {THEN_TOKEN,"then"}, {WHILE_TOKEN, "while"}, {DO_TOKEN,"do"},
                    {READ_TOKEN, "read"}, {WRITE_TOKEN, "write"}};

token symboleToken[] = {{MULT_TOKEN,"*"}, {PT_TOKEN, "."}, {VIR_TOKEN, ","}, {PV_TOKEN, ";"}, {PO_TOKEN, "("},
                        {PF_TOKEN,")"}, {MOINS_TOKEN, "-"}, {PLUS_TOKEN, "+"}, {DIV_TOKEN, "/"}, {EG_TOKEN, "="},{DP_TOKEN, ":"},
                        {INF_TOKEN, "<"}, {SUP_TOKEN, ">"}};
token SpecialToken[] = {  {INFEG_TOKEN, "<="}, {SUPEG_TOKEN, ">="}, {DIFF_TOKEN, "<>"},{AFF_TOKEN, ":="},
                        {FIN_TOKEN, "EOF"}};


char* keyword_token[] = {"program", "const", "var", "begin", "end", "if", "then", "while", "do", "read", "write"};
char*  keyword_code[]={"PROGRAM_TOKEN", "CONST_TOKEN", "VAR_TOKEN", "BEGIN_TOKEN", "END_TOKEN", "IF_TOKEN", "THEN_TOKEN", "WHILE_TOKEN", "DO_TOKEN", "READ_TOKEN", "WRITE_TOKEN"};
int keyword_token_size = sizeof(keyword_token)/sizeof(keyword_token[0]);


char symbole_token[] = {'*', '.', ',', ';', '(', ')', '-', '+','/','<','>',':','='};
char* symbole_code[] = {"MULT_TOKEN", "PT_TOKEN", "VR_TOKEN", "PV_TOKEN","PO_TOKEN", "PF_TOKEN", "MOINS_TOKEN", "PLUS_TOKEN", "DIV_TOKEN","INF_TOKEN","SUP_TOKEN","DP_TOKEN","EG_TOKEN"};
int symbole_token_size = sizeof(symbole_token)/sizeof(symbole_token[0]);



char* special_token[] = {"<=", ">=", "<>", ":=","EOF"};
char*  special_code[]={"INFEG_TOKEN", "SUPEG_TOKEN", "DIFF_TOKEN", "AFF_TOKEN","FIN_TOKEN"};
int special_token_size = sizeof(special_token)/sizeof(special_token[0]);

/*les fonctions de validation*/



CODES_LEX estMotcle(char* ch){
    for(int i = 0; i < keyword_token_size; i++){
        if(strcmp(ch, keyword_token[i]) == 0){
            Sym_Cour.CODE = nomToken[i].CODE;
            strcpy(Sym_Cour.NOM, nomToken[i].NOM);
            return Sym_Cour.CODE;
        }
    }
    Sym_Cour.CODE = ID_TOKEN;
    strcpy(Sym_Cour.NOM, ch);
    return Sym_Cour.CODE;
}

CODES_LEX estSpecial(char* ch){
    for(int i = 0; i < special_token_size; i++){
        if(strcmp(ch, special_token[i]) == 0){
            Sym_Cour.CODE = SpecialToken[i].CODE;
            strcpy(Sym_Cour.NOM, SpecialToken[i].NOM);
            return Sym_Cour.CODE;
        }
    }
    return ID_TOKEN;
}


bool estAlphabet(char c){
    if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_'){
        return true;
    }
    return false;
}


bool estNumerique(char c){
    if(c >= '0' && c <= '9'){
        return true;
    }
    return false;
}

bool estSymbole(char c){
    if(c == '+' || c == '(' || c == ')' || c == ';' || c == ',' || c == '&' || c == '*' || c == '.' || c == '/' || c == '-'|| c == '<' || c == '>'|| c == '=' ){
        return true;
    }
    return false;
}

bool estVide(char car){
    if(car == ' ' || car == '\t' || car == '\r' || car == '\n'){
        return true;
    }
    return false;
}


//lire le caractere suivant
char Lire_Car(FILE* fich){
    char Car_Cour= (char) fgetc(fich);
    return Car_Cour;
}

void setfichier(FILE *fich){
    fichier=fich;
}


//**********************************************************************************************************************

/*lecture*/
token lireFichier(){

    char Car_Cour;
    Car_Cour = Lire_Car( fichier);
    int i = 0;
    char* number = (char *)calloc(NUMBERSIZE,sizeof(char));
    char* chaine = (char *)calloc(IDFSIZE,sizeof(char));

        while(estVide(Car_Cour))
            Car_Cour=Lire_Car(fichier);

//-----------------------------------------------------------------numerique--------------------------------------------
        if(Car_Cour==EOF) {
            Sym_Cour.CODE = EOF;
            return Sym_Cour;


        }else if (estNumerique(Car_Cour)) {
            do {
                number[i] = Car_Cour;
                Sym_Cour.NOM[i]=Car_Cour;

                Car_Cour = Lire_Car(fichier); //lire le caractere suivant

                i++;
            } while (estNumerique(Car_Cour));
            Sym_Cour.CODE=NUM_TOKEN;
            return Sym_Cour;

        }

//-----------------------------------------------------------------Alphabet---------------------------------------------
        else if (estAlphabet(Car_Cour)) {
            Sym_Cour.NOM[i]=Car_Cour;
            chaine[i] = Car_Cour;
            Car_Cour= (char) fgetc(fichier);
            while( estAlphabet(Car_Cour)|| estNumerique(Car_Cour)){
                i++;
                Sym_Cour.NOM[i]=Car_Cour;
                chaine[i] = Car_Cour;
                Car_Cour=(char) fgetc(fichier);

            }
            /*for(int j=0;j<keyword_token_size;j++){
                if (strcmp( nomToken[j].NOM , Sym_Cour.NOM) == 0)
                    return nomToken[j];
            }*/
            Sym_Cour.CODE=  estMotcle(chaine);
            return Sym_Cour;
        }

        //-------------------------------------------------------------------Symbole------------------------------------
        else if (estSymbole(Car_Cour)||Car_Cour==':') {
            i =0;
            do {
                chaine[i] = Car_Cour;
                for( int j=0;j<symbole_token_size;j++){
                    if( Car_Cour == *symboleToken[j].NOM) {
                        Sym_Cour.CODE = symboleToken[j].CODE;
                        break;
                    }
                }
                Car_Cour = Lire_Car(fichier); //lire le caractere suivant
                i++;
            } while (estSymbole(Car_Cour));
            if(estSpecial(chaine)!=ID_TOKEN)
                Sym_Cour.CODE=estSpecial(chaine);
            return Sym_Cour;

    }else
        return Sym_Cour;


}



//affichage des erreurs
void afficherEr(ERREURS erreur){

    switch(erreur)
    {
        case IF_ER:
            printf("IF_ER \n");
            break;
        case PROGRAM_ER:
            printf("PROGRAM_ER \n");
            break;
        case CONST_ER:
            printf("CONST_ER \n");
            break;
        case VAR_ER:
            printf("VAR_ER \n");
            break;
        case BEGIN_ER:
            printf("BEGIN_ER \n");
            break;
        case END_ER:
            printf("END_ER \n");
            break;
        case THEN_ER:
            printf("THEN_ER \n");
            break;
        case WHILE_ER:
            printf("WHILE_ER \n");
            break;
        case DO_ER:
            printf("DO_ER \n");
            break;
        case READ_ER:
            printf("READ_ER \n");
            break;
        case WRITE_ER:
            printf("WRITE_ER \n");
            break;
        case PV_ER:
            printf("PV_ER \n");
            break;
        case PT_ER:
            printf("PT_ER \n");
            break;
        case PLUS_ER:
            printf("PLUS_ER \n");
            break;
        case MOINS_ER:
            printf("MOINS_ER \n");
            break;
        case MULT_ER:
            printf("MULT_ER \n");
            break;
        case DIV_ER:
            printf("DIV_ER \n");
            break;
        case VIR_ER:
            printf("VIR_ER \n");
            break;
        case AFF_ER:
            printf("AFF_ER \n");
            break;
        case INF_ER:
            printf("INF_ER \n");
            break;
        case INFEG_ER:
            printf("INFEG_ER \n");
            break;
        case SUP_ER:
            printf("SUP_ER \n");
            break;
        case SUPEG_ER:
            printf("SUPEG_ER \n");
            break;
        case DIFF_ER:
            printf("DIFF_ER \n");
            break;
        case PO_ER:
            printf("PO_ER \n");
            break;
        case PF_ER:
            printf("PF_ER \n");
            break;
        case FIN_ER:
            printf("FIN_ER \n");
            break;
        case ID_ER:
            printf("ID_ER \n");
            break;
        case NUM_ER:
            printf("NUM_ER \n");
            break;
        case ERREUR_ER:
            printf("ERREUR_ER \n");
            break;
        case EOF_ER:
            printf("EOF_ER \n");
            break;

        case EG_ER:
            printf("EG_ER \n");
            break;
        default:
            break;
    }

}



