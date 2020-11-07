#include<stdio.h>
#include<stdlib.h>

struct pol;
typedef struct polinom* Pozicija;

typedef struct polinom {
	int koef;
	int exp;
	Pozicija next;
}_pol;

void unesiSortirano(Pozicija, Pozicija);
Pozicija noviBroj(int, int);
void ucitajIzDat(char[50], Pozicija);
void zbrajanje(Pozicija, Pozicija, Pozicija);
int provjera(Pozicija, Pozicija);
void ispis(Pozicija);
Pozicija novaSuma(Pozicija);

int main() {

	_pol head;
	_pol first;
	_pol rezZbr;
	head.next = NULL;
	first.next = NULL;
	rezZbr.next = NULL;

	ucitajIzDat("Brojevi1.txt", &head);
	ucitajIzDat("Brojevi2.txt", &first);
	zbrajanje(&head, &first, &rezZbr);
	ispis(&rezZbr);
	
}

//prima ime datoteke i head, ucitava brojeve iz te datoteke i veze ih u listu sortirane
//------------------------------
void ucitajIzDat(char dat[50], Pozicija head) {

	Pozicija br = NULL;
	FILE* ulz = NULL;
	int a = 0;
	int b = 0;
	ulz = fopen(dat, "r");
	if (ulz == NULL) {
		printf("Greska pri otvaranju datoteke!\n");
		return -1;
	}


	while (!feof(ulz)) {
		fscanf(ulz, "%d %d", &a, &b);
		br = noviBroj(a, b);
		unesiSortirano(head, br);
	}

	fclose(ulz);
}

//stvara novi clan liste
//------------------------------
Pozicija noviBroj(int a, int b) {
	
	Pozicija br = NULL;

	br = (Pozicija)malloc(sizeof(struct polinom));
	br->koef = a;
	br->exp = b;

	return br;
}

//radi provjeru za sortiran unos u listu te stavlja svaki clan na svoje mjesto (manji exp -> veci)
//------------------------------
void unesiSortirano(Pozicija head, Pozicija br) {

	while (head->next != NULL && head->next->exp < br->exp)
		head = head->next;

	br->next = head->next;
	head->next = br;

}
void zbrajanje(Pozicija pr1, Pozicija pr2, Pozicija suma) {
	
	pr1 = pr1->next;
	pr2 = pr2->next;
	suma = novaSuma(suma);

	while (provjera(pr1, pr2)) {
		
		switch (provjera(pr1, pr2)) {

			case 1:									//isti exp
				suma->koef = pr1->koef + pr2->koef;
				suma->exp = pr1->exp;
				pr1 = pr1->next;
				pr2 = pr2->next;
				suma = novaSuma(suma);
				break;
				
			case 2:									//exp prvog veci, pr2 nije zadnji
				suma->koef = pr2->koef;
				suma->exp = pr2->exp;
				pr2 = pr2->next;
				suma = novaSuma(suma);
				break;

			case 3:									//exp drugog veci, pr1 nije zadnji
				suma->koef = pr1->koef;
				suma->exp = pr1->exp;
				pr1 = pr1->next;
				break;

			case 4:									//exp prvog veci, pr2 zadnji
				suma->koef = pr2->koef;
				suma->exp = pr2->exp;
				suma = novaSuma(suma);

				while (pr1 != NULL) {
					suma->koef = pr1->koef;
					suma->exp = pr1->exp;
					if (pr1->next == NULL)
						return 0;
					pr1 = pr1->next;
					suma = novaSuma(suma);
				}
				break;

			case 5:									//exp drugog veci, pr1 zadnji
				suma->koef = pr1->koef;
				suma->exp = pr1->exp;
				suma = novaSuma(suma);

				while (pr2 != NULL) {
					suma->koef = pr2->koef;
					suma->exp = pr2->exp;
					if (pr2->next == NULL)
						return 0;
					pr2 = pr2->next;
					suma = novaSuma(suma);
				}
				break;

			default: 
				break;

		}
	}
}

int provjera(Pozicija pr1, Pozicija pr2) {
	
	if (pr1->exp == pr2->exp) { return 1; }
	else if (pr1->exp > pr2->exp&& pr2->next != NULL) { return 2; }
	else if (pr1->exp < pr2->exp && pr1->next != NULL) { return 3; }
	else if (pr1->exp > pr2->exp&& pr2->next == NULL) { return 4; }
	else if (pr1->exp < pr2->exp && pr1->next == NULL) { return 5; }
	
	else { return -2; }

}

void ispis(Pozicija head) {
	head = head->next;
	while (head != NULL) {
		printf("%dx^%d + ", head->koef, head->exp);
		head = head->next;
	}
}
Pozicija novaSuma(Pozicija suma) {
	Pozicija pom = NULL;
	pom = noviBroj(0, 0);
	unesiSortirano(suma, pom);
	return pom;
}
