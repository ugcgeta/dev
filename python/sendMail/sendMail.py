# -*- coding: utf-8 -*-
import atexit
import sys
import os.path
import datetime
import smtplib
import threading
from email import Encoders
from email.Utils import formatdate
from email.MIMEBase import MIMEBase
from email.Header import Header
from email.MIMEMultipart import MIMEMultipart
from email.MIMEText import MIMEText

#Gmailアカウント
ADDRESS = "（所持しているアドレス）@gmail.com"
PASSWARD = "（パスワード）"
