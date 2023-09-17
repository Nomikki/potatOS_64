#include <kernel/arch/x64/idt.h>
#include <klib/stdio.h>
#include <drivers/io/ports.h>

IDT_descriptor idt_table[IDT_SIZE];

void set_idt_entry(uint16_t idx, uint8_t flags, uint16_t selector, uint8_t ist, void (*handler)())
{
    idt_table[idx].flags = flags;
    idt_table[idx].ist = ist;
    idt_table[idx].segment_selector = selector;
    idt_table[idx].offset_low = (uint16_t)((uint64_t)handler & 0xFFFF);
    idt_table[idx].offset_mid = (uint16_t)((uint64_t)handler >> 16);
    idt_table[idx].offset_high = (uint32_t)((uint64_t)handler >> 32);
    idt_table[idx].reserved = 0x0;

    if (idx % 2 == 0)
        kprintf("\n");

    kprintf("idt: %i,%shandler: 0x%Z   ", idx, idx < 10 ? "  " : " ", handler);
}

void load_idt()
{
    IDT_register idtr;
    idtr.limit = IDT_SIZE * sizeof(IDT_descriptor) - 1;
    idtr.offset = (uint64_t)&idt_table;

    __asm__ __volatile__("lidt %0"
                         :
                         : "g"(idtr));
}

void setup_idt()
{
    __asm__ volatile("cli");
    kprintf("\n");

    int i = 0;
    while (i < IDT_SIZE)
    {
        idt_table[i].flags = 0;
        idt_table[i].ist = 0;
        idt_table[i].offset_high = 0;
        idt_table[i].offset_low = 0;
        idt_table[i].reserved = 0;
        idt_table[i].offset_mid = 0;
        idt_table[i].segment_selector = 0;
        i++;
    }
    set_idt_entry(0x00, IDT_PRESENT_FLAG | IDT_INTERRUPT_TYPE_FLAG, KERNEL_CS, 0, interrupt_service_routine_0);
    set_idt_entry(0x01, IDT_PRESENT_FLAG | IDT_INTERRUPT_TYPE_FLAG, KERNEL_CS, 0, interrupt_service_routine_1);
    set_idt_entry(0x02, IDT_PRESENT_FLAG | IDT_INTERRUPT_TYPE_FLAG, KERNEL_CS, 0, interrupt_service_routine_2);
    set_idt_entry(0x03, IDT_PRESENT_FLAG | IDT_INTERRUPT_TYPE_FLAG, KERNEL_CS, 0, interrupt_service_routine_3);
    set_idt_entry(0x04, IDT_PRESENT_FLAG | IDT_INTERRUPT_TYPE_FLAG, KERNEL_CS, 0, interrupt_service_routine_4);
    set_idt_entry(0x05, IDT_PRESENT_FLAG | IDT_INTERRUPT_TYPE_FLAG, KERNEL_CS, 0, interrupt_service_routine_5);
    set_idt_entry(0x06, IDT_PRESENT_FLAG | IDT_INTERRUPT_TYPE_FLAG, KERNEL_CS, 0, interrupt_service_routine_6);
    set_idt_entry(0x07, IDT_PRESENT_FLAG | IDT_INTERRUPT_TYPE_FLAG, KERNEL_CS, 0, interrupt_service_routine_7);
    set_idt_entry(0x08, IDT_PRESENT_FLAG | IDT_INTERRUPT_TYPE_FLAG, KERNEL_CS, 0, interrupt_service_routine_err_8);
    set_idt_entry(0x09, IDT_PRESENT_FLAG | IDT_INTERRUPT_TYPE_FLAG, KERNEL_CS, 0, interrupt_service_routine_9);
    set_idt_entry(0x0A, IDT_PRESENT_FLAG | IDT_INTERRUPT_TYPE_FLAG, KERNEL_CS, 0, interrupt_service_routine_err_10);
    set_idt_entry(0x0B, IDT_PRESENT_FLAG | IDT_INTERRUPT_TYPE_FLAG, KERNEL_CS, 0, interrupt_service_routine_err_11);
    set_idt_entry(0x0C, IDT_PRESENT_FLAG | IDT_INTERRUPT_TYPE_FLAG, KERNEL_CS, 0, interrupt_service_routine_err_12);
    set_idt_entry(0x0D, IDT_PRESENT_FLAG | IDT_INTERRUPT_TYPE_FLAG, KERNEL_CS, 0, interrupt_service_routine_err_13);
    set_idt_entry(0x0E, IDT_PRESENT_FLAG | IDT_INTERRUPT_TYPE_FLAG, KERNEL_CS, 0, interrupt_service_routine_err_14);
    set_idt_entry(0x0F, IDT_PRESENT_FLAG | IDT_INTERRUPT_TYPE_FLAG, KERNEL_CS, 0, interrupt_service_routine_15);
    set_idt_entry(0x10, IDT_PRESENT_FLAG | IDT_INTERRUPT_TYPE_FLAG, KERNEL_CS, 0, interrupt_service_routine_16);
    set_idt_entry(0x11, IDT_PRESENT_FLAG | IDT_INTERRUPT_TYPE_FLAG, KERNEL_CS, 0, interrupt_service_routine_err_17);
    set_idt_entry(0x12, IDT_PRESENT_FLAG | IDT_INTERRUPT_TYPE_FLAG, KERNEL_CS, 0, interrupt_service_routine_18);
    set_idt_entry(0x20, IDT_PRESENT_FLAG | IDT_INTERRUPT_TYPE_FLAG, KERNEL_CS, 0, interrupt_service_routine_32);
    set_idt_entry(0x21, IDT_PRESENT_FLAG | IDT_INTERRUPT_TYPE_FLAG, KERNEL_CS, 0, interrupt_service_routine_33);
    set_idt_entry(0x22, IDT_PRESENT_FLAG | IDT_INTERRUPT_TYPE_FLAG, KERNEL_CS, 0, interrupt_service_routine_34);
    set_idt_entry(0xFF, IDT_PRESENT_FLAG | IDT_INTERRUPT_TYPE_FLAG, KERNEL_CS, 0, interrupt_service_routine_255);

    int picMasterCommand = 0x20;
    int picMasterData = 0x21;
    int picSlaveCommand = 0xA0;
    int picSlaveData = 0xA1;

    outportb(picMasterCommand, 0x11);
    outportb(picSlaveCommand, 0x11);

    outportb(picMasterData, 0x20);
    outportb(picSlaveData, 0x28);

    outportb(picMasterData, 0x04);
    outportb(picSlaveData, 0x02);

    outportb(picMasterData, 0x1);
    outportb(picSlaveData, 0x01);

    outportb(picMasterData, 0x00);
    outportb(picSlaveData, 0x00);

    load_idt();

    __asm__ volatile("sti");
}

