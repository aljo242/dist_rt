#ifndef VIRTUAL_MESH_H 
#define VIRTUAL_MESH_H
#include <cstdint>

// only possible to use positive coordinate values for this application
struct CartCoord
{
	uint32_t x{ 0 };
	uint32_t y{ 0 };
};

using VMeshDims = CartCoord;

class VMesh;

CartCoord toVirtual(const uint32_t addr, const VMesh& mesh);
uint32_t fromVirtual(const CartCoord coord, const VMesh& mesh);

class VMesh
{
public:
	// constructor for perfect square mesh
	VMesh(const uint32_t numPEs, const uint32_t ID, const uint32_t dataSize);
	VMesh(const uint32_t numPEs, const uint32_t ID, const uint32_t dataSize, const uint32_t rowSize, const uint32_t colSize);


	CartCoord Up(const uint32_t n) const;
	CartCoord Down(const uint32_t n) const;
	CartCoord Left(const uint32_t n) const;
	CartCoord Right(const uint32_t n) const;

public:
	uint32_t ownerID{ 0 };
	VMeshDims meshDims;
	VMeshDims dataDims;
	VMeshDims localDims;
	CartCoord virtualAddress;
};

#endif // VIRTUAL_MESH_H