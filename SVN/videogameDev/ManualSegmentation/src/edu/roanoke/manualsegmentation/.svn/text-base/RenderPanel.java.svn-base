package edu.roanoke.manualsegmentation;

import static javax.media.opengl.GL.GL_COLOR_BUFFER_BIT;
import static javax.media.opengl.GL.GL_DEPTH_BUFFER_BIT;
import static javax.media.opengl.GL.GL_DEPTH_TEST;
import static javax.media.opengl.GL.GL_FRONT;
import static javax.media.opengl.GL.GL_LEQUAL;
import static javax.media.opengl.GL.GL_NICEST;
import static javax.media.opengl.GL2ES1.GL_PERSPECTIVE_CORRECTION_HINT;
import static javax.media.opengl.GL2GL3.GL_QUADS;
import static javax.media.opengl.fixedfunc.GLLightingFunc.GL_AMBIENT;
import static javax.media.opengl.fixedfunc.GLLightingFunc.GL_DIFFUSE;
import static javax.media.opengl.fixedfunc.GLLightingFunc.GL_LIGHT0;
import static javax.media.opengl.fixedfunc.GLLightingFunc.GL_LIGHTING;
import static javax.media.opengl.fixedfunc.GLLightingFunc.GL_POSITION;
import static javax.media.opengl.fixedfunc.GLLightingFunc.GL_SMOOTH;
import static javax.media.opengl.fixedfunc.GLMatrixFunc.GL_MODELVIEW;
import static javax.media.opengl.fixedfunc.GLMatrixFunc.GL_PROJECTION;
import static javax.media.opengl.glu.GLU.GLU_SMOOTH;

import java.awt.Dimension;
import java.awt.Point;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;

import javax.media.opengl.GL2;
import javax.media.opengl.GLAutoDrawable;
import javax.media.opengl.GLCapabilities;
import javax.media.opengl.GLEventListener;
import javax.media.opengl.awt.GLJPanel;
import javax.media.opengl.glu.GLU;
import javax.media.opengl.glu.GLUquadric;
import javax.vecmath.Vector3f;

import com.jogamp.opengl.util.FPSAnimator;

/**
 * Displays an OpenGL rendering of a Kinect skeleton data file.
 *
 * @author durell
 */
@SuppressWarnings("serial")
public class RenderPanel extends GLJPanel implements GLEventListener {

    /** X-coordinate index in an array representing a point. */
    private static final int X = 0;

    /** Y-coordinate index in an array representing a point. */
    private static final int Y = 1;

    /** Z-coordinate index in an array representing a point. */
    private static final int Z = 2;

    /** Red channel index in an array representing a color. */
    private static final int RED = 0;

    /** Green channel index in an array representing a color. */
    private static final int GREEN = 0;

    /** Blue channel index in an array representing a color. */
    private static final int BLUE = 0;

    /** Alpha channel index in an array representing a color. */
    private static final int ALPHA = 0;

    /** Z-buffer clear depth. */
    private static final float Z_BUFFER_CLEAR_DEPTH = 1.0f;

    /** X-axis vector. */
    private static final float[] X_AXIS = {1.0f, 0.0f, 0.0f};

    /** Y-axis vector. */
    private static final float[] Y_AXIS = {0.0f, 1.0f, 0.0f};

    /** Z-axis vector. */
    private static final float[] Z_AXIS = {0.0f, 0.0f, 1.0f};

    /** Initial width of this panel, in pixels. */
    private static final int RENDER_PANEL_WIDTH = 640;

    /** Initial height of this panel, in pixels. */
    private static final int RENDER_PANEL_HEIGHT = 480;

    /** Frames per-second for OpenGL animator. */
    private static final int FRAMES_PER_SECOND = 30;

    /** Whether OpenGL animator should schedule frames at a fixed rate. */
    private static final boolean FIXED_RATE = true;

    /** Amount to multiply mouse movement by when translating the view. */
    private static final float MOUSE_TRANSLATION_SCALE_FACTOR = 0.01f;

