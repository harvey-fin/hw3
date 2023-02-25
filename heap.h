#ifndef HEAP_H
#define HEAP_H
#include <functional>
#include <stdexcept>
#include <vector>

template <typename T, typename PComparator = std::less<T> >
class Heap
{
public:
  /**
   * @brief Construct a new Heap object
   * 
   * @param m ary-ness of heap tree (default to 2)
   * @param c binary predicate function/functor that takes two items
   *          as an argument and returns a bool if the first argument has
   *          priority over the second.
   */
  Heap(int m=2, PComparator c = PComparator());

  /**
  * @brief Destroy the Heap object
  * 
  */
  ~Heap();

  /**
   * @brief Push an item to the heap
   * 
   * @param item item to heap
   */
  void push(const T& item);

  /**
   * @brief Returns the top (priority) item
   * 
   * @return T const& top priority item
   * @throw std::underflow_error if the heap is empty
   */
  T const & top() const;

  /**
   * @brief Remove the top priority item
   * 
   * @throw std::underflow_error if the heap is empty
   */
  void pop();

  /// returns true if the heap is empty

  /**
   * @brief Returns true if the heap is empty
   * 
   */
  bool empty() const;

    /**
   * @brief Returns size of the heap
   * 
   */
  size_t size() const;

private:
  /// Add whatever helper functions and data members you need below
  size_t get_target_child(size_t curr_idx);
  std::vector<T> data;
  int dim;
  PComparator comp;
};

// Add implementation of member functions here
template <typename T, typename PComparator>
Heap<T,PComparator>::Heap(int m, PComparator c):
dim(m), comp(c)
{
}

template <typename T, typename PComparator>
Heap<T,PComparator>::~Heap(){}

template <typename T, typename PComparator>
bool Heap<T,PComparator>::empty() const
{
  return (data.size() == 0);
}

template <typename T, typename PComparator>
size_t Heap<T,PComparator>::size() const
{
  return data.size();
}

template <typename T, typename PComparator>
void Heap<T,PComparator>::push(const T& item)
{
  data.push_back(item);
  std::size_t index = data.size() - 1;
  while (index) {
      std::size_t parent_index = (index - 1) / dim;
      T current = data[index];
      T parent = data[parent_index];
      if (comp(parent, current)) {
          break;
      }
      std::swap(data[index], data[parent_index]);
      index = parent_index;
  }
}

// We will start top() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
T const & Heap<T,PComparator>::top() const
{
  // Here we use exceptions to handle the case of trying
  // to access the top element of an empty heap
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
    throw std::underflow_error("Error, empty heap!");
  }
  // If we get here we know the heap has at least 1 item
  // Add code to return the top element
  return data[0];
}


// We will start pop() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
void Heap<T,PComparator>::pop()
{
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
    throw std::underflow_error("Error, empty heap!");
  } 
  std::swap(data[0], data[data.size()-1]);
  data.pop_back();
  if (!data.size()){return;}
  size_t curr_idx = 0;
  size_t target_idx = get_target_child(curr_idx);
  while(target_idx){
    std::swap(data[curr_idx], data[target_idx]);
    curr_idx = target_idx;
    target_idx = get_target_child(curr_idx);
  }
}

template <typename T, typename PComparator>
size_t Heap<T,PComparator>::get_target_child(size_t curr_idx)
{
  if (curr_idx*dim+1 > data.size()-1)
  {
    return 0;
  }
  else if ((curr_idx+1)*dim >= data.size()-1)
  {
    T max_val = data[curr_idx*dim+1];
    size_t max_idx = curr_idx*dim+1;
    for (size_t i=curr_idx*dim+1; i<data.size(); i++){
      T curr_val = data[i];
      if (comp(curr_val, max_val)){
        max_val = curr_val;
        max_idx = i;
      }
    }
    if (comp(max_val, data[curr_idx])){return max_idx;}
    else{return 0;}
  }
  else{
    T max_val = data[curr_idx*dim+1];
    size_t max_idx = curr_idx*dim+1;
    for (size_t i=curr_idx*dim+1; i<(curr_idx+1)*dim+1; i++){
      T curr_val = data[i];
      if (comp(curr_val, max_val)){
        max_val = curr_val;
        max_idx = i;
      }
    }
    if (comp(max_val, data[curr_idx])){return max_idx;}
    else{return 0;}
  }
}



#endif

