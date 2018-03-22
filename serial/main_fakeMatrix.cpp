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

void edtDistance2(std::string* s0, std::string* s1){
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
    istart = max(1, sl - s1len);
    iend = min(sl - 1, s0len);
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
  std::cout << dAnterior[s0len] << std::endl;
}

int main() {
  std::string s0, s1;
  std::cin >> s0;
  std::cin >> s1;
  if(s0.size() < s1.size())
    s0.swap(s1);
  edtDistance2(&s0, &s1);
  return 0;
}
