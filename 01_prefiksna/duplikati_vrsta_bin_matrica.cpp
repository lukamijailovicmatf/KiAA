#include <iostream>
#include <cstdlib>
#include <vector>

#define MAX (100)

struct Cvor {

  // prebrojava koliko se puta red, u ovom slucaju red matrice, javlja u stablu
  // samo ce listovi imati vrednost ove promenljive razlicitu od 0
  int brojac;
  
  // nema potrebe za koriscenjem mape, znamo da je matrica binarna
  // tako da sigurno imamo najvise 2 potomka (0 ili 1)
  Cvor *potomci[2];
};

Cvor *napravi_cvor() {

  Cvor *novi_cvor = (Cvor*)malloc(sizeof(Cvor));
  
  novi_cvor->brojac = 0;
  novi_cvor->potomci[0] = novi_cvor->potomci[1] = nullptr;
  
  return novi_cvor;
}

// koren -> koren stabla; red -> red koji se dodaje; n -> duzina reda;
// i -> pozicija u redu do koje smo stigli; redni_broj -> redni broj reda
// da znamo koji je red duplikat;
void dodaj_red(Cvor *koren, std::vector<int> red, int n, int i, int redni_broj) {

   // ukoliko smo dosli do kraja reda, azuriramo broj pojavljivanja tog reda u stablu
   // ukoliko je broj pojavljivanja tog reda veci od 1, prijavljujemo duplikat tako sto ispisujemo njegov redni broj
   // kako smo dodali ceo red, sam cvor je list pa zavrsavamo rekurziju
   if (i == n) {
      koren->brojac++;
      if (koren->brojac > 1) {
        std::cout << redni_broj << std::endl;
      }
      return;
   }
   
   // uzimamo trenutnu cifru u redu (0 ili 1)
   int cifra = red[i];
   
   // ukoliko nemamo odgovarajuci cvor u stablu za tu cifru, moramo da ga kreiramo
   if (koren->potomci[cifra] == nullptr) {
      koren->potomci[cifra] = napravi_cvor();
   }
   
   // rekurzivno nastavljamo do lista za sledeci element u redu (i + 1)
   dodaj_red(koren->potomci[cifra], red, n, i + 1, redni_broj);
}

void oslobodi_stablo(Cvor *koren) {
  
  if (koren == nullptr) {
    return;
  }
  
  for (auto& potomak : koren->potomci) {
    oslobodi_stablo(potomak);
  }
  
  free(koren);
}

int main() {

  int n;
  std::cin >> n;
  
  std::vector<std::vector<int>> matrica(n, std::vector<int>(n));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      std::cin >> matrica[i][j];
    }
  }
  
  Cvor *koren = napravi_cvor();
  
  // prolazimo kroz svaki red matrice i dodajemo ga u stablo
  // prosledjujemo i + 1 kao redni broj reda (prvi red je 1, drugi je 2, itd.)
  for (int i = 0; i < n; i++)
    dodaj_red(koren, matrica[i], n, 0, i + 1);
    
  oslobodi_stablo(koren);

  return 0;
}
