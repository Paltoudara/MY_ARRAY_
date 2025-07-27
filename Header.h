#pragma once
#include<iostream>
#include<type_traits>
#include<algorithm>
#include<initializer_list>
#include<functional>
#include<cstdlib>
#include"Macros.h"
#include<cassert>
#include<utility>
#include<memory>
_PANAGIOTIS_BEGIN
//this class behaves pretty similar to std::array
//with some differences:
//final keywords
//array_iterators inside the class 
//aslo an my_array with zero size is not allowed
//also reverse iterators are not implemented
//all the other methods though are pretty much the same
template<typename _Ty, std::size_t count>
class my_array  final {
private:
	//this is a custom array_iterator class
	//it supports nearly all the operations 
	//that a regurarl iterator supports
	//it has private members:ptr,begin,end
	//- ptr->where we are at the array 
	//- begin->where is the begining of the array
	//- end-> where is the end of the array 
	//note that: end for as size of the array+1 one past last element
	//supported operations:
	//- operator ++ makes ptr go forward but we check 
	//if ptr is valid in the range [begin,end) then we move him
	//else we make no move the ptr can only go to (begin,end]
	//- operator !=/== is for iterators comparison pretty much
	//compares ptr's
	//- reference qualifiers where needed and is necessary
	//- like operator * and operator ->
	//- operator += makes ptr to go forward for a certain index
	//if it is possible if we reach the end then we stay there 
	//and we can't go further
	//- operator + return another iterator which points forward by
	//a certain index you gave if this it doesn't reach the end
	//- operators -,--,-= same concepts but this time 
	//the only difference is that we move backwards and
	// we can only move in the range (begin,end] in order to
	//be at [begin,end)
	//also note that the *,-> operators only work in the 
	//range [begin,end) because that where the elements are
	//also operator [] is supported and it throws if
	//ptr+pos is not in the range [begin,end) 
	//also note that: the iterator can only point to nullptr
	//or to an array
	// also note that:this iterator is used to get the element 
	// and change it nothing else
	//and but last if the iterator becomes invalid it is your
	//duty to not perform any operations in it becauses 
	//in order for the iterator to work is must point to a valid
	//range
	//this class is a wrapped around pointers simple enough
	class array_iterator final {
	private:
		_Ty* ptr;
		_Ty* begin;
		_Ty* end;
	public:
		// //
		array_iterator()noexcept
			:ptr{}, begin{}, end{}
		{
		}
		// //
		array_iterator(_Ty* ptr1, _Ty* begin1, _Ty* end1)noexcept
			:ptr{ ptr1 }, begin{ begin1 }, end{ end1 }
		{
		}
		// //
		array_iterator(const array_iterator& other)noexcept = default;
		// //
		array_iterator(array_iterator&& other)noexcept = default;
		// //
		bool operator !=(const array_iterator& other)const noexcept {
			return ptr != other.ptr;
		}
		// //
		constexpr bool operator ==(const array_iterator& other)const noexcept {
			return ptr == other.ptr;
		}
		// //
		array_iterator operator++()noexcept {
			if ((ptr != nullptr) && (ptr >= begin && ptr < end)) {
				ptr++;
			}
			return array_iterator{ ptr,begin,end };
		}
		// //
		array_iterator operator++(int)noexcept {
			array_iterator tmp{ ptr,begin,end };
			if ((ptr != nullptr) && (ptr >= begin && ptr < end)) {
				ptr++;
			}
			return  tmp;
		}
		// //
		_Ty& operator *()& {
			if ((ptr != nullptr) && (ptr >= begin && ptr < end)) {
				return *ptr;
			}
			throw tried_to_access_an_empty_iterator_{ "tried to access an empty iterator" };
		}
		// //
		const _Ty& operator *()const& {
			if ((ptr != nullptr) && (ptr >= begin && ptr < end)) {
				return *ptr;
			}
			throw tried_to_access_an_empty_iterator_{ "tried to access an empty iterator" };
		}
		// //
		const _Ty&& operator *()const&& {
			if ((ptr != nullptr) && (ptr >= begin && ptr < end)) {
				return std::move(*ptr);
			}
			throw tried_to_access_an_empty_iterator_{ "tried to access an empty iterator" };
		}
		// //
		_Ty&& operator *()&& {
			if ((ptr != nullptr) && (ptr >= begin && ptr < end)) {
				return std::move(*ptr);
			}
			throw tried_to_access_an_empty_iterator_{ "tried to access an empty iterator" };
		}
		// //
		array_iterator operator+=(std::size_t counter)noexcept {
			for (std::size_t i = 0; i < counter; i++) {
				if ((ptr != nullptr) && (ptr >= begin && ptr < end)) {
					ptr++;
				}
				else break;
			}
			return array_iterator{ ptr, begin, end };
		}
		// //
		const _Ty* operator ->()const& {
			if ((ptr != nullptr) && (ptr >= begin && ptr < end)) {
				return std::addressof(*ptr);
			}
			throw tried_to_access_an_empty_iterator_{ "tried to access an empty iterator" };
		}
		// //
		_Ty* operator ->()& {
			if ((ptr != nullptr) && (ptr >= begin && ptr < end)) {
				return std::addressof(*ptr);
			}
			throw tried_to_access_an_empty_iterator_{ "tried to access an empty iterator" };
		}
		// //
		const _Ty* operator ->()const&& {
			if ((ptr != nullptr) && (ptr >= begin && ptr < end)) {
				return std::addressof(*ptr);
			}
			throw tried_to_access_an_empty_iterator_{ "tried to access an empty iterator" };
		}
		// //
		_Ty* operator ->()&& {
			if ((ptr != nullptr) && (ptr >= begin && ptr < end)) {
				return std::addressof(*ptr);
			}
			throw tried_to_access_an_empty_iterator_{ "tried to access an empty iterator" };
		}
		// //
		array_iterator operator +(std::size_t counter)const noexcept {
			_Ty* curr{ ptr };
			for (std::size_t i = 0; i < counter; i++) {
				if ((curr != nullptr) && (curr >= begin && curr < end))curr++;
				else break;
			}
			return array_iterator{ curr,begin,end };
		}
		// //
		friend array_iterator operator+(std::size_t counter, const
			array_iterator& it)noexcept {
			return it + counter;
		}
		// //
		array_iterator operator --()noexcept {
			if ((ptr != nullptr) && (ptr > begin && ptr <= end)) {
				ptr--;
			}
			return array_iterator{ ptr,begin,end };
		}
		// //
		array_iterator operator --(int)noexcept {
			array_iterator tmp{ ptr,begin,end };
			if ((ptr != nullptr) && (ptr > begin && ptr <= end)) {
				ptr--;
			}
			return tmp;
		}
		// //
		array_iterator operator -=(std::size_t counter)noexcept {
			for (std::size_t i = 0; i < counter; i++) {
				if ((ptr != nullptr) && (ptr > begin && ptr <= end)) {
					ptr--;
				}
				else break;
			}
			return array_iterator{ ptr,begin,end };
		}
		// //
		array_iterator operator -(std::size_t counter)noexcept {
			_Ty* curr{ ptr };
			for (std::size_t i = 0; i < counter; i++) {
				if ((curr != nullptr) && (curr > begin && curr <= end)) {
					curr--;
				}
				else break;
			}
			return array_iterator{ curr,begin,end };
		}
		// //
		array_iterator operator=(const array_iterator& other)noexcept {
			ptr = other.ptr;
			begin = other.begin;
			end = other.end;
			return *this;
		}
		// //
		array_iterator operator=(array_iterator&& other)noexcept {
			ptr = other.ptr;
			begin = other.begin;
			end = other.end;
			return *this;
		}
		// //
		~array_iterator()noexcept {
			ptr = end = begin = nullptr;
		}
		// //
		_Ty& operator [](std::size_t pos)& {
			if (pos >= count) {
				throw array_subscript_out_of_range{ "tried to access"
				"invalid index of an array" };
			}
			if ((ptr != nullptr) && (ptr + pos >= begin && ptr + pos < end)) {
				return ptr[pos];
			}
			throw tried_to_access_an_empty_iterator_{ "tried to access an empty iterator" };
		}
		// //
		const _Ty& operator [](std::size_t pos)const& {
			if (pos >= count) {
				throw array_subscript_out_of_range{ "tried to access"
				"invalid index of an array" };
			}
			if ((ptr != nullptr) && (ptr + pos >= begin && ptr + pos < end)) {
				return ptr[pos];
			}
			throw tried_to_access_an_empty_iterator_{ "tried to access an empty iterator" };
		}
		// //
		const _Ty&& operator [](std::size_t pos)const&& {
			if (pos >= count) {
				throw array_subscript_out_of_range{ "tried to access"
				"invalid index of an array" };
			}
			if ((ptr != nullptr) && (ptr + pos >= begin && ptr + pos < end)) {
				return std::move(ptr[pos]);
			}
			throw tried_to_access_an_empty_iterator_{ "tried to access an empty iterator" };
		}
		// //
		_Ty&& operator [](std::size_t pos)&& {
			if (pos >= count) {
				throw array_subscript_out_of_range{ "tried to access"
				"invalid index of an array" };
			}
			if ((ptr != nullptr) && (ptr + pos >= begin && ptr + pos < end)) {
				return std::move(ptr[pos]);
			}
			throw tried_to_access_an_empty_iterator_{ "tried to access an empty iterator" };
		}
	};
	//this is a custom const_iterator class
	//it works exactly the same with the iterator class
	//above except that this iterator is used in order
	//to only get the element not change it 
	//that why there are only const versions
	//of the operators *,->
	class array_const_iterator final {
	private:
		_Ty* ptr;
		_Ty* begin;
		_Ty* end;
	public:
		// //
		array_const_iterator()noexcept
			:ptr{}, begin{}, end{}
		{
		}
		// //
		array_const_iterator(_Ty* ptr1, _Ty* begin1, _Ty* end1)noexcept
			:ptr{ ptr1 }, begin{ begin1 }, end{ end1 }
		{
		}
		// //
		array_const_iterator(const array_const_iterator& other)noexcept = default;
		// //
		array_const_iterator(array_const_iterator&& other)noexcept = default;
		// //
		bool operator !=(const array_const_iterator& other)const noexcept {
			return ptr != other.ptr;
		}
		// //
		bool operator ==(const array_const_iterator& other)const noexcept {
			return ptr == other.ptr;
		}
		// //
		array_const_iterator operator++()noexcept {
			if ((ptr != nullptr) && (ptr >= begin && ptr < end)) {
				ptr++;
			}
			return array_const_iterator{ ptr,begin,end };
		}
		// //
		array_const_iterator operator++(int)noexcept {
			array_const_iterator tmp{ ptr,begin,end };
			if ((ptr != nullptr) && (ptr >= begin && ptr < end)) {
				ptr++;
			}
			return  tmp;
		}
		// //
		const _Ty& operator *()const& {
			if ((ptr != nullptr) && (ptr >= begin && ptr < end)) {
				return *ptr;
			}
			throw tried_to_access_an_empty_iterator_{ "tried to access an empty iterator" };
		}
		// //
		const _Ty&& operator *()const&& {
			if ((ptr != nullptr) && (ptr >= begin && ptr < end)) {
				return std::move(*ptr);
			}
			throw tried_to_access_an_empty_iterator_{ "tried to access an empty iterator" };
		}
		// //
		array_const_iterator operator+=(std::size_t counter)noexcept {
			for (std::size_t i = 0; i < counter; i++) {
				if ((ptr != nullptr) && (ptr >= begin && ptr < end)) {
					ptr++;
				}
				else break;
			}
			return array_const_iterator{ ptr, begin, end };
		}
		// //
		const _Ty* operator ->()const& {
			if ((ptr != nullptr) && (ptr >= begin && ptr < end)) {
				return std::addressof(*ptr);
			}
			throw tried_to_access_an_empty_iterator_{ "tried to access an empty iterator" };
		}
		// //
		const _Ty* operator ->()const&& {
			if ((ptr != nullptr) && (ptr >= begin && ptr < end)) {
				return std::addressof(*ptr);
			}
			throw tried_to_access_an_empty_iterator_{ "tried to access an empty iterator" };
		}
		// //
		array_const_iterator operator +(std::size_t counter)const noexcept {
			_Ty* curr{ ptr };
			for (std::size_t i = 0; i < counter; i++) {
				if ((curr != nullptr) && (curr >= begin && curr < end))curr++;
				else break;
			}
			return array_const_iterator{ curr,begin,end };
		}
		// //
		friend array_const_iterator operator+(std::size_t counter, const
			array_const_iterator& it)noexcept {
			return it + counter;
		}
		// //
		array_const_iterator operator --()noexcept {
			if ((ptr != nullptr) && (ptr > begin && ptr <= end)) {
				ptr--;
			}
			return array_const_iterator{ ptr,begin,end };
		}
		// //
		array_const_iterator operator --(int)noexcept {
			array_const_iterator tmp{ ptr,begin,end };
			if ((ptr != nullptr) && (ptr > begin && ptr <= end)) {
				ptr--;
			}
			return tmp;
		}
		// //
		array_const_iterator operator -=(std::size_t counter)noexcept {
			for (std::size_t i = 0; i < counter; i++) {
				if ((ptr != nullptr) && (ptr > begin && ptr <= end)) {
					ptr--;
				}
				else break;
			}
			return array_const_iterator{ ptr,begin,end };
		}
		// //
		array_const_iterator operator -(std::size_t counter)noexcept {
			_Ty* curr{ ptr };
			for (std::size_t i = 0; i < counter; i++) {
				if ((curr != nullptr) && (curr > begin && curr <= end)) {
					curr--;
				}
				else break;
			}
			return array_const_iterator{ curr,begin,end };
		}
		// //
		array_const_iterator operator=(const array_const_iterator& other)noexcept {
			ptr = other.ptr;
			begin = other.begin;
			end = other.end;
			return *this;
		}
		// //
		array_const_iterator operator=(array_const_iterator&& other)noexcept {
			ptr = other.ptr;
			begin = other.begin;
			end = other.end;
			return *this;
		}
		// //
		~array_const_iterator()noexcept {
			ptr = end = begin = nullptr;
		}
		// //
		const _Ty& operator [](std::size_t pos)const& {
			if (pos >= count) {
				throw array_subscript_out_of_range{ "tried to access"
				"invalid index of an array" };
			}
			if ((ptr != nullptr) && (ptr + pos >= begin && ptr + pos < end)) {
				return ptr[pos];
			}
			throw tried_to_access_an_empty_iterator_{ "tried to access an empty iterator" };
		}
		// // 
		const _Ty&& operator [](std::size_t pos)const&& {
			if (pos >= count) {
				throw array_subscript_out_of_range{ "tried to access"
				"invalid index of an array" };
			}
			if ((ptr != nullptr) && (ptr + pos >= begin && ptr + pos < end)) {
				return std::move(ptr[pos]);
			}
			throw tried_to_access_an_empty_iterator_{ "tried to access an empty iterator" };
		}
	};
	//
public:
	static_assert(std::is_object_v<_Ty>, "The C++ Standard forbids container adaptors of non-object types "
		"because of [container.requirements].");
	static_assert(count > 0, "my_array<T, 0> is ill-formed: zero-sized arrays are not allowed.");
	using iterator = array_iterator;
	using const_iterator = array_const_iterator;
	_Ty array[count];
	//begin func done
	_NODISCARD iterator begin()noexcept {
		//this pretty much return an iterator to the
		//begining of the array more explanation up 
		//where we explain the custom iterator class
		return iterator{ array,array,array + count };
	}
	//end func done
	_NODISCARD iterator end()noexcept {
		//this pretty much return an iterator to the
		//end of the array more explanation up 
		//where we explain the custom iterator class
		return iterator{ array + count,array,array + count };
	}
	//cbegin func
	_NODISCARD const_iterator cbegin()noexcept {
		//this pretty much return a const_iterator to the
		//begining of the array more explanation up 
		//where we explain the custom const_iterator class
		return const_iterator{ array,array,array + count };
	}
	//cbegin fun done
	_NODISCARD const_iterator cend()noexcept {
		//this pretty much return an iterator to the
		//end of the array more explanation up 
		//where we explain the custom const_iterator class
		return const_iterator{ array + count,array,array + count };
	}
	//constructors,destructors and operator= 
	// are implicitly declared
	//empty func done
	_NODISCARD constexpr bool empty()const noexcept {
		//the array is never empty
		return false;
	}
	//size func done
	_NODISCARD constexpr std::size_t size()const noexcept {
		//return size of array
		return count;
	}
	//front func done
	_NODISCARD constexpr const _Ty& front()const noexcept {
		//returns the first element of an array
		return array[0];
	}
	//front func done
	_NODISCARD constexpr _Ty& front() noexcept {
		//returns the first element of an array
		return array[0];
	}
	//back func done
	_NODISCARD constexpr const _Ty& back()const noexcept {
		//returns the last element of an array
		return array[count - 1];
	}
	//back func done
	_NODISCARD constexpr _Ty& back() noexcept {
		//returns the last element of an array
		return array[count - 1];
	}

