# -*- coding: utf-8 -*-
import atexit
import sys
import os.path
import datetime
import smtplib
import threading
from email import encoders
from email.utils import formatdate
from email.mime.base import MIMEBase
from email.header import Header
from email.mime.multipart import MIMEMultipart
from email.mime.text import MIMEText

#Gmailアカウント
ADDRESS = "ugcgeta2@gmail.com"
PASSWARD = "ug0063ug0063"

#SMTPサーバの設定(Gmail用)
SMTP = "smtp.gmail.com"
PORT = 587

class SendMail():

	def __init__(self,add,sub,body):
		self.add = add
		self.sub = sub
		self.body = body

		self.thread = threading.Thread(target = self.send)
		self.thread.start()


	def create_message(self, from_addr, to_addr, subject, body, mime=None, attach_file=None):

		"""
		メッセージを作成する
		@:param from_addr 差出人
		@:param to_addr 宛先
		@:param subject 件名
		@:param body 本文
		@:param mime MIME
		@:param attach_file 添付ファイル
		@:return メッセージ
		"""
		msg = MIMEMultipart()
		msg["From"] = from_addr
		msg["To"] = to_addr
		msg["Date"] = formatdate()
		msg["Subject"] = Header(subject, "utf-8")
		body = MIMEText(body,"plain","utf-8")
		msg.attach(body)
		# 添付ファイル
		#if mime != None and attach_file != None:
		#    attachment = MIMEBase(mime['type'],mime['subtype'])
		#    file = open(attach_file['path'])
		#    attachment.set_payload(file.read())
		#    file.close()
		#    encoders.encode_base64(attachment)
		#    msg.attach(attachment)
		#    attachment.add_header("Content-Disposition","attachment", filename=attach_file['name'])

		return msg

	def send_gmail(self, from_addr, to_addrs, msg):
		"""
		メールを送信する
		@:param from_addr 差出人
		@:param to_addr 宛先(list)
		@:param msg メッセージ
		"""
		smtpobj = smtplib.SMTP(SMTP, PORT)
		smtpobj.ehlo()
		smtpobj.starttls()
		smtpobj.ehlo()
		smtpobj.login(ADDRESS, PASSWARD)
		smtpobj.sendmail(from_addr, to_addrs, msg.as_string())
		smtpobj.close()

	def send(self):
		msg = self.create_message(ADDRESS, self.add, self.sub, self.body)
		self.send_gmail(ADDRESS, [self.add], msg)

def send(add, sub, body):
	SendMail(add, sub, body)

if __name__ == '__main__':
	print('send("ugcgeta@gmail.com", "Test", "ABC_TEST")')
	send("ugcgeta@gmail.com", "Test", "ABC_TEST")
	
