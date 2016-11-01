/*
 * hello.c - Simple kernel module.
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/usb.h>
#include <linux/hid.h>

static const struct usb_device_id id_table[] = {
	{ USB_INTERFACE_INFO(USB_INTERFACE_CLASS_HID,
         USB_INTERFACE_SUBCLASS_BOOT, USB_INTERFACE_PROTOCOL_KEYBOARD) },
	{},
};

MODULE_DEVICE_TABLE(usb, id_table);


static int __init init_module_1(void)
{
	pr_info("Hello World!\n");
	return 0;
}

static void __exit cleanup_module_1(void)
{
	pr_info("GoodBye World!\n");
	return;
}

module_init(init_module_1);
module_exit(cleanup_module_1);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Skanda Guruanand");
MODULE_DESCRIPTION("USB Keyboard Module");
