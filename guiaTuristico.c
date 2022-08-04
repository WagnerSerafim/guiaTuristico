#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <locale.h>
#define SIZE 100

typedef struct pturistico {
  
  char regiao[20];
  char nome[100];
  char local[100];
  char qualidade[25];
  char resumo[100];
}ponto;

void salva(char objeto[]){ // Funcao para substituir scanf
  char resp;int i = 0;
  while ((resp = getchar()) != '\n' && resp !=EOF){
    objeto[i] = resp;
    i++;
  }
  objeto[i] = '\0';
}

ponto implementa_atracao(ponto l){ // Fun��o para salvar as infos da atracao
  ponto cria;

  printf("\nDigite o nome da atra��o:\n>>");
  salva(cria.nome);
  

  printf("\nDigite o local da atracao:\n>>");
  salva(cria.local);

  printf("\nDigite a qualidade da atracao [otimo, bom, regular, ruim, pessimo, caro, barato, gratis]:\n>>");
  salva(cria.qualidade);

  printf("\nDigite o resumo da atracao:\n>>");
  salva(cria.resumo);

  return cria;
}

void imprime(ponto objeto){
  printf("%s\n", objeto.nome);
  printf("%s\n", objeto.local);
  printf("%s\n", objeto.qualidade);
  printf("%s\n", objeto.resumo);
}

bool checaexiste(){ // Checa se o arquivo existe
  FILE *f;
  if ((f=fopen("atracs.bin", "rb")) == NULL){
    return false;
  }
  else{
    fclose(f);
    return true;
  }
}

void preenchevetor(ponto vet[], int posi, int posf){ // vet eh o vetor com as infos, posi eh a pos inicial e posf a pos final, iremos preencher o vetor de i ate f
  int i;
  for (i=posi; i<posf;i++){
    strcpy(vet[i].regiao, "0");
    strcpy(vet[i].nome, "0");
    strcpy(vet[i].local, "0");
    strcpy(vet[i].qualidade, "0");
    strcpy(vet[i].resumo, "0");
  }
}

int pegainfosab(ponto vet[]){ 
  FILE *f; int i=0; ponto tmp;
  f = fopen("atracs.bin", "rb");
  while (fread(&tmp, sizeof(ponto), 1, f)){
    vet[i] = tmp;
    i++;
  }
  preenchevetor(vet, i, SIZE);
  return i; 
}

void escreveab(ponto vet[]){
  FILE *f; ponto tmp; int i = 0;
  f = fopen("atracs.bin", "wb");
  while (i<SIZE){
    if (strcmp(vet[i].regiao, "0") != 0){
      tmp = vet[i];
      fwrite(&tmp, sizeof(ponto), 1, f);
    }
    i++;
  }

}

void addatrac(ponto tudo[], int* vetpos, char regiao[20]){
  ponto tmp;int postmp;
  postmp = *vetpos;
  

  tmp = implementa_atracao(tmp);
  strcpy(tmp.regiao, regiao);
  imprime(tmp);
  tudo[postmp] = tmp;
  postmp++;
  *vetpos = postmp;
}

void rmatrac(ponto tudo[], int* vetpos, char regiao[20]){
  int postmp;int i=0;char resp[20];int j;bool gate = false;
  postmp = *vetpos;ponto seguradora;
  
  printf("\nQual o nome da atra��o que voce deseja remover?\n>>");
  salva(resp);
  while (i < postmp){
    if ((strcmp(tudo[i].regiao, regiao) == 0) && (strcmp(tudo[i].nome, resp) == 0)){
      printf("\nAs seguintes informa��es ser�o removidas\n");
      imprime(tudo[i]);
      strcpy(tudo[i].regiao, "0");
      strcpy(tudo[i].nome, "0");
      strcpy(tudo[i].local, "0");
      strcpy(tudo[i].qualidade, "0");
      strcpy(tudo[i].resumo, "0");
      j = i;
      gate = true;
      break;
    }
    i++;
  }
  if (gate){
    j++;
    while (i<SIZE){
      seguradora = tudo[j];
      tudo[i] = seguradora;
      i++;
      j++;
    }
    postmp--;
    *vetpos = postmp;
  }else{
    printf("\nN�o foi possivel encontrar uma atra��o com esse nome no programa, caso tenha certeza que digitou corretamente, favor entrar em contato com os desenvolvedores\n");
  }
}

