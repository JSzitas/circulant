# circulant

A bloody simple data structure, both dynamic (and heap allocated) and fixed (and stack allocated). 
This does one thing, and one thing only; provides a fixed size data structure that replaces oldest 
elements with newest ones, without dynamically growing memory, or forcing the user to be aware of indexing. 

## Setup

When using time series models, you frequently want to keep only the last *p* (or *k*, or *m*, or whatever your preferred notation is) 
values at any given time. The simplest example would be an **AR(p)** model, which requires using the last **p** values for prediction 
at any given time. 

If you are lazy, you **could** just use an ever growing vector, like so: 

``` cpp

std::vector<float> y(10);
// push values onto y that actually matter to me
// ... and then estimate, say, an AR(5), with coefficient stored as: 

const size_t p = 5;
std::vector<float> coef(p);

// during prediction, we naturally do the following for the first observation: 
float prediction = 0.0;
for(size_t i = 0; i < p; ++i) {
  prediction += coef[i] * y[i];
}
// note that this only works if your coefficients are ordered p, p-1, ..., 1, 
// or your y is inverted (which is silly), so normally, you do something more like
for(size_t i = 0; i < p; ++i) {
  prediction += coef[p - 1 -i] * y[i];
}
// which works for the first step
// however, making recursive predictions, if lazy, you wind up doing this: 
y.push_back(prediction);
// and then your life takes a turn for the worse 
const size_t offset = 1;
for(size_t i = 0; i < p; ++i) {
  // MIND THE OFFSET
  prediction += coef[p - 1 -i] * y[i + offset];
}
// the only saving grace being that for a h step forecast, you could just do: 
std::vector<float> predicted_values(h);
for(size_t i = 0; i < h; ++i) {
  float prediction = 0.0;
  for(size_t j = 0; j < p; ++j) {
    prediction += coef[p - 1 -j] * y[j + i];
  }
  predicted_values[i] = prediction;
  y.push_back(prediction);
}
// however, if you do this, you have essentialy ruined y for future forecasting 
// so typically, you will, instead, copy y and work with that - perhaps copying 
// only the first few values 
```

However, that does not really alleviate some issues - you are potentially copying more values
than you need, allocating more memory than you might like, and just generally not having a very 
good time. You might get the bright idea to use a queue for this, to lower your memory usage: 

``` cpp

std::queue the_improvement(p);
// push back, pop front, etc.
```

## Payoff

However that is not quite continguous in memory, and it does not necessarily provide the fastest 
access, and you could get potentially a bit squeamish about dynamic allocations and all that. 

Enter, finally, the **circulant**! 

``` cpp
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
```

This dumb little thing only holds up to **k** elements, specified at creation (or 
at compile time, for the **fixed_circulant** which mimics **std::array**). 

Pushing back on it replaces the oldest value with the newest one, while creating an index which is 
'valid' in the sense that indexing into the object with **'operator []'** will give you the 
expected result (index 0 is always the oldest element, and the elements are appropriately ordered). 

This is done via modular indexing - the vector/array essentialy loop over in their indexes. 
The main advantage of this is memory savings, ease of use, and generally making it harder 
to run into indexing issues when attempting to do recursive time series forecasting. 

## Usage + more examples

To use this, simply copy the circulant header into your project and include: 

``` cpp
#include "circulant.h"
```

To build and view examples, you will need **make** or the commands from the command line. 
If you already have **make**, you can simply 

```
make example
```

then run the example from the command line. Reading this should also provide some clarity into 
how the data structure is meant to be used. 
