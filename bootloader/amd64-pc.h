#pragma once

/* Halt the CPU. */
static inline void hlt()
{
	asm("hlt");
}

/* Disable interrupts. */
static inline void cli()
{
	asm("cli");
}

/* Enable interrupts. */
static inline void sti()
{
	asm("sti");
}