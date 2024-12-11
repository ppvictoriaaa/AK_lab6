#include <linux/module.h>
#include <linux/printk.h>
#include <linux/bug.h>
#include <linux/slab.h>
#include "hello1.h"

MODULE_LICENSE("Dual BSD/GPL");
MODULE_DESCRIPTION("Hello2 module");
MODULE_AUTHOR("IO-24 Victoria Pekur");

static int hello_count = 1;
module_param(hello_count, int, 0644);
MODULE_PARM_DESC(hello_count, "Number of times to print 'Hello, world!!!' message");

static int __init hello2_init(void)
{
    BUG_ON(hello_count < 0 || hello_count > 10);

    if (hello_count == 0 || (hello_count >= 5 && hello_count <= 10)) {
        pr_warn("Warning! hello_count is %u: The number is 0 or > 5 and < 10\n", hello_count);
    }

    pr_info("Calling print_hello() from Hello1 module\n");
    print_hello(hello_count);
    return 0;
}

static void __exit hello2_exit(void)
{
    pr_info("Bye bye from Hello2 module\n");
}

module_init(hello2_init);
module_exit(hello2_exit);

