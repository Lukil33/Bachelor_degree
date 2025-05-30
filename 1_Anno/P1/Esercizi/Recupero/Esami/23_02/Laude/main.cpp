#include <iostream>
#include <cstdlib>

// Inserire qui sotto le definizioni delle funzioni SnowFlake e KochCurve
int SnowFlake(double line_l, int level){
    if(level != 0){
        line_l = line_l/3;
        SnowFlake(line_l, level-1);
    }
}
// Inserire qui sopra le definizioni delle funzioni SnowFlake e KochCurve


int main(int argc, char **argv) {
  int level = 2;
  double line_length = 90.0;

  if (argc == 3) {
    level = strtol(argv[1], NULL, 10);
    line_length = strtod(argv[2], NULL);
  }

  std::cout << "Un fiocco di neve per ll="
           << line_length <<  " e level ="
           << level << " e': " << std::endl;
  SnowFlake(line_length, level);
  std::cout << std::endl;
}
