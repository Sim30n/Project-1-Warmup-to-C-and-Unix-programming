// Petteri Särkkä 16.7.2020
// Project 1: Warmup to C and Unix programming
// lähteet:
// C ohjelmoinnin perusteet Kurssimateriaali
// GeeksforGeeks nettisivu:
// https://www.geeksforgeeks.org/doubly-linked-list/
// Linux getline() man page
// stackoverflow:
//https://stackoverflow.com/questions/25028761/dynamically-allocate-string-using-malloc

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LEN 1024
FILE* tiedosto;

struct Node{
  char *lause;
  struct Node *pNext;
  struct Node *pPrev;
};
typedef struct Node Solmu;

// lisää lauseen listan loppuun
Solmu* solmuLisaa(Solmu *pA, char *lause){
  Solmu *ptr, *ptrUusi;
  // muistin varaus
  if ((ptrUusi=(Solmu*)malloc(sizeof(Solmu))) == NULL){
    fprintf(stderr, "malloc failed");
    exit(1);
  }
  if ((ptrUusi->lause=malloc(strlen(lause)+1)) == NULL){
    fprintf(stderr, "malloc failed");
    exit(1);
  }
  // solmun alustus
  strcpy(ptrUusi -> lause, lause);
  ptrUusi -> pNext = NULL;
  // uuden alkion lisäys listaan
  if (pA == NULL){
    ptrUusi -> pPrev = NULL;
    pA = ptrUusi;
  } else {
    ptr = pA;
    while(ptr->pNext != NULL){
      ptr = ptr->pNext;
    }
    ptr->pNext = ptrUusi;
    ptrUusi->pPrev = ptr;
  }
  return pA;
}
// tulostaa listan nurin perin terminaaliin
void tulosta(Solmu *pA){
  // listan läpikäynti
  Solmu *ptr = pA;
  Solmu *last;
  if (ptr==NULL){
    printf("empty list\n");
  } else {
    while(ptr != NULL){
      last = ptr;
      ptr = ptr->pNext;
    }
    while (last != NULL) {
        printf("%s", last->lause);
        last = last->pPrev;
    }
  }
}

// kirjoittaa listan tiedostoon
void kirjoita(Solmu *pA, char *tiedostonimi){
  if ((tiedosto = fopen(tiedostonimi, "w")) == NULL){
    fprintf(stderr, "error: cannot open file '%s'\n", tiedostonimi);
    exit(1);
  }
  // listan läpikäynti
  Solmu *ptr = pA;
  Solmu *last;
  if (ptr==NULL){
    printf("empty list\n");
  } else {
    while(ptr != NULL){
      last = ptr;
      ptr = ptr->pNext;
    }
    while (last != NULL) {
        fprintf(tiedosto, "%s", last->lause);
        last = last->pPrev;
    }
  }
  fclose(tiedosto);
}

// vapauttaa muistin
Solmu *tyhjenna(Solmu *pA){
  Solmu *ptr = pA;
  while(ptr != NULL){
    pA = ptr->pNext;
    free(ptr->lause);
    free(ptr);
    ptr = pA;
  }
  return pA;
}

// lukee annetun tiedoston
Solmu *lue(char *tiedostonimi){
  Solmu *pAlku = NULL;
  char * line = NULL;
  size_t len = 0;
  ssize_t read;
  tiedosto = fopen(tiedostonimi, "r");
  if (tiedosto == NULL){
    fprintf(stderr,"error: cannot open file '%s'.\n", tiedostonimi);
    exit(1);
  }
  while ((read = getline(&line, &len, tiedosto)) != -1) {
      pAlku = solmuLisaa(pAlku, line);
  }
  fclose(tiedosto);
  if (line){
    free(line);
  }
  return pAlku;
}

 // pääohjelma
int main(int argc, char *argv[]){
  Solmu *pAlku = NULL;
  if(argc < 2){
    fprintf(stderr,"usage: reverse <input> <output>\n");
    exit(1);
  } else if (argc > 3){
    fprintf(stderr, "usage: reverse <input> <output>\n");
    exit(1);
  } else if (argc == 2){
    pAlku = lue(argv[1]);
    tulosta(pAlku);
  } else if (argc == 3){
    pAlku = lue(argv[1]);
    kirjoita(pAlku, argv[2]);
  }
  tyhjenna(pAlku);
  return (0);
}
