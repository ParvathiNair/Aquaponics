import time
import serial
import smtplib


# TO = 'putyour@email.here'
# GMAIL_USER = 'putyour@email.here'
# GMAIL_PASS = 'putyourpasswordhere'
# SUBJECT = 'Intrusion!!'
# TEXT = 'Your PIR sensor detected movement'


TO = 'soorya.annadurai@gmail.com'
GMAIL_USER = 'missile.blast@gmail.com'
GMAIL_PASS = 'Cannonballs13'
SUBJECT = 'Test subject'
TEXT = 'Sample text in the email. Cheers!'
ser = serial.Serial('COM4', 9600)


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

while True:
	message = ser.readline()
	print(message)
	if message[0] == 'H' :
		send_email()
	time.sleep(0.5)
# send_email()