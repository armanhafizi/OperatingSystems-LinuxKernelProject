#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/slab.h>
#include <linux/uaccess.h>
#include <linux/sysfs.h> 
#include <linux/kobject.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Agha Mohammadi, Hossein-Amiri, Amir Hossein-Hafizi, Arman");
MODULE_DESCRIPTION("A simple example Linux module.");
MODULE_VERSION("0.01");

volatile char etx_value[] = "INITIAL VALUE";

struct kobject *kobj_ref;
 
static int __init etx_init(void);
static void __exit etx_exit(void);

static ssize_t sysfs_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf);
static ssize_t sysfs_store(struct kobject *kobj, struct kobj_attribute *attr,const char *buf, size_t count);
static ssize_t sysfs_show_(struct kobject *kobj, struct kobj_attribute *attr, char *buf);
static ssize_t sysfs_store_(struct kobject *kobj, struct kobj_attribute *attr,const char *buf, size_t count);

struct kobj_attribute etx_attr1 = __ATTR(file1, 0660, sysfs_show, sysfs_store);
struct kobj_attribute etx_attr2 = __ATTR(file2, 0444, sysfs_show_, NULL);

static ssize_t sysfs_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
    return sprintf(buf, "%s\n", "STATIC MESSAGE");
}

static ssize_t sysfs_store(struct kobject *kobj, struct kobj_attribute *attr,const char *buf, size_t count)
{
	sscanf(buf,"%s",&etx_value);
	return count;
}

static ssize_t sysfs_show_(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
    return sprintf(buf, "%s\n", etx_value);
}

static int __init etx_init(void)
{
	kobj_ref = kobject_create_and_add("sample_module", fs_kobj);
	if(sysfs_create_file(kobj_ref,&etx_attr1.attr))
	{
		printk(KERN_INFO"Cannot create sysfs file etx_value ......\n");
		goto r_sysfs;
	}
	if(sysfs_create_file(kobj_ref,&etx_attr2.attr))
	{
		printk(KERN_INFO"Cannot create sysfs file ext_value_ ......\n");
		goto r_sysfs_;
	}
	return 0;
r_sysfs:
	kobject_put(kobj_ref); 
	sysfs_remove_file(fs_kobj, &etx_attr1.attr);
r_sysfs_:
	kobject_put(kobj_ref);
	sysfs_remove_file(fs_kobj, &etx_attr1.attr);
	sysfs_remove_file(fs_kobj, &etx_attr2.attr);
}

static void __exit etx_exit(void){
	kobject_put(kobj_ref);
	sysfs_remove_file(fs_kobj, &etx_attr1.attr);
	sysfs_remove_file(fs_kobj, &etx_attr2.attr);
}

module_init(etx_init);
module_exit(etx_exit);