    /** Amount to multiply mouse movement by when rotating the view. */
    private static final float MOUSE_ROTATION_SCALE_FACTOR = 1.0f;

    /** Maximum thickness of bone in meters. */
    private static final float BONE_THICKNESS = 0.1f;

    /** Bone ambient reflectivity RGB values. */
    private static final float[] BONE_AMBIENT_REFLECTIVITY = {0.25f, 0.25f,
        0.25f};

    /** Bone diffuse reflectivity RGB values. */
    private static final float[] BONE_DIFFUSE_REFLECTIVITY = {0.8f, 0.8f, 0.8f};

    /** Dark tile color. */
    private static final float[] DARK_TILE_COLOR = {0.2f, 0.2f, 0.2f};

    /** Light tile color. */
    private static final float[] LIGHT_TILE_COLOR = {0.8f, 0.8f, 0.8f};

    /** black color array. */
    private static final float[] BLACK = {0.0f, 0.0f, 0.0f};

    /** Light ambient emission RGB values. */
    private static final float[] LIGHT_AMBIENT_EMISSION = {1.0f, 1.0f, 1.0f};

    /** Light diffuse emission RGB values. */
    private static final float[] LIGHT_DIFFUSE_EMISSION = {1.0f, 1.0f, 1.0f};

    /** Light position. */
    private static final float[] LIGHT_POSITION = {20.0f, 20.0f, 20.0f};

    /** Background color. */
    private static final float[] BACKGROUND_COLOR = {1.0f, 1.0f, 1.0f, 1.0f};

    /** Number of slabs in bone sphere, higher is better looking but slower. */
    private static final int BONE_SLABS = 20;

    /** Number of slices in bone sphere, higher is better looking but slower. */
    private static final int BONE_SLICES = 40;

    /** Offset in array for OpenGL parameter. */
    private static final int PARAMETER_ARRAY_OFFSET = 0;

    /** Number of super samples for anti-aliasing. */
    private static final int ANTI_ALIASING_SAMPLES = 4;

    /** Floor tile size in meters. */
    private static final float FLOOR_TILE_SIZE = 1.0f;

    /** The floor's width in tiles. */
    private static final int FLOOR_TILE_COLUMNS = 10;

    /** The floor's height in tiles. */
    private static final int FLOOR_TILE_ROWS = 10;

    /** Initial camera rotation about the y-axis in degrees. */
    private static final float INITIAL_CAMERA_ROTATION = 180.0f;

    /** Initial camera translation along the z-axis. */
    private static final float INITIAL_CAMERA_TRANSLATION = 4.0f;

    /** Distance to the near clipping plane, must be positive. */
    private static final float NEAR_CLIPPING_DISTANCE = 0.1f;

    /** Distance to the far clipping plane, must be positive. */
    private static final float FAR_CLIPPING_DISTANCE = 100.0f;

    /** Degrees of the field of view in the y-direction. */
    private static final float Y_FIELD_OF_VIEW = 45.0f;

    /**
     * Factory method for creating a GLCapabilities that using anti-aliasing.
     *
     * @return A new GLCapabilities that uses anti-aliasing and all other
     *         settings at defaults.
     */
    private static GLCapabilities createMultisampleCapabilities() {
        final GLCapabilities capabilities = new GLCapabilities(null);
        capabilities.setSampleBuffers(true);
        capabilities.setNumSamples(ANTI_ALIASING_SAMPLES);
        return capabilities;
    }

    /** Animator with separate thread that repeatedly calls draw function. */
    private final FPSAnimator animator;

    /** OpenGL utilities object. */
    private GLU glu;

    /** Current camera x, y, and z-axis rotation. */
    private final float[] cameraRotation = {0.0f, INITIAL_CAMERA_ROTATION, 0.0f};

    /** Current camera x, y, and z-axis translation. */
    private final float[] cameraTranslation = {0.0f, 0.0f, 0.0f};

    /** Location of the mouse when dragged. */
    private Point mouseLocation;

