#include <iostream>

#include "classes/util/Util.hpp"

using namespace std;

int main() {
    input_params();
    if(is_valid_params(N, M, w, x, y, z)) open_museum();
    else cout << "Invalid parameters" << endl;
}