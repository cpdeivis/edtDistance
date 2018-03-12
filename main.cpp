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
//Encaminha a matriz e a posição cartesiana da célula em questão
int compare(int **matriz, int i, int j){
  return min(matriz[i - 1][j -1], matriz[i - 1][j],matriz[i][j -1]);
}
void edtDistance(std::string* s0, std::string* s1){
  //region Cria e pre-Popula M A T R I X
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
  //region Logic
  int i, j, t, lim = rows + cols -2;
  for(t = 1; t <= lim -1; ++t){
    //Slices
    for(i = t, j = 1; i >= 1 ; --i, ++j)
      if((i < rows) && (j < cols)){
        std::cout << i << ", " << j << " | ";
        matriz[i][j] = compare(matriz, i, j);
      }
    std::cout << std::endl;
  }
  //endregion

  //std::cout << matriz[rows-1][cols-1] << std::endl;
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
