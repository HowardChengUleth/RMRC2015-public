#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>

using namespace std;

struct ingredient
{
  string name;
  double weight;
  double percentage;
};

int main(int argc, char *argv[])
{
  int ncase;
  cin >> ncase;
  for (int icase=0; icase<ncase; ++icase) {
    int ningredient,nservings,nrequired;
    cin >> ningredient >> nservings >> nrequired;
    std::vector < ingredient > recipe;

    recipe.resize(ningredient);
    int imain = -1;
    double closeness = 0;
    for (int iingredient = 0; iingredient < ningredient; ++iingredient) {
      ingredient &item=recipe[iingredient];
      cin >> item.name >> item.weight >> item.percentage;
      if (imain == -1 || fabs(item.percentage-100.0) < closeness) {
        closeness = fabs(item.percentage-100.0);
        imain = iingredient;
      }
    }
    ingredient &principle = recipe[imain];
    cout << "Recipe # " << (icase+1) << endl;
    for (int iingredient = 0; iingredient < ningredient; ++iingredient) {
      ingredient &item=recipe[iingredient];
      double weight = principle.weight*item.percentage/principle.percentage*nrequired/nservings;
      cout << fixed;
      cout.precision(1);
      cout << item.name << " " << weight << endl;
    }
    cout << "----------------------------------------" << endl;
  }
  return 0;
}

