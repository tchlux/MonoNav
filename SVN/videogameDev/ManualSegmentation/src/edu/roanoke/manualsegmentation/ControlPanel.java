package edu.roanoke.manualsegmentation;

import java.awt.Dimension;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JComponent;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.ScrollPaneConstants;
import javax.swing.SwingConstants;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;

/**
 * Panel containing controls and information for Manual Segmentation frame
 * including time-line slider, play/pause button, forward/backward buttons, time
 * label, and frame label.
 *
 * @author durell
 */
@SuppressWarnings("serial")
public class ControlPanel extends JPanel implements ActionListener, Runnable,
ChangeListener {

    /**
     * Action to perform when left arrow key is pressed.
     */
    /*
    private class BackwardAction extends AbstractAction {
        @Override
        public void actionPerformed(final ActionEvent actionEvent) {
            backwardButton.doClick();
        }
    }
     */
    /**
     * Action to perform when the right arrow key is pressed.
     */
    /*
    private class ForwardAction extends AbstractAction {
        @Override
        public void actionPerformed(final ActionEvent actionEvent) {
            forwardButton.doClick();
        }
    }
     */
    /**
     * Action to perform when the space bar is pressed.
     */
    /*
    private class PlayPauseAction extends AbstractAction {
        @Override
        public void actionPerformed(final ActionEvent actionEvent) {
            playPauseButton.doClick();
        }
    }
     */
    /** Initial width of this panel, in pixels. */
    private static final int CONTROL_PANEL_WIDTH = 640;

    /** Initial height of this panel, in pixels. */
    private static final int CONTROL_PANEL_HEIGHT = 60;

    /** Play animation frames per second. */
    private static final int FRAMES_PER_SECOND = 30;

    /** Number of milliseconds in one second. */
    private static final int MILLISECONDS_PER_SECOND = 1000;

    /** Amount of time, in milliseconds, between each frame. */
    private static final int TARGET_ELAPSED_TIME = MILLISECONDS_PER_SECOND
            / FRAMES_PER_SECOND;

    /** Time label text. */
    private static final String TIME_LABEL_TEXT = "Time: ";

    /** Frame label text. */
    private static final String FRAME_LABEL_TEXT = "Frame: ";

    /** Play button text. */
    private static final String PLAY_BUTTON_TEXT = "Play";

    /** Pause button text. */
    private static final String PAUSE_BUTTON_TEXT = "Pause";

    /** Back button text. */
    private static final String BACK_BUTTON_TEXT = "Backward";

    /** Forward button text. */
    private static final String FORWARD_BUTTON_TEXT = "Forward";

    /** Button width. */
    private static final int BUTTON_WIDTH = 100;

    /** Button width. */
    private static final int BUTTON_HEIGHT = 24;

    /** Kinect skeleton data file to control. */
    private KinectDataFile kinectDataFile = null;

    /** Slider to specify current frame, and select frames. */
    private SliderPanel sliderPanel;

    /** Button to retreat current frame by one. */
    private JButton backwardButton;

    /** Button to play animation in kinectDataFile. */
    private JButton playPauseButton;

    /** Button to advance current frame by one. */
    private JButton forwardButton;

    /** Label for current time. */
    private final JLabel timeLabel;

    /** Label for current frame. */
    private final JLabel frameLabel;

    /** Thread for animation when playing. */
    private Thread animationThread;

    /** Animation run loop control variable. */
    private boolean running = false;

    /**
     * Initialize control panel.
     */
    public ControlPanel() {
        // TODO: get rid of control panel size magic numbers by calculating
        // sizes
        // Initialize this control panel
        final Dimension preferredSize = new Dimension();
        preferredSize.width = CONTROL_PANEL_WIDTH;
        preferredSize.height = CONTROL_PANEL_HEIGHT;
        setPreferredSize(preferredSize);
        setLayout(new GridBagLayout());

        // Add slider panel
        final GridBagConstraints constraints = new GridBagConstraints();
        constraints.anchor = GridBagConstraints.CENTER;
        constraints.fill = GridBagConstraints.BOTH;
        constraints.weightx = 1.0;
        constraints.weighty = 1.0;
        constraints.gridx = 0;
        constraints.gridy = 0;
        constraints.gridwidth = 3;
        final JComponent topPane = initializeSliderPanel();
        add(topPane, constraints);

        // Add frame label
        constraints.weighty = 0.0;
        constraints.gridwidth = 1;
        constraints.gridx = 0;
        constraints.gridy = 1;
        timeLabel = new JLabel(TIME_LABEL_TEXT, SwingConstants.CENTER);
        add(timeLabel, constraints);

        // Add button label
        JComponent buttonPanel = initializeButtonPanel();
        constraints.gridx = 1;
        add(buttonPanel, constraints);

        // Add time label
        constraints.gridx = 2;
        frameLabel = new JLabel(FRAME_LABEL_TEXT, SwingConstants.CENTER);
        add(frameLabel, constraints);

    }

    /**
     * Initialize the slider panel inside a scroll pane.
     *
     * @return The scroll pane that contains the slider panel.
     */
    private JComponent initializeSliderPanel() {
        sliderPanel = new SliderPanel();
        sliderPanel.addChangeListener(this);
        final JScrollPane scrollPane = new JScrollPane();
        final int horizontalScollPolicy =
                ScrollPaneConstants.HORIZONTAL_SCROLLBAR_AS_NEEDED;
        final int verticalScrollPolicy =
                ScrollPaneConstants.VERTICAL_SCROLLBAR_NEVER;
        scrollPane.setHorizontalScrollBarPolicy(horizontalScollPolicy);
        scrollPane.setVerticalScrollBarPolicy(verticalScrollPolicy);
        scrollPane.setViewportView(sliderPanel);
        return scrollPane;
    }

    /**
     * Initialize the button panel containing the forward, backward, and
     * play/pause buttons.
     *
     * @return The panel containing the buttons.
     */
    private JComponent initializeButtonPanel() {
        // Initialize panel
        final JPanel buttonPanel = new JPanel();
        buttonPanel.setLayout(new GridBagLayout());
        final GridBagConstraints buttonPanelConstraints =
                new GridBagConstraints();

        // Add back button
        buttonPanelConstraints.anchor = GridBagConstraints.CENTER;
        buttonPanelConstraints.fill = GridBagConstraints.HORIZONTAL;
        buttonPanelConstraints.gridy = 0;
        buttonPanelConstraints.gridx = 0;
        backwardButton = new JButton(BACK_BUTTON_TEXT);
        Dimension buttonPreferredSize = new Dimension(BUTTON_WIDTH,
                BUTTON_HEIGHT);
        backwardButton.setPreferredSize(buttonPreferredSize);
        backwardButton.addActionListener(this);
        backwardButton.setFocusable(false);
        buttonPanel.add(backwardButton, buttonPanelConstraints);

        // Add play/pause button
        buttonPanelConstraints.gridx = 1;
        playPauseButton = new JButton(PLAY_BUTTON_TEXT);
        playPauseButton.setPreferredSize(buttonPreferredSize);
        playPauseButton.addActionListener(this);
        playPauseButton.setFocusable(false);
        buttonPanel.add(playPauseButton, buttonPanelConstraints);

        // Add forward button
        buttonPanelConstraints.gridx = 2;
        forwardButton = new JButton(FORWARD_BUTTON_TEXT);
        forwardButton.setPreferredSize(buttonPreferredSize);
        forwardButton.addActionListener(this);
        forwardButton.setFocusable(false);
        buttonPanel.add(forwardButton, buttonPanelConstraints);

        return buttonPanel;
    }

    /**
     * Handle button presses.
     *
     * @param actionEvent
     *        Event that triggered function call.
     */
    @Override
    public final void actionPerformed(final ActionEvent actionEvent) {
        final Object actionSource = actionEvent.getSource();
        if (actionSource == backwardButton) {
            final int currentFrameNumber = kinectDataFile
                    .getCurrentFrameNumber();
            kinectDataFile.setCurrentFrameNumber(currentFrameNumber - 1);
            sliderPanel.repaint();
        } else if (actionSource == playPauseButton) {
            if (playPauseButton.getText().equals(PLAY_BUTTON_TEXT)) {
                playPauseButton.setText(PAUSE_BUTTON_TEXT);
                animationThread = new Thread(this);
                animationThread.start();
            } else {
                animationThread.interrupt();
            }
        } else if (actionSource == forwardButton) {
            final int currentFrameNumber = kinectDataFile
                    .getCurrentFrameNumber();
            kinectDataFile.setCurrentFrameNumber(currentFrameNumber + 1);
            sliderPanel.repaint();
        }
    }

    /**
     * Update the frame and time labels based on the current frame.
     */
    private void updateLabels() {
        int currentFrame = kinectDataFile.getCurrentFrameNumber();
        frameLabel.setText(FRAME_LABEL_TEXT + currentFrame);
        final double time = (double) currentFrame / FRAMES_PER_SECOND;
        final String timeString = String.format("%.2f", time);
        timeLabel.setText(TIME_LABEL_TEXT + timeString);
    }

    /*
     * When the animation thread is started, repeatedly update the current frame
     * and the slider head position.
     *
     * @see java.lang.Runnable#run()
     */
    @Override
    public final void run() {
        if (kinectDataFile == null) {
            return;
        }
        if (kinectDataFile.isCurrentFrameAtEnd()) {
            kinectDataFile.setCurrentFrameToStart();
        }
        long currentTime = System.currentTimeMillis();
        int elapsedTime = 0;
        running = true;
        while (running) {
            final long previousTime = currentTime;
            currentTime = System.currentTimeMillis();
            elapsedTime += (int) (currentTime - previousTime);
            final int elapsedFrames = elapsedTime / TARGET_ELAPSED_TIME;
            int currentFrameNumber = kinectDataFile.getCurrentFrameNumber();
            currentFrameNumber += elapsedFrames;
            kinectDataFile.setCurrentFrameNumber(currentFrameNumber);
            updateLabels();
            elapsedTime -= elapsedFrames * TARGET_ELAPSED_TIME;
            if (kinectDataFile.isCurrentFrameAtEnd()) {
                running = false;
            }
            sliderPanel.repaint();
            int sleepTime = TARGET_ELAPSED_TIME - elapsedTime;
            if (sleepTime < 0) {
                sleepTime = 0;
            }
            try {
                Thread.sleep(sleepTime);
            } catch (final InterruptedException exception) {
                running = false;
            }
        }
        playPauseButton.setText(PLAY_BUTTON_TEXT);
    }

    /**
     * Set the Kinect skeleton data file to control.
     *
     * @param newKinectDataFile
     *        The Kinect data file to control.
     */
    public final void setKinectDataFile(
            final KinectDataFile newKinectDataFile) {
        kinectDataFile = newKinectDataFile;
        sliderPanel.setKinectDataFile(kinectDataFile);
    }

    /*
     * Update the frame and time labels when the slider head moves.
     *
     * @see javax.swing.event.ChangeListener#stateChanged(
     * javax.swing.event.ChangeEvent)
     */
    @Override
    public final void stateChanged(final ChangeEvent changeEvent) {
        updateLabels();
    }

}
