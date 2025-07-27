# 🧱 _MY_ARRAY_ WITH C++
THIS IS A CONTAINER WHICHS PRETTY MUCHS MIMICS AN ARRAY IN C++
IT SUPPORTS THE FOLLOWING OPERATIONS:
1. IT HAS CUSTOM ITERATOS CLASSES :ITERATOR AND CONST_ITERATOR
2. IT ALSO SUPPORTS ALL THE REGURARL OPERATIONS AN STD::ARRAY HAS
3. DIFFERENCES ARE THAT THIS ARRAY DOESN'T HAVE REVERSE ITERATORS SO YOU HAVE TO USE ITERATOR OR CONST ITERATOR AND MAKE IT GO BACKWARDS WHICH IS STILL GOOD</br>
SUPPORTED FUNCTIONS:
1. at() function which checks is used to access the array with index passed with check if it valid
2. operator [] is the same case with the at function however this array doesn't have the check be careful
3. fill() function which assigns a certain value that you passed to the array
4. swap() function which is used to swap to arrays with the same size and type
5. data() function which returns the raw array that the class i holding,NOTE that:this array is pretty much a wrapper around a raw c array
6. max_size() pretty much returns the size of array
7. constructors and destructors and operators = are all implicit
8. size() is the same with max size
9. size==0 is not allowed the size of the array must be >0 so the array will never be empty so empty() func will always return false
10. front() func returns the first element of the array
11. back() func returns the last element of the array
12. and also the begin(),end(),cbegin(),cend() funcs which use iterator and const_iterator
# 🔂iterator ,🧠 LOGIC BEHIND THE ITERATOR 
Pretty much the my custom iterator class is just a wrapper around three pointers begin,end,ptr:
1. ptr is the position we are currently at the array
2. begin is the start of the array (the first element)
3. end is one element past the last element of the array
begin,end are pretty much the bounds for the array ptr is currently pointing simple as that</br>
also the iterator supports the following operations:
 - operator ++ makes ptr go forward but we check 
if ptr is valid in the range [begin,end) then we move him
else we make no move the ptr can only go to (begin,end]
 - operator !=/== is for iterators comparison pretty much
compares ptr's
 - reference qualifiers where needed and is necessary
 - like operator * and operator ->
 - operator += makes ptr to go forward for a certain index
if it is possible if we reach the end then we stay there 
and we can't go further
 - operator + return another iterator which points forward by
a certain index you gave if this it doesn't reach the end
 - operators -,--,-= same concepts but this time
the only difference is that we move backwards and
we can only move in the range (begin,end] in order to
be at [begin,end) </br>
- also note that the *,-> operators only work in the
range [begin,end) because that where the elements are
- also operator [] is supported and it throws if
ptr+pos is not in the range [begin,end) 
- also note that: the iterator can only point to nullptr
or to an array
- also note that:this iterator is used to get the element 
and change it nothing else
- last if the iterator becomes invalid it is your
duty to not perform any operations in it becauses 
in order for the iterator to work is must point to a valid
range
# 🔂CONST_ITERATOR,🧠 LOGIC BEHIND THE CONST_ITERATOR 
- this is a custom const_iterator class
it works exactly the same with the iterator class
above except that this iterator is used in order
to only get the element not change it 
that why there are only const versions
of the operators *,->
# 📬IF YOU HAVE ANY ISSEUES ON THIS PLZ FEEL FREE TO SUBMIT THEM 📬

    
# 👥CONTRIBUTORS:

🎨~The-Mastermind1
