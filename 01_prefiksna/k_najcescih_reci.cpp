#include <iostream>
#include <cstdlib>
#include <vector>
#include <unordered_map>
#include <queue>

struct Cvor {
  std::string rec;
  int brojac;
  std::unordered_map<char, Cvor*> potomci;
};

Cvor *napravi_cvor() {
  
  Cvor *novi_cvor = new Cvor();
  
  novi_cvor->rec = "";
  novi_cvor->brojac = 0;
  
  return novi_cvor;
}

void dodaj_rec(Cvor *koren, std::string& rec, int i) {

  if (i == (int)rec.size()) {
    koren->brojac++;
    koren->rec = rec;
    return;
  }
  
  auto iterator = koren->potomci.find(rec[i]);
  if (iterator == koren->potomci.end()) {
    koren->potomci[rec[i]] = napravi_cvor();
  }
  
  dodaj_rec(koren->potomci[rec[i]], rec, i + 1);
}

// struktura za uporedjivanje cvorova u redu sa prioritetom (hip-u)
struct komparator {
  bool operator() (Cvor *n1, Cvor *n2) {
    if (n1->brojac != n2->brojac)
      return n1->brojac < n2->brojac;
    else
      return n1->rec > n2->rec;
  }
};

// funkcija koja pronalazi reci i ubacuje ih u red sa prioritetom
void ubaci_reci_u_hip(Cvor *koren, std::priority_queue<Cvor*, std::vector<Cvor*>, komparator>& hip) {
  
  if (koren->rec != "") {
    hip.push(koren);
  }
  
  auto pocetak = koren->potomci.begin();
  auto kraj = koren->potomci.end();
  
  while (pocetak != kraj) {
    ubaci_reci_u_hip(pocetak->second, hip);
    pocetak++;
  }
}

void oslobodi_stablo(Cvor *koren) {

  if (koren == nullptr)
    return;
    
  for (auto& par : koren->potomci)
    oslobodi_stablo(par.second);
    
  delete koren;
}

int main() {

  std::vector<std::string> reci = {
                                     "code", "coder", "coding", "codable", "codec", "codecs", "coded",
                                     "codeless", "codec", "codecs", "codependence", "codex", "codify",
                                     "codependents", "codes", "code", "coder", "codesign", "codec",
                                     "coding", "coding", "codec", "codecs", "codiscovered"
                                  };
                                  
  Cvor* koren = napravi_cvor();
  
  for(std::string& rec : reci)
    dodaj_rec(koren, rec, 0);
    
  std::priority_queue<Cvor*, std::vector<Cvor*>, komparator> hip;
  ubaci_reci_u_hip(koren, hip);
  
  int k = 3;
  Cvor *tmp;
  
  while (k && hip.size()) {
    tmp = hip.top();
    hip.pop();
    std::cout << tmp->rec << " se pojavljuje " << tmp->brojac << " puta" << std::endl;
    k--;
  }
  
  oslobodi_stablo(koren);

  return 0;
}