	//max_size func done
	_NODISCARD constexpr std::size_t max_size() const noexcept {
		//again the size of the array
		return count;
	}
	//data func done
	_NODISCARD constexpr const _Ty* data() const noexcept {
		//pretty much returns the raw array
		return array;
	}
	//data func done
	_NODISCARD constexpr _Ty* data() noexcept {
		//pretty much returns the raw array
		return array;
	}
	//at func done
	_NODISCARD  const _Ty& at(std::size_t pos)const {
		//this func is the same with operator []
		//but this func checks the index you passed
		//std::cout << "hello\n";
		if (pos >= count)
		{
			throw array_subscript_out_of_range{ "tried to access"
			"invalid index of an array" };
		}
		return array[pos];
	}
	//at func done 
	_NODISCARD constexpr _Ty& at(std::size_t pos) {
		//this func is the same with operator []
		//but this func checks the index you passed
		std::cout << "hello\n";
		if (pos >= count)
		{
			throw array_subscript_out_of_range{ "tried to access"
			"invalid index of an array" };
		}
		return array[pos];
	}
	//operator [] func done
	_NODISCARD constexpr const _Ty& operator [](std::size_t pos)const noexcept {
		//pretty much used to access the array
		//beware of invalid indexes
		assert(pos < count);
		return array[pos];
	}
	//operator [] func done
	_NODISCARD constexpr _Ty& operator [](std::size_t pos) noexcept {
		//pretty much used to access the array
		//beware of invalid indexes
		assert(pos < count);
		return array[pos];
	}
	//fill func done
	constexpr void fill(const _Ty& _Value) {
		//fill method of an array pretty much assigns all elements
		//into this value
		std::fill_n(array, count, _Value);
	}
	//swap func done
	constexpr void swap(my_array<_Ty, count>& other)
		noexcept(std::is_nothrow_swappable_v<_Ty>) {
		//swaps the contents of two arrays with the same sizes and types
		std::swap(array, other.array);
	}

};

//this is a structure that forces all types past to be the same
template <class _First, class... _Rest>
struct _Enforce_same {
	static_assert(
		std::conjunction_v<std::is_same<_First, _Rest>...>, "N4950 [array.cons]/2: Mandates: (is_same_v<T, U> && ...) is true.");
	using type = _First;
};
//this is a deduction guide same with the std::array is 
//forces the elements passed to be the same 
template <class _First, class... _Rest>
my_array(_First, _Rest...) -> my_array<typename _Enforce_same<_First, _Rest...>::type, 1 + sizeof...(_Rest)>;
//


_PANAGIOTIS_END
