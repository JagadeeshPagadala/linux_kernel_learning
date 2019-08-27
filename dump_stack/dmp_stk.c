#include <linux/module.h>

MODULE_DESCRIPTION("Module to understand the flow of insmod/rmmod");
MODULE_AUTHOR("Jagadeesh Pagadala <jagdsh.linux@gmail.com>");
MODULE_LICENSE("GPL");
/* init module*/
static int __init  dmp_stk_init(void)
{
	printk("Entering....into\n");
	/*
	[103372.733701] CPU: 3 PID: 106694 Comm: insmod Kdump: loaded Tainted: G           OE  ------------   3.10.0-957.27.2.el7.x86_64 #1
	[103372.733703] Hardware name: VMware, Inc. VMware Virtual Platform/440BX Desktop Reference Platform, BIOS 6.00 07/02/2015
	[103372.733704] Call Trace:
	[103372.733750]  [<ffffffff9c964147>] dump_stack+0x19/0x1b
	[103372.733755]  [<ffffffffc0767017>] dmp_stk_init+0x17/0x1000 [dmp_stk]
	[103372.733758]  [<ffffffff9c20210a>] do_one_initcall+0xba/0x240
	[103372.733762]  [<ffffffff9c31a3bc>] load_module+0x272c/0x2bc0
	[103372.733765]  [<ffffffff9c5a4f60>] ? ddebug_proc_write+0x100/0x100
	[103372.733769]  [<ffffffff9c315f43>] ? copy_module_from_fd.isra.44+0x53/0x150
	[103372.733772]  [<ffffffff9c31aa36>] SyS_finit_module+0xa6/0xd0
	[103372.733776]  [<ffffffff9c976ddb>] system_call_fastpath+0x22/0x27
	*/
	dump_stack();

	return 0;
}

/* exit moodule*/
static void __exit dmp_stk_exit(void)
{
	printk("Exiting from\n");
	/*
	[103380.583101] Exiting from
	[103380.583107] CPU: 0 PID: 106960 Comm: rmmod Kdump: loaded Tainted: G           OE  ------------   3.10.0-957.27.2.el7.x86_64 #1
	[103380.583109] Hardware name: VMware, Inc. VMware Virtual Platform/440BX Desktop Reference Platform, BIOS 6.00 07/02/2015
	[103380.583111] Call Trace:
	[103380.583120]  [<ffffffff9c964147>] dump_stack+0x19/0x1b
	[103380.583125]  [<ffffffffc0780017>] dmp_stk_exit+0x17/0x1000 [dmp_stk]
	[103380.583129]  [<ffffffff9c317a0e>] SyS_delete_module+0x19e/0x310
	[103380.583134]  [<ffffffff9c976ddb>] system_call_fastpath+0x22/0x27
	*/
	dump_stack();

	return;
}
module_init(dmp_stk_init);
module_exit(dmp_stk_exit);

