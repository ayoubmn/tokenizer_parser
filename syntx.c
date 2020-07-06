#include "syntx.h"

void Test(CODES_LEX code , ERREURS erreur){
    CODES_LEX c= Sym_Cour.CODE;
    if(Sym_Cour.CODE==code)
        lireFichier();
    else
        afficherEr(erreur);
}
void CONSTS(){
    switch (Sym_Cour.CODE)	{
        case CONST_TOKEN:
            lireFichier();
            Test(ID_TOKEN,ID_ER);
        loop1:
            Test(EG_TOKEN,EG_ER);
            Test(NUM_TOKEN,	NUM_ER);
            Test(PV_TOKEN,	PV_ER);
            if(Sym_Cour.CODE == ID_TOKEN){
                lireFichier();
                goto loop1;}

            break;
        case VAR_TOKEN:
            break;
        case BEGIN_TOKEN:
            break;
        default:

            afficherEr(CONST_ER) ;

            break;
    }
}


void VARS()	{
    switch (Sym_Cour.CODE){
        case VAR_TOKEN:
            lireFichier();
            Test(ID_TOKEN,	ID_ER);
            while (Sym_Cour.CODE==VIR_TOKEN){
                lireFichier();
                Test(ID_TOKEN,	ID_ER);
            }
            Test(PV_TOKEN,	PV_ER);
            break;
        case BEGIN_TOKEN:
            break;
        default:
            afficherEr(CONST_ER) ;
            break;
    }
}

void INSTS(){
    Test(BEGIN_TOKEN, BEGIN_ER);
    INST();
    while(Sym_Cour.CODE != END_TOKEN && Sym_Cour.CODE != FIN_TOKEN)
    {
        Test(PV_TOKEN,PV_ER);
        INST();
    }
    Test(END_TOKEN,END_ER);
}

void INST(){
    switch(Sym_Cour.CODE){
        case BEGIN_TOKEN:
            INSTS();
            break;
        case ID_TOKEN:
            AFFEC();
            break;
        case IF_TOKEN:
            SI();
            break;
        case WHILE_TOKEN:
            TANTQUE();
            break;
        case WRITE_TOKEN:
            ECRIRE();
            break;
        case READ_TOKEN:
            LIRE();
            break;

    }

}


void CAS(){
    lireFichier();
    Test(ID_TOKEN,ID_ER);
    Test(NUM_TOKEN,NUM_ER);
    INST();
    while(Sym_Cour.CODE == NUM_TOKEN)
    {
        lireFichier();
        INST();
    }

    Test(END_TOKEN, END_ER);

}


void POUR(){
    lireFichier();
    Test(ID_TOKEN,ID_ER);
    Test(AFF_TOKEN,AFF_ER);
    Test(NUM_TOKEN,NUM_ER);
    Test(DO_TOKEN,DO_ER);
    INST();

}




void ECRIRE(){
    lireFichier();
    Test(PO_TOKEN,PO_ER);
    EXPR();
    while(Sym_Cour.CODE == VIR_TOKEN)
    {
        lireFichier();
        EXPR();
    }
    Test(PF_TOKEN,PF_ER);

}

void LIRE(){
    lireFichier();
    Test(PO_TOKEN,PO_ER);
    Test(ID_TOKEN,ID_ER);
    while(Sym_Cour.CODE == VIR_TOKEN)
    {
        lireFichier();
        Test(ID_TOKEN,ID_ER);
    }
    Test(PF_TOKEN,PF_ER);


}

void TANTQUE(){
    lireFichier();
    COND();
    Test(DO_TOKEN,DO_ER);
    INST();



}




void SI(){
    lireFichier();
    COND();
    Test(THEN_TOKEN,THEN_ER);
    INST();



}

void COND(){
    EXPR();
    if((Sym_Cour.CODE==EG_TOKEN) || (Sym_Cour.CODE==DIFF_TOKEN) || (Sym_Cour.CODE==INF_TOKEN) || (Sym_Cour.CODE==SUP_TOKEN) || (Sym_Cour.CODE==INFEG_TOKEN) || (Sym_Cour.CODE==SUPEG_TOKEN)){
        lireFichier();
        EXPR();
    }
    else{
        afficherEr(ERREUR_ER);
    }
}


