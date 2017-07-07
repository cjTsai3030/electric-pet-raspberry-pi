import os
import cv2
import math

def resizeImage(img):
	dst = cv2.resize(img, None, fx = 0.25, fy=0.25, interpolation = cv2.INTER_LINEAR)
	return dst

cap = cv2.VideoCapture(0)

# camture image from webcam
ret, frame = cap.read()
grey_frame = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

grey_frame =cv2.medianBlur(grey_frame, 5) 

ret, thresh = cv2.threshold(grey_frame, 50, 255, cv2.THRESH_BINARY)

circles = cv2.HoughCircles(thresh, cv2.cv.CV_HOUGH_GRADIENT, 1,75, param1=50, param2=13, minRadius=0, maxRadius=175)

for i in circles[0,:]:
	cv2.circle(frame, (i[0],i[1]), i[2], (0,255,0), 2)
	cv2.circle(frame, (i[0],i[1]), 2, (0,255,0), 3)



#cv2.circle(grey_frame, (x1,y1), 10, (255,100,255), -1)

# show image 
cv2.imshow('grey',grey_frame)
cv2.imshow('thresh', thresh)
cv2.waitKey(0)
