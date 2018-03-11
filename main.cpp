#include <iostream>
#include <string>

//region Min's
int min(int a, int b){
  return (a < b)? a: b;
}
int min(int top, int left, int dia){
  return min(min(top, left), dia);
}
//endregion
void edtDistance(std::string* s0, std::string* s1){
  //region Create and pre-Populatte M A T R I X
  int rows = (*s0).size() + 1, cols = (*s1).size() + 1;
  int **matriz{nullptr};
  matriz = new int*[rows];
  for(auto i = 0; i < rows; i++){
    matriz[i] = new int[cols];
    matriz[i][0] = i;
  }
  for(auto i = 0; i < cols; i++)
    matriz[0][i] = i;
  //endregion
}

int main() {
  std::string s0, s1;
  std::cin >> s0;
  std::cin >> s1;
  if(s0.size() < s1.size())
    s0.swap(s1);
  edtDistance(&s0, &s1);
  return 0;
}
