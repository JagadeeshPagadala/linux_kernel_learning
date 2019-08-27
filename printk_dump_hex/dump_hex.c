#include <linux/module.h>

MODULE_DESCRIPTION("Linux kernel module to demonstrate hex_dump usage!");
MODULE_AUTHOR("jagdsh.linux@gmail.com");
MODULE_LICENSE("GPL");

static int __init  null_init(void)
{
	char mybuf[] = "abcdef";

	/*
 	*[ 2498.180923] HEX DUMP: ffff9ffc15597d21: 61 62 63 64 65 66 00                             abcdef.
	*/
	print_hex_dump(KERN_INFO, "HEX DUMP: ", DUMP_PREFIX_ADDRESS, 16, 1, mybuf, ARRAY_SIZE(mybuf),true);

	/*
	*[ 2498.180930] HEX DUMP: 61 62 63 64 65 66 00                             abcdef.
	*/
	print_hex_dump(KERN_INFO, "HEX DUMP: ", DUMP_PREFIX_NONE, 16, 1, mybuf, ARRAY_SIZE(mybuf),true);

	/*
	*[ 2498.180933] HEX DUMP: 00000000: 61 62 63 64 65 66 00                             abcdef.
 	*/ 	
	print_hex_dump(KERN_INFO, "HEX DUMP: ", DUMP_PREFIX_OFFSET, 16, 1, mybuf, ARRAY_SIZE(mybuf),true);


	return 0;
}

static void __exit null_exit(void)
{
	return;
}
module_init(null_init);
module_exit(null_exit);

