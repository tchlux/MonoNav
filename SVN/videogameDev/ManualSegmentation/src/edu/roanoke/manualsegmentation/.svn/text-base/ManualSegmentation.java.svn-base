/**
 * Graphical program for manual segmenting kinect motion data files.
 */

package edu.roanoke.manualsegmentation;

import java.awt.Dimension;
import java.awt.EventQueue;
import java.awt.Menu;
import java.awt.MenuBar;
import java.awt.MenuItem;
import java.awt.MenuShortcut;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.io.File;
import java.io.IOException;

import javax.swing.JFileChooser;
import javax.swing.JFrame;
import javax.swing.JOptionPane;
import javax.swing.JSplitPane;

/**
 * Program main window, contains OpenGL rendering of skeleton and slider for
 * selecting sub-sequences.
 *
 * @author durell
 */
@SuppressWarnings("serial")
public class ManualSegmentation extends JFrame implements ActionListener {

    /**
     * Window closing listener that closes the entire application when the
     * window is closed.
     */
    class ExitOnCloseWindowListener extends WindowAdapter {

        /*
         * Close application in response to window closing.
         *
         * @see java.awt.event.WindowAdapter#windowClosing(
         * java.awt.event.WindowEvent)
         */
        @Override
        public void windowClosing(final WindowEvent windowEvent) {
            quit();
        }
    }

    /** Main window title. */
    private static final String WINDOW_TITLE = "Manual Segmentation";

    /** Text for file open error dialog window. */
    private static final String OPEN_ERROR_TEXT = "Could not open file \"%s\".";

    /** Text for file save error dialog window. */
    private static final String SAVE_ERROR_TEXT = "Could not save file \"%s\".";

    /** Text for save error dialog window when no segment is selected. */
    private static final String SELECTION_ERROR_TEXT = "Could not save file. "
            + "No frames are currently selected.";

    /** File to load when program first starts. */
    private static final String DEFAULT_FILE_NAME =
        "res/KinectPositionRotationData.txt";

    /** Text of file menu. */
    private static final String FILE_MENU_TEXT = "File";

    /** Text of open menu item. */
    private static final String OPEN_MENU_TEXT = "Open";

    /** Text of save menu item. */
    private static final String SAVE_MENU_TEXT = "Save";

    /** Text of quit menu item. */
    private static final String QUIT_MENU_TEXT = "Quit";

    /**
     * Run the program by creating a new window.
     *
     * @param args
     *        Command line arguments, unused.
     */
    public static void main(final String[] args) {
        EventQueue.invokeLater(new Runnable() {
            @Override
            public void run() {
                final ManualSegmentation mainFrame = new ManualSegmentation();
                mainFrame.setVisible(true);
            }
        });
    }

    /** Panel containing OpenGL rendering of skeleton. */
    private RenderPanel renderPanel;

    /** Panel containing slider and play/pause button. */
    private ControlPanel controlPanel;

    /**  */
    private KinectDataFile kinectDataFile;

    /**
     *
     */
    public ManualSegmentation() {
        initFrame();
        initMenu();
        setKinectDataFile();
    }

    /*
     * Handle menu item selection.
     *
     * @see java.awt.event.ActionListener#actionPerformed(
     * java.awt.event.ActionEvent)
     */
    @Override
    public final void actionPerformed(final ActionEvent e) {
        final String menuItem = e.getActionCommand();
        if (menuItem == OPEN_MENU_TEXT) {
            openFile();
        }
        if (menuItem == SAVE_MENU_TEXT) {
            saveFile();
        }
        if (menuItem == QUIT_MENU_TEXT) {
            quit();
        }
    }

    /**
     * Initialize the main window to contain the skeleton render and slider
     * control panel.
     */
    private void initFrame() {
        final ExitOnCloseWindowListener exitOnCloseWindowListener;
        renderPanel = new RenderPanel();
        controlPanel = new ControlPanel();
        final JSplitPane splitPane = new JSplitPane();
        splitPane.setOrientation(JSplitPane.VERTICAL_SPLIT);
        splitPane.setLeftComponent(renderPanel);
        splitPane.setRightComponent(controlPanel);
        final Dimension renderPanelSize = renderPanel.getPreferredSize();
        final Dimension controlPanelSize = controlPanel.getPreferredSize();
        final Dimension splitPaneSize = new Dimension();
        final int renderPanelWidth = renderPanelSize.width;
        final int renderPanelHeight = renderPanelSize.height;
        final int controlPanelWidth = controlPanelSize.width;
        final int controlPanelHeight = controlPanelSize.height;
        splitPaneSize.width = Math.max(renderPanelWidth, controlPanelWidth);
        splitPaneSize.height = renderPanelHeight + controlPanelHeight;
        splitPane.setPreferredSize(splitPaneSize);
        final int splitPaneHeight = splitPaneSize.height;
        final double splitWeight = (double) renderPanelHeight / splitPaneHeight;
        splitPane.setResizeWeight(splitWeight);
        splitPane.setDividerSize(0);
        setContentPane(splitPane);
        exitOnCloseWindowListener = new ExitOnCloseWindowListener();
        addWindowListener(exitOnCloseWindowListener);
        setTitle(WINDOW_TITLE);
        pack();
        setLocationRelativeTo(null);
    }

