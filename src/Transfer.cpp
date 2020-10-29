#include "Transfer.h"
#include "VMesh.h"

namespace transfer
{
	void copyToLocalBuffer(double* global, double* local, const VMesh& mesh)
	{
		// get mesh dims
		// translate to global indices
		// perform copies to local array from global using generated indices
		VMeshDims startIndices{ 0, 0 };
		VMeshDims endIndices{ 0, 0 };

		auto addr = mesh.virtualAddress;
		auto block = mesh.localDims;
		auto data = mesh.dataDims;

		startIndices = { addr.x * block.x, addr.y * block.y };
		endIndices = { (addr.x + 1) * block.x, (addr.y + 1) * block.y };

		//printf("Virtual Address: [%d, %d]\nStart Indices: [%d, %d]\nEnd Indices: [%d, %d]\n",
		//    addr.x, addr.y, startIndices.x, startIndices.y, 
		//    endIndices.x, endIndices.y);

		// printf("\n");
		int localIndex = 0;
		for (int j = startIndices.y; j < endIndices.y; ++j)
		{
			for (int i = startIndices.x; i < endIndices.x; ++i)
			{
				const int globalIndex = i + data.x * j;
				//printf("local index: %d, [%d][%d], global index: %d\t\t\n", localIndex, i, j, globalIndex);
				local[localIndex] = global[globalIndex];
				++localIndex;
			}
			// printf("\n");
		}
		// printf("\n");

		const int disp = 1;
		auto up = mesh.Up(disp);
		auto down{ mesh.Down(disp) };
		auto left{ mesh.Left(disp) };
		auto right{ mesh.Right(disp) };

		//printf("{%d}\n\tUp: [%d, %d]\n\tDown: [%d, %d]\n\tLeft: [%d, %d]\n\tRight: [%d, %d]\n",
		//    mesh.ownerID, up.x, up.y, down.x, down.y, left.x, left.y, right.x, right.y);    
		//printf("owner ID: {%d}\n", mesh.ownerID);
		//printMat(local, block.x, block.y);
	}

	void copyToGlobalBuffer(double* global, double* local, const VMesh& mesh)
	{

	}
}