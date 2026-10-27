#include <iostream>
#include <cstdlib>
#include <vector>
#include <map>

struct Cvor {
  // samo listovi ce imati ovu promenljivu postavljenu na neku rec, jer ostali cvorovi ne cuvaju reci vec njihove delove
  // u listu se rec zavrsava pa je tu i cuvamo
  std::string rec;
  std::map<char, Cvor*> potomci;
};

Cvor *napravi_cvor() {
  
  Cvor *novi_cvor = new Cvor();
  novi_cvor->rec = "";
  
  return novi_cvor;
}

void dodaj_rec(Cvor *koren, std::string& rec, int i) {
  
  if (i == (int)rec.size()) {
    koren->rec = rec;
    return;
  }
  
  auto iterator = koren->potomci.find(rec[i]);
  if (iterator == koren->potomci.end()) {
    koren->potomci[rec[i]] = napravi_cvor();
  }
  
  dodaj_rec(koren->potomci[rec[i]], rec, i + 1);
}

void leksikografski(Cvor *koren) {
  
  if (koren->rec != "") {
    std::cout << koren->rec << std::endl;
  }
  
  auto pocetak = koren->potomci.begin();
  auto kraj = koren->potomci.end();
  
  while (pocetak != kraj) {
    leksikografski(pocetak->second);
    pocetak++;
  }
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

  //  std::vector<std::string> reci =
        // {
        //         "lexicographic", "sorting", "of", "a", "set", "of", "keys", "can",
        //         "be", "accomplished", "with", "a", "simple", "trie", "based",
        //         "algorithm", "we", "insert", "all", "keys", "in", "a", "trie",
        //         "output", "all", "keys", "in", "the", "trie", "by", "means", "of",
        //         "preorder", "traversal", "which", "results", "in", "output", "that",
        //         "is", "in", "lexicographically", "increasing", "order", "preorder",
        //         "traversal", "is", "a", "kind", "of", "depth", "first", "traversal"
        // };

  std::vector<std::string> reci = {"cod", "coder", "coding", "codecs"};
  
  // int n;
  // std::cin >> n;
  
  // std::vector<std::string> reci(n + 1);
  // for (int i = 0; i < n; i++)
    // std::cin >> reci[i];
  
  Cvor *koren = napravi_cvor();
  
  for (std::string& rec : reci) {
    dodaj_rec(koren, rec, 0);
  }
  
  leksikografski(koren);
  
  oslobodi_stablo(koren);

  return 0;
}
