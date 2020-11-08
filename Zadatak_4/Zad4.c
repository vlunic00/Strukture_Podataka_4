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
int provjeraZbrajanja(Pozicija, Pozicija);
void ispis(Pozicija);
Pozicija noviRez(Pozicija);
void mnozenje(Pozicija, Pozicija, Pozicija);


int main() {

	_pol head;
	_pol first;
	_pol rezZbr;
	_pol rezMno;
	head.next = NULL;
	first.next = NULL;
	rezZbr.next = NULL;
	rezMno.next = NULL;

	ucitajIzDat("Brojevi1.txt", &head);
	ucitajIzDat("Brojevi2.txt", &first);
	zbrajanje(&head, &first, &rezZbr);
	ispis(&rezZbr);
	mnozenje(&head, &first, &rezMno);

	printf("%dx^%d\n", rezMno.next->koef, rezMno.next->exp);

	return 0;
	
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

//popunjava clanove liste sume ovisno o exponentima svakog pribrojnika
//------------------------------
void zbrajanje(Pozicija pr1, Pozicija pr2, Pozicija suma) {
	
	pr1 = pr1->next;
	pr2 = pr2->next;
	suma = noviRez(suma);

	while (provjeraZbrajanja(pr1, pr2)) {
		
		switch (provjeraZbrajanja(pr1, pr2)) {

			case 1:									//isti exp
				suma->koef = pr1->koef + pr2->koef;
				suma->exp = pr1->exp;
				pr1 = pr1->next;
				pr2 = pr2->next;
				suma = noviRez(suma);
				break;
				
			case 2:									//exp prvog veci, pr2 nije zadnji
				suma->koef = pr2->koef;
				suma->exp = pr2->exp;
				pr2 = pr2->next;
				suma = noviRez(suma);
				break;

			case 3:									//exp drugog veci, pr1 nije zadnji
				suma->koef = pr1->koef;
				suma->exp = pr1->exp;
				pr1 = pr1->next;
				break;

			case 4:									//exp prvog veci, pr2 zadnji
				suma->koef = pr2->koef;
				suma->exp = pr2->exp;
				suma = noviRez(suma);

				while (pr1 != NULL) {
					suma->koef = pr1->koef;
					suma->exp = pr1->exp;
					if (pr1->next == NULL)
						return 0;
					pr1 = pr1->next;
					suma = noviRez(suma);
				}
				break;

			case 5:									//exp drugog veci, pr1 zadnji
				suma->koef = pr1->koef;
				suma->exp = pr1->exp;
				suma = noviRez(suma);

				while (pr2 != NULL) {
					suma->koef = pr2->koef;
					suma->exp = pr2->exp;
					if (pr2->next == NULL)
						return 0;
					pr2 = pr2->next;
					suma = noviRez(suma);
				}
				break;
			case -2:
				printf("Greska pri provjeri pribrojnika.\n");
				break;

			default: 
				break;

		}
	}
}

//radi provjeru stanja izmedju prvog i drugog pribrojnika
//------------------------------
int provjeraZbrajanja(Pozicija pr1, Pozicija pr2) {
	
	if (pr1->exp == pr2->exp) { return 1; }
	else if (pr1->exp > pr2->exp && pr2->next != NULL) { return 2; }
	else if (pr1->exp < pr2->exp && pr1->next != NULL) { return 3; }
	else if (pr1->exp > pr2->exp && pr2->next == NULL) { return 4; }
	else if (pr1->exp < pr2->exp && pr1->next == NULL) { return 5; }
	
	else { return -2; }

}
//mnozi prijasnji umnozak sa svakim clanom
//------------------------------
void mnozenje(Pozicija fakt1, Pozicija fakt2, Pozicija umn) {

	fakt1 = fakt1->next;
	fakt2 = fakt2->next;
	Pozicija pom = fakt2;
	umn = noviRez(umn);

	while (fakt1 != NULL) {
		umn->koef = umn->koef + fakt1->koef + fakt2->koef;
		umn->exp = umn->exp * fakt1->exp * fakt2->exp;
		
		if (fakt2->next == NULL) {
			fakt1 = fakt1->next;
			fakt2 = pom;
		}
	}
}

//ispisuje zavrsnu sumu
//------------------------------
void ispis(Pozicija head) {
	head = head->next;
	while (head != NULL) {
		printf("%dx^%d + ", head->koef, head->exp);
		head = head->next;
	}
}

//stvara novi clan u listi sume/umnoska i odma ga uclani u listu(sort nije bitan jer su pocetno 0 0)
//------------------------------
Pozicija noviRez(Pozicija rez) {
	Pozicija pom = NULL;
	pom = noviBroj(0, 1);
	unesiSortirano(rez, pom);
	return pom;
}
