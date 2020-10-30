#ifndef TRANSFER_H 
#define TRANSFER_H

class VMesh;

namespace transfer
{
	void copyToLocalBuffer(double* global, double* local, const VMesh& mesh);
	void copyToGlobalBuffer(double* global, double* local, const VMesh& mesh);
}

#endif // TRANSFER_H