#pragma once

#include <stdint.h>
#include <stddef.h>

#include "efi.h"

EFI_Status GetImage(EFI_Handle Handle, EFI_SystemTable *System, EFI_LoadedImageProtocol **Image);
EFI_Status GetRootFilesystem(EFI_Handle Handle, EFI_SystemTable *System, EFI_Handle Device, EFI_SimpleFilesystemProtocol **RootFilesystem);
EFI_Status GetRootDirectory(EFI_SimpleFilesystemProtocol *RootFilesystem, EFI_FileProtocol **RootDirectory);