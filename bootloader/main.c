#include "efi.h"

uint64_t Main(EFI_Handle Handle, EFI_SystemTable * SystemTable)
{
	uint16_t Message[] = L"f,mdlgjdsf/gdfGDFGdFGDFG";
	uint64_t Status;

	Status = SystemTable->Output->ClearScreen(SystemTable->Output);
	if(Status != 0)
		return Status;

	Status = SystemTable->Output->OutputString(SystemTable->Output, Message);
	if(Status != 0)
		return Status;

	return 0;
}