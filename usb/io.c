#include "usb.h"
#include <minix/syslib.h>
#include "io.h"

PUBLIC unsigned u_inb(U16_t port) {
	u32_t value;
	int s;
	if ((s=sys_inb(port, &value)) !=OK)
		printf("USB: warning, sys_inb failed: %d\n", s);
	return value;
}
PUBLIC unsigned u_inw(U16_t port) {
	u32_t value;
	int s;
	if ((s=sys_inw(port, &value)) !=OK)
		printf("USB: warning, sys_inw failed: %d\n", s);
	return value;
}
PUBLIC unsigned u_inl(U16_t port) {
	U32_t value;
	int s;
	if ((s=sys_inl(port, &value)) !=OK)
		printf("USB: warning, sys_inl failed: %d\n", s);
	return value;
}
PUBLIC void u_outb(U16_t port, U8_t value) {
	int s;
	if ((s=sys_outb(port, value)) !=OK)
		printf("USB: warning, sys_outb failed: %d\n", s);
}
PUBLIC void u_outw(U16_t port, U16_t value) {
	int s;
	if ((s=sys_outw(port, value)) !=OK)
		printf("USB: warning, sys_outw failed: %d\n", s);
}
PUBLIC void u_outl(U16_t port, U32_t value) {
	int s;
	if ((s=sys_outl(port, value)) !=OK)
		printf("USB: warning, sys_outl failed: %d\n", s);
}
