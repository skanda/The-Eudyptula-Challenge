/*
 * hello.c - Misc kernel module.
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <linux/poll.h>
#include <linux/errno.h>
#include <linux/string.h>

#define MY_ID "80bf78032ef4"
#define ID_LEN 13
#define BUF_LEN 80

static char msg[BUF_LEN] = {0};
static char *id = MY_ID;

static ssize_t hello_read(struct file *file, char __user *buf,
		size_t count, loff_t *ppos)
{
	return simple_read_from_buffer(buf, count, ppos, id, strlen(id));
}

static ssize_t hello_write(struct file *file, char const __user *buf,
		size_t count, loff_t *ppos)
{
	simple_write_to_buffer(msg, BUF_LEN, ppos, buf, count);

	if (!strncmp(msg, MY_ID, strlen(MY_ID)) && count - 1 == strlen(MY_ID))
		return count;

	return -EINVAL;
}
static const struct file_operations hello_fops = {
	.owner = THIS_MODULE,
	.read = hello_read,
	.write = hello_write
};

static struct miscdevice hello_dev = {
	MISC_DYNAMIC_MINOR,
	"eduyptula",
	&hello_fops
};

static int __init init_module_1(void)
{
	int ret;

	ret = misc_register(&hello_dev);
	pr_debug("Hello World!\n");

	return ret;
}

static void __exit cleanup_module_1(void)
{
	misc_deregister(&hello_dev);
}

module_init(init_module_1);
module_exit(cleanup_module_1);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Skanda Guruanand");
MODULE_DESCRIPTION("Misc Kernel Module");
