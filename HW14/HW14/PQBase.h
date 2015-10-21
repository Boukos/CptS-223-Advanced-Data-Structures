#pragma once

template <typename T>

class PQBase 
{
public:
	virtual ~PQBase() { }
	virtual void Add(const T& toCopyAndAdd) = 0;
	virtual bool IsEmpty() const = 0;
	virtual bool RemoveMax(T& outputItem) = 0;
private:
};
