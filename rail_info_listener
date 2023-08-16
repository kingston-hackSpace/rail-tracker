#========================================================
# Kingston hackSpace (kingstonhack.space)
# Project: train times video display
# This script will take data from british rail and
# compare departure times to the current time  
#
# Distributed under the creative commons license
# 
# Giants upon whose shoulders we stand...
# https://groups.google.com/g/openraildata-talk
# 
#========================================================



import http.client
import urllib.parse
import xml.dom.minidom

from datetime import datetime
from datetime import time
from datetime import timedelta

import xml.etree.ElementTree as ET

now = datetime.now()

current_time = now.strftime("%H:%M:%S")
current_second = now.second

a = [time(11, 59),time(12,1),time(13,17)]
d = ['TST','TST','TST']


class soap_consumer:

	def __init__(self, msg, json=False):
		self.msg = msg
		self.json = json
	
	def envelope(self):
		if self.json:
			return self.msg
		else:
			doc = xml.dom.minidom.Document()
			env = doc.createElement('soapenv:Envelope')
			
			env.setAttribute('xmlns:soapenv','http://schemas.xmlsoap.org/soap/envelope/')
		#	env.setAttribute('xmlns:soapenv','http://www.w3.org/2003/05/soap-envelope')
			env.setAttribute('xmlns:typ','http://thalesgroup.com/RTTI/2013-11-28/Token/types')
			env.setAttribute('xmlns:ldb','http://thalesgroup.com/RTTI/2012-01-13/ldb/')
		#	env.setAttribute('xmlns:wsdl','http://schemas.xmlsoap.org/wsdl/')
		#	env.setAttribute('xmlns:soap','http://schemas.xmlsoap.org/wsdl/soap/')
		#	env.setAttribute('xmlns:soap12', 'http://schemas.xmlsoap.org/wsdl/soap12/')
		#	env.setAttribute('xmlns:tns', 'http://thalesgroup.com/RTTI/2017-10-01/ldb/')
		#	env.setAttribute('targetNamespace', 'http://thalesgroup.com/RTTI/2017-10-01/ldb/')
			
			#print(self.msg)
			
			#XML input request data
			rawdom = xml.dom.minidom.parseString(self.msg)		
			#messagenodes = rawdom.childNodes
			messagenode = rawdom.firstChild
			#Header
			header = doc.createElement('soapenv:Header')
			Tok = doc.createElement('typ:AccessToken')
			Tokn = doc.createElement('typ:TokenValue')
			# get a token text node at https://www.nationalrail.co.uk/developers/
			Tokn_text = doc.createTextNode("INSERT_TOKEN_TEXT_NODE_HERE")
			Tokn.appendChild(Tokn_text)
			#Tokn.oldwritexml =''
			Tok.appendChild(Tokn)
			
			header.appendChild(Tok)
			env.appendChild(header)
			
			#Body
			body = doc.createElement('soapenv:Body')
			body.appendChild(messagenode)
			#for i in messagenodes:
			#	body.appendChild(i)
			
			env.appendChild(body)
			doc.appendChild(env)
			
			#print(doc)
			
			return doc.toxml('utf-8')
	
	def send_request(self, url, path, accept, SA, content_type, https=True):
		data = self.envelope()
		
		#print(data)
		#print(len(data))
		#print(path)
		headers = { "Content-type" : content_type, "Accept": accept, "SOAPAction": SA, "Content-length": len(data)}
		conn = ''
		#print (headers)
		if https:
			conn = http.client.HTTPSConnection(url, 443)
		else:
			conn = http.client.HTTPConnection(url, 80)

		#print(conn)
		conn.request("POST", path, data, headers)
		
		response = conn.getresponse()
		resp_data = response.read()
		
		#print(resp_data)
		
		if response.status == 200:
			conn.close()
			return resp_data
		else:
			return 'Status:' + str(response.status) + ': ' + str(resp_data)
#change the codes on this line to change the data destinations/ departures see https://en.wikipedia.org/wiki/UK_railway_stations_%E2%80%93_A for full list of codes
swsc = soap_consumer('<ldb:GetDepartureBoardRequest xmlns:ldb="http://thalesgroup.com/RTTI/2016-02-16/ldb/"><ldb:numRows>16</ldb:numRows><ldb:crs>NBY</ldb:crs><ldb:filterCrs>RDG</ldb:filterCrs><ldb:filterType>to</ldb:filterType><ldb:timeOffset>10</ldb:timeOffset><ldb:timeWindow>120</ldb:timeWindow></ldb:GetDepartureBoardRequest>')
resp = swsc.send_request('realtime.nationalrail.co.uk', '/OpenLDBWS/ldb9.asmx', 'application/soap+xml','http://thalesgroup.com/RTTI/2012-01-13/ldb/GetDepartureBoard', 'text/xml;charset=utf-8')
#print(resp)



def display_results():
	output = resp.decode('utf-8')
	times = output.split('<lt4:std>')
	dests = output.split('<lt4:crs>')
	for i in range (1,len(times)):
		hour = times[i][0:2]
		minute = times[i][3:5]
		dest = dests[i][0:3]
		#print("" , dest , hour, minute)
		add_time_to_list(dest,hour,minute)
		
def add_time_to_list(dest,h,m):
	#is the time unique?
	is_match = False
	for i in range (0,len(a)):
		if (h == a[i].hour) and (m == a[i].minute):
			print("exists")
			is_match = True
	if (is_match == False):	
		a.append(time(int(h),int(m)))
		d.append(dest)

def display_array():
	for i in range (0,len(a)):
		print("",d[i], a[i])
			
display_results()

display_array()

def check_time():
	now = datetime.now()
	while (len(a) > 0):
		t1 = timedelta(hours = now.hour, minutes = now.minute)
		t2 = timedelta(hours = a[0].hour, minutes = a[0].minute)
		if (t1.total_seconds()>t2.total_seconds()):
			print("deleted")
			a.pop(0)
			d.pop(0)
		else:
			print("keep")
			break
		
	for i in range(0,len(a)):
		if (now.hour == a[i].hour) and (now.minute == a[i].minute):
			print("It's time!")
			#insert procedure for when a departure is due

def display_times():
	if (len(a)>0):
		for i in range(0,len(a)):
			print (d[i],a[i].hour,a[i].minute)
	else:
		print("empty list!!")
		a.append(time(13,13))
		d.append('TST')
		display_results()

while(True):
	now =datetime.now()
	if current_second != now.second:
		if current_second == 0:
			print ("One minute elapsed!!")
			display_times()
			check_time()
		print (now.second)
		current_second = now.second
