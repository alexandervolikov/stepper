from serial import Serial
from time import sleep
import PySimpleGUI as sg 

def int_to_bytes(val):
    a = [0, 0, 0, 0]
    a[3] = val%256
    a[2] = (val//256)%256
    a[1] = (val//256//256)%256
    a[0] = (val//256//256//256)%256
    return a

def start(port, speed, step, numb, delay):
    serial = Serial(port, baudrate=9600, timeout=5)
    sleep(3)
    print(port, speed, step, numb, delay)
    print(serial.name)
    serial.flushInput()
    serial.write(int_to_bytes(int(speed)))
    serial.write(int_to_bytes(int(step)))
    serial.write(int_to_bytes(int(numb)))
    serial.write(int_to_bytes(int(delay)))
    serial.close()

layout = [[sg.Text(text='Com-port', font='Any 15')],
          [sg.Input(key='-COM-', font='Any 15', size=(16,1) )],
          [sg.Text(text='Speed', font='Any 15')],      
          [sg.Input(key='-SPEED-', font='Any 15', size=(16,1) )],
          [sg.Text(text='Step', font='Any 15')],      
          [sg.Input(key='-STEP-', font='Any 15', size=(16,1) )],
          [sg.Text(text='Num of steps', font='Any 15')],      
          [sg.Input(key='-NUM-', font='Any 15', size=(16,1) )],
          [sg.Text(text='Interval, ms', font='Any 15')],      
          [sg.Input(key='-DELAY-', font='Any 15', size=(16,1) )],      
          [sg.Button(button_text='START', font='Any 20',)]] 

window = sg.Window('Stepper', layout)  

while True:                             # The Event Loop
    event, values = window.read() 
    print(event, values)

    if event == 'START':
        start(values['-COM-'], values['-SPEED-'], values['-STEP-'], values['-NUM-'], values['-DELAY-'])

    if event == sg.WIN_CLOSED or event == 'Exit':
        break      

window.close()