#include <chrono>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

template <typename tip> void bubble_sort(tip *niz, int vel) {
  for (int i = 0; i < vel; i++)
    for (int j = i; j < vel; j++)
      if (niz[i] > niz[j]) {
        auto temp = niz[i];
        niz[i] = niz[j];
        niz[j] = temp;
      }
}

template <typename tip> void selection_sort(tip *niz, int vel) {
  if (niz == nullptr)
    return;
  for (int i = 0; i < vel; i++) {
    tip min = niz[i];
    int mini = i;
    for (int j = i + 1; j < vel; j++)
      if (niz[j] < min) {
        min = niz[j];
        mini = j;
      }
    auto temp = niz[mini];
    niz[mini] = niz[i];
    niz[i] = temp;
  }
}

template <typename tip>
int Particija(tip *niz, int prvi, int zadnji) {
    tip pivot = niz[prvi];
    int p = prvi + 1;
    while (p <= zadnji && niz[p] <= pivot) {
        p++;
    }
    for (int i = p + 1; i <= zadnji; i++) {
        if (niz[i] < pivot) {
            std::swap(niz[i], niz[p]);
            p++;
        }
    }
    std::swap(niz[prvi], niz[p - 1]);
    return p - 1;
}

template <typename tip>
void quick_sort_helper(tip *niz,int prvi, int zadnji){
  if(prvi<zadnji){
       int j=Particija(niz,prvi,zadnji);
       quick_sort_helper(niz,prvi,j-1);
       quick_sort_helper(niz,j+1,zadnji);
   }
}

template <typename Tip>
void quick_sort(Tip* niz, int vel){
   quick_sort_helper(niz,0,vel-1);
}

template <typename tip>
void Merge(tip *niz, const int l, const int p, const int q, const int u) {
  int i = 0;
  int j = q - l;
  int k = l;
  tip *B = new tip[u - l + 1];
  for (int m = 0; m <= u - l; m++)
    B[m] = niz[l + m];
  while (i <= p - l && j <= u - l) {
    if (B[i] < B[j]) {
      niz[k] = B[i];
      i++;
    } else {
      niz[k] = B[j];
      j++;
    }
    k++;
  }
  while (i <= p - l) {
    niz[k] = B[i];
    k++;
    i++;
  }
  while (j <= u - l) {
    niz[k] = B[j];
    k++;
    j++;
  }
  delete[] B;
}

template <typename tip> void merge_sort_helper(tip *niz, int l, int u) {
  if (u > l) {
    int p = (l + u - 1) / 2;
    int q = p + 1;
    merge_sort_helper(niz, l, p);
    merge_sort_helper(niz, q, u);
    Merge(niz, l, p, q, u);
  }
}

template <typename tip> void merge_sort(tip *niz, int vel) {
  merge_sort_helper(niz, 0, vel - 1);
}


void generisi(std::string file, int vel) {
  ofstream ULAZ(file);
  for (int i = 0; i < vel; i++)
    ULAZ.put(char(rand()));
  ULAZ.close();
}

void ucitaj(std::string file, int *&niz, int &vel) {
  int c;
  ifstream ULAZ(file);
  std::vector<int> v;
  while (ULAZ >> c) {
    v.push_back(c);
  }
  vel = v.size();
  niz = new int[vel];
  for (int i = 0; i < vel; i++)
    niz[i] = v[i];
  ULAZ.close();
}

void funkcija(std::string file, int *&niz, int &vel, std::string izlaz) {
  ucitaj(file, niz, vel);
  std::cout << "Niz glasi: ";
  for (int i = 0; i < vel; i++) {
    std::cout << niz[i];
    if (i != vel - 1)
      std::cout << " ";
  }
  std::cout << std::endl;
start:
  std::cout << "Za: merge sort - 1 , quick sort - 2 , bubble sort - 3 , "
               "selection sort - 4 : ";
  int n;
  std::cin >> n;
  auto start = std::chrono::high_resolution_clock::now();
  switch (n) {
  case 1:
    merge_sort(niz, vel);
    break;
  case 2:
    quick_sort(niz, vel);
    break;
  case 3:
    bubble_sort(niz, vel);
    break;
  case 4:
    selection_sort(niz, vel);
    break;
  default: {
    std::cout << "Unesite ispravnu opciju!" << std::endl;
    goto start;
  }
  }
auto stop = std::chrono::high_resolution_clock::now();
auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
  for (int i = 0; i < vel - 1; i++)
    if (niz[i] > niz[i + 1])
      std::cout << "GRESKA!";
  std::cout << std::endl;
  std::cout << std::endl;
  std::cout << "Niz jeste sortiran\nTrajanje sortiranja: " << duration.count()
            << " ms\nNiz sortiran: ";
  for (int i = 0; i < vel; i++) {
    std::cout << niz[i];
    if (i != vel - 1)
      std::cout << " ";
  }
  std::ostringstream os;
  std::ofstream IZLAZ(izlaz);
  for (int i = 0; i < vel; i++) {
    os << niz[i];
    if (i != vel - 1)
      os << ", ";
  }
  std::string s(os.str());
  IZLAZ << s;
  IZLAZ.close();
}

int main() {
int vel(10000000);
int* niz = new int[vel];
for (int i(0); i<vel; i++)
	niz[i] = rand();
quick_sort(niz, vel);
for(int i(0); i<vel-1; i++) 
	if(niz[i] > niz[i+1]) {
		cout << "Greska: i="<<i<<" "<<niz[i]<<">"<<niz[i+1]<<endl;
		break;
	}
cout << "OK";
delete[] niz;
}