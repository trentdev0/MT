#include "efi.hpp"

uint64_t Main(EFI::Handle Handle, EFI::SystemTable * SystemTable)
{
	uint16_t Message[] = {'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd', '!', '\0'};
	uint64_t Status;

	Status = SystemTable->Output->ClearScreen(SystemTable->Output);
	if(Status != 0)
		return Status;

	Status = SystemTable->Output->OutputString(SystemTable->Output, Message);
	if(Status != 0)
		return Status;

	return 0;
}