void veratrac(ponto tudo[], int* vetpos, char regiao[20]){
  int i = 0;ponto seguradora; bool gate = false;char resp[20];
  int postmp = *vetpos;

  printf("\nQual o nome da atra��o que voce gostaria de ver?\n>>");
  salva(resp);

  while (i<postmp){
    if ((strcmp(tudo[i].regiao, regiao) == 0) && (strcmp(tudo[i].nome, resp) == 0)){
      gate = true;
      seguradora = tudo[i];
    }
    i++;
  }
  
  if (gate){
    imprime(seguradora);
  }else{
    printf("\nN�o foi poss�vel encontrar uma atra��o com esse nome\n");
  }

}

void modatrac(ponto tudo[], int* vetpos, char regiao[20]){
  int i = 0; ponto seguradora;char resp[20];bool gate = false; 
  int postmp = *vetpos;

  printf("\nQual o nome da atra��o que voce deseja alterar?\n>>");
  salva(resp);

 //printf("\nvamo ver se chega aqui\n"); // Isso aq eh temporario
 
  while (i<postmp){
    if ((strcmp(tudo[i].regiao, regiao) == 0) && (strcmp(tudo[i].nome, resp) == 0)){
      seguradora = tudo[i];
      imprime(seguradora);
      printf("\nDigite as novas informa��es\n");
      seguradora = implementa_atracao(seguradora);
      strcpy(seguradora.regiao, regiao);
      tudo[i] = seguradora;
      gate = true;
      break;
    }
    i++;
  }

  if (!gate){
    printf("\nN�o foi possivel encontrar uma atra��o com esse nome no programa, caso tenha certeza que digitou corretamente, favor entrar em contato com os desenvolvedores\n");
  }
}

void segundomenu(ponto tudo[], int* vetpos, char regiao[20]){ // char regiao marca em que regiao estamos
  char resp1[50];char resp2[50];char resp3[50];bool arq;int pos;


  
  printf("\nDeseja fazer alguma altera��o ou ver alguma informa��o sobre alguma atra��o?\n1-->Sim\nQualquer outra tecla-->N�o\n>>");
  salva(resp1);

  if (strcmp(resp1, "1") == 0){
    while (true){
      printf("Qual altera��o voce deseja fazer? \n");
      printf("\n1-->Adicionar atra��o\n2-->Excluir atra��o\n3-->Modificar uma atra��o\n4-->Mostrar alguma informa��o\n5-->Voltar ao menu principal\n>>");
      salva(resp2);
      
      // O que o user quer fazer
      if (strcmp(resp2, "1") == 0){
        printf("\nVoce vai adicionar alguma atra��o\n");
        addatrac(tudo, vetpos, regiao);
      }else if(strcmp(resp2, "2") == 0){
        printf("\nVoce vai excluir alguma atra��o\n");
        rmatrac(tudo, vetpos, regiao);
      }else if(strcmp(resp2, "3") == 0){
        printf("\nVoce vai modificar alguma atra��o\n");
        modatrac(tudo, vetpos, regiao);
      }else if(strcmp(resp2, "4") == 0){
        printf("\nVoce vai ver alguma info especifica\n");
        veratrac(tudo, vetpos, regiao);
      }else if(strcmp(resp2, "5") == 0){
        break;
      }else{
        printf("\nOp��o Inv�lida\n");
      }

      // O que o user quer fazer depois de fazer altera��es
      printf("\nDeseja continuar as altera��es?\n1-->Sim\n2-->Nao\n>>");
      salva(resp3);
      if (strcmp(resp3, "1") == 0){
        continue;
      }else if (strcmp(resp3, "2") == 0){
        break;
      }else{
        printf("\nOp��o Inv�lida\n");
        continue;
      }
    }
  }
}