    /** Kinect skeleton data file to render. */
    private KinectDataFile kinectDataFile = null;

    /** Y-coordinate of the floor plane. */
    private float floorY;

    /**
     * Initialize render panel and begin animation.
     */
    public RenderPanel() {
        super(createMultisampleCapabilities());
        final Dimension preferredSize = new Dimension();
        preferredSize.width = RENDER_PANEL_WIDTH;
        preferredSize.height = RENDER_PANEL_HEIGHT;
        setPreferredSize(preferredSize);
        MouseEventHandler mouseEventHandler = new MouseEventHandler();
        addMouseListener(mouseEventHandler);
        addMouseMotionListener(mouseEventHandler);
        addGLEventListener(this);
        animator = new FPSAnimator(this, FRAMES_PER_SECOND, FIXED_RATE);
        animator.start();
    }

    /*
     * Display Kinect skeleton data skeleton and floor plane.
     *
     * @see javax.media.opengl.GLEventListener#display(
     * javax.media.opengl.GLAutoDrawable)
     */
    @Override
    public final void display(final GLAutoDrawable drawable) {
        final GL2 gl = drawable.getGL().getGL2();
        gl.glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        moveView(gl);
        drawScene(gl);
    }


    /**
     * Move the view based on camera translation and rotation.
     *
     * @param gl GL object to change view of.
     */
    private void moveView(final GL2 gl) {
        gl.glLoadIdentity();

        // Test code below
        final Vector3f hipJoint = kinectDataFile.getJointPosition(KinectDataFile.HIP_CENTER);
        // gl.glTranslatef(hipJoint.x, hipJoint.y, hipJoint.z - 4.0f);
        gl.glTranslatef(hipJoint.x, hipJoint.y, hipJoint.z - INITIAL_CAMERA_TRANSLATION);
        // Test code above
        gl.glTranslatef(cameraTranslation[X], cameraTranslation[Y],
                cameraTranslation[Z]);
        gl.glRotatef(cameraRotation[X], X_AXIS[X], X_AXIS[Y], X_AXIS[Z]);
        gl.glRotatef(cameraRotation[Y], Y_AXIS[X], Y_AXIS[Y], Y_AXIS[Z]);
        gl.glRotatef(cameraRotation[Z], Z_AXIS[X], Z_AXIS[Y], Z_AXIS[Z]);
    }


    /**
     * Draw scene consisting of floor and skeleton.
     *
     * @param gl GL object to draw to.
     */
    private void drawScene(final GL2 gl) {
        drawFloor(gl);
        drawSkeleton(gl);
    }

    /*
     * @see javax.media.opengl.GLEventListener#dispose(
     * javax.media.opengl.GLAutoDrawable)
     */
    @Override
    public void dispose(final GLAutoDrawable drawable) {
    }

    /**
     * Draw a single skeleton bone between specified two joints as a stretched
     * sphere.
     *
     * @param fromJointNumber
     *        Kinect skeleton data file joint index that is one end of the bone.
     * @param toJointNumber
     *        Kinect skeleton data file joint index that is other end of the
     *        bone.
     * @param gl
     *        GL object to draw with.
     */
    private void drawBone(final int fromJointNumber, final int toJointNumber,
            final GL2 gl) {
        final Vector3f fromJoint = kinectDataFile
                .getJointPosition(fromJointNumber);
        final Vector3f toJoint = kinectDataFile.getJointPosition(toJointNumber);
        drawBone(fromJoint, toJoint, gl);
    }

