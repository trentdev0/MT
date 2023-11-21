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