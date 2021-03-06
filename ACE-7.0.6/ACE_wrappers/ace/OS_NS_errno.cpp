// -*- C++ -*-
#include "ace/OS_NS_errno.h"

#if !defined (ACE_HAS_INLINED_OSCALLS)
# include "ace/OS_NS_errno.inl"
#endif /* ACE_HAS_INLINED_OSCALLS */


#ifdef ACE_MQX
int
ACE_OS::mqx_error_to_errno(int mqx_error)
{
  switch (mqx_error)
    {
    // Not really an error.
    case FS_EOF:
      return 0;

    case FS_INVALID_FUNCTION_CODE:
    case FS_INVALID_PARAMETER:
    case FS_INVALID_HANDLE:
    case FS_ERROR_INVALID_DRIVE_HANDLE:
    case FS_ERROR_INVALID_FILE_HANDLE:
    case MQX_INVALID_POINTER:
    case MQX_INVALID_PARAMETER:
    case FS_INVALID_MEMORY_BLOCK_ADDRESS:
    case MQX_INVALID_SIZE:
    case MQX_INVALID_MEMORY_BLOCK:
    case MQX_INVALID_TASK_PRIORITY:
    case MQX_INVALID_TASK_STATE:
    case MQX_INVALID_TASK_ID:
    case MQX_INVALID_PROCESSOR_NUMBER:
    case MQX_INVALID_VECTORED_INTERRUPT:
    case MQX_INVALID_TEMPLATE_INDEX:
    case MQX_INVALID_CONFIGURATION:
    case MQX_INVALID_COMPONENT_HANDLE:
    case MQX_INVALID_COMPONENT_BASE:
    case MQX_INVALID_COMPONENT_NAME:
    case MQX_INVALID_HANDLE:
    case MQX_INVALID_TASK_QUEUE:
    case MQX_INVALID_LWSEM:
    case MQX_SCHED_INVALID_POLICY:
    case MQX_SCHED_INVALID_PARAMETER_PTR:
    case MQX_SCHED_INVALID_PARAMETER:
    case MQX_SCHED_INVALID_TASK_ID:
    case MQX_INVALID_IO_CHANNEL:
    case MQX_INVALID_DEVICE:
    case MQX_INVALID_CLOCK_SPEED:
    case MQX_IPC_INVALID_MESSAGE:
    case MQX_MEM_POOL_INVALID:
    case MQX_LWMEM_POOL_INVALID:
    case MQX_LWEVENT_INVALID:
    case MQX_LWTIMER_INVALID:
      return EINVAL;
    case FS_FILE_NOT_FOUND:
    case FS_PATH_NOT_FOUND:
      return ENOENT;
    case FS_ACCESS_DENIED:
    case FS_OPERATION_NOT_ALLOWED:
    case FS_SHARING_VIOLATION:
    case MQX_NOT_RESOURCE_OWNER:
    case MQX_ACCESS_ERROR:
      return EPERM;
    case FS_INSUFFICIENT_MEMORY:
    case FS_PMGR_INSUF_MEMORY:
    case MQX_OUT_OF_MEMORY:
    case MQX_KERNEL_MEMORY_TOO_SMALL:
    case MQX_MEM_POOL_TOO_SMALL:
    case MQX_OUT_OF_MMU_PAGE_TABLES:
      return ENOMEM;
    case FS_FILE_EXISTS:
    case MQX_COMPONENT_EXISTS:
    case MQX_IPC_ROUTE_EXISTS:
    case MQX_MMU_CONTEXT_EXISTS:
    case FS_ALREADY_ASSIGNED:
      return EEXIST;
    case FS_DISK_FULL:
    case FS_ROOT_DIR_FULL:
      return ENOSPC;
    case FS_DISK_IS_WRITE_PROTECTED:
      return EROFS;
    case FS_BAD_DISK_UNIT:
    case FS_INVALID_LENGTH_IN_DISK_OPERATION:
    case FS_NOT_A_DOS_DISK:
    case FS_SECTOR_NOT_FOUND:
    case FS_WRITE_FAULT:
    case FS_READ_FAULT:
    case FS_NOT_INITIALIZED:
    case FS_ERROR_UNKNOWN_FS_VERSION:
    case FS_LOST_CHAIN:
    case FS_INVALID_DEVICE:
    case FS_INVALID_CLUSTER_NUMBER:
    case FS_FAILED_TO_DELETE_LFN:
    case FS_BAD_LFN_ENTRY:
    case FS_PMGR_INVALID_PARTITION:
    case FS_PMGR_UNKNOWN_PARTITION:
    case FS_PMGR_INVALID_PARTTABLE:
    case FS_PMGR_EXFAT_PARTITION:
    case MQX_IO_OPERATION_NOT_AVAILABLE:
      return EIO;
    case FS_CANNOT_CREATE_DIRECTORY:
      return ENOTDIR;
    case MQX_LWSEM_WAIT_TIMEOUT:
      return ETIME;

    // These seem like generic errors
    case MQX_MMU_ERROR:
    case MQX_ERROR:

    // Need more info to categorize
    case FS_ATTEMPT_TO_REMOVE_CURRENT_DIR:
    case MQX_INVALID_CHECKSUM:
    case MQX_OUT_OF_TASK_DESCRIPTORS:
    case MQX_CANNOT_CALL_FUNCTION_FROM_ISR:
    case MQX_TASK_QUEUE_EMPTY:
    case MQX_NO_TASK_TEMPLATE:
    case MQX_COMPONENT_DOES_NOT_EXIST:
    case MQX_COULD_NOT_CREATE_IPC_TASK:
    case MQX_TOO_MANY_PRIORITY_LEVELS:
    case MQX_TOO_MANY_INTERRUPTS:
    case MQX_DUPLICATE_TASK_TEMPLATE_INDEX:
    case MQX_TIMER_ISR_INSTALL_FAIL:
    case MQX_INTER_PROCESSOR_INIT_FAILED:
    case MQX_IPC_SERVICE_NOT_AVAILABLE:
    case MQX_MMU_CONTEXT_DOES_NOT_EXIST:
    case MQX_MMU_PARENT_TASK_CANNOT_BE_MMU:
    case MQX_RTC_UNLOCK_FAILED:
    case MQX_NO_USER_TASKS:
    case MQX_TOO_MANY_USER_TASKS:
    case MQX_TASKQ_CREATE_FAILED:
    case MQX_INVALD_INT_ENABLE:
    case MQX_UNABLE_TO_CREATE_COMPONENT:
    case MQX_CLOCK_TRIM_FAILED:

    /* These are serious and should definitely return EFAULT unless there is a
     * more appropriate error code.
     */
    case MQX_CORRUPT_MEMORY_SYSTEM:
    case MQX_CORRUPT_STORAGE_POOL:
    case MQX_CORRUPT_STORAGE_POOL_FREE_LIST:
    case MQX_CORRUPT_STORAGE_POOL_POINTERS:
    case MQX_CORRUPT_QUEUE:
    case MQX_CORRUPT_INTERRUPT_STACK:
    case MQX_UNHANDLED_INTERRUPT:

    default:
      return EFAULT;
    }
}
#endif
