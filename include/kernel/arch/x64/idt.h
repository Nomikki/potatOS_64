#ifndef KERNEL_ARCH_X64_IDT_H
#define KERNEL_ARCH_X64_IDT_H

#include <stdint.h>

#define IDT_SIZE 256

#define IDT_PRESENT_FLAG 0x80
#define IDT_INTERRUPT_TYPE_FLAG 0x0E
#define IDT_SEGMENT_SELECTOR 0x08

#define PIC_MASTER_COMMAND 0x20
#define PIC_MASTER_DATA 0x21
#define PIC_SLAVE_COMMAND 0xA0
#define PIC_SLAVE_DATA  0xA1

#define KERNEL_CS 0x8

struct cpu_status
{
    uint64_t r15;
    uint64_t r14;
    uint64_t r13;
    uint64_t r12;
    uint64_t r11;
    uint64_t r10;
    uint64_t r9;
    uint64_t r8;
    uint64_t rdi;
    uint64_t rsi;
    uint64_t rbp;
    uint64_t rdx;
    uint64_t rcx;
    uint64_t rbx;
    uint64_t rax;

    uint64_t interrupt_number;
    uint64_t error_code;

    uint64_t rip;
    uint64_t cs;
    uint64_t rflags;
    uint64_t rsp;
    uint64_t ss;
} __attribute__((__packed__));

/*
    Flag field:
    Bits    Name        Description
    3:0     Type        In long mode there are two types of
                        descriptions we can put here: trap gates and
                        interrupt gates.
                        Interrupt gate will clear interrupt flag before
                        running the handler function, and a trap gate will not.
                        Interrupts can occur while inside of the handler function.
                        Interrupt:  0b1110
                        Trap:       0b1111
    4       Reserved    Set to zero
    6:5     DPL         The Descriptor Privilege Level determines
                        the highest cpu ring that can trigger this interrupt
                        via software. A default of zero is fine.
    7       Present     If zero, mmean this descriptor is not valid and
                        we dont support handling this vector.
                        Set this bit to tell the cpu we support this vector,
                        and that the handler addres is valid.

*/
typedef struct IDT_desc
{
    uint16_t offset_low;
    uint16_t segment_selector;
    uint8_t ist;   // only first 2 bits are used, the rest is 0
    uint8_t flags; // P(resent) DPL (0) TYPE
    uint16_t offset_mid;
    uint32_t offset_high;
    uint32_t reserved; // 0
} __attribute__((__packed__)) IDT_descriptor;

typedef struct IDT_reg
{
    uint16_t limit;
    uint64_t offset;
} __attribute__((__packed__)) IDT_register;

extern void interrupt_service_routine_0(); 
extern void interrupt_service_routine_1(); 
extern void interrupt_service_routine_2(); 
extern void interrupt_service_routine_3(); 
extern void interrupt_service_routine_4(); 
extern void interrupt_service_routine_5(); 
extern void interrupt_service_routine_6(); 
extern void interrupt_service_routine_7(); 
extern void interrupt_service_routine_err_8(); 
extern void interrupt_service_routine_9(); 
extern void interrupt_service_routine_err_10(); 
extern void interrupt_service_routine_err_11(); 
extern void interrupt_service_routine_err_12(); 
extern void interrupt_service_routine_err_13(); 
extern void interrupt_service_routine_err_14(); 
extern void interrupt_service_routine_15(); 
extern void interrupt_service_routine_16(); 
extern void interrupt_service_routine_err_17(); 
extern void interrupt_service_routine_18(); 
extern void interrupt_service_routine_32(); 
extern void interrupt_service_routine_33(); 
extern void interrupt_service_routine_34(); 
extern void interrupt_service_routine_255();

/*
void set_idt_entry(uint8_t vector, void *handler, uint8_t dpl);
void setup_idt();
*/

void init_idt();
void load_idt();
void set_idt_entry(uint16_t idx, uint8_t flags, uint16_t selector, uint8_t ist, void (*handler)());
extern struct cpu_status *interrupts_handler(struct cpu_status *);
void default_isr();

extern IDT_descriptor idt_table[IDT_SIZE];

#endif // KERNEL_ARCH_X64_IDT_H