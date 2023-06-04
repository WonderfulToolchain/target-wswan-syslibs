OUTPUT_FORMAT("elf32-i386")
ENTRY(_start)
SECTIONS {
	. = SEGMENT_START ("text-segment", 0x6800);

	.text : {
		__stext = .;
		KEEP(*(".start"))
		*(.text ".text.*")
		*(".fartext.*")
		*(".farrodata.*")
		__etext = .;
	}

	.data : {
		. = ALIGN (2);
		__sdata = .;
		*(.rodata ".rodata.*")
		*(.data ".data.*")
		. = ALIGN (2);
		__edata = .;
	}
	"__ldata!" = 0;
	__ldata = SIZEOF(.data);
	"__lwdata!" = 0;
	__lwdata = (__ldata + 1) / 2;

	.bss . (NOLOAD) :
	{
		*(.bss ".bss.*")
		. = ALIGN (2);
		__ebss = .;
	}
	"__lbss!" = 0;
	__lbss = SIZEOF(.bss);
	"__lwbss!" = 0;
	__lwbss = (__lbss + 1) / 2;
}
