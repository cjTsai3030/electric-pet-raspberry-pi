import os
import cv2
import numpy as np

cap = cv2.VideoCapture(0)

ret, frame = cap.read()

frame = cv2.medianBlur(frame, 5)

cimg = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
#cv2.imshow('aa',cimg)
#cv2.waitKey(0)

circles = cv2.HoughCircles(cimg,cv2.cv.CV_HOUGH_GRADIENT,1,20, param1=60,param2=40,minRadius=10,maxRadius=100)

#circles = np.uint16(np.around(circles))

for i in circles[0,:]:
	cv2.circle(frame, (i[0],i[1]), i[2], (0,255,0),2)

cv2.imshow('aa', frame)
cv2.waitKey(0)