    /**
     * Draw a single skeleton bone between the two points as a stretched sphere.
     *
     * @param fromPoint
     *        Point that is one end of the bone.
     * @param toPoint
     *        Point that is the other end of the bone.
     * @param gl
     *        GL object to draw with.
     */
    private void drawBone(final Vector3f fromPoint, final Vector3f toPoint,
            final GL2 gl) {
        // Compute rotation
        final Vector3f sourceVector = new Vector3f(1.0f, 0.0f, 0.0f);
        final Vector3f destinationVector = new Vector3f();
        destinationVector.sub(toPoint, fromPoint);
        final float length = destinationVector.length();
        destinationVector.normalize();
        final Vector3f rotationVector = new Vector3f();
        rotationVector.cross(sourceVector, destinationVector);
        final float rotationAngle = (float) Math.toDegrees(sourceVector
                .angle(destinationVector));

        // Transform bone
        gl.glPushMatrix();
        gl.glTranslatef(fromPoint.x, fromPoint.y, fromPoint.z);
        gl.glRotatef(rotationAngle, rotationVector.x, rotationVector.y,
                rotationVector.z);
        gl.glTranslatef(length / 2.0f, 0.0f, 0.0f);
        gl.glScalef(length / BONE_THICKNESS, 1.0f, 1.0f);

        // Draw bone
        final GLUquadric quad = glu.gluNewQuadric();
        glu.gluQuadricNormals(quad, GLU_SMOOTH);
        gl.glMaterialfv(GL_FRONT, GL_AMBIENT, BONE_AMBIENT_REFLECTIVITY,
                PARAMETER_ARRAY_OFFSET);
        gl.glMaterialfv(GL_FRONT, GL_DIFFUSE, BONE_DIFFUSE_REFLECTIVITY,
                PARAMETER_ARRAY_OFFSET);
        final float sphereRadius = BONE_THICKNESS / 2.0f;
        glu.gluSphere(quad, sphereRadius, BONE_SLICES, BONE_SLABS);
        gl.glPopMatrix();
    }

    /**
     * Draw checkered floor plane parallel to the y-plane.
     *
     * @param gl
     *        GL object to draw with.
     */
    private void drawFloor(final GL2 gl) {
        final float width = FLOOR_TILE_SIZE * FLOOR_TILE_COLUMNS;
        final float height = FLOOR_TILE_SIZE * FLOOR_TILE_ROWS;
        final float minX = -width / 2.0f;
        final float minZ = -height / 2.0f;
        for (int rowCnt = 0; rowCnt < FLOOR_TILE_ROWS; rowCnt++) {
            for (int colCnt = 0; colCnt < FLOOR_TILE_COLUMNS; colCnt++) {
                final float x = minX + FLOOR_TILE_SIZE * colCnt;
                final float z = minZ + FLOOR_TILE_SIZE * rowCnt;
                if ((rowCnt + colCnt) % 2 == 0) {
                    drawFloorTile(x, z, FLOOR_TILE_SIZE, LIGHT_TILE_COLOR, gl);
                } else {
                    drawFloorTile(x, z, FLOOR_TILE_SIZE, DARK_TILE_COLOR, gl);
                }
            }
        }
    }

    /**
     * Draw a single floor tile as a quadrangle parallel to the y-plane.
     *
     * @param x
     *        The x-coordinate of forward left corner of the tile.
     * @param z
     *        The z-coordinate of the forward left corner of the tile.
     * @param tileSize
     *        The size of the tile, in meters.
     * @param color
     *        The color of the tile.
     * @param gl
     *        GL object to draw with.
     */
    private void drawFloorTile(final float x, final float z,
            final float tileSize, final float[] color, final GL2 gl) {
        gl.glBegin(GL_QUADS);
        gl.glMaterialfv(GL_FRONT, GL_AMBIENT, color, PARAMETER_ARRAY_OFFSET);
        gl.glMaterialfv(GL_FRONT, GL_DIFFUSE, BLACK, PARAMETER_ARRAY_OFFSET);
        gl.glNormal3f(0.0f, 1.0f, 0.0f);
        gl.glVertex3f(x, floorY, z);
        gl.glVertex3f(x + tileSize, floorY, z);
        gl.glVertex3f(x + tileSize, floorY, z + tileSize);
        gl.glVertex3f(x, floorY, z + tileSize);
        gl.glEnd();
    }

