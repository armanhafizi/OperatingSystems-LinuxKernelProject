#include <asm/linkage.h>

notrace int __vdso_OS_project(void)
{
	int x;
	asm("mov $0x1, %eax\n\t");
	asm("cpuid\n\t");
	asm("mov %%eax, %0\n\t":"=r" (x));
	int model = (x >> 4)%16;
	int extendedModel = (x >> 16)%16;
	return model + (extendedModel << 4);
}

int OS_project(void)
    __attribute__((weak, alias("__vdso_OS_project")));
