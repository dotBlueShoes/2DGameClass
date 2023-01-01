#pragma once

// [ This can be reassigned but it's inner data type cannot ]
// const ptr* value
// [ This cannot be reassigned but it's inner data type can ]
// ptr * const value

//template <class T>
//struct pointer {
//	T* value;
//
//	constexpr pointer(T* const other) {
//		value = other;
//	}
//
//	//pointer<T>& operator=(const pointer<T>& other) {
//	//	value = other.value;
//	//	return *this;  // Return a reference to myself.
//	//}
//
//	pointer<T>& operator=(T* const other) {
//		value = other;
//		return *this;  // Return a reference to myself.
//	}
//
//};