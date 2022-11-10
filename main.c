#define _CRT_SECURE_NO_WARNINGS
#define duzineImenaIPrezimena 64
#define MAX_LEN 1024
#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<stdlib.h>


#pragma region Structs
typedef struct Node* Position;
struct Node {
int _multiplier;
int _exponent;
Position _next;
};
#pragma endregion
#pragma region Function definitions
int CountRows(char*);
Position InsertFromFile(char*, Position, int);
int InsertSorted(int, int, Position);
int InsertAfter(int, int, Position);
Position AddPolynomials(Position, Position,int);
Position MultiplyPolynomials(Position , Position );
int Print(Position);
#pragma endregion


int main() {
char fname[20] = "";
int numOfPolynomials=0;
printf("Upisite iz kojeg filea zelite ucitati ljude\n");
scanf("%s", fname);
numOfPolynomials = CountRows(fname);
Position ListOfHeads = malloc(numOfPolynomials * sizeof(struct Node));
if (ListOfHeads == NULL) {
return 1;
}
ListOfHeads=InsertFromFile(fname, &ListOfHeads, numOfPolynomials);
MultiplyPolynomials(&(ListOfHeads[1]), &(ListOfHeads[2]));
return 0;
}

#pragma region Functions
int CountRows(char* fileName) {
int cnt = 0;
char* buffer = malloc(1024);
if (buffer == NULL) {
return 1;
}
FILE* f=NULL;
f = fopen(fileName, "r");
while (1) {
if (fgets(buffer, 50, f) == '\0')
break;
cnt++;
}
fclose(f);
return cnt;
}
Position InsertFromFile(char* fileName, Position ListOfHeads, int cnt) {
FILE* f = NULL;
int i = 0, multiplier=0, exponent=0, numOfNodes=0, counterPolynomials = 0, len = 0;
char* buffer = malloc(MAX_LEN);
if (buffer == NULL) {
return 1;
}
f = fopen(fileName, "r");//Probaj risit sa sscanf i bufferon da nebi crashalo
if (f == NULL || cnt == 0) {
printf("Datoteka nije valjana\n");
return 1;
}
while (counterPolynomials<cnt) {
fgets(buffer, 50, f);
//numOfNodes = sscanf(buffer, "%d %d %n", &multiplier, &exponent, &len);
struct Node Head = { ._next = NULL, ._exponent = NULL, ._multiplier = NULL };
char delim[] = " ";
char* ptr = strtok(buffer, delim);
int flag = 0;
while (ptr != NULL)
{
if (!flag) {
multiplier = atoi(ptr);
flag++;
}
else {
exponent = atoi(ptr);
InsertSorted(multiplier, exponent, &Head);
flag--;
}
ptr = strtok(NULL, delim);
}
ListOfHeads[counterPolynomials] = Head;
counterPolynomials++;
}

return ListOfHeads;
}
int InsertSorted(int multiplier, int exponent, Position p) {
while (p->_next != NULL) {
if (p->_next->_exponent > exponent) {
InsertAfter(multiplier, exponent, p);
return 0;
}
else if (p->_next->_exponent == exponent) {
p->_next->_multiplier += multiplier;
return 0;
}
else {
p = p->_next;
}
}
InsertAfter(multiplier, exponent, p);

}
int InsertAfter(int multiplier, int exponent, Position p) {
if (!multiplier) {
return 0;
}
Position node = (Position)malloc(sizeof(struct Node));
if (node == NULL) {
return 1;
}
node->_multiplier = multiplier;
node->_exponent = exponent;
node->_next = p->_next;
p->_next = node;
return 0;
}
Position AddPolynomials(Position p1, Position p2,int toPrint) {
struct Node Head = { ._exponent = NULL,._multiplier = NULL ,._next = NULL };
p1 = p1->_next;
p2 = p2->_next;
while (p1!= NULL  && p2 != NULL ) {
if (p1->_exponent > p2->_exponent) {
InsertSorted(p2->_multiplier, p2->_exponent, &Head);
p2 = p2->_next;
}
else if (p1->_exponent < p2->_exponent) {
InsertSorted(p1->_multiplier, p1->_exponent, &Head);
p1 = p1->_next;
}
else {
InsertSorted((p1->_multiplier + p2->_multiplier), p1->_exponent, &Head);
p1 = p1->_next;
p2 = p2->_next;
}
}
if (p1 == NULL) {
while(p2 != NULL){
InsertSorted(p2->_multiplier, p2->_exponent,&Head);
p2 = p2->_next;
}
}
if (p2 == NULL) {
while (p1 != NULL) {
InsertSorted(p1->_multiplier, p1->_exponent, &Head);
p1 = p1->_next;
}
}
if (toPrint == 1) {
Print(&Head);
}
return &Head;
}
Position MultiplyPolynomials(Position p1, Position p2) {
Position temp1 = p1;
struct Node Head = { ._exponent = NULL,._multiplier = NULL ,._next = NULL };
while (p2->_next != NULL) {
struct Node HeadTemp = { ._exponent = NULL,._multiplier = NULL ,._next = NULL };
while (p1->_next != NULL) {
InsertAfter((p2->_next->_multiplier*p1->_next->_multiplier), (p2->_next->_exponent + p1->_next->_exponent), &HeadTemp);
p1 = p1->_next;
}
p2 = p2->_next;
p1 = temp1;
Head=*(AddPolynomials(&Head, &HeadTemp,0));
}
Print(&Head);
return &Head;
}
int Print(Position P) {
while(P->_next!=NULL){
printf("%d*x**%d",P->_next->_multiplier,P->_next->_exponent);
if (P->_next->_next != NULL) {
printf(" + ");
}
P = P->_next;
}
printf("\n");
}
#pragma endregion
