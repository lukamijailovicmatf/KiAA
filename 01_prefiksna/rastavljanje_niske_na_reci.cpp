#include <iostream>
#include <cstdlib>
#include <vector>
#include <unordered_map>

struct Cvor {
  bool je_list;
  std::unordered_map<char, Cvor*> potomci;
};

Cvor *napravi_cvor() {

  Cvor *novi_cvor = new Cvor();
  novi_cvor->je_list = false;
  
  return novi_cvor;
}

void dodaj_rec(Cvor *koren, std::string& rec, int i) {

  if (i == (int)rec.size()) {
    koren->je_list = true;
    return;
  }
  
  auto iterator = koren->potomci.find(rec[i]);
  if (iterator == koren->potomci.end()) {
    koren->potomci[rec[i]] = napravi_cvor();
  }
  
  dodaj_rec(koren->potomci[rec[i]], rec, i + 1);
}

// funkcija koja proverava da li se data niska moze izdeliti na reci iz stabla
bool razbijanje_reci(Cvor *koren, std::string& niska) {

  // duzina niske koju delimo
  int n = niska.size();
  
  // vektor logickih vrednosti koji nam govori sledece:
  // ako je validno[i] = true, prvih 'i' karaktera niske se MOZE naci u stablu (moze se pravilno izdeliti)
  // ako je validno[i] = false, prvih 'i' karaktera niske se NE MOZE izdeliti na reci iz stabla
  std::vector<bool> validno(n + 1, false);
  
  // na pocetku pretpostavljamo da prazan pocetak moze da se nadje u stablu
  validno[0] = true;
  
  Cvor *tmp;
  
  // idemo kroz nisku karakter po karakter
  for (int i = 0; i < n; i++) {
    // ukoliko se prvih 'i' karaktera moze naci u stablu, nastavljamo dalje pretragu
    if (validno[i]) {
      // krecemo uvek od korena stabla
      tmp = koren;
      // idemo od i-tog karaktera do kraja niske i trazimo poklapanja u stablu
      for (int j = i; j < n; j++) {
        // proveravamo da li se karakter nalazi u mapi tekuceg cvora
        auto iterator = tmp->potomci.find(niska[j]);
        // ukoliko nema puta za to slovo, prekidamo unutrasnju petlju
        if (iterator == tmp->potomci.end()) {
          break;
        }
        // ukoliko put postoji, prelazimo na taj cvor
        tmp = tmp->potomci[niska[j]];
        // ukoliko dodjemo do lista, to znaci da se tu zavrsava neka rec iz stabla
        // to znaci da smo uspeli da poklopimo karaktere od 0 do j, pa postavljamo validno[j + 1] na true
        if (tmp->je_list) {
          validno[j + 1] = true;
        }
        // ukoliko smo dosli do kraja cele niske i tekuci cvor je list, znaci da cela niska moze biti
        // izdeljena i odmah vracamo true
        if (j == n - 1 && tmp->je_list) {
          return true;
        }
      }
    }
  }
  
  // ukoliko dodjemo do ove tacke, znaci da niska ne moze biti izdeljena pa vracamo false
  return false;
}

void oslobodi_stablo(Cvor *koren) {
  
  if (koren == nullptr) {
    return;
  }
  
  for (auto& par : koren->potomci) {
    oslobodi_stablo(par.second);
  }
  
  delete koren;
}

int main() {
  
  std::vector<std::string> reci = { "this", "th", "is", "famous", "word", "break", "b", "r", "e", 
                                    "a", "k", "br", "bre", "brea", "ak", "prob", "lem" 
                                  };
                                  
  // int n;
  // std::cin >> n;
  
  // std::vector<std::string> reci(n + 1);
  // for (int i = 0; i < n; i++)
    // std::cin >> reci[i];
                                  
  Cvor *koren = napravi_cvor();
  
  // ubacujemo sve reci iz recnika u stablo
  for (std::string& rec : reci) {
    dodaj_rec(koren, rec, 0);
  }
  
  // niska koju pokusavamo da izdelimo na reci iz stabla
  std::string tekst = "wordbreakproblem";
  
  // proveravamo da li se niska moze izdeliti i u skladu sa rezultatom provere
  // ispisujemo odredjeni rezultat na stdout
  if (razbijanje_reci(koren, tekst)) {
    std::cout << "DA" << std::endl;
  } else {
    std::cout << "NE" << std::endl;
  }
  
  oslobodi_stablo(koren);
  
  return 0;
}
