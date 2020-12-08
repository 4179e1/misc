#ifndef UHCI_IO_H
#define UHCI_IO_H

_PROTOTYPE( unsigned u_inb, (U16_t port) );
_PROTOTYPE( unsigned u_inw, (U16_t port) );
_PROTOTYPE( unsigned u_inl, (U16_t port) );

_PROTOTYPE( void u_outb, (U16_t port, U8_t value) );
_PROTOTYPE( void u_outw, (U16_t port, U16_t value) );
_PROTOTYPE( void u_outl, (U16_t port, U32_t value) );
#endif /* _IO_H */
