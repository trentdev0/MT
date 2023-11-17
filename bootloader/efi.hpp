#pragma once

#include <stdint.h>

namespace EFI
{
	typedef void * Handle;
	typedef uint64_t Status;
	typedef uint64_t UnsignedInteger;

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
	} MemoryType;

	typedef enum
	{
		EFI_ALLOCATE_ANY_PAGES,
		EFI_ALLOCATE_MAX_ADDRESS,
		EFI_ALLOCATE_ADDRESS,
		EFI_MAX_ALLOCATE_TYPE
	} AllocateType;

	typedef struct
	{
		uint32_t data1;
		uint16_t data2;
		uint16_t data3;
		uint8_t data4[8];
	} GUID;
	
	typedef struct
	{
		uint32_t type;
		uint64_t physical_start;
		uint64_t virtual_start;
		uint64_t pages;
		uint64_t attributes;
	} MemoryDescriptor;

	typedef struct
	{
		uint64_t Signature;
		uint32_t Revision;
		uint32_t HeaderSize;
		uint32_t CRC32;
		uint32_t Reserved;
	} TableHeader;

	typedef struct TextOutputStruct
	{
		void (*Unused0)();

		uint64_t (*OutputString)(struct TextOutputStruct *, uint16_t *);

		void (*Unused1)();
		void (*Unused2)();
		void (*Unused3)();
		void (*Unused4)();

		uint64_t (*ClearScreen)(struct TextOutputStruct *);

		void (*Unused5)();
		void (*Unused6)();
		void *Unused7;
	} TextOutput;

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
	} Time;

	typedef struct
	{
		TableHeader Header;

		void (*Unused0)();
		void (*Unused1)();

		uint64_t (*AllocatePages)(AllocateType, MemoryType, uint64_t, uint64_t *);
		uint64_t (*FreePages)(uint64_t, uint64_t);
		uint64_t (*GetMemoryMap)(uint64_t *, MemoryDescriptor *, uint64_t *, uint64_t *, uint32_t *);
		uint64_t (*AllocatePool)(MemoryType, uint64_t, void **);
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

		uint64_t (*ExitBootServices)(Handle, uint64_t);

		void (*Unused20)();
		void (*Unused21)();
		void (*Unused22)();

		void (*Unused23)();
		void (*Unused24)();

		uint64_t (*OpenProtocol)(Handle, GUID *, void **, Handle, Handle, uint32_t);
		uint64_t (*CloseProtocol)(Handle, GUID *, Handle, Handle);
		void (*Unused25)();

		uint64_t (*ProtocolsPerHandle)(Handle, GUID ***, uint64_t *);
		void (*unused26)();
		void (*unused27)();
		void (*unused28)();
		void (*unused29)();

		void (*Unused30)();

		void (*Unused31)();
		void (*Unused32)();
		void (*Unused33)();
	} BootTable;

	typedef struct
	{
		TableHeader Header;
		uint16_t *Unused0;
		uint32_t Unused1;
		void *Unused2;
		void *Unused3;
		void *Unused4;
		TextOutput *Output;
		void *Unused5;
		TextOutput *Error;
		void *Unused6;
		BootTable *Boot;
		uint64_t Unused7;
		void *Unused8;
	} SystemTable;
}