struct cpu_status *interrupt_dispatch(struct cpu_status *context)
{
    uint64_t interrupt_number = context->interrupt_number;

    if (interrupt_number < 0x20)
    {

        switch (interrupt_number)
        {
        case 8:
            kprintf("Double fault.");
            break;
        case 13:
            kprintf("General protection fault.");
            kprintf("\n");

            break;
        case 14:
            kprintf("Page fault.");
            kprintf("\n");

            uint64_t cr2_content = 0;
            asm("mov %%cr2, %0"
                : "=r"(cr2_content));
            kprintf("Faulting address: %Z\n", cr2_content);

        default:
            break;
        }

        kprintf("\n");
        kprintf("Interrupt vector: %Z\n", interrupt_number);

        kprintf("r15:  %Z  ", context->r15);
        kprintf("r14:  %Z\n", context->r14);
        kprintf("r13:  %Z  ", context->r13);
        kprintf("r12:  %Z\n", context->r12);
        kprintf("r11:  %Z  ", context->r11);
        kprintf("r10:  %Z\n", context->r10);
        kprintf("r9:   %Z  ", context->r9);
        kprintf("r8:   %Z\n", context->r8);
        kprintf("rdi:  %Z  ", context->rdi);
        kprintf("rsi:  %Z\n", context->rsi);
        kprintf("rbp:  %Z  ", context->rbp);
        kprintf("rdx:  %Z\n", context->rdx);
        kprintf("rcx:  %Z  ", context->rcx);
        kprintf("rbx:  %Z\n", context->rbx);
        kprintf("rax:  %Z\n", context->rax);

        kprintf("\n");

        kprintf("err: %Z\n", context->error_code);
        kprintf("rip: %Z\n", context->rip);
        kprintf("cs:  %Z\n", context->cs);
        kprintf("rfl: %Z\n", context->rflags);
        kprintf("rsp: %Z\n", context->rsp);
        kprintf("ss:  %Z\n", context->ss);
    }

    if (interrupt_number >= 0x20 && interrupt_number < 0x20 + 16)
    {
        int picMasterCommand = 0x20;
        int picSlaveCommand = 0xA0;

        outportb(picMasterCommand, 0x20);

        if (0x20 + 8 <= interrupt_number)
        {
            outportb(picSlaveCommand, 0x20);
        }
        //return context;

        if (interrupt_number == 0x21)
        {
            uint8_t scancode = inportb(0x60);
            kprintf("%c", scancode);
        }
    }

    /*
    while (1)
    {
        asm("hlt");
    }
    */

    outportb(0x20, 0x20);
    outportb(0xA0, 0x20);

    return context;
}