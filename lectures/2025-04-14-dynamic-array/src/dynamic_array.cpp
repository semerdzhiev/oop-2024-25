#include "dynamic_array.h"

#include <iostream>

namespace examples {

int* dynamic_array::copy_array(int* arr, size_t size)
{
	int* buffer = new int[size];

	for (size_t i = 0; i < size; ++i) {
		buffer[i] = arr[i];
	}

	return buffer;
}

dynamic_array::dynamic_array()
	: m_data(nullptr), m_allocated(0)
{
}

dynamic_array::dynamic_array(size_t size)
{
	m_data = new int[size];
	m_allocated = size;
}

dynamic_array::~dynamic_array()
{
	delete [] m_data;
}

dynamic_array::dynamic_array(dynamic_array const& other)
{
	m_data = copy_array(other.m_data, other.m_allocated);
	m_allocated = other.m_allocated;
}

dynamic_array& dynamic_array::operator=(dynamic_array const& other)
{
	if (this != &other)
	{
		// Try to create a copy of the other array
		// If the allocation fails, we will not change the current array
		// (strong exception safety guarantee).
		int* buffer = copy_array(other.m_data, other.m_allocated);

		// If we reach this point, the allocation was successful.
		// We can safely delete the old buffer and switch to the new one.
		delete[] m_data;
		m_data = buffer;
		m_allocated = other.m_allocated;
	}

	return *this;
}


int& dynamic_array::at(size_t index)
{
	if(index >= m_allocated)
		throw std::out_of_range("index outside of the bounds of the array");

	return m_data[index];
}

const int& dynamic_array::at(size_t index) const
{
	if(index >= m_allocated)
		throw std::out_of_range("index outside of the bounds of the array");

	return m_data[index];
}

void dynamic_array::swap(dynamic_array &other) noexcept
{
	std::swap(m_data, other.m_data);
	std::swap(m_allocated, other.m_allocated);
}

bool dynamic_array::operator< (const dynamic_array& other) const noexcept
{
	size_t limit = std::min(m_allocated, other.m_allocated);

	for (size_t i = 0; i < limit; i++)
	{
		if (m_data[i] < other.m_data[i])
			return true;
		else if (m_data[i] > other.m_data[i])
			return false;
	}

	return m_allocated < other.m_allocated;
}

bool dynamic_array::operator== (const dynamic_array& other) const noexcept
{
	if(m_allocated != other.m_allocated)
		return false;

	for(size_t i = 0; i < m_allocated; ++i)
	{
		if(m_data[i] != other.m_data[i])
			return false;
	}

	return true;
}

///
/// Outputs the contents of the array to an output stream.
///
/// The array is represented in the following format:
///    array <size> <element0> <element1> ... <elementN>
/// where
///    <size> is the number of elements in the array
///    <elementX> are the elements of the array.
///
std::ostream& operator<<(std::ostream &output, const dynamic_array &arr)
{
	output << "array " << arr.size();

	for (size_t i = 0; i < arr.size(); ++i) {
		output << " " << arr[i];
	}

	return output;
}

std::istream& operator>>(std::istream &input, dynamic_array &arr)
{
	 // 1: Read the identifier "array"
	std::string identifier;
	input >> identifier;

	if (identifier != "array") {
		// NOTE
		// If the read operation fails, then identifier will still be empty
		// and will not have a value of "array". Thus, this check can
		// potentially cover both the case where the read operation fails
		// and the case where the identifier is not "array".
		input.setstate(std::ios::failbit);
		return input;
	}

	// 2: Read the size of the array
	size_t size = 0;
	input >> size;

	if(input.fail()) {
		return input;
	}

	// 3: Create a temporary array of the specified size and read the data
	try {
		dynamic_array temp(size);

		size_t read_count = 0; // How many elements have been read successfully

		for(read_count = 0; read_count < size && input.good(); read_count++) {
			input >> temp[read_count]; // Read each element into the temporary array
			if (input.fail())
				return input;
		}

		if(read_count == size) {
			// If we have read all elements successfully, swap the
			// contents of the temporary array with the current array.
			arr.swap(temp);
		}
		else {
			// If we have read less elements than expected, set the failbit.
			input.setstate(std::ios::failbit);
		}
	}
	catch(std::bad_alloc&) {
		// In this case the creation of the array has failed.
		// Probably, the size was too large.
		input.setstate(std::ios::failbit);
	}

	return input;
}

} // namespace fmi