#include <iostream>
#include <vector>
#include <exception>


template <class T>
  class MinHeap {
     public:
       MinHeap (int d);
       /* Constructor that builds a d-ary Min Heap
          This should work for any d >= 2,
          but doesn't have to do anything for smaller d.*/

       ~MinHeap ();

       void add (T item, int priority);
         /* adds the item to the heap, with the given priority. */

       const T & peek () const;
         /* returns the element with smallest priority.  
			Break ties however you wish.  
			Throws an exception if the heap is empty. */

       void remove ();
         /* removes the element with smallest priority.
			Break ties however you wish.
            Throws an exception if the heap is empty. */

       bool isEmpty () const;
         /* returns true iff there are no elements on the heap. */
        

   private:
    
      // whatever you need to naturally store things.
      // You may also add helper functions here.
      std::vector<std::pair<T, int>> heapPriority;//stores heap priority
      int d;//stores number of children each node has


  };

template <class T>
MinHeap<T>::~MinHeap ()
{

}

template <class T>
MinHeap<T>::MinHeap(int d)
{
    this->d = d;//stores d-ary value assumes d>=2
}

template <class T>
void MinHeap<T>::add(T item, int priority)
{
	heapPriority.push_back(std::make_pair(item, priority));
    int lastVectorElement = heapPriority.size() - 1;
    while (lastVectorElement - 1 >= 0)//checks if child has a parent
    {
      if(heapPriority[lastVectorElement].second < heapPriority[(lastVectorElement-1)/d].second)
      {
          //swaps the child with its parent if the child has a lower priority
		  std::pair<T, int> temp = heapPriority[lastVectorElement];
          heapPriority[lastVectorElement] = heapPriority[(lastVectorElement-1)/d];
          heapPriority[(lastVectorElement-1)/d] = temp;
          lastVectorElement = (lastVectorElement-1)/d;
      }
	  //NEW SHIT AHHHHHHHHHHHHHHHHHHHHHHHHH DELETE THISI IF ELSE IF YOUR PROGRAM IS BROKEN!!!!!!!!!! - breaks ties
	  else if (heapPriority[lastVectorElement].second == heapPriority[(lastVectorElement-1)/d].second && heapPriority[lastVectorElement].first < heapPriority[(lastVectorElement-1)/d].first)
      {
		    std::pair<T, int> temp = heapPriority[lastVectorElement];
          heapPriority[lastVectorElement] = heapPriority[(lastVectorElement-1)/d];
          heapPriority[(lastVectorElement-1)/d] = temp;
          lastVectorElement = (lastVectorElement-1)/d;
      }
      else {break;}//breaks if parent has a lower priority
    }
}
template<class T>
const T& MinHeap<T>::peek () const
{
	if(isEmpty())
	{
	 	throw std::logic_error("Heap is Empty");
	}
	
	return heapPriority.front().first;
}

template<class T>
void MinHeap<T>::remove()
{
	//swap first and last element of vector
	if(isEmpty())
	{
		throw std::logic_error("Heap is Empty");
	}
  	int lastVectorElement = heapPriority.size() - 1;
	//make first element the last element
	heapPriority[0] = heapPriority[lastVectorElement];
	heapPriority.pop_back();
    lastVectorElement--;
  	/*find lowest priority child and swap it with the current until you reach
  	the bottom or all children of the parent are higher priority*/
    int parentPosition = 0;
    int bestChildIndex;
    int bestChildPriority;
    while(parentPosition * d + 1 <= lastVectorElement)
    {
      /*bubble the top item down by replacing it with the least prioritized child
      to ensure minheap stays a minheap*/
      bestChildPriority = heapPriority[parentPosition * d + 1].second;
      bestChildIndex = parentPosition * d + 1;
      for (int i = 2; i <= d; i++)
      {//compares all children to find the smallest child - from 2-d because we comapring priority at i to its predecessor
        if ((parentPosition * d + i) <= lastVectorElement)
        {//makes sure we access allocted vector memory
          { 
            if(heapPriority[parentPosition * d + i].second < bestChildPriority)
            {
              bestChildIndex = parentPosition * d + i;
              bestChildPriority = heapPriority[parentPosition * d + i].second;
            }else if (heapPriority[parentPosition * d + i].second == bestChildPriority)//NEW NEW SHIT AHHHHHHHHHH - breaks ties
            {
              if(heapPriority[parentPosition * d + i].first < heapPriority[bestChildIndex].first)//NEW SHIT - breaks ties
			  {
				bestChildIndex = parentPosition * d + i;
              	bestChildPriority = heapPriority[parentPosition * d + i].second;
			  }
            }
          }
        }
      }
      //swap the parent with the bestChild if bestChildPriority < parent priority
    	if(heapPriority[bestChildIndex].second < heapPriority[parentPosition].second)
    	{
		std::pair<T, int> temp = heapPriority[parentPosition];
        heapPriority[parentPosition] = heapPriority[bestChildIndex];
        heapPriority[bestChildIndex] = temp;
		parentPosition = bestChildIndex;
    	}
		//DELETE THIS FUCKING SHIT AHHHHHHHHH IIT BETTER NOT BREAK YO PROGRAM - breaks ties
		else if (heapPriority[bestChildIndex].second == heapPriority[parentPosition].second && heapPriority[bestChildIndex].first < heapPriority[parentPosition].first)
      	{
			  //swap the parent with the bestChild
			std::pair<T, int> temp = heapPriority[lastVectorElement];
          	heapPriority[lastVectorElement] = heapPriority[(lastVectorElement-1)/d];
          	heapPriority[(lastVectorElement-1)/d] = temp;
          	lastVectorElement = (lastVectorElement-1)/d;
		}
		else
		  {
			  break;//breaks if all children have a higher priority
		  }
    }
}
template <class T>
bool MinHeap<T>::isEmpty() const
{
    return heapPriority.empty();
}