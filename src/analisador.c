#include <stdlib.h>
#include <stdio.h>
#include "ast.h"
#include "mepa.h"

static int countVar = 0;

static int countLocalVar = 0;

static int countProc = 0;

static int countFun = 0;

static int errors = 0;

static int desvio = 0;

static int escopo = 0;

static Table tabelaSimbolos;

static Commands lstMepa;

int analisaDecVars(A_LstDecVar listaVars){
    if(escopo == 0){
        return resolveAnalisaDecVars(listaVars, &countVar);
    }
    return resolveAnalisaDecVars(listaVars, &countLocalVar);
}

int resolveAnalisaDecVars(A_LstDecVar listaVars, int *contador) {
    int qtdVar = 0;
    while(listaVars != NULL){
        Table tabela = addVar(
            tabelaSimbolos,
            listaVars->decVar->id, 
            listaVars->decVar->tipo, 
            escopo, 
            *addVarMepa(lstMepa, contador)-1
        );
        if(tabela == NULL){
            errors = errors+1;
        }
        qtdVar = qtdVar+1;
        listaVars = listaVars->prox;
    }
    return qtdVar;
}

void analisaDecParam(A_DecParam decParam, int *endereco){
    A_LstIdent lstIdent = decParam->lstIdent;
    while (lstIdent != NULL)
    {
        addParam(tabelaSimbolos, lstIdent->id, decParam->tipo, *endereco);
        lstIdent = lstIdent->prox;
        *endereco = *endereco+1;
    }
}

int countParam(A_ParamFormal paramFormal){
    int qtd = 0;
    A_LstDecParam lst = paramFormal->listDecParam;
    while (lst != NULL)
    {
        A_LstIdent lstIdent = lst->decParam->lstIdent;
        while (lstIdent != NULL)
        {
            qtd = qtd+1;
            lstIdent = lstIdent->prox;
        }
        lst = lst->prox;
    }
    return qtd;
}

LstAtributes analisaParamFormal(A_ParamFormal paramFormal, int totalParam){
    int endereco = -3 -totalParam;
    A_LstDecParam lst = paramFormal->listDecParam;
    while (lst != NULL)
    {
        analisaDecParam(lst->decParam, &endereco);
        lst = lst->prox;
    }
}

void analisaDecProc(A_DecProc decProc){
    escopo = escopo+1;
    addProc(tabelaSimbolos,decProc->id, 1, countProc);
    addEntraProc(lstMepa, escopo, countProc);
    int totalParam = countParam(decProc->paramFormal);
    analisaParamFormal(decProc->paramFormal, totalParam);
    int qtdVar = analisaBloco(decProc->bloco);
    if(qtdVar > 0){
        desalocaMemoriaMepa(lstMepa, qtdVar);
    }
    addRetornaProc(lstMepa, escopo, totalParam);
    escopo = escopo-1;
    countProc = countProc+1;
    countLocalVar = 0;
}

void analisaDecFun(A_DecFun decFun){
    escopo = escopo+1;
    addFunc(tabelaSimbolos, decFun->id, 1, countFun);
    addEntraProc(lstMepa, escopo, countFun);
    int totalParam = countParam(decFun->paramFormal);
    analisaParamFormal(decFun->paramFormal, totalParam);
    int qtdVar = analisaBloco(decFun->bloco);
    if(qtdVar > 0){
        desalocaMemoriaMepa(lstMepa, qtdVar);
    }
    addRetornaProc(lstMepa, escopo, totalParam);
    escopo = escopo-1;
    countFun = countFun+1;
    countLocalVar = 0;
}

void analisaDecSub(A_LstDecSub listSub){
    while(listSub != NULL){
        if(listSub->tipo == Proced){
            analisaDecProc(listSub->decProc);
        }
        if(listSub->tipo == Fun){
            analisaDecFun(listSub->decFun);
        }
        listSub = listSub->prox;
    }
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
    if(escopo == 0){
        TableLine variavel = buscarVariavel(tabelaSimbolos, fator->id);
        if(variavel == NULL){
            printf("\nVariavel fator %s não existe\n", fator->id);
            errors = errors +1;
            return;
        }
        LoadVarMepa(lstMepa, variavel->endereco, variavel->escopo);
        return;
    }

    Atributes atrib = buscaUltimoElemento(tabelaSimbolos, fator->id);
    if(atrib == NULL){
        TableLine variavel = buscarVariavel(tabelaSimbolos, fator->id);
        if(variavel == NULL){
            printf("\nVariavel fator do procedimento %s não existe\n", fator->id);
            errors = errors +1;
            return;
        }
        LoadVarMepa(lstMepa, variavel->endereco, variavel->escopo);
        return;
    }
    LoadVarMepa(lstMepa, atrib->endereco, escopo);
}

