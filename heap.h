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
  std::vector<T> heap;
  int m; 
  PComparator pcomp; 

};

// Add implementation of member functions here
//Constructor
template <typename T, typename PComparator>
Heap<T, PComparator>::Heap(int m, PComparator c) : m(m), pcomp(c){

}

//Destructor
template <typename T, typename PComparator>
Heap<T, PComparator>::~Heap() {

}

//Push
template <typename T, typename PComparator>
void Heap<T, PComparator>::push(const T& item) {
  heap.push_back(item);
  

  size_t i = heap.size() - 1; //Index of item
  while (i != 0) {
    size_t parent = (i - 1) / m; //Parent node of item (divide by amount of children possible)
    if (pcomp(heap[i], heap[parent])) { //If the comparison is true (index better than parent)
      std::swap(heap[i], heap[parent]); //Swap item and parent
      i = parent;
    } else {
      break;
    }
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
    throw std::underflow_error("Empty heap");
  }
  // If we get here we know the heap has at least 1 item
  // Add code to return the top element

  //Return top of heap (1st element)
  return heap[0];


}


// We will start pop() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
void Heap<T,PComparator>::pop() {
  if(empty()) {
    throw std::underflow_error("Empty heap.");
  }
  
  std::swap(heap[0], heap.back());
  heap.pop_back();
  
  size_t i = 0;
  while (true) {
    size_t leftmostChild = i*m + 1;
    if (leftmostChild >= heap.size()) {
      break; // No children
    }
    size_t m_unsigned = static_cast<size_t>(m);
    size_t bestChildI = leftmostChild;
    // Find the highest priority child
    for (size_t c = 0; c < m_unsigned && leftmostChild + c < heap.size(); c++) {
      if (pcomp(heap[leftmostChild + c], heap[bestChildI])) {
        bestChildI = leftmostChild + c;
      }
    }
    
    if (pcomp(heap[bestChildI], heap[i])) {
      std::swap(heap[i], heap[bestChildI]);
      i = bestChildI;
    } else {
      break; // Heap property restored
    }
  }
}

template <typename T, typename PComparator>
bool Heap<T, PComparator>::empty() const {
  return heap.empty();
}

template <typename T, typename PComparator>
size_t Heap<T, PComparator>::size() const {
  return heap.size();
}


#endif