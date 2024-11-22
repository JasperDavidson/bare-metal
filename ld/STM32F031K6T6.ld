/* Label the program's entry point */
ENTRY(reset_handler)

/* End of RAM / Start of stack */
_estack = 0x20001000;

/* Set minimum size for stackand other dynamic memory */
_Min_Leftover_RAM = 0x400;

MEMORY 
{
    FLASH ( rx )    : ORIGIN = 0x08000000, LENGTH = 32K
    RAM   ( rxw )   : ORIGIN = 0x20000000, LENGTH = 4K
}

SECTIONS
{
    /* The vector table goes at the start of flash. */
    .vector_table :
    {
        . = ALIGN(4);
        KEEP (*(.vector_table))
        . = ALIGN(4);
    } >FLASH

    /* Contains the main program code */
    .text :
    {
        . = ALIGN(4);
        *(.text)
        *(.text*)
        . = ALIGN(4);
    } >FLASH

    /* Contains read-only data like constants */
    .rodata :
    {
        . = ALIGN(4);
        *(.rodata)
        *(.rodata*)
        . = ALIGN(4);
    } >FLASH

    /* Data set aside in RAM for memory that can change, like variables */
    _sidata = .;
    .data : AT(_sidata)
    {
        . = ALIGN(4);
        _sdata = .;
        *(.data)
        *(.data*)
        _edata = .;
        . = ALIGN(4);
    } >RAM

    /* Initialized to zero upon startup */
    .bss :
    {
        . = ALIGN(4);
        _sbss = .;
        *(.bss)
        *(.bss*)
        *(COMMON)
        _ebss = .;
        . = ALIGN(4);
    } >RAM

    /* Space set aside for the stack/heap */
    .dynamic_allocations :
    {
        . = ALIGN(4);
        _ssystem_ram = .;
        . = . + _Min_Leftover_RAM;
        . = ALIGN(4);
        _esystem_ram = .;
    } >RAM
}