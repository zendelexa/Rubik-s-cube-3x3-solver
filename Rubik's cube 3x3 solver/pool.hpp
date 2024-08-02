#pragma once

#include <vector>

template<typename T>
class Pool
{
	struct Chunk
	{
		int size = 0;
		T *mem;

		// Raises C2597 error if CHUNK_SIZE is not passed as a parameter
		// C2597 Illegal reference to non static member
		Chunk(const int CHUNK_SIZE)
		:
			mem((T *)calloc(CHUNK_SIZE, sizeof(T)))
		{}
	};

	const int CHUNK_SIZE;
	std::vector<Chunk *> chunks;

public:
	Pool(int chunk_size = 1000)
	:
		CHUNK_SIZE(chunk_size)
	{}

	template<typename... Args>
	T *create(Args... args)
	{
		if (chunks.empty() || chunks.back()->size == CHUNK_SIZE)
		{
			chunks.push_back(new Chunk(CHUNK_SIZE));
		}

		chunks.back()->mem[chunks.back()->size] = T(args...);
		chunks.back()->size++;
		return &chunks.back()->mem[chunks.back()->size - 1];
	}
};