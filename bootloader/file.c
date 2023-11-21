#include <stdint.h>
#include <stddef.h>

#include "efi.h"

EFI_Status GetImage(EFI_Handle Handle, EFI_SystemTable *System, EFI_LoadedImageProtocol **Image)
{
	EFI_GUID GUID = EFI_LOADED_IMAGE_PROTOCOL_GUID;

	return System->Boot->OpenProtocol(Handle, &GUID, (void **)Image, Handle, NULL, EFI_OPEN_PROTOCOL_BY_HANDLE_PROTOCOL);
}

EFI_Status GetRootFilesystem(EFI_Handle Handle, EFI_SystemTable *System, EFI_Handle Device, EFI_SimpleFilesystemProtocol **RootFilesystem)
{
	EFI_GUID GUID = EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID;

	return System->Boot->OpenProtocol(Device, &GUID, (void **)RootFilesystem, Handle, NULL, EFI_OPEN_PROTOCOL_BY_HANDLE_PROTOCOL);
}

EFI_Status GetRootDirectory(EFI_SimpleFilesystemProtocol *RootFilesystem, EFI_FileProtocol **RootDirectory)
{
	return RootFilesystem->OpenVolume(RootFilesystem, RootDirectory);
}


EFI_Status ReadFixed(EFI_SystemTable *System, EFI_FileProtocol *File, uint64_t Offset, size_t Size, void *Destination)
{
	EFI_Status Status = EFI_SUCCESS;
	unsigned char *Buffer = Destination;
	size_t Read = 0;

	Status = File->SetPosition(File, Offset);
	if(Status != EFI_SUCCESS)
	{
		return Status;
	}

	while(Read < Size)
	{
		uint64_t Remains = Size - Read;

		Status = File->Read(File, &Remains, (void *)(Buffer + Read));
		if(Status != EFI_SUCCESS)
		{
			return Status;
		}

		Read += Remains;
	}

	return Status;
}