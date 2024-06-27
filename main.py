import serial
import time

# Initialize serial connection
arduino = serial.Serial(port='COM3', baudrate=9600, timeout=.1)

def send_word(word):
    for char in word:
        if char.isalpha():
            arduino.write((char.upper() + '\n').encode())  # Send character to Arduino
            time.sleep(1)  # Wait 1 second between letters
    # Turn off display after sending the word
    arduino.write('off\n'.encode())

if __name__ == "__main__":
    while True:
        word = input("Enter a word (letters A-Z only) or 'exit' to quit: ")
        if word.lower() == 'exit':
            break
        send_word(word)
