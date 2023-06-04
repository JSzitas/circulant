#include "circulant.h"

int main() {
  {
    // simplest test case - size 1
    std::cout << "A dynamically allocated circulant that only hold the last value." << std::endl;
    circulant<float> obj(std::vector<float>({1}));
    obj.print();
    const size_t n_insertions = 7;
    for(size_t i = 0; i < n_insertions; i++) {
      std::cout << "Insertion no.: " << i << std::endl;
      obj.push_back(obj.size()+1+i);
      obj.print();
      for(size_t j = 0; j < obj.size(); j++) {
        obj.print(j);
      }
      std::cout << "Back: " << obj.back() << std::endl;
    }
  }
  {
    // more complex test case - size 4
    std::cout << "A dynamically allocated circulant that holds 4 values." << std::endl;
    circulant<float> obj(std::vector<float>({1,2,3,4}));
    obj.print();
    const size_t n_insertions = 13;
    for(size_t i = 0; i < n_insertions; i++) {
      std::cout << "Insertion no.: " << i << std::endl;
      obj.push_back(obj.size()+1+i);
      obj.print();
      for(size_t j = 0; j < obj.size(); j++) {
        obj.print(j);
      }
      std::cout << "Back: " << obj.back() << std::endl;
    }
  }
  {
    // simple static test case - size 1
    std::cout << "A statically allocated circulant that holds the last value." << std::endl;
    fixed_circulant<float, 1> obj;
    const size_t n_insertions = 7;
    for(size_t i = 0; i < n_insertions; i++) {
      std::cout << "Insertion no.: " << i << std::endl;
      obj.push_back(i);
      obj.print();
    }
  }
  {
    // more complex test case - size 4
    std::cout << "A statically allocated circulant that holds 4 values." << std::endl;
    fixed_circulant<float,4> obj;
    obj.push_back(0);
    obj.push_back(1);
    obj.push_back(2);
    obj.push_back(3);
    obj.print();
    const size_t n_insertions = 13;
    for(size_t i = 0; i < n_insertions; i++) {
      std::cout << "Insertion no.: " << i << std::endl;
      obj.push_back(4+i);
      obj.print();
      for(size_t j = 0; j < 4; j++) {
        obj.print(j);
      }
    }
  }
  return 0;
}
