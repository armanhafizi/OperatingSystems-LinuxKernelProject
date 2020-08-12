/*****************************************************
 * This code was compiled and tested on Ubuntu 18.04.1
 * with kernel version 4.15.0
 *****************************************************/

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>
#include <linux/ip.h>
#include <linux/tcp.h>
#include <linux/udp.h>

MODULE_LICENSE("GPL");

static struct nf_hook_ops *nfho = NULL;

static unsigned int hfunc(void *priv, struct sk_buff *skb, const struct nf_hook_state *state)
{
    struct iphdr *iph;
    struct udphdr *udph;
    if (!skb)
        return NF_ACCEPT;

    iph = ip_hdr(skb);
    unsigned int src_ip = (unsigned int)iph->saddr;
    unsigned int dest_ip = (unsigned int)iph->daddr;
    if(src_ip==2091392849){
        printk(KERN_INFO "DROP: IP addres = %pI4  DEST = %pI4\n", &src_ip, &dest_ip);
        return NF_DROP;
    }
    else{
        printk(KERN_INFO "ACCEPT: IP addres = %pI4  DEST = %pI4\n", &src_ip, &dest_ip);
        return NF_ACCEPT;
    }

}

static int __init part1_step3_init(void)
{
    nfho = (struct nf_hook_ops*)kcalloc(1, sizeof(struct nf_hook_ops), GFP_KERNEL);
    
    /* Initialize netfilter hook */
    nfho->hook  = (nf_hookfn*)hfunc;        /* hook function */
    nfho->hooknum   = NF_INET_PRE_ROUTING;      /* received packets */
    nfho->pf    = PF_INET;          /* IPv4 */
    nfho->priority  = NF_IP_PRI_FIRST;      /* max hook priority */
    
    nf_register_net_hook(&init_net, nfho);
    return 0;
}

static void __exit part1_step3_exit(void)
{
    nf_unregister_net_hook(&init_net, nfho);
    kfree(nfho);
}

module_init(part1_step3_init);
module_exit(part1_step3_exit);