void mostratodas(ponto tudo[], int* vetpos, bool existe,  char regiao[20]){
  int i = 0; int postmp;ponto seguradora;int hack = 0;
  postmp = *vetpos;
  if (postmp!=0){
  
    while (i<postmp){
      seguradora = tudo[i];
      if (strcmp(seguradora.regiao, regiao) == 0){
        if (hack == 0){
          printf("\nAs atra��es encontradas nesta regi�o s�o: \n");
          hack++;      
        }
        printf("%s\n", seguradora.nome);
      }
      i++;
    }
  }else if (hack == 0){
    printf("\nAinda n�o existem atra��es neste regi�o, seja o primeiro a adicionar!\n");
  } 
  else{
    printf("\nAinda n�o existem atra��es neste regi�o, seja o primeiro a adicionar!\n");
  }  

}

void iniciar(){
	int i;
  char resp1[50];char resp2[50];ponto tudo[SIZE];bool existe;int vetpos;
  existe = checaexiste(); // Checa se o arq existe ou nao
  if (existe){
    vetpos = pegainfosab(tudo); // Pega as infos do arquivo binario(pegainfosab) e salva no vetor 'tudo'      
  }else{
    preenchevetor(tudo, 0, SIZE); // Como o arquivo n�o existe preenchemos todas as posi��es do vetor
    vetpos = 0;
  }

  while (true){
    printf("|===================================================|\n");
    printf("  MENU DE ATRA��ES DO BRASIL PARA VOC� SE DIVERTIR!\n");
    printf("|===================================================|\n");
    printf("  CONHE�A DE TODAS REGI�ES DESSE PA�S MARAVILHOSO!\n");
    printf("|===================================================|\n\n");
    printf("Aqui est� todas regi�es que voc� pode conhecer!\n1 --> Regi�o Norte\n2 --> Regi�o Nordeste\n3 --> Regi�o Centro-Oeste\n4 --> Regi�o Sudeste\n5 --> Regi�o Sul\n6 --> Sair\n");
    printf("\nQual voc� deseja?\n>>");
    salva(resp1);
	printf("\n");
    if (strcmp(resp1, "1") == 0){
      printf("\nVoce selecionou a Regi�o Norte!\n");
      mostratodas(tudo, &vetpos, existe, "norte");
      segundomenu(tudo, &vetpos, "norte");
    }else if (strcmp(resp1, "2") == 0){
      printf("\nVoce selecionou a Regi�o Nordeste\n");
      mostratodas(tudo, &vetpos, existe, "nordeste");
      segundomenu(tudo, &vetpos, "nordeste");
    }else if (strcmp(resp1, "3") == 0){
      printf("\nVoce selecionou a Regi�o Centro-Oeste\n");
      mostratodas(tudo, &vetpos, existe, "centrooeste");
      segundomenu(tudo, &vetpos, "centrooeste");
    }else if (strcmp(resp1, "4") == 0){
      printf("\nVoce selecionou a Regi�o Sudeste\n");
      mostratodas(tudo, &vetpos, existe, "sudeste");
      segundomenu(tudo, &vetpos, "sudeste");
    }else if(strcmp(resp1, "5") == 0){
      printf("\nVoce seleciounou a Regi�o Sul\n");
      mostratodas(tudo, &vetpos, existe, "sul");
      segundomenu(tudo, &vetpos, "sul");
    }else if(strcmp(resp1, "6") ==0){
      printf("\nMuito obrigado por tudo, volte sempre!\n");
      break;
    }else{
      printf("\nOp��o Inv�lida\n");
    }

    printf("Deseja continuar a navegar? \n1-->Sim\n2-->N�o\n");
    salva(resp2);
    if (strcmp(resp2, "1") == 0){
      continue;
    }else if (strcmp(resp2, "2") == 0){
      printf("\nMuito obrigado por tudo, volte sempre!\n");
      for (i=0; i<SIZE;i++){
        if (strcmp(tudo[i].regiao, "0") != 0){
          imprime(tudo[i]);
        }
      }
      escreveab(tudo); // Essa funcao anota tudo no arquivo binario
      break;
    }else{
      printf("\nOp��o invalida, terminando o programa...\n");
      break;
    }
  }
}

int main(){
  setlocale(LC_ALL,"");
  iniciar();

  return 0;
}
