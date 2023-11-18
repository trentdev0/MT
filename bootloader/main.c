#include "efi.h"

uint64_t Main(EFI_Handle Handle, EFI_SystemTable * SystemTable)
{
	SystemTable->Output->ClearScreen(SystemTable->Output);

	return 0;
}