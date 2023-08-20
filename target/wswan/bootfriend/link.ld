OUTPUT_FORMAT("elf32-i386")
ENTRY(_start)
FORCE_COMMON_ALLOCATION
FORCE_GROUP_ALLOCATION
SECTIONS
{
	.text : {
		KEEP(*(".start"))
		*(.text ".text.*")
		*(".fartext.*")
		*(".farrodata.*")
	}

	.data : {
		. = ALIGN (2);
		*(.rodata ".rodata.*")
		*(.data ".data.*")
	}

	.bss . (NOLOAD) : {
		. = ALIGN (2);
		*(.bss ".bss.*")
	}
}
