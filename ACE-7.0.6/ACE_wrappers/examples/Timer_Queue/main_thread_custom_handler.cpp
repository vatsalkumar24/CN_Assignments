//=============================================================================
/**
 *  @file    main_thread_custom_handler.cpp
 *
 *    Implements a threaded timer queue.
 *    This code exercises the Timer_Queue_Test_Driver class using
 *    threads.
 *    It also uses custom event handlers for timer events.
 *
 *  @author Douglas Schmidt      <d.schmidt@vanderbilt.edu> && Sergio Flores-Gaitan <sergio@cs.wustl.edu>  && Alon Diamant         <diamant.alon@gmail.com>
 */
//=============================================================================


#include "ace/OS_main.h"
#include "Driver.h"
#include "Thread_Timer_Queue_Custom_Handler_Test.h"
#include <memory>

typedef Timer_Queue_Test_Driver<Thread_Timer_Queue,
                                Custom_Handler_Input_Task,
                                Custom_Handler_Input_Task::ACTION>
  THREAD_TIMER_QUEUE_TEST_DRIVER;

int
ACE_TMAIN (int, ACE_TCHAR *[])
{
    // unique ptr ensures that the driver memory is released
    // automatically.
    THREAD_TIMER_QUEUE_TEST_DRIVER *tqtd = 0;
    ACE_NEW_RETURN (tqtd, Thread_Timer_Queue_Custom_Handler_Test, -1);

    std::unique_ptr <THREAD_TIMER_QUEUE_TEST_DRIVER> driver (tqtd);

    return driver->run_test ();
}

