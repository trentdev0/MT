#pragma once

#include <stdint.h>

typedef void *EFI_Handle;
typedef uint64_t EFI_Status;
typedef uint64_t EFI_UnsignedInteger;

static const uint64_t MAX_BIT = 0x8000000000000000ULL;

#define ERROR_CODE(status) (MAX_BIT | (status))

static const EFI_Status EFI_SUCCESS = 0;
static const EFI_Status EFI_LOAD_ERROR = ERROR_CODE(1);
static const EFI_Status EFI_INVALID_PARAMETER = ERROR_CODE(2);
static const EFI_Status EFI_UNSUPPORTED = ERROR_CODE(3);
static const EFI_Status EFI_BUFFER_TOO_SMALL = ERROR_CODE(5);

#define EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID {0x0964e5b22, 0x6459, 0x11d2, {0x8e, 0x39, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b}}
#define EFI_LOADED_IMAGE_PROTOCOL_GUID {0x5b1b31a1, 0x9562, 0x11d2, {0x8e, 0x3f, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b}}
#define EFI_OPEN_PROTOCOL_BY_HANDLE_PROTOCOL 0x00000001

typedef enum
{
	EFI_RESERVED_MEMORY_TYPE,
	EFI_LOADER_CODE,
	EFI_LOADER_DATA,
	EFI_BOOT_SERVICES_CODE,
	EFI_BOOT_SERVICES_DATA,
	EFI_RUNTIME_SERVICES_CODE,
	EFI_RUNTIME_SERVICES_DATA,
	EFI_CONVENTIAL_MEMORY,
	EFI_UNUSABLE_MEMORY,
	EFI_ACPI_RECLAIM_MEMORY,
	EFI_ACPI_MEMORY_NVS,
	EFI_MEMORY_MAPPED_IO,
	EFI_MEMORY_MAPPED_IO_PORT_SPACE,
	EFI_PAL_CODE,
	EFI_PERSISTENT_MEMORY,
	EFI_MAX_MEMORY_TYPE
} EFI_MemoryType;

typedef enum
{
	EFI_ALLOCATE_ANY_PAGES,
	EFI_ALLOCATE_MAX_ADDRESS,
	EFI_ALLOCATE_ADDRESS,
	EFI_MAX_ALLOCATE_TYPE
} EFI_AllocateType;

typedef struct
{
	uint32_t Data0;
	uint16_t Data1;
	uint16_t Data2;
	uint8_t Data3[8];
} EFI_GUID;

typedef struct
{
	uint32_t Type;
	uint64_t PhysicalStart;
	uint64_t VirtualStart;
	uint64_t Pages;
	uint64_t Attributes;
} EFI_MemoryDescriptor;

typedef struct
{
	uint8_t Type;
	uint8_t Subtype;
	uint16_t Length;
} EFI_DevicePathProtocol;

typedef struct
{
	uint16_t Year;
	uint8_t Month;
	uint8_t Day;
	uint8_t Hour;
	uint8_t Minute;
	uint8_t Second;
	uint8_t Unused0;
	uint32_t Nanosecond;
	int16_t TimeZone;
	uint8_t Daylight;
	uint8_t Unused1;
} EFI_Time;

typedef struct
{
	uint64_t Signature;
	uint32_t Revision;
	uint32_t HeaderSize;
	uint32_t CRC32;
	uint32_t Reserved;
} EFI_TableHeader;

typedef struct _EFI_TextOutputStruct
{
	void (*Unused0)();

	uint64_t (*OutputString)(struct _EFI_TextOutputStruct *, uint16_t *);

	void (*Unused1)();
	void (*Unused2)();
	void (*Unused3)();
	void (*Unused4)();

	uint64_t (*ClearScreen)(struct _EFI_TextOutputStruct *);

	void (*Unused5)();
	void (*Unused6)();
	void *Unused7;
} EFI_TextOutput;

typedef enum
{
	EFI_FILE_MODE_READ = 0x0000000000000001,
	EFI_FILE_MODE_WRITE = 0x0000000000000002,
	EFI_FILE_MODE_CREATE = 0x8000000000000000
} EFI_FileOpenMode;

typedef enum
{
	EFI_FILE_READ_ONLY = 0x1,
	EFI_FILE_HIDDEN = 0x2,
	EFI_FILE_SYSTEM = 0x4,
	EFI_FILE_RESERVED = 0x8,
	EFI_FILE_DIRECTORY = 0x10,
	EFI_FILE_ARCHIVE = 0x20
} EFI_FileAttribute;

