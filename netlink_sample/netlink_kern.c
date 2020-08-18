#include <linux/module.h>
#include <net/sock.h>
#include <linux/netlink.h>
#include <linux/skbuff.h>
  

#ifndef NETLINK_USER
#define NETLINK_USER 24 /* MAX NETLINK  defs are 32.... Refer include/uapi/linux/netlink.h*/
#endif

struct sock *nl_sk = NULL;
static int pid = 0;

static void hello_nl_recv_msg(struct sk_buff *skb)
{

	struct nlmsghdr *nlh;
	struct sk_buff *skb_out;
	int msg_size;
	char *msg="Hello from kernel";
	int res;

	printk(KERN_INFO "Entering: %s:[%d] \n", __FUNCTION__, __LINE__);

	msg_size=strlen(msg);

	nlh=(struct nlmsghdr*)skb->data;
	printk(KERN_INFO "Netlink received msg payload:%s  %s:[%d]\n",(char*)nlmsg_data(nlh), __FUNCTION__, __LINE__);
	pid = nlh->nlmsg_pid; /*pid of sending process */

	skb_out = nlmsg_new(msg_size,0);
	if(!skb_out)
	{

	    printk(KERN_ERR "Failed to allocate new skb %s:[%d]\n", __FUNCTION__, __LINE__);
	    return;

	} 
	nlh=nlmsg_put(skb_out,0,0,NLMSG_DONE,msg_size,0);  
	NETLINK_CB(skb_out).dst_group = 0; /* not in mcast group */
	strncpy(nlmsg_data(nlh),msg,msg_size);

	res=nlmsg_unicast(nl_sk,skb_out,pid);

	if(res<0)
	    printk(KERN_INFO "Error while sending bak to user %s:[%d]\n", __FUNCTION__, __LINE__);
}

static int __init hello_init(void)
{

	printk("Entering: %s:[%d] \n",__FUNCTION__, __LINE__);
	//This is for 3.6 kernels and above.
	struct netlink_kernel_cfg cfg = {
	    .input = hello_nl_recv_msg,
	};

	nl_sk = netlink_kernel_create(&init_net, NETLINK_USER, &cfg);
	if(!nl_sk)
	{

	    printk(KERN_ALERT "Error creating socket. %s:[%d]\n", __FUNCTION__, __LINE__);
	    return -10;

	}

	printk(KERN_INFO " before sleep\n");
	mdelay(5000);	
	printk(KERN_INFO " after sleep\n");
	

	return 0;
}

static void __exit hello_exit(void) {

	printk(KERN_INFO "exiting hello module. %s:[%d]\n", __FUNCTION__, __LINE__);
	netlink_kernel_release(nl_sk);
}

module_init(hello_init); module_exit(hello_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("jagdsh.linux@gmail.com");
