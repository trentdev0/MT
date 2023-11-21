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

	EFI_FileInformation KernelFileInformation;

	EFI_GUID GUID = EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID;

	uint64_t Size = sizeof(KernelFileInformation);
	Status = KernelFile->GetInfo(KernelFile, &GUID, &Size, (void *)&KernelFileInformation);
	if(Status != 0)
	{
		SystemTable->Output->OutputString(SystemTable->Output, L"Failed to load kernel!\r\nCould not obtain file information regarding `ntoskrnl.exe`!\r\n");
		goto Hang;
	}

	for(uint64_t i = 0; i < KernelFileInformation.PhysicalSize; i++)
	{
		SystemTable->Output->OutputString(SystemTable->Output, L"a");
	}

Hang:
	/* Let's disable interrupts & halt the CPU. */
	cli();
	while(1) { hlt(); }

	return 0;
}