    /**
     * Initialize the menu bar to contain a file menu.
     */
    private void initMenu() {
        final MenuBar menuBar = new MenuBar();
        final Menu fileMenu = new Menu(FILE_MENU_TEXT);
        final MenuItem openMenuItem = new MenuItem(OPEN_MENU_TEXT);
        final MenuShortcut openMenuShortcut = new MenuShortcut(KeyEvent.VK_O);
        openMenuItem.setShortcut(openMenuShortcut);
        openMenuItem.addActionListener(this);
        fileMenu.add(openMenuItem);
        final MenuItem saveMenuItem = new MenuItem(SAVE_MENU_TEXT);
        final MenuShortcut saveMenuShortcut = new MenuShortcut(KeyEvent.VK_S);
        saveMenuItem.setShortcut(saveMenuShortcut);
        saveMenuItem.addActionListener(this);
        fileMenu.add(saveMenuItem);
        final MenuItem quitMenuItem = new MenuItem(QUIT_MENU_TEXT);
        final MenuShortcut quitMenuShortcut = new MenuShortcut(KeyEvent.VK_Q);
        quitMenuItem.setShortcut(quitMenuShortcut);
        quitMenuItem.addActionListener(this);
        fileMenu.add(quitMenuItem);
        menuBar.add(fileMenu);
        setMenuBar(menuBar);
    }

    /**
     * Prompt the user to select a Kinect skeleton data file and open the
     * specified file.
     */
    private void openFile() {
        final JFileChooser fileChooser = new JFileChooser();
        final int fileChooserState = fileChooser.showOpenDialog(this);
        if (fileChooserState == JFileChooser.APPROVE_OPTION) {
            final File openFile = fileChooser.getSelectedFile();
            final String filePath = openFile.getAbsolutePath();
            setKinectDataFile(filePath);
        }
    }

    /**
     * Clean up OpenGL resources and close the program.
     */
    private void quit() {
        renderPanel.stop();
        dispose();
        System.exit(0);
    }

    /**
     * Prompt the user to enter a file name and save the currently selected
     * frames to a new file.
     */
    private void saveFile() {
        if (!kinectDataFile.isSelection()) {
            JOptionPane.showMessageDialog(this, SELECTION_ERROR_TEXT);
            return;
        }
        final JFileChooser fileChooser = new JFileChooser();
        final int fileChooserState = fileChooser.showSaveDialog(this);
        if (fileChooserState == JFileChooser.APPROVE_OPTION) {
            final File saveFile = fileChooser.getSelectedFile();
            final String filePath = saveFile.getAbsolutePath();
            try {
                kinectDataFile.writeFile(filePath);
            } catch (final IOException ioException) {
                final String messageText = String.format(SAVE_ERROR_TEXT,
                        filePath);
                JOptionPane.showMessageDialog(this, messageText);
            }
        }
    }

    /**
     * Set the currently displayed Kinect skeleton data file to the default
     * file.
     */
    public final void setKinectDataFile() {
        setKinectDataFile(DEFAULT_FILE_NAME);
    }

    /**
     * Set the currently displayed Kinect skeleton data file to the specified
     * file.
     *
     * @param newKinectDataFile
     *        A Kinect skeleton data file.
     */
    public final void setKinectDataFile(
            final KinectDataFile newKinectDataFile) {
        kinectDataFile = newKinectDataFile;
        renderPanel.setKinectDataFile(kinectDataFile);
        controlPanel.setKinectDataFile(kinectDataFile);
    }

    /**
     * Open the specified Kinect skeleton data file and set the currently
     * displayed Kinect skeleton data file to it. If the file can not be opened
     * an error dialog is displayed and the current Kinect skeleton data file is
     * not changed.
     *
     * @param kinectDataFileName
     *        The path to a Kinect skeleton data file.
     */
    public final void setKinectDataFile(final String kinectDataFileName) {
        try {
            final KinectDataFile newKinectDataFile;
            newKinectDataFile = new KinectDataFile(kinectDataFileName);
            setKinectDataFile(newKinectDataFile);
        } catch (final IOException ioException) {
            final String messageText = String.format(OPEN_ERROR_TEXT,
                    kinectDataFileName);
            JOptionPane.showMessageDialog(this, messageText);
        }
    }
}
