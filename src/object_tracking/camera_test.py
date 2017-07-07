import cv2

cap = cv2.VideoCapture(0)
flag, frame = cap.read()
cv2.imshow('aaaaa', frame)
cv2.imsave('aaa.jpg', frame)
