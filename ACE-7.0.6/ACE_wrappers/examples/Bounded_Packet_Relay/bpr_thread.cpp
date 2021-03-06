
//=============================================================================
/**
 *  @file    bpr_thread.cpp
 *
 *  Exercises drivers for a bounded packet relay, based on threaded timer queues.
 *
 *  @author Chris Gill <cdgill@cs.wustl.edu>
 *  @author Douglas C. Schmidt   <d.schmidt@vanderbilt.edu>
 *
 * Based on the Timer Queue Test example written by Carlos O'Ryan <coryan@cs.wustl.edu>
 * and Douglas C. Schmidt <d.schmidt@vanderbilt.edu> and Sergio Flores-Gaitan <sergio@cs.wustl.edu>
 */
//=============================================================================

#include "Thread_Bounded_Packet_Relay.h"
#include <memory>

typedef Bounded_Packet_Relay_Driver<Thread_Timer_Queue>
  THREAD_BOUNDED_PACKET_RELAY_DRIVER;

typedef ACE_Command_Callback<Bounded_Packet_Relay,Bounded_Packet_Relay::ACTION>
  INPUT_CALLBACK;

// A snippet from Andrew Marvell (Oliver Cromwell's poet laureate)
static const char input_text [] =
"But ever at my back I hear\n"
" Time's winged chariot hurrying near.";

int
ACE_TMAIN (int, ACE_TCHAR *[])
{
  // Construct a new thread manager for the input device task.  Auto
  // ptr ensures memory is freed when we exit this scope.
  ACE_Thread_Manager *input_task_mgr;
  ACE_NEW_RETURN (input_task_mgr,
                  ACE_Thread_Manager,
                  -1);
  std::unique_ptr <ACE_Thread_Manager> mgr (input_task_mgr);

  // Construct a new input device wrapper.  Auto ptr ensures memory is
  // freed when we exit this scope.
  Text_Input_Device_Wrapper *input_device;
  ACE_NEW_RETURN (input_device,
                  Text_Input_Device_Wrapper (input_task_mgr,
                                             sizeof (input_text),
                                             input_text),
                  -1);
  std::unique_ptr <Text_Input_Device_Wrapper> input (input_device);

  // Construct a new output device wrapper.  Auto ptr ensures memory
  // is freed when we exit this scope.
  Text_Output_Device_Wrapper *output_device = 0;
  ACE_NEW_RETURN (output_device,
                  Text_Output_Device_Wrapper,
                  -1);
  std::unique_ptr <Text_Output_Device_Wrapper> output (output_device);

  // Construct a new bounded packet relay.  Auto ptr ensures memory is
  // freed when we exit this scope.
  Bounded_Packet_Relay *packet_relay = 0;
  ACE_NEW_RETURN (packet_relay,
                  Bounded_Packet_Relay (input_task_mgr,
                                        input_device,
                                        output_device),
                  -1);
  std::unique_ptr <Bounded_Packet_Relay> relay (packet_relay);

  // Construct a receive input callback command for the relay, and register
  // it with the input device.  Auto ptr ensures memory is freed when we exit
  // this scope.
  INPUT_CALLBACK *input_callback = 0;
  ACE_NEW_RETURN (input_callback,
                  INPUT_CALLBACK (*packet_relay,
                                  &Bounded_Packet_Relay::receive_input),
                  -1);
  std::unique_ptr <INPUT_CALLBACK> callback (input_callback);
  if (input_device->set_send_input_msg_cmd (input_callback) < 0)
    {
      ACE_ERROR_RETURN ((LM_ERROR,
                         "failed to register input callback"),
                        -1);
    }

  // Construct a new bounded packet relay driver.  Auto ptr ensures
  // memory is freed when we exit this scope.
  THREAD_BOUNDED_PACKET_RELAY_DRIVER *tbprd = 0;

  ACE_NEW_RETURN (tbprd,
                  Thread_Bounded_Packet_Relay_Driver (packet_relay),
                  -1);

  std::unique_ptr <THREAD_BOUNDED_PACKET_RELAY_DRIVER> driver (tbprd);

  return driver->run ();
  // All dynamically allocated memory is released when main() returns.
}

