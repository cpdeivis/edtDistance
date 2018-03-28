#include <iostream>
#include <string>

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
  return dAnterior[s1len];
}
int lcs(std::string* s0, std::string* s1){
  int s0len = (*s0).size(), s1len = (*s1).size();
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
        if((*s0)[j - 1] == (*s1)[i - 1])
          dAtual[i] = dAnterior2[i - 1] + 1;
        else
          dAtual[i] = max(dAnterior[i], dAnterior[i-1]);
    }
    dTemp = dAnterior2;
    dAnterior2 = dAnterior;
    dAnterior = dAtual;
    dAtual = dTemp;
  }
  return dAnterior[s1len];
}

int main() {
  std::string s0, s1;
  std::cin >> s0;
  std::cin >> s1;
  if(s0.size() < s1.size())
    s0.swap(s1);
  std::cout << edtDistance(&s0, &s1) << std::endl;
  std::cout << lcs(&s0, &s1) << std::endl;
  return 0;
}
