#include <stdlib.h>
#include <stdio.h>
#include "ast.h"
#include "mepa.h"

static int countVar = 0;

static int errors = 0;

static int desvio = 0;

static Table tabelaSimbolos;

static Commands lstMepa;

void analisaDecVars(A_LstDecVar listaVars){
    while(listaVars != NULL){
        Table tabela = addVar(
            tabelaSimbolos,
            listaVars->decVar->id, 
            listaVars->decVar->tipo, 
            0, 
            *addVarMepa(lstMepa, &countVar)-1
        );
        if(tabela == NULL){
            errors = errors+1;
        }
        listaVars = listaVars->prox;
    }
}

void analisaDecSub(A_LstDecSub listSub){
    // implementar
}

void analisaOperacaoTermo(TermoOperator operacao){
    switch (operacao)
    {
    case Somar:
        addSomaMepa(lstMepa);
        break;
    case Subtrair:
        addSubtMepa(lstMepa);
        break;
    case Numero:
        break;
    case Or:
        addOrMepa(lstMepa);
        break;
    default:
        errors = errors+1;
        printf("Operação %s desconhecida", operacao);
        break;
    }
}

void analisaOperacaoFator(FatorOperator operacao){
    switch (operacao)
    {
    case Multi:
        addMultMepa(lstMepa);
        break;
    case Div:
        addDivMepa(lstMepa);
        break;
    case Fator:
        break;
    case And:
        addAndMepa(lstMepa);
        break;
    default:
        errors = errors+1;
        printf("Operação %s desconhecida", operacao);
        break;
    }
}

void analisaFatorId(A_Fator fator){
    TableLine variavel = buscarVariavel(tabelaSimbolos, fator->id);
    if(variavel == NULL){
        printf("\nVariavel %s não existe\n", fator->id);
        errors = errors +1;
        return;
    }
    LoadVarMepa(lstMepa, variavel->endereco, variavel->escopo);
}

void analisaFator(A_Fator fator){
    switch (fator->type)
    {
        case Id:
            analisaFatorId(fator);
            break;
        case Num:
            addNumMepa(lstMepa, fator->num); 
            break;
        case Logico:
            addLogicoMepa(lstMepa, fator->logico);
            break;
        case Not:
            analisaFator(fator->fator);
            addNotLogicoMepa(lstMepa);
            break;
        case Menos:
            analisaFator(fator->fator);
            addInvertSinalMepa(lstMepa);
            break;
        case Expressao:
            analisaExpress(fator->expressao);
            break;
    }
}

void analisaLstFator(A_LstFator lstFator){
    bool primeiroTermo = true;
    while(lstFator != NULL){
        if(primeiroTermo){
            analisaFator(lstFator->fator);
            primeiroTermo = false;
        }
        if(lstFator->prox != NULL){
            analisaFator(lstFator->prox->fator);
        }
        analisaOperacaoFator(lstFator->operador);
        lstFator = lstFator->prox;
    }
}

void analisaTermo(A_Termo termo){
    analisaLstFator(termo->lstFator);
}

void analisaLstTermo(A_LstTermo lstTermo){
    bool primeiroTermo = true;
    while(lstTermo != NULL){
        if(primeiroTermo){
            analisaTermo(lstTermo->termo);
            primeiroTermo = false;
        }
        if(lstTermo->prox != NULL){
            analisaTermo(lstTermo->prox->termo);
        }
        analisaOperacaoTermo(lstTermo->operador);
        lstTermo = lstTermo->prox;
    }
}

void analisaSimpExpress(A_Simp_Express simp_express){   
    analisaLstTermo(simp_express->lstTermo);
}

void analisaExpressRelacao(Relacao relacao){
    switch (relacao)
    {
    case Igual:
        addIgualMepa(lstMepa);
        break;
    case Diferente:
        addDiferenteMepa(lstMepa);
        break;
    case Menor:
        addMenorMepa(lstMepa);
        break;
    case MenorIgual:
        addMenorIgualMepa(lstMepa);
        break;
    case Maior:
        addMaiorMepa(lstMepa);
        break;
    case MaiorIgual:
        addMaiorIgualMepa(lstMepa);
        break;
    default:
        break;
    }
}

