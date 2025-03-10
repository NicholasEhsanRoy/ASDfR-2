import multiprocessing
import os
import time
import signal

# Function to stress CPU core 0
def stress_cpu():
    print(f"Stressing CPU Core 0 with PID {os.getpid()}... (Press Ctrl+C to stop)")
    
    # Run an infinite loop to keep the core busy
    try:
        while True:
            pass  # Busy wait (max CPU usage)
    except KeyboardInterrupt:
        print("\nStress test interrupted. Exiting...")
        return

# Main function
def main():
    # Create a process to run on Core 0
    process = multiprocessing.Process(target=stress_cpu)
    process.start()

    # Bind the process to Core 0
    try:
        os.sched_setaffinity(process.pid, {1})
    except AttributeError:
        print("os.sched_setaffinity is not supported on this platform.")

    # Handle termination signals gracefully
    def terminate_process(signal_number, frame):
        print("\nTermination signal received. Stopping stress test...")
        process.terminate()
        process.join()
        exit(0)

    # Register signal handlers for clean exit
    signal.signal(signal.SIGINT, terminate_process)  # Handle Ctrl+C
    signal.signal(signal.SIGTERM, terminate_process)  # Handle termination signals

    # Wait for the process to complete (infinite unless interrupted)
    try:
        while process.is_alive():
            time.sleep(1)
    except KeyboardInterrupt:
        terminate_process(None, None)

# Run the script
if __name__ == "__main__":
    main()
