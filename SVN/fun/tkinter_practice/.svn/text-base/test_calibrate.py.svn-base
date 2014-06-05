import cv, cv2, pickle

USER_REQUEST_CALIB = True
CALIB_INDIVIDUAL = False

class Calibrate:
    def __init__(self, cam1, cam2):
        if REMOTE:
            brick = nxt.locator.find_one_brick()
            print "Found remote"
            self.remote = Touch(brick, PORT_1)
        #The number of chessboard images to take to use for calibration. 
        self.cam1 = cam1
        self.cam2 = cam2
        self.num_images = 10
        self.num_x_corners = 10
        self.num_y_corners = 7
        self.num_points = self.num_x_corners * self.num_y_corners
        self.x_size = 219 #mm
        self.y_size = 146 #mm
        self.points = self.get_points()
        frame1 = cv.QueryFrame(self.cam1)
        frame2 = cv.QueryFrame(self.cam2)
        self.image_width = int(frame1.width)
        self.image_height = int(frame1.height)
        self.calibrate()
        
        
    #Pre: self.num_images, self.num_y_corners, self.num_points must 
    #be positive integers. 
    #self.x_size, self.y_size must be the x, y dimensions of the board.
    #Post: todo
    def get_points(self):
        points = []
        square_size = self.y_size / float(self.num_y_corners - 1)
        for image_index in range(self.num_images):
            for point_index in range(self.num_points):
                x = (point_index % self.num_x_corners) * square_size
                y = (point_index // self.num_x_corners) * square_size
                points.append((x, y, 0))
        return points

    def get_chessboard_corners(self):
        if USER_REQUEST_CALIB:
            print "Press space to take chessboard readings."
        cv.NamedWindow("cam1 calibration")
        cv.NamedWindow("cam2 calibration")
        cv.MoveWindow("cam1 calibration", 0, 200)
        cv.MoveWindow("cam2 calibration", 720, 200)
        pairs_found = 0
        chessboard_corners1 = []
        chessboard_corners2 = []
        while pairs_found < self.num_images:
            frame1 = cv.QueryFrame(self.cam1)
            frame2 = cv.QueryFrame(self.cam2)
            gray_frame1 = self.convert(frame1)
            gray_frame2 = self.convert(frame2)
            found1, corners1 = cv.FindChessboardCorners(frame1,(10, 7), cv2.CALIB_CB_FAST_CHECK + cv.CV_CALIB_CB_FILTER_QUADS)
            found2, corners2 = cv.FindChessboardCorners(frame2,(10, 7), cv2.CALIB_CB_FAST_CHECK + cv.CV_CALIB_CB_FILTER_QUADS)
            if found1:
                cv.DrawChessboardCorners(frame1, (10, 7), corners1, found1)
            if found2:
                cv.DrawChessboardCorners(frame2, (10, 7), corners2, found2)
            cv.ShowImage("cam1 calibration", frame1)
            cv.ShowImage("cam2 calibration", frame2)
            key = cv.WaitKey(1)
            space_pressed = False
            if key == 32 or key == 1048608:
                space_pressed = True
            elif key == 1048603 or key == 27:
                assert False
            elif key != -1:
                print "key:", key
            if found1 and found2:
                if not USER_REQUEST_CALIB or space_pressed:
                    pairs_found += 1
                    print "ACQUIRED PAIR", pairs_found
                    corners1 = cv.FindCornerSubPix(gray_frame1, corners1, (11, 11), (-1, -1), (cv.CV_TERMCRIT_ITER + cv.CV_TERMCRIT_EPS, 30, 0.1))
                    corners2 = cv.FindCornerSubPix(gray_frame2, corners2, (11, 11), (-1, -1), (cv.CV_TERMCRIT_ITER + cv.CV_TERMCRIT_EPS, 30, 0.1))
                    chessboard_corners1 += corners1
                    chessboard_corners2 += corners2
        cv.DestroyAllWindows()
        return chessboard_corners1, chessboard_corners2
    
    #Pre: None.  
    #Post: creates a cvmat object point array. 
    def create_object_points(self):
        #import inspect
        #print inspect.getargspec(cv.StereoCalibrate)
        object_points = cv.CreateMat(self.num_images * self.num_points, 3, 
                                     cv.CV_32FC1)
        for row_index in range(object_points.rows):
            #xyz = list(self.points[row_index])
            #xyz.append(0)
            for col_index in range(3):
                object_points[row_index, col_index] = self.points[row_index][col_index]
        return object_points

    #Pre: None
    #Post: creates two cvmat image point arrays.
    #NOTE: Requires cameras to acquire chessboards. 
    def create_image_points(self):
        image_points1 = cv.CreateMat(self.num_images * self.num_points, 2,
                                    cv.CV_32FC1)
        image_points2 = cv.CreateMat(self.num_images * self.num_points, 2,
                                    cv.CV_32FC1)
        corners1, corners2 = self.get_chessboard_corners()
        for row_index in range(image_points1.rows):
            for col_index in range(2):
                image_points1[row_index, col_index] = corners1[row_index][col_index]
        for row_index in range(image_points2.rows):
            for col_index in range(2):
                image_points2[row_index, col_index] = corners2[row_index][col_index]

        return image_points1, image_points2
    
    #Pre: None
    #Post: returns a number-of-points array. 
    def create_npts(self):
        npts = cv.CreateMat(self.num_images, 1, cv.CV_32SC1)
        for i in range(npts.rows):
            npts[i, 0] = self.num_points
        return npts

    # def compute_intr_dist_for_cam(self, object_points, image_points, npts, size):
    #     intrinsics = cv.CreateMat(3, 3, cv.CV_64FC1)
    #     distortion = cv.CreateMat(4, 1, cv.CV_64FC1)
    #     rotation = cv.CreateMat(self.num_images, 3, cv.CV_64FC1)
    #     translation = cv.CreateMat(self.num_images, 3, cv.CV_64FC1)
    #     cv.CalibrateCamera2(object_points, image_points, npts, size, 
    #                         intrinsics, distortion, rotation, translation)
    #     return intrinsics, distortion
        

    #Pre: None
    #Post: sets attributes for the method undistort. 
    def calibrate(self):
        object_points = self.create_object_points()
        image_points1, image_points2 = self.create_image_points()
        npts = self.create_npts()
        size = (self.image_width, self.image_height)
        # if CALIB_INDIVIDUAL:
        #     intrinsics1,distortion1=self.compute_intr_dist_for_cam(object_points, image_points1, npts, size)
        #     intrinsics2,distortion2=self.compute_intr_dist_for_cam(object_points, image_points2, npts, size)
        #     f = cv.CV_CALIB_SAME_FOCAL_LENGTH + cv.CV_CALIB_FIX_INTRINSIC
        # else:
        f = cv.CV_CALIB_SAME_FOCAL_LENGTH
        intrinsics1 = cv.CreateMat(3, 3, cv.CV_64FC1)
        intrinsics2 = cv.CreateMat(3, 3, cv.CV_64FC1)
        distortion1 = cv.CreateMat(4, 1, cv.CV_64FC1)
        distortion2 = cv.CreateMat(4, 1, cv.CV_64FC1)
        rotation = cv.CreateMat(3, 3, cv.CV_64FC1)
        translation = cv.CreateMat(3, 1, cv.CV_64FC1)
        # cv.SetZero(intrinsics1)
        # cv.SetZero(intrinsics2)
        # cv.SetZero(distortion1)
        # cv.SetZero(distortion2)
        # cv.SetZero(rotation)
        # cv.SetZero(translation)
        cv.StereoCalibrate(object_points, image_points1, image_points2,npts,
                           intrinsics1, distortion1, intrinsics2, 
                           distortion2, size, rotation, translation, 
                           flags=f)

        # if FORCE_TRANS_VALUES != []:
        #     for i in range(translation.rows):
        #         value = FORCE_TRANS_VALUES[i]
        #         if value != None:
        #             translation[i, 0] = value
        values = [round(translation[i, 0], 5) for i in range(translation.rows)]
        print "Translation vector:", values
        mag = (values[0]**2 + values[1]**2 + values[2]**2) ** 0.5
        print "Mag of translation:", mag

        # index = 0
        # for row_index in range(rotation.rows):
        #     for col_index in range(rotation.cols):
        #         if index == 0 or index == 4 or index == 8:
        #             rotation[row_index, col_index] = 1
        #         else:
        #             rotation[row_index, col_index] = 0
        #         index += 1

        # if FORCE_ROT_VALUES != []:
        #     index = 0
        #     for row_index in range(rotation.rows):
        #         for col_index in range(rotation.cols):
        #             rotation[row_index,col_index] = FORCE_ROT_VALUES[index]
        #             index += 1

        for row_index in range(rotation.rows):
            for col_index in range(rotation.cols):
                print rotation[row_index, col_index]
        #print "Rotation vector:", [round(rotation[i, 0], 5) for i in range(rotation.rows)]
        
        rect1 = cv.CreateMat(3, 3, cv.CV_64FC1)#rectification1
        rect2 = cv.CreateMat(3, 3, cv.CV_64FC1)
        proj1 = cv.CreateMat(3, 4, cv.CV_64FC1)
        proj2 = cv.CreateMat(3, 4, cv.CV_64FC1)
        q     = cv.CreateMat(4, 4, cv.CV_64FC1)
        roi1, roi2 = cv.StereoRectify(intrinsics1, intrinsics2, distortion1,
                                      distortion2, size, rotation, 
                                      translation, rect1, rect2, proj1, 
                                      proj2, q, 
                                      flags=cv.CV_CALIB_ZERO_DISPARITY, 
                                      alpha=0)
        
        #save q:
        # import numpy
        # q_file = open("Q.p", "w")
        # pickle.dump(numpy.asarray(q), q_file)
        # q_file.close()
        
        print "1:", roi1, "2:", roi2
        mapx1 = cv.CreateImage(size, cv.IPL_DEPTH_32F, 1)
        mapy1 = cv.CreateImage(size, cv.IPL_DEPTH_32F, 1)
        mapx2 = cv.CreateImage(size, cv.IPL_DEPTH_32F, 1)
        mapy2 = cv.CreateImage(size, cv.IPL_DEPTH_32F, 1)
        cv.InitUndistortRectifyMap(intrinsics1, distortion1, rect1, 
                                   proj1, mapx1, mapy1)
        cv.InitUndistortRectifyMap(intrinsics2, distortion2, rect2, 
                                   proj2, mapx2, mapy2)
        self.mapx1 = mapx1
        self.mapy1 = mapy1
        self.mapx2 = mapx2
        self.mapy2 = mapy2
        
        
    #Pre: image must be an image from a camera QueryFrame call.
    #Post: Converts image to a grayscale usable by BM disparity.
    def convert(self, image):
        gray_image = cv.CreateImage(cv.GetSize(image), 8, 1)
        cv.CvtColor(image, gray_image, cv.CV_BGR2GRAY)
        return gray_image

    
    #Pre: image must be a grayscale. first_cam must be a boolean indicating
    #whether the image came from the first or second camera. 
    #Post: Returns an undistorted image ready to be used to 
    #compute a disparity map. 
    def undistort(self, image, first_cam):
        new_image = cv.CreateImage((self.image_width, self.image_height), 
                                   cv.IPL_DEPTH_8U, 1)
        if first_cam:
            cv.Remap(image, new_image, self.mapx1, self.mapy1)
        else:
            cv.Remap(image, new_image, self.mapx2, self.mapy2)
        return new_image


if __name__ == "__main__":
    cam1 = cv.CaptureFromCAM(1)
    cam2 = cv.CaptureFromCAM(2)
    c = Calibrate(cam1, cam2)
    cv.NamedWindow("Left")
    cv.NamedWindow("Right")
    cv.MoveWindow("Left", 0, 0)
    cv.MoveWindow("Right", 720, 0)
    while True:
        frame1 = cv.QueryFrame(cam1)
        frame2 = cv.QueryFrame(cam2)
        gray1, gray2 = c.convert(frame1), c.convert(frame2)
        undis1 = c.undistort(gray1, True)
        undis2 = c.undistort(gray2, False)
        cv.ShowImage("Left", undis1)
        cv.ShowImage("Right", undis2)
        
        key = cv.WaitKey(1)
        if key == 27 or key == 1048603:
            break