void analisaExpress(A_Express express){
    analisaSimpExpress(express->simp_express);
    if(express->relacao != ExpressaoSimples){
        analisaSimpExpress(express->simp_express2);
        analisaExpressRelacao(express->relacao);
    }
}

void analisaAtrib(A_Atrib atrib){
    TableLine variavel = buscarVariavel(tabelaSimbolos, atrib->id);
    if(variavel == NULL){
        printf("\nVariavel %s não existe\n", atrib->id);
        errors = errors +1;
    }
    analisaExpress(atrib->express);
    addAtribMepa(lstMepa, variavel->endereco, variavel->escopo);
}

void analisaWrite(A_Write write){
    A_LstExpress lst = write->lstExpressoes;
    while(lst != NULL){
        analisaExpress(lst->expressao);
        lst = lst->prox;
        addWriteMepa(lstMepa);
    }
}

void analisaRead(A_Read read){
    A_LstIdent lst = read->lstIdent;
    while(lst != NULL){
        TableLine line = buscarVariavel(tabelaSimbolos, lst->id);
        if(line != NULL){
            addReadMepa(lstMepa, line->endereco, line->escopo);
        }
        lst = lst->prox;
    }
}

void analisaCmd(A_Cmd cmd){
    switch (cmd->type)
    {
    case Atrib:
        analisaAtrib(cmd->atrib);
        break;
    case Write:
        analisaWrite(cmd->write);
        break;
    case Read:
        analisaRead(cmd->read);
        break;
    case If:
        analisaIf(cmd->cond);
        break;
    }
}

void analisaIf(A_Condicional cond){
    analisaExpress(cond->expressao);
    addDesvioCond(lstMepa, desvio/*Desvia L1*/);
    switch (cond->condType)
    {
    case Comando:
        analisaCmd(cond->cmdThen);
        if(cond->cmdElse == NULL){
            addNadaLabel(lstMepa, &desvio/*Escreve L1*/);
            return;
        }
        addDesvioCond(lstMepa, (desvio+1)/*Desvia L2*/);
        addNadaLabel(lstMepa, &desvio/*Escreve L1*/);
        analisaCmd(cond->cmdElse);
        addNadaLabel(lstMepa, &desvio/*Escreve L2*/);
        break;
    case ThenComandoComposto:
        analisaCmdComp(cond->cmdCompThen);
        if(cond->cmdElse == NULL){
            addNadaLabel(lstMepa, &desvio/*Escreve L1*/);
            return;
        }
        addDesvioCond(lstMepa, (desvio+1)/*Desvia L2*/);
        addNadaLabel(lstMepa, &desvio/*Escreve L1*/);
        analisaCmd(cond->cmdElse);
        addNadaLabel(lstMepa, &desvio/*Escreve L2*/);
        break;
    case ElseComandoComposto:
        analisaCmd(cond->cmdThen);
        addDesvioCond(lstMepa, (desvio+1)/*Desvia L2*/);
        addNadaLabel(lstMepa, &desvio/*Escreve L1*/);
        analisaCmdComp(cond->cmdCompElse);
        addNadaLabel(lstMepa, &desvio/*Escreve L2*/);
        break;
    }
}

void analisaLstCmd(A_LstCmd lstCmd){
    while(lstCmd != NULL){
        analisaCmd(lstCmd->cmd);
        lstCmd = lstCmd->prox;
    }
}

void analisaCmdComp(A_CmdComp cmdComp){
    analisaLstCmd(cmdComp->lstCmd);
}

void analisaBloco(A_Bloco bloco){
    analisaDecVars(bloco->secDecVar);
    analisaDecSub(bloco->secDecSub);
    analisaCmdComp(bloco->cmdComp);
}

int analisaPrograma(A_Programa prog, Table tabela, Commands mepa){
    tabelaSimbolos = tabela;
    lstMepa = mepa;
    addProgram(tabelaSimbolos, prog->id);
    addTipo(tabelaSimbolos, "integer");
    addTipo(tabelaSimbolos, "boolean");
    analisaBloco(prog->bloco);
    desalocaMemoriaMepa(lstMepa, countVar);
    return errors;
}