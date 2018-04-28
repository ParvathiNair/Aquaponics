import time
import serial
import smtplib


TO = 'soorya.annadurai@gmail.com'
GMAIL_USER = 'missile.blast@gmail.com'
GMAIL_PASS = 'Cannonballs13'
SUBJECT = 'Test subject'
TEXT = 'Sample text in the email. Cheers!'
ser = serial.Serial('/dev/cu.usbmodem1411', 9600)


def send_email():
	print("Sending Email")
	smtpserver = smtplib.SMTP("smtp.gmail.com",587)
	smtpserver.ehlo()
	smtpserver.starttls()
	smtpserver.ehlo
	smtpserver.login(GMAIL_USER, GMAIL_PASS)
	header = 'To:' + TO + '\n' + 'From: ' + GMAIL_USER
	header = header + '\n' + 'Subject:' + SUBJECT + '\n'
	print header
	msg = header + '\n' + TEXT + ' \n\n'
	smtpserver.sendmail(GMAIL_USER, TO, msg)
	smtpserver.close()

print "Starting the DesktopEmailServer.py script..."
while True:
	message = ser.read()
	if message > 0:
		print "Read a message! Yay!"

	# message = ser.readline()
	# print(message)
	# if message[0] == 'H' :
		# send_email()
	# time.sleep(0.5)