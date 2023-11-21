#include "efi.h"
#include "amd64-pc.h"
#include "pe.h"
#include "file.h"

uint64_t Main(EFI_Handle Handle, EFI_SystemTable * SystemTable)
{
	SystemTable->Output->ClearScreen(SystemTable->Output);
	SystemTable->Output->OutputString(SystemTable->Output, L"Hello, world!\r\n");

	/* Set up the filesystem basics. */

	EFI_SimpleFilesystemProtocol *RootFilesystem;
	EFI_FileProtocol *RootDirectory;

	EFI_LoadedImageProtocol *LoadedImageProtocol;
	uint16_t Status = GetImage(Handle, SystemTable, &LoadedImageProtocol);
	if(Status != 0)
	{
		SystemTable->Output->OutputString(SystemTable->Output, L"Failed to set up filesystem!\r\nCould not get image!\r\n");
		goto Hang;
	}

	Status = GetRootFilesystem(Handle, SystemTable, LoadedImageProtocol->Device, &RootFilesystem);
	if(Status != 0)
	{
		SystemTable->Output->OutputString(SystemTable->Output, L"Failed to set up filesystem!\r\nCould not get root filesystem!\r\n");
		goto Hang;
	}

	Status = GetRootDirectory(RootFilesystem, &RootDirectory);
	if(Status != 0)
	{
		SystemTable->Output->OutputString(SystemTable->Output, L"Failed to set up filesystem!\r\nCould not get root directory!\r\n");
		goto Hang;
	}

	/* Let's load up the kernel! */

	EFI_FileProtocol *KernelFile;

	Status = RootDirectory->Open(RootDirectory, &KernelFile, L"efi\\boot\\ntoskrnl.exe", EFI_FILE_MODE_READ, EFI_FILE_READ_ONLY);
	if(Status != 0)
	{
		SystemTable->Output->OutputString(SystemTable->Output, L"Failed to load kernel!\r\nCould not open `ntoskrnl.exe`!\r\n");
		goto Hang;
	}

	DOSHeader _DOSHeader;

	Status = ReadFixed(SystemTable, KernelFile, 0, sizeof(DOSHeader), &_DOSHeader);
	if(Status != 0)
	{
		SystemTable->Output->OutputString(SystemTable->Output, L"Failed to load kernel!\r\nCould not read DOS header from `ntoskrnl.exe`!\r\n");
		goto Hang;
	}

	PEHeader _PEHeader;

	Status = ReadFixed(SystemTable, KernelFile, _DOSHeader.e_lfanew, sizeof(PEHeader), &_PEHeader);
	if(Status != 0)
	{
		SystemTable->Output->OutputString(SystemTable->Output, L"Failed to load kernel!\r\nCould not read PE header from `ntoskrnl.exe`!\r\n");
		goto Hang;
	}

	if(_DOSHeader.e_magic != 0x5A4D)
	{
		SystemTable->Output->OutputString(SystemTable->Output, L"Failed to load kernel!\r\nKernel does not contain a valid DOS header!\r\n");
		goto Hang;
	}

	if(_PEHeader.mMachine != 0x8664)
	{
		SystemTable->Output->OutputString(SystemTable->Output, L"Failed to load kernel!\r\nKernel does not contain a valid PE header!\r\n");
		goto Hang;
	}

Hang:
	/* Let's disable interrupts & halt the CPU. */
	cli();
	while(1) { hlt(); }

	return 0;
}