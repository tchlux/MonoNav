package edu.roanoke.manualsegmentation;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.GradientPaint;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.geom.Point2D;
import java.awt.geom.Rectangle2D;
import java.util.ArrayList;

import javax.swing.JPanel;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;

/**
 * A panel that allows the user change the current frame and select a range of
 * frames of a Kinect skeleton data file. Clicking and dragging will set the
 * current frame. Shift-dragging will select sub-portions. Alt-dragging zooms in
 * and out.
 */
@SuppressWarnings("serial")
public class SliderPanel extends JPanel {

    /** Color of the top of the slider gradient. */
    private static final Color SLIDER_TOP_BACKGROUND_COLOR = Color.white;

    /** Color of the bottom of the slider gradient. */
    private static final Color SLIDER_BOTTOM_BACKGROUND_COLOR = Color.gray;

    /** Color of the top of the selection gradient. */
    private static final Color SLIDER_TOP_SELECTION_COLOR = Color.white;

    /** Color of the bottom of the selection gradient. */
    private static final Color SLIDER_BOTTOM_SELECTION_COLOR = Color.yellow;

    /** Amount to multiply mouse movement by when zooming. */
    private static final double RESIZE_SCALE_FACTOR = 2.0;

    /** Color of the slider head. */
    private static final Color SLIDER_HEAD_COLOR = Color.red;

    /** Number of pixels wide the selection boundaries are. */
    private static final int SELECTION_SIZE = 3;

    /** X-coordinate of the mouse when dragging. */
    private int previousMouseX = -1;

    /** The Kinect data file the the slider controls. */
    private KinectDataFile kinectDataFile = null;

    /** List of change listeners to notify when slider head moves. */
    private final ArrayList<ChangeListener> listeners;

    /**
     * Initialize slider panel.
     */
    public SliderPanel() {
        final MouseEventHandler mouseEventHandler = new MouseEventHandler();
        addMouseListener(mouseEventHandler);
        addMouseMotionListener(mouseEventHandler);
        listeners = new ArrayList<ChangeListener>();
    }

    /**
     * Add listener for changes in the slider's head location.
     *
     * @param listener The change listener to add.
     */
    public final void addChangeListener(final ChangeListener listener) {
        listeners.add(listener);
    }

    /**
     * Draw the slider background as a rectangle with a gradient and outline.
     *
     * @param graphics
     *        The graphics object to draw to.
     */
    private void drawBackground(final Graphics2D graphics) {
        final double panelWidth = getWidth();
        final double rectLeft = 0.0;
        final double rectRight = panelWidth;
        drawRectangle(rectLeft, rectRight, SLIDER_TOP_BACKGROUND_COLOR,
                SLIDER_BOTTOM_BACKGROUND_COLOR, graphics);
    }

    /**
     * Draw the slider head as a filled rectangle.
     *
     * @param graphics
     *        The graphics object to draw to.
     */
    private void drawHead(final Graphics2D graphics) {
        if (kinectDataFile == null) {
            return;
        }
        double headWidth = frameToX(1);
        headWidth = Math.max(headWidth, 1.0);
        final double panelWidth = getWidth();
        final double panelHeight = getHeight();
        final int currentFrameNumber = kinectDataFile.getCurrentFrameNumber();
        final double headCenterX = frameToX(currentFrameNumber);
        double headX = headCenterX - headWidth / 2.0;
        final double minHeadX = 0.0;
        final double maxHeadX = panelWidth - headWidth;
        headX = Math.max(minHeadX, Math.min(maxHeadX, headX));
        graphics.setColor(SLIDER_HEAD_COLOR);
        final Rectangle2D headRectangle = new Rectangle2D.Double(headX, 0.0,
                headWidth, panelHeight);
        graphics.fill(headRectangle);
    }

