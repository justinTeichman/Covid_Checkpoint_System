import cv2
import re
#import the two libraries 

def func():
    cap = cv2.VideoCapture(0) # setup variables for capturing the video and decting the qr code
    detector = cv2.QRCodeDetector()

    print("Reading QR code using Raspberry Pi camera")

    while True: # loop until a QR code is found or process is cancelled by user

        _, img = cap.read() # video capturing from webcam and displaying the read qr code 
        data, bbox, _ = detector.detectAndDecode(img) # qr code detection 
            
        if bbox is not None: # if the box is being displayed
            
            for i in range(len(bbox)): # parse through pixel boxes
                cv2.line(img, tuple(bbox[i][0]), tuple(bbox[(i+1) % len(bbox)][0]), color=(255,0, 0), thickness=2)
                cv2.putText(img, data, (int(bbox[0][0][0]), int(bbox[0][0][1]) - 10), cv2.FONT_HERSHEY_SIMPLEX,0.5, (0, 255, 0), 2)
                
            if data:
                print("Data found: " + data) # print if the data has been detected
                cap.release() #stop the video capturing
                cv2.destroyAllWindows() #close down window
                new = ""
                new = data # create new variable for returning
                return(new)
                
        cv2.imshow("code detector", img) # display on box that code has been detected

        if cv2.waitKey(1) == ord("q"): # if the user hits q to quit the process
            break

    
func()