void AFFEC(){
    Test(ID_TOKEN,ID_ER);
    Test(AFF_TOKEN,AFF_ER);
    EXPR();
}

void EXPR(){
    TERM();
    while(Sym_Cour.CODE==MOINS_TOKEN || Sym_Cour.CODE==PLUS_TOKEN){
        lireFichier();
        TERM();
    }
}



void TERM(){
    FACT();
    while(Sym_Cour.CODE==MULT_TOKEN||Sym_Cour.CODE==DIV_TOKEN){
        lireFichier();
        FACT();
    }
}

void FACT(){
    switch (Sym_Cour.CODE){
        case ID_TOKEN:
            Test(ID_TOKEN, ID_ER);
            break;
        case NUM_TOKEN:
            Test(NUM_TOKEN, NUM_ER);
            break;
        case PO_TOKEN:
            lireFichier();
            EXPR();
            Test(PF_TOKEN, PF_ER);
            break;
        default:
            afficherEr(ERREUR_ER);

    }

}


void BLOCK(){
    CONSTS();
    VARS();
    INSTS();

}

void PROGRAM(){
    Test(PROGRAM_TOKEN,	PROGRAM_ER);
    Test(ID_TOKEN, ID_ER);
    Test(PV_TOKEN, PV_ER);
    BLOCK();
    Test(PT_TOKEN, PT_ER);
}





//----------------------------------------------------------Affichage des symboles--------------------------------------

void afficherSymb(CODES_LEX code){

    switch(code)
    {
        case IF_TOKEN:
            printf("IF_TOKEN \n");
            break;
        case PROGRAM_TOKEN:
            printf("PROGRAM_TOKEN \n");
            break;
        case CONST_TOKEN:
            printf("CONST_TOKEN \n");
            break;
        case VAR_TOKEN:
            printf("VAR_TOKEN \n");
            break;
        case BEGIN_TOKEN:
            printf("BEGIN_TOKEN \n");
            break;
        case END_TOKEN:
            printf("END_TOKEN \n");
            break;
        case THEN_TOKEN:
            printf("THEN_TOKEN \n");
            break;
        case WHILE_TOKEN:
            printf("WHILE_TOKEN \n");
            break;
        case DO_TOKEN:
            printf("DO_TOKEN \n");
            break;
        case READ_TOKEN:
            printf("READ_TOKEN \n");
            break;
        case WRITE_TOKEN:
            printf("WRITE_TOKEN \n");
            break;
        case PV_TOKEN:
            printf("PV_TOKEN \n");
            break;
        case PT_TOKEN:
            printf("PT_TOKEN \n");
            break;
        case PLUS_TOKEN:
            printf("PLUS_TOKEN \n");
            break;
        case MOINS_TOKEN:
            printf("MOINS_TOKEN \n");
            break;
        case MULT_TOKEN:
            printf("MULT_TOKEN \n");
            break;
        case DIV_TOKEN:
            printf("DIV_TOKEN \n");
            break;
        case VIR_TOKEN:
            printf("VIR_TOKEN \n");
            break;
        case AFF_TOKEN:
            printf("AFF_TOKEN \n");
            break;
        case INF_TOKEN:
            printf("INF_TOKEN \n");
            break;
        case INFEG_TOKEN:
            printf("INFEG_TOKEN \n");
            break;
        case SUP_TOKEN:
            printf("SUP_TOKEN \n");
            break;
        case SUPEG_TOKEN:
            printf("SUPEG_TOKEN \n");
            break;
        case DIFF_TOKEN:
            printf("DIFF_TOKEN \n");
            break;
        case PO_TOKEN:
            printf("PO_TOKEN \n");
            break;
        case PF_TOKEN:
            printf("PF_TOKEN \n");
            break;
        case FIN_TOKEN:
            printf("FIN_TOKEN \n");
            break;
        case ID_TOKEN:
            printf("ID_TOKEN \n");
            break;
        case NUM_TOKEN:
            printf("NUM_TOKEN \n");
            break;
        case ERROR_TOKEN:
            printf("ERREUR_TOKEN \n");
            break;
        case EOF_TOKEN:
            printf("EOF_TOKEN \n");
            break;

        case EG_TOKEN:
            printf("EG_TOKEN \n");
            break;
        default:
            break;
    }

}