    /**
     * Draw the skeleton of current frame of the kinectDataFile.
     *
     * @param gl
     *        GL object to draw to.
     */
    private void drawSkeleton(final GL2 gl) {
        if (kinectDataFile == null) {
            return;
        }
        drawBone(KinectDataFile.HIP_CENTER, KinectDataFile.SPINE, gl);
        drawBone(KinectDataFile.SPINE, KinectDataFile.SHOULDER_CENTER, gl);
        drawBone(KinectDataFile.SHOULDER_CENTER, KinectDataFile.HEAD, gl);
        drawBone(KinectDataFile.SHOULDER_CENTER, KinectDataFile.SHOULDER_LEFT,
                gl);
        drawBone(KinectDataFile.SHOULDER_LEFT, KinectDataFile.ELBOW_LEFT, gl);
        drawBone(KinectDataFile.ELBOW_LEFT, KinectDataFile.WRIST_LEFT, gl);
        drawBone(KinectDataFile.WRIST_LEFT, KinectDataFile.HAND_LEFT, gl);
        drawBone(KinectDataFile.SHOULDER_CENTER, KinectDataFile.SHOULDER_RIGHT,
                gl);
        drawBone(KinectDataFile.SHOULDER_RIGHT, KinectDataFile.ELBOW_RIGHT, gl);
        drawBone(KinectDataFile.ELBOW_RIGHT, KinectDataFile.WRIST_RIGHT, gl);
        drawBone(KinectDataFile.WRIST_RIGHT, KinectDataFile.HAND_RIGHT, gl);
        drawBone(KinectDataFile.HIP_CENTER, KinectDataFile.HIP_LEFT, gl);
        drawBone(KinectDataFile.HIP_LEFT, KinectDataFile.KNEE_LEFT, gl);
        drawBone(KinectDataFile.KNEE_LEFT, KinectDataFile.ANKLE_LEFT, gl);
        drawBone(KinectDataFile.ANKLE_LEFT, KinectDataFile.FOOT_LEFT, gl);
        drawBone(KinectDataFile.HIP_CENTER, KinectDataFile.HIP_RIGHT, gl);
        drawBone(KinectDataFile.HIP_RIGHT, KinectDataFile.KNEE_RIGHT, gl);
        drawBone(KinectDataFile.KNEE_RIGHT, KinectDataFile.ANKLE_RIGHT, gl);
        drawBone(KinectDataFile.ANKLE_RIGHT, KinectDataFile.FOOT_RIGHT, gl);
    }

    /*
     * Initialize OpenGL.
     *
     * @see javax.media.opengl.GLEventListener#init(
     * javax.media.opengl.GLAutoDrawable)
     */
    @Override
    public final void init(final GLAutoDrawable drawable) {
        final GL2 gl = drawable.getGL().getGL2();
        glu = new GLU();
        gl.glClearColor(BACKGROUND_COLOR[RED], BACKGROUND_COLOR[GREEN],
                BACKGROUND_COLOR[BLUE], BACKGROUND_COLOR[ALPHA]);
        gl.glClearDepth(Z_BUFFER_CLEAR_DEPTH);
        gl.glEnable(GL_DEPTH_TEST);
        gl.glDepthFunc(GL_LEQUAL);
        gl.glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
        gl.glShadeModel(GL_SMOOTH);
        gl.glLightfv(GL_LIGHT0, GL_AMBIENT, LIGHT_AMBIENT_EMISSION,
                PARAMETER_ARRAY_OFFSET);
        gl.glLightfv(GL_LIGHT0, GL_DIFFUSE, LIGHT_DIFFUSE_EMISSION,
                PARAMETER_ARRAY_OFFSET);
        gl.glLightfv(GL_LIGHT0, GL_POSITION, LIGHT_POSITION,
                PARAMETER_ARRAY_OFFSET);
        gl.glEnable(GL_LIGHTING);
        gl.glEnable(GL_LIGHT0);
    }