typedef struct
{
	uint64_t Size;
	uint64_t FileSize;
	uint64_t PhysicalSize;
	EFI_Time CreateTime;
	EFI_Time LastAccessTime;
	EFI_Time ModificationTime;
	uint64_t Attribute;
	uint16_t Filename[256];
} EFI_FileInformation;

typedef struct _EFI_FileProtocol
{
	uint64_t Revision;
	EFI_Status (*Open)(struct _EFI_FileProtocol *, struct _EFI_FileProtocol **, uint16_t *, uint64_t, uint64_t);
	EFI_Status (*Close)(struct _EFI_FileProtocol *);

	void (*Unused0)();

	EFI_Status (*Read)(struct _EFI_FileProtocol *, uint64_t *, void *);

	void (*Unused1)();

	uint64_t (*GetPosition)(struct _EFI_FileProtocol *, uint64_t *);
	uint64_t (*SetPosition)(struct _EFI_FileProtocol *, uint64_t);

	uint64_t (*GetInfo)(struct _EFI_FileProtocol *, EFI_GUID *, uint64_t *, void *);

	void (*Unused2)();
	void (*Unused3)();
	void (*Unused4)();
	void (*Unused5)();
	void (*Unused6)();
	void (*Unused7)();
} EFI_FileProtocol;

typedef struct
{
	EFI_TableHeader Header;

	void (*Unused0)();
	void (*Unused1)();

	uint64_t (*AllocatePages)(EFI_AllocateType, EFI_MemoryType, uint64_t, uint64_t *);
	uint64_t (*FreePages)(uint64_t, uint64_t);
	uint64_t (*GetMemoryMap)(uint64_t *, EFI_MemoryDescriptor *, uint64_t *, uint64_t *, uint32_t *);
	uint64_t (*AllocatePool)(EFI_MemoryType, uint64_t, void **);
	uint64_t (*FreePool)(void *);

	void (*Unused2)();
	void (*Unused3)();
	void (*Unused4)();
	void (*Unused5)();
	void (*Unused6)();
	void (*Unused7)();

	void (*Unused8)();
	void (*Unused9)();
	void (*Unused10)();
	void (*Unused11)();
	void *Reserved;
	void (*Unused12)();
	void (*Unused13)();
	void (*Unused14)();
	void (*Unused15)();

	void (*Unused16)();
	void (*Unused17)();
	void (*Unused18)();
	void (*Unused19)();

	uint64_t (*ExitBootServices)(EFI_Handle, uint64_t);

	void (*Unused20)();
	void (*Unused21)();
	void (*Unused22)();

	void (*Unused23)();
	void (*Unused24)();

	uint64_t (*OpenProtocol)(EFI_Handle, EFI_GUID *, void **, EFI_Handle, EFI_Handle, uint32_t);
	uint64_t (*CloseProtocol)(EFI_Handle, EFI_GUID *, EFI_Handle, EFI_Handle);
	void (*Unused25)();

	uint64_t (*ProtocolsPerHandle)(EFI_Handle, EFI_GUID ***, uint64_t *);
	void (*unused26)();
	void (*unused27)();
	void (*unused28)();
	void (*unused29)();

	void (*Unused30)();

	void (*Unused31)();
	void (*Unused32)();
	void (*Unused33)();
} EFI_BootTable;

typedef struct
{
	EFI_TableHeader Header;
	uint16_t *Unused0;
	uint32_t Unused1;
	void *Unused2;
	void *Unused3;
	void *Unused4;
	EFI_TextOutput *Output;
	void *Unused5;
	EFI_TextOutput *Error;
	void *Unused6;
	EFI_BootTable *Boot;
	uint64_t Unused7;
	void *Unused8;
} EFI_SystemTable;

typedef struct _EFI_SimpleFilesystemProtocol
{
	uint64_t Revision;
	EFI_Status (*OpenVolume)(struct _EFI_SimpleFilesystemProtocol *, EFI_FileProtocol **);
} EFI_SimpleFilesystemProtocol;

typedef struct
{
	uint32_t Revision;
	EFI_Handle Parent;
	EFI_SystemTable *system;

	EFI_Handle Device;
	EFI_DevicePathProtocol *FilePath;
	void *Reserved;

	uint32_t LoadOptionsSize;
	void *LoadOptions;

	void *ImageBase;
	uint64_t ImageSize;
	EFI_MemoryType ImageCodeType;
	EFI_MemoryType ImageDataType;
	void (*Unused)();
} EFI_LoadedImageProtocol;