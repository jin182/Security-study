#include<Windows.h>

char shellcode[] =  "\x6A\x03\xC7\x44\x24\x04\x63\x61\x6C\x63\x33\xC0\x88\x44\x24\x08\x8D\x44\x24\x04\x50\xB8\x91\x2C\x49\x77\xFF\xD0";

void main(void)
{
	int *shell = (int*)shellcode;
	__asm {
		jmp shell
	}
}
//ASM문법
// PUSH 3
// MOV dword ptr[esp + 4h], 0x636c6163
// // MOV byte ptr[esp + 8h], 0x0
// XOR eax, eax
// MOV byte ptr[esp + 8h], al
// LEA eax, [esp + 4h]
// push eax
// MOV eax, 0x75342C91
// CALL eax