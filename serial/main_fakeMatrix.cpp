#include <iostream>
#include <fstream>
#include <string>
#include <iterator>

//region M-in(ax)'s
int min(int a, int b){
  return (a < b) ? a : b;
}
int min(int top, int left, int dia){
  return min(min(top, left), dia);
}
int max(int a, int b){
  return (a > b) ? a : b;
}
//endregion

int edtDistance(std::string* s0, std::string* s1){
  int s0len = (*s0).size(), s1len = (*s1).size();
  int sMax = max(s0len, s1len) + 1, sMin = min(s0len, s1len);
  //region Create Diagonals
  int * dAnterior2 {new int[sMax]};
  dAnterior2[0] = 0;               // 0 - 1 - X
  int * dAnterior {new int[sMax]}; // 1 - X - x
  dAnterior[0] = 1;                // X - x - x
  dAnterior[1] = 1;
  int * dAtual {new int[sMax]};
  int * dTemp {new int[sMax]};
  //endregion
  // sl = Slices/Fatias/Diagonal_Atual
  for(int sl = 2, istart, iend; sl <= s0len + s1len; sl++){
    istart = max(1, sl - s0len);
    iend = min(sl - 1, s1len);
    // Fill Diagonals with base, if need
    if(sl <= sMin)
      dAtual[0] = sl;
    if(sl <= sMax)
      dAtual[sl] = sl;
    // Real Joke is Here =/
    for(int i = istart, j; i <= iend; i++){
        j = sl - i;
        dAtual[i] = min(dAnterior[i], dAnterior[i-1], dAnterior2[i - 1]) + ((*s0)[j - 1] == (*s1)[i - 1] && i == j ? 0 : 1);
    }
    dTemp = dAnterior2;
    dAnterior2 = dAnterior;
    dAnterior = dAtual;
    dAtual = dTemp;
  }
  int result = dAnterior[s1len];
  //delete[] dTemp;
  delete[] dAnterior2;
  delete[] dAnterior;
  delete[] dAtual;
  return result;
}
int lcs(const std::string &s0, const std::string &s1){
  int s0len = (s0).size(), s1len = (s1).size();
  int sMax = max(s0len, s1len) + 1, sMin = min(s0len, s1len);
  //region Create Diagonals
  int * dAnterior2 {new int[sMax]};
  dAnterior2[0] = 0;               // 0 - 0 - X
  int * dAnterior {new int[sMax]}; // 0 - X - x
  dAnterior[0] = 0;                // X - x - x
  dAnterior[1] = 0;
  int * dAtual {new int[sMax]};
  int * dTemp {new int[sMax]};
  //endregion
  // sl = Slices/Fatias/Diagonal_Atual
  for(int sl = 2, istart, iend; sl <= s0len + s1len; sl++){
    istart = max(1, sl - s0len);
    iend = min(sl - 1, s1len);
    // Fill Diagonals with base, if need
    if(sl <= sMin)
      dAtual[0] = 0;
    if(sl <= sMax)
      dAtual[sl] = 0;
    // Another real Joke is Here =/
    for(int i = istart, j; i <= iend; i++){
        j = sl - i;
        if((s0)[j - 1] == (s1)[i - 1])
          dAtual[i] = dAnterior2[i - 1] + 1;
        else
          dAtual[i] = max(dAnterior[i], dAnterior[i-1]);
    }
    dTemp = dAnterior2;
    dAnterior2 = dAnterior;
    dAnterior = dAtual;
    dAtual = dTemp;
  }
  int result = dAnterior[s1len];
  delete[] dAtual;
  // When uncomment this line, valgrind cries harder than now
  //delete[] dTemp;
  delete[] dAnterior2;
  delete[] dAnterior;
  return result;
}

int main() {
  std::string s0, n0, s1, n1;
  std::ifstream entrada0{"inputs/test0.txt"}, entrada1{"inputs/test1.txt"};
  if(entrada0.is_open() && entrada1.is_open()){
    std::getline(entrada0, n0);
    s0 = { std::istreambuf_iterator<char>(entrada0), std::istreambuf_iterator<char>() };
    std::getline(entrada1,n1);
    s1 = { std::istreambuf_iterator<char>(entrada1), std::istreambuf_iterator<char>() };
    entrada0.close();
    entrada1.close();
    std::cout << n0 << s0.size() <<" | " << n1 << s1.size() << std::endl;
    if(s0.size() < s1.size())
      std::cout << lcs(s1, s0) << std::endl;
    else
      std::cout << lcs(s0, s1) << std::endl;
      //s0.swap(s1);
    //std::cout << lcs(s0, s1) << std::endl;
    //std::cout << n0 << s0.size() <<" | " << n1 << s1.size() << std::endl;
  }
  return 0;
}