    /*
     * Update the OpenGL viewport when the panel is resized.
     *
     * @see javax.media.opengl.GLEventListener#reshape(
     * javax.media.opengl.GLAutoDrawable, int, int, int, int)
     */
    @Override
    public final void reshape(final GLAutoDrawable drawable, final int x,
            final int y, final int width, final int height) {
        final GL2 gl = drawable.getGL().getGL2();
        float aspectRatio;
        if (height == 0) {
            aspectRatio = width;
        } else {
            aspectRatio = (float) width / height;
        }
        gl.glViewport(0, 0, width, height);
        gl.glMatrixMode(GL_PROJECTION);
        gl.glLoadIdentity();
        glu.gluPerspective(Y_FIELD_OF_VIEW, aspectRatio,
                NEAR_CLIPPING_DISTANCE, FAR_CLIPPING_DISTANCE);
        gl.glMatrixMode(GL_MODELVIEW);
    }

    /**
     * Set the Kinect skeleton data file to use when rendering.
     *
     * @param newKinectDataFile
     *        The Kinect data file to use when rendering.
     */
    public final void setKinectDataFile(
            final KinectDataFile newKinectDataFile) {
        kinectDataFile = newKinectDataFile;
        floorY = Float.POSITIVE_INFINITY;
        final int numberOfFrames = kinectDataFile.getNumberOfFrames();
        for (int frame = 0; frame < numberOfFrames; frame++) {
            kinectDataFile.setCurrentFrameNumber(frame);
            final Vector3f rightFoot = kinectDataFile
                .getJointPosition(KinectDataFile.FOOT_RIGHT);
            if (rightFoot.y < floorY) {
                floorY = rightFoot.y;
            }
            final Vector3f leftFoot = kinectDataFile
                .getJointPosition(KinectDataFile.FOOT_LEFT);
            if (leftFoot.y < floorY) {
                floorY = leftFoot.y;
            }
        }
        kinectDataFile.setCurrentFrameNumber(0);
    }

    /**
     * Stop the animation.
     */
    public final void stop() {
        animator.stop();
    }

    /**
     * Class to handle mouse press, release, and drag events.
     */
    private class MouseEventHandler extends MouseAdapter {
        /*
         * Update the current mouse location for mouse movement calculations.
         *
         * @see java.awt.event.MouseListener#mousePressed(
         * java.awt.event.MouseEvent)
         */
        @Override
        public final void mousePressed(final MouseEvent event) {
            mouseLocation = event.getPoint();
        }

        /*
         * Update the camera when the mouse is dragged. An alt and shift drag
         * rotates the view and an alt or shift drag translates the view.
         *
         * @see java.awt.event.MouseMotionListener#mouseDragged(
         * java.awt.event.MouseEvent)
         */
        @Override
        public final void mouseDragged(final MouseEvent event) {
            final Point currentMouseLocation = event.getPoint();
            final int mouseDeltaX = currentMouseLocation.x - mouseLocation.x;
            final int mouseDeltaY = currentMouseLocation.y - mouseLocation.y;
            final boolean isShiftDown = event.isShiftDown();
            // final boolean isAltDown = event.isAltDown();
            final boolean isAltDown = event.isControlDown();
            if (isShiftDown && !isAltDown) {
                cameraTranslation[X] += mouseDeltaX
                        * MOUSE_TRANSLATION_SCALE_FACTOR;
                cameraTranslation[Y] -= mouseDeltaY
                        * MOUSE_TRANSLATION_SCALE_FACTOR;
            } else if (!isShiftDown && isAltDown) {
                cameraTranslation[X] += mouseDeltaX
                        * MOUSE_TRANSLATION_SCALE_FACTOR;
                cameraTranslation[Z] += mouseDeltaY
                        * MOUSE_TRANSLATION_SCALE_FACTOR;
            } else if (isShiftDown && isAltDown) {
                cameraRotation[Y] += mouseDeltaX * MOUSE_ROTATION_SCALE_FACTOR;
                cameraRotation[X] += mouseDeltaY * MOUSE_ROTATION_SCALE_FACTOR;
            }
            mouseLocation = currentMouseLocation;
        }


    }

}