    /**
     * Draw a rectangle that takes up the entire height of the panel with a
     * gradient and outline.
     *
     * @param rectLeft
     *        The x-coordinate of the left edge of the rectangle.
     * @param rectRight
     *        The x-coordinate of the right edge of the rectangle.
     * @param topColor
     *        The color of the top of the rectangle.
     * @param bottomColor
     *        The color of the bottom of the rectangle.
     * @param graphics
     *        The graphics object to draw to.
     */
    private void drawRectangle(final double rectLeft, final double rectRight,
            final Color topColor, final Color bottomColor,
            final Graphics2D graphics) {
        final double rectangleWidth = rectRight - rectLeft;
        final Point2D.Double topPoint = new Point2D.Double(0.0, 0.0);
        final double panelHeight = getHeight();
        final Point2D.Double bottomPoint = new Point2D.Double(0.0, panelHeight);
        final GradientPaint gradientPaint = new GradientPaint(topPoint,
                topColor, bottomPoint, bottomColor);
        graphics.setPaint(gradientPaint);
        final Rectangle2D rectangle = new Rectangle2D.Double(rectLeft, 0.0,
                rectangleWidth - 1.0, panelHeight - 1.0);
        graphics.fill(rectangle);
        graphics.setColor(bottomColor);
        graphics.draw(rectangle);
    }

    /**
     * Draw the current selection as a rectangle with gradient and outline.
     *
     * @param graphics
     *        The graphics object to draw to.
     */
    private void drawSelection(final Graphics2D graphics) {
        if (kinectDataFile == null || !kinectDataFile.isSelection()) {
            return;
        }
        int selectionStartFrame = kinectDataFile.getSelectionStartFrameNumber();
        int selectionEndFrame = kinectDataFile.getSelectionEndFrameNumber();
        double selectionStartX = frameToX(selectionStartFrame);
        double selectionEndX = frameToX(selectionEndFrame);
        double rectLeft = Math.min(selectionStartX, selectionEndX);
        double rectRight = Math.max(selectionStartX, selectionEndX);
        drawRectangle(rectLeft, rectRight, SLIDER_TOP_SELECTION_COLOR,
                SLIDER_BOTTOM_SELECTION_COLOR, graphics);
    }

    /**
     * Convert the specified frame number to an x-coordinate in the slider
     * panel.
     *
     * @param frame
     *        The frame number to convert.
     * @return The x-coordinate of the specified frame.
     */
    private int frameToX(final int frame) {
        final int panelWidth = getWidth();
        final int numberOfFrames = kinectDataFile.getNumberOfFrames();
        return (int) ((double) frame / numberOfFrames * panelWidth);
    }

    /**
     * Resize the panel to zoom in or out based on mouse movement.
     *
     * @param mouseX The current mouse location.
     */
    private void zoomSlider(final int mouseX) {
        int panelWidth = getWidth();
        final int panelHeight = getHeight();
        final int dragDistance = mouseX - previousMouseX;
        previousMouseX = mouseX;
        panelWidth += (int) (dragDistance * RESIZE_SCALE_FACTOR);
        setPreferredSize(new Dimension(panelWidth, panelHeight));
        revalidate();
    }

    /**
     * Move the slider head based on the current mouse location.
     *
     * @param mouseX The current mouse location.
     */
    private void moveHead(final int mouseX) {
        final int frame = xToFrame(mouseX);
        kinectDataFile.setCurrentFrameNumber(frame);
        kinectDataFile.setSelectionEndFrameNumber(frame);
        repaint();
        notifyListeners();
    }

    /**
     * Notify slider change listeners that the head has moved.
     */
    private void notifyListeners() {
        ChangeEvent changeEvent = new ChangeEvent(this);
        for (ChangeListener listener : listeners) {
            listener.stateChanged(changeEvent);
        }
    }

    /**
     * If alt is down, resize the panel to zoom in or out. If the alt is not
     * down, set the current frame number.
     *
     * @param mouseX The current mouse x-coordinate.
     * @param isAltDown Whether the alt key is currently pressed.
     */
    private void updateSlider(final int mouseX, final boolean isAltDown) {
        if (isAltDown) {
            zoomSlider(mouseX);
        } else {
            moveHead(mouseX);
        }
    }

