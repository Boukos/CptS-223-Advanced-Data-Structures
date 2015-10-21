// Cpt S 223 Homework Assignment - MyString class
// Eric Chen 11381898

#include "MyString.h"

using namespace std;

MyString::MyString()
{
	// Make an empty string. Note that this is different from a NULL string.
	m_str = new char[1];
	m_str[0] = 0;
}

MyString::MyString(const char* str)
{
	// Special case for a null string
	if (!str)
	{
		m_str = new char[1];
		m_str[0] = 0;
		return;
	}

	int len = Length(str);
	m_str = new char[len + 1];
	Copy(m_str, str, len + 1);
}

MyString::MyString(const MyString& str)
{
	// Special case for a null string
	if (!str.m_str)
	{
		m_str = new char[1];
		m_str[0] = 0;
		return;
	}

	// Create a DEEP copy
	int len = Length(str.m_str);
	m_str = new char[len + 1];			// +1 for null
	Copy(m_str, str.m_str, len + 1);
}

// This is a private constructor that assumes both parameters are valid, 
// thus there isn't any error checking done on these parameters.
MyString::MyString(const char* str, int charCount)
{
	m_str = new char[charCount + 1];
	Copy(m_str, str, charCount);
	m_str[charCount] = 0;
}

MyString::~MyString()
{
	if (m_str)
	{
		delete[] m_str;
		m_str = NULL;
	}
#if defined(DEBUG) || defined(_DEBUG)
	else
	{
		std::cout << "DEBUG: WARNING, destructor called when m_str is NULL!" << std::endl;
	}
#endif
}

// Compares the desired number of characters in two strings and returns true if
// they are all equal. If the null-terminator on either string is encountered
// before the desired number of characters have been compared, then false
// will be returned.
bool MyString::AreEqual(const char* str1, const char* str2, int numCharsToCompare)
{
	while (numCharsToCompare--)
	{
		if (!str1[0])
		{
			return (0 == str2[0] && 0 == numCharsToCompare);
		}

		if (str1[0] != str2[0])
		{
			return false;
		}

		str1++;
		str2++;
	}

	// Coming here means we compared the desired number of characters
	// and didn't encounter a mismatch, so we return true.
	return true;
}

// Copies the specified number of characters from the source to destination. 
// No null terminators are used for anything. The specified number of characters 
// will be copied exactly and this could potentially go past a null terminator.
void MyString::Copy(char* destination, const char* source, int count)
{
	while (count--)
	{
		*destination++ = *source++;
	}
}

// Utility function that returns true if the arrays are equal
bool MyString::ArraysEqual(const int arr1[], const int arr2[], int size)
{
	for (int i = 0; i < size; i++)
	{
		if (arr1[i] != arr2[i])
		{
			return false;
		}
	}
	return true;
}

// Returns the number of strings that were added to output
int MyString::GetAnagrams(vector<MyString>& candidates, vector<MyString>& output)
{
	int baseLength = Length();
	int base_charCount[256] = {0};

	for (int i = 0; i < baseLength; i++)				// This records the how many of each letter there are in the base string
	{
		base_charCount[(unsigned char)m_str[i]]++;
	}

	for (int i = 0; i < candidates.size(); i++)
	{
		int candidateLength = Length(candidates[i].m_str);

		if (candidateLength == baseLength)				// This weeds out any candidates whose length doesn't match the base length
		{
			int candidate_charCount[256] = {0};

			for (int j = 0; j < candidateLength; j++)	// This records the how many of each letter there are in the candidate string
			{
				candidate_charCount[(unsigned char)candidates[i].m_str[j]]++;
			}
			if (ArraysEqual(base_charCount, candidate_charCount, 256))
			{
				output.push_back(candidates[i]);		// If arrays are equal, add the candidate to output
			}
		}
	}
	return output.size();								// return the number of anagrams in output
}

// Start the search for the character at the specified index
// Return the index of the character if it is found, -1 if it isn't
int MyString::IndexOf(char c, int startIndex) const
{
	for (int i = startIndex; m_str[i] != 0; i++)
	{
		if (m_str[i] == c)
		{
			return i;
		}
	}
	return -1;
}

// Start the search for the character at the specified index
// Return the index of the character if it is found, -1 if it isn't
int MyString::IndexOf(const char* str, int startIndex) const
{
	int thisLen = Length();
	int strLen = Length(str);

	for (int i = startIndex; i <= (thisLen-strLen); i++)
	{
		if (AreEqual(&m_str[i], str, strLen))
		{
			return i;
		}
	}
	return -1;
}

int MyString::Length() const
{
	return Length(m_str);
}

int MyString::Length(const char* str)
{
	int len = 0;
	while (*str++)
	{
		len++;
	}
	return len;
}

// Sets the string to a new string value. This is the kind of function 
// that only a mutable string class would have.
void MyString::Set(const char* str)
{
	// First delete the old string
	if (m_str)
	{
		delete[] m_str;
	}

	if (str)
	{
		int len = Length(str);
		m_str = new char[len + 1];
		char* dst = m_str;
		while (*dst++ = *str++);
	}
	else
	{
		m_str = new char[1];
		m_str[0] = 0;
	}
}

void MyString::Split(char c, std::vector<MyString>& outputVector) const
{
	int newIndex = 0;
	int oldIndex = 0;
	MyString subStr;

	while ((newIndex = IndexOf(c, oldIndex)) > 0)	// Searches for the split char, loop with index if found
	{
		if (Substring(oldIndex, newIndex-oldIndex, subStr))
		{
			outputVector.push_back(subStr);			// Add the substring to output vector
		}
		else
		{
			break;
		}

		oldIndex = newIndex + 1;					// New index including last split character
	}

	Substring(oldIndex, Length(m_str)-oldIndex, subStr);
	outputVector.push_back(subStr);
}

// Gets a substring from this string and stores it in the output string. If 
// the substring cannot be parsed, then false is returned and the output 
// string is not modified.
bool MyString::Substring(int startIndex, int length, MyString& output) const
{
	if (length < 1 || startIndex < 0)
	{
		return false;
	}
	else if (Length(m_str) < (startIndex + length))		// Out of range
	{
		return false;
	}
	else	// Substring satisfies conditions to be copied
	{
		if (output.m_str)
		{
			delete[] output.m_str;						// Delete old string
		}
		output.m_str = new char[length + 1];			// +1 for null character
		Copy(output.m_str, m_str+startIndex, length);	// Copy to output
		output.m_str[length] = 0;						// Add null char to end of substring
		return true;
	}
}

void MyString::Write(std::ostream& stream)
{
	stream << m_str;
}