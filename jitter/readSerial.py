import serial
import time

def read_serial(port, baudrate, timeout=1):
    """
    Reads data from the serial port and prints it to the console.
    
    Args:
        port (str): The serial port to connect to (e.g., '/dev/ttyUSB0' or 'COM3').
        baudrate (int): The baud rate for the serial connection.
        timeout (float): The timeout for the serial connection in seconds.
    """
    try:
        # Initialize the serial connection
        ser = serial.Serial(port, baudrate, timeout=timeout)
        print(f"Connected to {port} at {baudrate} baud.")
        print("Press Ctrl+C to stop reading.\n")
        
        while True:
            if ser.in_waiting > 0:
                # Read a line from the serial buffer
                line = ser.readline().decode('utf-8', errors='replace').strip()
                if line:
                    # Print the received line to the console
                    print(line)
    except serial.SerialException as e:
        print(f"Error: {e}")
    except KeyboardInterrupt:
        print("\nStopping serial read.")
    finally:
        # Clean up and close the connection
        if 'ser' in locals() and ser.is_open:
            ser.close()
            print(f"Closed connection to {port}.")

if __name__ == "__main__":
    # User configuration
    SERIAL_PORT = "/dev/ttyACM0"  # Replace with your serial port (e.g., COM3 on Windows)
    BAUD_RATE = 115200           # Match the baud rate of your device
    
    read_serial(SERIAL_PORT, BAUD_RATE)