    private void updateBoundaries(final int mouseX, final boolean isAltDown) {
        if (isAltDown) {
            return;
        }
        final int frame = xToFrame(mouseX);
        final int lowFrameNumber = xToFrame(mouseX - SELECTION_SIZE);
        final int highFrameNumber = xToFrame(mouseX + SELECTION_SIZE);
        final int selectionStartFrameNumber = kinectDataFile.getSelectionStartFrameNumber();
        final int selectionEndFrameNumber = kinectDataFile.getSelectionEndFrameNumber();
        final boolean isSelectionStart = selectionStartFrameNumber >= lowFrameNumber &&
            selectionStartFrameNumber <= highFrameNumber;
        final boolean isSelectionEnd = selectionEndFrameNumber >= lowFrameNumber &&
            selectionEndFrameNumber <= highFrameNumber;
        if (isSelectionStart) {
            kinectDataFile.setSelectionStartFrameNumber(selectionEndFrameNumber);
            kinectDataFile.setSelectionEndFrameNumber(selectionStartFrameNumber);
        }
        if (!isSelectionStart && !isSelectionEnd) {
            kinectDataFile.setSelectionStartFrameNumber(frame);
        }
    }

    /*
     * Draw the timeline, segment boundaries, head position, and current
     * selection.
     *
     * @see javax.swing.JComponent#paintComponent(java.awt.Graphics)
     */
    @Override
    public final void paintComponent(final Graphics g) {
        super.paintComponent(g);
        final Graphics2D g2 = (Graphics2D) g;
        drawBackground(g2);
        drawSelection(g2);
        drawHead(g2);
    }

    /**
     * Set the Kinect skeleton data file to control.
     *
     * @param newKinectDataFile
     *        The Kinect data file to control.
     */
    public final void setKinectDataFile(
            final KinectDataFile newKinectDataFile) {
        this.kinectDataFile = newKinectDataFile;
        repaint();
    }

    /**
     * Convert the specified x-coordinate in the panel to a frame number.
     *
     * @param x
     *        The x-coordinate to convert.
     * @return The frame number of the specified x-coordinate.
     */
    public final int xToFrame(final int x) {
        final int panelWidth = getWidth();
        final int numberOfFrames = kinectDataFile.getNumberOfFrames();
        return (int) ((double) x / panelWidth * numberOfFrames);
    }

    /**
     * Class to handle mouse press, release, and drag events.
     */
    private class MouseEventHandler extends MouseAdapter {
        /*
         * When the mouse is pressed, set the current frame number.
         *
         * @see java.awt.event.MouseListener#mousePressed(
         * java.awt.event.MouseEvent)
         */
        @Override
        public final void mousePressed(final MouseEvent event) {
            final int mouseX = event.getX();
            // final int frame = xToFrame(mouseX);
            // final boolean isAltDown = event.isAltDown();
            final boolean isAltDown = event.isControlDown();
            updateBoundaries(mouseX, isAltDown);
            updateSlider(mouseX, isAltDown);
        }

        /*
         * When the mouse is released, set the current frame number.
         *
         * @see java.awt.event.MouseListener#mouseReleased(
         * java.awt.event.MouseEvent)
         */
        @Override
        public final void mouseReleased(final MouseEvent event) {
            final int mouseX = event.getX();
            // final boolean isAltDown = event.isAltDown();
            final boolean isAltDown = event.isControlDown();
            updateSlider(mouseX, isAltDown);
        }

        /*
         * If alt is down, resize the panel to zoom in or out. If the alt is not
         * down, set the current frame number.
         *
         * @see java.awt.event.MouseMotionListener#mouseDragged(
         * java.awt.event.MouseEvent)
         */
        @Override
        public final void mouseDragged(final MouseEvent event) {
            final int mouseX = event.getX();
            // final boolean isAltDown = event.isAltDown();
            final boolean isAltDown = event.isControlDown();
            updateSlider(mouseX, isAltDown);
        }
    }
}
