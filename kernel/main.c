void Main()
{
	asm("cli");
	while(1) { asm("hlt"); }
}