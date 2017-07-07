from socket import error as SocketError
import errno
import cv2
import numpy as np


cap = cv2.VideoCapture(0)
data =""


while True:
	
	flag, frame =cap.read()
	cv2.imwrite('aaa.jpg', frame)
	#frame = cv2.medianBlur(frame, 5)

	rgbl_red = np.array([10,15,100])     #10 15 100
	rgbu_red = np.array([50,60,200])    #50 56 200

	rgb_mask = cv2.inRange(frame, rgbl_red,rgbu_red)

	circles = cv2.HoughCircles(rgb_mask,cv2.cv.CV_HOUGH_GRADIENT,3,100, param1=70,param2=40,minRadius=0,maxRadius=100)
	
	#1,20, param1=70,param2=40,min=0,max=100)
	cv2.rectangle(frame,(200,200), (400,350), (0,255.0))
	if circles is not None:
		print circles[0,0]
		i = circles[0,0]
		cv2.circle(frame, (i[0],i[1]), i[2], (0,255,0),2)
		if i[1] < 200:
			data = "1\n"
		elif i[1] > 350:
			data = "2\n"
		elif i[0] <200:
			data = "3\n"
		elif i[0]> 400:
			data = "4\n"
		print data
		
		
		data = ""
		#for i in circles[0,:]:
	        	#cv2.circle(frame, (i[0],i[1]), i[2], (0,255,0),2)
			#print 340 - i[0]
	else: 
		print "5"
	
	cv2.imshow('origin', frame)
	cv2.imshow('red', rgb_mask)
	cv2.imwrite('ccc.jpg', frame)
	cv2.imwrite('bbb.jpg', rgb_mask)
	circles = []
	k = cv2.waitKey(200) & 0xFF
	if k == 27:




                break
