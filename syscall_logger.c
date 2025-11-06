#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kprobes.h>
#include <linux/sched.h>  

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Deepak Kushwaha");
MODULE_DESCRIPTION("Simple syscall logger using kprobes");
MODULE_VERSION("1.0");

static struct kprobe kp_open, kp_exec;

static int handler_pre(struct kprobe *p, struct pt_regs *regs)
{
    printk(KERN_INFO "[syscall_logger] %s called by PID=%d (%s)\n",
           p->symbol_name, current->pid, current->comm);
    return 0; 
}

static int __init logger_init(void)
{
    int ret;

    kp_open.symbol_name = "__x64_sys_openat";
    kp_open.pre_handler = handler_pre;

    ret = register_kprobe(&kp_open);
    if (ret < 0) {
        printk(KERN_ERR "Failed to register kprobe for openat: %d\n", ret);
        return ret;
    }

    kp_exec.symbol_name = "__x64_sys_execve";
    kp_exec.pre_handler = handler_pre;

    ret = register_kprobe(&kp_exec);
    if (ret < 0) {
        printk(KERN_ERR "Failed to register kprobe for execve: %d\n", ret);
        unregister_kprobe(&kp_open);
        return ret;
    }

    printk(KERN_INFO "[syscall_logger] Module loaded. Monitoring syscalls.\n");
    return 0;
}

static void __exit logger_exit(void)
{
    unregister_kprobe(&kp_exec);
    unregister_kprobe(&kp_open);
    printk(KERN_INFO "[syscall_logger] Module unloaded safely.\n");
}

module_init(logger_init);
module_exit(logger_exit);