void analisaChamFun(A_Chamada_Fun chamFun){
    TableLine linha = buscarElemento(tabelaSimbolos,chamFun->id, Func);
    if(linha == NULL){
        printf("Função %s não foi encontrado", chamFun->id);
        errors = errors+1;
        return;
    }
    A_LstExpress lst = chamFun->lstExpressoes;
    while(lst != NULL){
        analisaExpress(lst->expressao);
        lst = lst->prox;
    }
    addAmemMepa(lstMepa, 1);
    addChamadaProcMepa(lstMepa, linha->escopo, linha->endereco);
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
        case F_Fun:
            analisaChamFun(fator->chamFun);
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
    if(escopo == 0){
        TableLine variavel = buscarVariavel(tabelaSimbolos, atrib->id);
        if(variavel == NULL){
            printf("\nVariavel atrib %s não existe\n", atrib->id);
            errors = errors +1;
            return;
        }
        analisaExpress(atrib->express);
        addAtribMepa(lstMepa, variavel->endereco, variavel->escopo);
        return;
    }
    Atributes localVar = buscaUltimoElemento(tabelaSimbolos, atrib->id);
    if(localVar == NULL){
        if(isUltimoElementoFuncao(tabelaSimbolos)) {
            TableLine funcao = getUltimoElementoFuncao(tabelaSimbolos, atrib->id);
            if(funcao != NULL){
                analisaExpress(atrib->express);
                int qtdParam = countQtdParamFunction(funcao);
                addAtribMepa(lstMepa, (funcao->endereco-4-qtdParam), funcao->escopo);  
                return;
            }              
        }
        TableLine variavel = buscarVariavel(tabelaSimbolos, atrib->id);
        if(variavel == NULL){
            printf("\nVariavel atrib %s não existe\n", atrib->id);
            errors = errors +1;  
            return;
        }
        analisaExpress(atrib->express);
        addAtribMepa(lstMepa, variavel->endereco, variavel->escopo);
        return;
    }
    analisaExpress(atrib->express);
    addAtribMepa(lstMepa, localVar->endereco, escopo);
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

void analisaWhile(A_Repeticao repet){
    addNadaLabel(lstMepa, &desvio/* Escreve L1*/);
    analisaExpress(repet->expressao);
    addDesvioCond(lstMepa, desvio/* Desvia L2*/);
    if(repet->cmdComp != NULL){
        analisaCmdComp(repet->cmdComp);
    }else{
        analisaCmd(repet->cmd);
    }
    addDesvio(lstMepa, (desvio-1));
    addNadaLabel(lstMepa, &desvio);
}

void analisaChamProc(A_Chamada_Proc chamProc){
    TableLine linha = buscarElemento(tabelaSimbolos,chamProc->id, Proc);
    if(linha == NULL){
        printf("Procedimento %s não foi encontrado", chamProc->id);
        errors = errors+1;
        return;
    }
    A_LstExpress lst = chamProc->lstExpressoes;
    while(lst != NULL){
        analisaExpress(lst->expressao);
        lst = lst->prox;
    }
    addChamadaProcMepa(lstMepa, linha->escopo, linha->endereco);
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
    case While:
        analisaWhile(cmd->repet);
        break;
    case ChamProc:
        analisaChamProc(cmd->chamProc);
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
        addDesvio(lstMepa, (desvio+1)/*Desvia L2*/);
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
        addDesvio(lstMepa, (desvio+1)/*Desvia L2*/);
        addNadaLabel(lstMepa, &desvio/*Escreve L1*/);
        analisaCmd(cond->cmdElse);
        addNadaLabel(lstMepa, &desvio/*Escreve L2*/);
        break;
    case ElseComandoComposto:
        analisaCmd(cond->cmdThen);
        addDesvio(lstMepa, (desvio+1)/*Desvia L2*/);
        addNadaLabel(lstMepa, &desvio/*Escreve L1*/);
        analisaCmdComp(cond->cmdCompElse);
        addNadaLabel(lstMepa, &desvio/*Escreve L2*/);
        break;
    case ComandoComposto:
        analisaCmdComp(cond->cmdCompThen);
        addDesvio(lstMepa, (desvio+1)/*Desvia L2*/);
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

int analisaBloco(A_Bloco bloco){
    int qtdVar = 0;
    if(escopo == 0){
        qtdVar = analisaDecVars(bloco->secDecVar);
        addDesvio(lstMepa, 0);
        desvio = desvio+1;
        analisaDecSub(bloco->secDecSub);
        addNadaLabelInicioMain(lstMepa);
        analisaCmdComp(bloco->cmdComp);
        return qtdVar;
    }
    qtdVar = analisaDecVars(bloco->secDecVar);
    analisaCmdComp(bloco->cmdComp);
    return qtdVar;
}

int analisaPrograma(A_Programa prog, Table tabela, Commands mepa){
    tabelaSimbolos = tabela;
    lstMepa = mepa;
    addProgram(tabelaSimbolos, prog->id);
    addTipo(tabelaSimbolos, "integer");
    addTipo(tabelaSimbolos, "boolean");
    analisaBloco(prog->bloco);
    if(countVar > 0){
        desalocaMemoriaMepa(lstMepa, countVar);
    }
    return errors;
}