import serial

def read_serial(port, baudrate, timeout=1):
    """
    Continuously reads and prints data from a serial port.

    Args:
        port (str): The serial port to connect to (e.g., '/dev/ttyUSB0' or 'COM3').
        baudrate (int): The baud rate for the serial connection.
        timeout (float): Timeout in seconds for the serial connection.
    """
    try:
        # Open the serial connection
        ser = serial.Serial(port, baudrate, timeout=timeout)
        print(f"Connected to {port} at {baudrate} baud.\nPress Ctrl+C to stop.\n")
        
        while True:
            if ser.in_waiting > 0:  # Check if data is available
                data = ser.readline().decode('utf-8', errors='replace').strip()
                if data:
                    print(data)  # Print received data
    except serial.SerialException as error:
        print(f"Serial error: {error}")
    except KeyboardInterrupt:
        print("\nStopped serial reading.")
    finally:
        if 'ser' in locals() and ser.is_open:
            ser.close()
            print(f"Closed connection to {port}.")

if __name__ == "__main__":
    # Replace with your serial port and baud rate
    SERIAL_PORT = "/dev/ttyACM0"  # Adjust for your system
    BAUD_RATE = 115200           # Match with your device
    
    read_serial(SERIAL_PORT, BAUD_RATE)
