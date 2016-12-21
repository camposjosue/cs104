#ifndef MSORT_H
#define MSORT_H

#include <vector>
#include <string>
#include <math.h>

template <typename T, typename Comparator>
void mort(std::vector<T>& a, int l, int r, Comparator comp);
template <typename T, typename Comparator>
void Merge (std::vector<T>& a, int l, int r, int m, Comparator comp);



struct IntComp {
    bool operator()(const int& lhs, const int& rhs) 
    { // Uses string's built in operator< 
      // to do lexicographic (alphabetical) comparison
      return lhs < rhs; 
    }
};
struct GrtDoubleComp {
    bool operator()(const double& lhs, const double& rhs) 
    { // Uses string's built in operator< 
      // to do lexicographic (alphabetical) comparison
      return lhs < rhs; 
    }
};

 struct AlphaStrComp {
    bool operator()(const std::string& lhs, const std::string& rhs) 
    { // Uses string's built in operator< 
      // to do lexicographic (alphabetical) comparison
      return lhs < rhs; 
    }
  };

  struct LengthStrComp {
    bool operator()(const std::string& lhs, const std::string& rhs) 
    { // Uses string's built in operator< 
      // to do lexicographic (alphabetical) comparison
      return lhs.size() < rhs.size(); 
    }
  };


template <typename T, typename Comparator>
void mergeSort (std::vector<T>& myArray, Comparator comp){
	int left=0;
	int right= myArray.size()-1;

	mort(myArray, left, right, comp);
}

template <typename T, typename Comparator>
void mort(std::vector<T>& a, int l, int r, Comparator comp)
{
	if (l<r) { // otherwise, just one element, which is sorted
		int m = floor((l+r)/2);
		mort(a, l, m, comp);
		mort(a, m+1, r, comp);
		Merge(a, l, r, m, comp); // this is a separate function given below
	}
}

template <typename T, typename Comparator>
void Merge (std::vector<T>& a, int l, int r, int m, Comparator comp)
{
	T temp[r+1-l];
	// trace through the two subarrays, copying into a temporary one
	int i = l, j = m+1, k = 0;
	while (i <= m || j <= r) // at least one subarray contains another element
	{
		if (i <= m && (j > r || a[i] <= a[j]))
		// next smallest element in left subarray
		{ temp[k] = a[i]; i ++; k ++; }
		else { temp[k] = a[j]; j ++; k ++; }
		// next smallest element in right subarray
	}
	// now copy over the merged array into the original
	for (k = 0; k < r+1-l; k ++)
		a[k+l] = temp[k];
};

#endif 