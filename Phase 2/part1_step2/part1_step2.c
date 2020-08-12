#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/kernel.h>
#include <linux/cred.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Agha Mohammadi, Hossein-Amiri, Amir Hossein-Hafizi, Arman");
MODULE_DESCRIPTION("A simple example Linux module.");
MODULE_VERSION("0.01");

static char * message = "unentered argument";
module_param(message, charp, 0660);

static int __init part1_step2_init(void)
{
	printk(KERN_INFO "initialization: part 1 step 2 module has been loaded successfully.\n");
	printk(KERN_INFO "name: Agha Mohammadi, Hossein-Amiri, Amir Hossein-Hafizi, Arman\n");
	printk(KERN_INFO "input message: %s\n", message);
	return 0;
}

static void __exit part1_step2_exit(void)
{
	printk(KERN_INFO "termination: part 1 step 2 module has been unloaded successfully.\n");
}

module_init(part1_step2_init);
module_exit(part1_step2_exit);
