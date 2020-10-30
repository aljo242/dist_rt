#include "VMesh.h"
#include <cstdlib>
#include <cstdio>
#include <cmath>


VMesh::VMesh(const uint32_t numPEs, const uint32_t ID, const uint32_t dataSize)
	:
	ownerID(ID)
{
	meshDims.x = static_cast<uint32_t>(std::sqrt(numPEs));
	if (meshDims.x * meshDims.x == numPEs)
	{
		meshDims.y = meshDims.x;
	}
	else
	{
		meshDims.y = static_cast<uint32_t>(numPEs / meshDims.x);
	}

	if (ownerID == 0)
	{
		// printf("Creating 2D mesh (%d x %d) from %d PEs...\n", meshDims.x, meshDims.y, numPEs);
		// printf("Owning ID is: {%d}\n", ownerID);
	}

	dataDims.x = static_cast<uint32_t>(std::sqrt(dataSize));
	if (dataDims.x * dataDims.x == dataSize)
	{
		dataDims.y = dataDims.x;
	}
	else
	{
		dataDims.y = static_cast<uint32_t>(numPEs / dataDims.x);
	}

	if (ownerID == 0)
	{
		// printf("2D Matrix (%d x %d) from %d total size...\n", dataDims.x, dataDims.y, dataSize);
	}

	const uint32_t blockDim = dataDims.y / meshDims.x;
	localDims = { blockDim, blockDim };
	const uint32_t localSize = blockDim * blockDim;

	if (ownerID == 0)
	{
		printf("Local matrix slice of size %d is a (%d x %d) block\n", localSize, blockDim, blockDim);
	}

	virtualAddress.x = static_cast<uint32_t>(ownerID % meshDims.x);
	virtualAddress.y = static_cast<uint32_t>(ownerID / meshDims.x);
}


VMesh::VMesh(const uint32_t numPEs, const uint32_t ID, const uint32_t dataSize, const uint32_t rowSize, const uint32_t colSize)
	:
	ownerID(ID)
{
	meshDims.x = static_cast<uint32_t>(std::sqrt(numPEs));
	if (meshDims.x * meshDims.x == numPEs)
	{
		meshDims.y = meshDims.x;
	}
	else
	{
		meshDims.y = static_cast<uint32_t>(numPEs / meshDims.x);
	}

	if (ownerID == 0)
	{
		printf("Creating 2D mesh (%d x %d) from %d PEs...\n", meshDims.x, meshDims.y, numPEs);
		printf("Owning ID is: {%d}\n", ownerID);
	}

	dataDims.x = rowSize;
	if (dataDims.x * dataDims.x == dataSize)
	{
		dataDims.y = dataDims.x;
	}
	else
	{
		dataDims.y = colSize;
	}

	if (ownerID == 0)
	{
		// printf("2D Matrix (%d x %d) from %d total size...\n", dataDims.x, dataDims.y, dataSize);
	}

	localDims = { dataDims.x / meshDims.y, dataDims.y / meshDims.x };
	const uint32_t localSize = localDims.x * localDims.y;

	if (ownerID == 0)
	{
		printf("Local matrix slice of size %d is a (%d x %d) block\n", localSize, localDims.x, localDims.y);
	}

	virtualAddress.x = static_cast<uint32_t>(ownerID % meshDims.x);
	virtualAddress.y = static_cast<uint32_t>(ownerID / meshDims.x);
}

CartCoord VMesh::Up(const uint32_t n) const
{
	auto coord = virtualAddress;
	coord.y = (coord.y + n) % meshDims.y;
	return coord;
}

CartCoord VMesh::Down(const uint32_t n) const
{
	auto coord = virtualAddress;
	coord.y = (coord.y - n) % meshDims.y;
	// wrap around
	if (coord.y < 0)
	{
		coord.y += meshDims.y;
	}
	return coord;
}

CartCoord VMesh::Left(const uint32_t n) const
{
	auto coord = virtualAddress;
	coord.x = (coord.x - n) % meshDims.x;
	// wrap around
	if (coord.x < 0)
	{
		coord.x += meshDims.x;
	}
	return coord;
}

CartCoord VMesh::Right(const uint32_t n) const
{
	auto coord = virtualAddress;
	coord.x = (coord.x + n) % meshDims.x;
	return coord;
}

CartCoord toVirtual(const uint32_t addr, const VMesh& mesh)
{
	CartCoord coord;
	coord.x = static_cast<uint32_t>(addr % mesh.meshDims.x);
	coord.y = static_cast<uint32_t>(addr / mesh.meshDims.x);

	return coord;
}

uint32_t fromVirtual(const CartCoord coord, const VMesh& mesh)
{
	return coord.x + mesh.meshDims.x * coord.y;
}