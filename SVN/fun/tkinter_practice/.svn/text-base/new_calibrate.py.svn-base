# dims=(8,5)
# c=cv.CaptureFromCAM(0)
# points = []
# while len(points)==0:
#     f=cv.QueryFrame(c)
#     cv.CvtColor(f,grey,cv.CV_BGR2GRAY)
#     found,points=cv.FindChessboardCorners(grey,dims,cv.CV_CALIB_CB_ADAPTIVE_THRESH)
#     if found!=0:
#         cv.DrawChessboardCorners(f,dims,points,found)
#         cv.ShowImage("win2",f)
#         cv.WaitKey(2)
# #Number of calibration patterns used
# nimage=1#total_number_of_images_with_chessboard_pattern
# #Number of points in chessboard
# num_pts=70#width_of_board * height_of_board
# opts = cv.CreateMat(nimages * num_pts, 3, cv.CV_32FC1)
# ipts = cv.CreateMat((points) * num_pts, 2, cv.CV_32FC1)
# npts = cv.CreateMat(nimages, 1, cv.CV_32SC1)
# intrinsics = cv.CreateMat(3, 3, cv.CV_64FC1)
# distortion = cv.CreateMat(4, 1, cv.CV_64FC1)

# cv.SetZero(intrinsics)
# cv.SetZero(distortion)

# cv.SetZero(intrinsics2)
# cv.SetZero(distortion2)
# # focal lengths have 1/1 ratio
# intrinsics[0,0] = 1.0
# intrinsics[1,1] = 1.0
# size=cv.GetSize(f)
# cv.CalibrateCamera2(opts, ipts, npts, size,intrinsics, distortion,
# cv.CreateMat(points), 3, cv.CV_32FC1),cv.CreateMat(lenpoints), 3,
# cv.CV_32FC1),flags = 0)
# mapx = cv.CreateImage((mat_w,mat_h), cv.IPL_DEPTH_32F, 1)
# mapy = cv.CreateImage((mat_w,mat_h), cv.IPL_DEPTH_32F, 1)
# cv.InitUndistortMap(intrinsics, distortion, mapx, mapy)
# r = cv.CloneImage(img)
# cv.Remap(img, r, mapx, mapy)
