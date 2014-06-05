package edu.roanoke.manualsegmentation;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.EOFException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Scanner;

import javax.vecmath.Vector3f;
import javax.vecmath.Vector4f;

/**
 * This class represents a Kinect skeleton data file.
 *
 * @author durell
 */
public class KinectDataFile {
    /**
     * This class represents a frame of Kinect skelton data.
     */
    private class Frame {

        /** Frame time. */
        public float time;

        /** List of joint positions. */
        public final ArrayList<Joint> joints;

        /** List of bone orientations. */
        public final ArrayList<Bone> bones;

        /**
         * Create a new frame by reading from the specified reader.
         *
         * @param reader
         *        A buffered reader ready to read a frame.
         * @throws Exception
         *         Throws an exception if there is any problem reading the file.
         */
        public Frame(final BufferedReader reader) throws Exception {
            final String line = reader.readLine();
            if (line == null || line.length() == 0) {
                throw new EOFException("End of file reached.");
            }
            time = Float.parseFloat(line);
            joints = new ArrayList<Joint>();
            for (int jointIndex = 0; jointIndex < NUMBER_OF_JOINTS; jointIndex++) {
                final Joint joint = new Joint(reader);
                joints.add(joint);
            }
            bones = new ArrayList<Bone>();
            for (int boneIndex = 0; boneIndex < NUMBER_OF_BONES; boneIndex++) {
                final Bone bone = new Bone(reader);
                bones.add(bone);
            }
            reader.readLine();
        }

        /**
         * Return the location of the specified joint.
         *
         * @param jointNumber
         *        Joint number, see static instance data valid for values.
         * @return The location of the specified joint.
         */
        public Vector3f getJointPosition(final int jointNumber) {
            final Joint joint = joints.get(jointNumber);
            return joint.position;
        }

        /**
         * Translate the position of every joint in this frame by the
         * specified amount.
         *
         * @param translation
         *        Amount to translate the joint positions by.
         */
        public void translatePositions(final Vector3f translation) {
            for (int jointIndex = 0; jointIndex < NUMBER_OF_JOINTS; jointIndex++) {
                final Joint joint = joints.get(jointIndex);
                joint.position.add(translation);
            }
        }

        /**
         * Write this frame to the specified printWriter.
         *
         * @param printWriter
         *        The PrintWriter to write this frame to.
         */
        public void write(final PrintWriter printWriter) {
            printWriter.println(time);
            for (int jointIndex = 0; jointIndex < NUMBER_OF_JOINTS; jointIndex++) {
                final Joint joint = joints.get(jointIndex);
                joint.write(printWriter);
            }
            for (int boneIndex = 0; boneIndex < NUMBER_OF_BONES; boneIndex++) {
                final Bone bone = bones.get(boneIndex);
                bone.write(printWriter);
            }
            printWriter.println("--------------------------");
        }

        /**
         * Write this frame with the specified offsets to the
         * specified printWriter.
         *
         * @param printWriter
         *        The PrintWriter to write this frame to.
         * @param positionOffset
         *        The amount to offset the position of each joint by.
         * @param timeOffset
         *        The number of seconds to offset the time of each frame by.
         */
        public void write(final PrintWriter printWriter,
                          final Vector3f positionOffset,
                          final float timeOffset) {
            printWriter.println(time - timeOffset);
            for (int jointIndex = 0; jointIndex < NUMBER_OF_JOINTS; jointIndex++) {
                final Joint joint = joints.get(jointIndex);
                joint.write(printWriter, positionOffset);
            }
            for (int boneIndex = 0; boneIndex < NUMBER_OF_BONES; boneIndex++) {
                final Bone bone = bones.get(boneIndex);
                bone.write(printWriter);
            }
            printWriter.println("--------------------------");
        }

    }

    /**
     * Class that represents a single joint in a Kinect skeleton data file.
     */
    private class Joint {

        /** Joint name. */
        public final String name;

        /** Joint location. */
        public final Vector3f position;

        /**
         * Create new joint by reading from the specified reader.
         *
         * @param reader
         *        A buffered reader ready to read a joint.
         * @throws Exception
         *         Throws an exception if there is any problem reading the file.
         */
        public Joint(final BufferedReader reader) throws Exception {
            final String line = reader.readLine();
            final Scanner scanner = new Scanner(line);
            scanner.useDelimiter(" ");
            name = scanner.next();
            final float x = Float.parseFloat(scanner.next());
            final float y = Float.parseFloat(scanner.next());
            final float z = Float.parseFloat(scanner.next());
            position = new Vector3f(x, y, z);
            scanner.close();
        }

        /**
         * Write this joint to the specified printWriter.
         *
         * @param printWriter
         *        The PrintWriter to write this joint to.
         */
        public void write(final PrintWriter printWriter) {
            printWriter.print(name + " ");
            printWriter.print(position.x + " ");
            printWriter.print(position.y + " ");
            printWriter.print(position.z + "\n");
        }


        /**
         * Write this joint to the specified printWriter.
         *
         * @param printWriter
         *        The PrintWriter to write this joint to.
         * @param positionOffset
         *        The number of seconds to offset the time of each frame by.
         */
        public void write(final PrintWriter printWriter,
                          final Vector3f positionOffset) {
            Vector3f offsetPosition = new Vector3f(position);
            offsetPosition.sub(positionOffset);
            printWriter.print(name + " ");
            printWriter.print(offsetPosition.x + " ");
            printWriter.print(offsetPosition.y + " ");
            printWriter.print(offsetPosition.z + "\n");
        }
    }

    /**
     * Class that represents a single bone in a Kinect skeleton data file.
     */
    private class Bone {

        /** Bone name. */
        public final String name;

        /** Bone orientation. */
        public final Vector4f orientation;

        /**
         * Create new bone by reading from the specified reader.
         *
         * @param reader
         *        A buffered reader ready to read a bone.
         * @throws Exception
         *         Throws an exception if there is any problem reading the file.
         */
        public Bone(final BufferedReader reader) throws Exception {
            final String line = reader.readLine();
            final Scanner scanner = new Scanner(line);
            scanner.useDelimiter(" ");
            name = scanner.next() + " " + scanner.next();
            final float x = Float.parseFloat(scanner.next());
            final float y = Float.parseFloat(scanner.next());
            final float z = Float.parseFloat(scanner.next());
            final float w = Float.parseFloat(scanner.next());
            orientation = new Vector4f(x, y, z, w);
            scanner.close();
        }

        /**
         * Write this bone to the specified printWriter.
         *
         * @param printWriter
         *        The PrintWriter to write this bone to.
         */
        public void write(final PrintWriter printWriter) {
            printWriter.print(name + " ");
            printWriter.print(orientation.x + " ");
            printWriter.print(orientation.y + " ");
            printWriter.print(orientation.z + " ");
            printWriter.print(orientation.z + "\n");
        }
    }

    /** Hip center joint id. */
    public static final int HIP_CENTER = 0;

    /** Spine joint id. */
    public static final int SPINE = 1;

    /** Shoulder center id. */
    public static final int SHOULDER_CENTER = 2;

    /** Head id. */
    public static final int HEAD = 3;

    /** Shoulder left id. */
    public static final int SHOULDER_LEFT = 4;

    /** Elbow left id. */
    public static final int ELBOW_LEFT = 5;

    /** Wrist left id. */
    public static final int WRIST_LEFT = 6;

    /** Hand left id. */
    public static final int HAND_LEFT = 7;

    /** Shoulder right id. */
    public static final int SHOULDER_RIGHT = 8;

    /** Elbow right id. */
    public static final int ELBOW_RIGHT = 9;

    /** Wrist right id. */
    public static final int WRIST_RIGHT = 10;

    /** Hand right id. */
    public static final int HAND_RIGHT = 11;

    /** Hip left id. */
    public static final int HIP_LEFT = 12;

    /** Knee left id. */
    public static final int KNEE_LEFT = 13;

    /** Ankle left id. */
    public static final int ANKLE_LEFT = 14;

    /** Foot left id. */
    public static final int FOOT_LEFT = 15;

    /** Hip right id. */
    public static final int HIP_RIGHT = 16;

    /** Knee right id. */
    public static final int KNEE_RIGHT = 17;

    /** Ankle right id. */
    public static final int ANKLE_RIGHT = 18;

    /** foot right id. */
    public static final int FOOT_RIGHT = 19;

    /** Number of joints in one frame of data file. */
    public static final int NUMBER_OF_JOINTS = 20;

    /** Number of bones in one frame of data file. */
    public static final int NUMBER_OF_BONES = 20;

    /** List of frames in data file. */
    private ArrayList<Frame> frames;

    /** Current frame number for animation. */
    private int currentFrameNumber = 0;

    /** Selection start frame number. */
    private int selectionStartFrameNumber = 0;

    /** Selection end frame number. */
    private int selectionEndFrameNumber = 0;

    /**
     * Create new Kinect data file by reading the file at the specified path.
     *
     * @param fileName
     *        String of the file's path.
     * @throws IOException
     *         Thrown if there is any error reading the file.
     */
    public KinectDataFile(final String fileName) throws IOException {
        readFile(fileName);
    }

    /**
     * Return new frame number that is in the range of the number of frames for
     * this Kinect data file by setting out of range frames to the nearest
     * in-range frame.
     *
     * @param frameNumber
     *        The frame number to clamp.
     * @return The frame number, clamped.
     */
    private int clampFrameNumber(final int frameNumber) {
        final int numberOfFrames = getNumberOfFrames();
        final int minFrameNumber = 0;
        final int maxFrameNumber = numberOfFrames - 1;
        return Math.max(minFrameNumber, Math.min(maxFrameNumber, frameNumber));
    }

    /**
     * Return the current frame number.
     *
     * @return The current frame number.
     */
    public final int getCurrentFrameNumber() {
        return currentFrameNumber;
    }

    /**
     * Return the position of the specified joint.
     *
     * @param jointNumber
     *        ID of the joint position to return.
     * @return Position of the specified joint.
     */
    public final Vector3f getJointPosition(final int jointNumber) {
        final Frame frame = frames.get(currentFrameNumber);
        return frame.getJointPosition(jointNumber);
    }

    /**
     * Return the number of frames in this Kinect data file.
     *
     * @return The number of frames.
     */
    public final int getNumberOfFrames() {
        return frames.size();
    }

    /**
     * Return the last frame in the current selection.
     *
     * @return The last frame in the selection.
     */
    public final int getSelectionEndFrameNumber() {
        return selectionEndFrameNumber;
    }

    /**
     * Return the first frame in the current selection.
     *
     * @return The first frame in the selection.
     */
    public final int getSelectionStartFrameNumber() {
        return selectionStartFrameNumber;
    }

    /**
     * Return true if the current frame number is at the end of the selection or
     * at the end of the file and false otherwise.
     *
     * @return Whether the current frame is at the end of the selection or
     *         frame.
     */
    public final boolean isCurrentFrameAtEnd() {
        final int numberOfFrames = getNumberOfFrames();
        if (selectionStartFrameNumber == selectionEndFrameNumber) {
            if (currentFrameNumber >= numberOfFrames - 1) {
                return true;
            }
        } else {
            if (selectionStartFrameNumber < selectionEndFrameNumber) {
                if (currentFrameNumber >= selectionEndFrameNumber) {
                    return true;
                }
            } else {
                if (currentFrameNumber >= selectionStartFrameNumber) {
                    return true;
                }
            }
        }
        return false;
    }

    /**
     * Return true if there currently is a selection.
     *
     * @return Whether there is a selection.
     */
    public final boolean isSelection() {
        return selectionStartFrameNumber != selectionEndFrameNumber;
    }

    /**
     * Read the Kinect data file with the specified path.
     *
     * @param fileName
     *        Path to the file to read.
     * @throws IOException
     *         Thrown if there is any error reading the file.
     */
    private void readFile(final String fileName) throws IOException {
        BufferedReader reader = null;
        try {
            FileReader fileReader;
            fileReader = new FileReader(fileName);
            reader = new BufferedReader(fileReader);
            reader.readLine();
            frames = new ArrayList<Frame>();
            while (true) {
                final Frame frame = new Frame(reader);
                frames.add(frame);
            }
        } catch (final EOFException eofException) {
            // do nothing, end of file
        } catch (final Exception exception) {
            throw new IOException("Error reading file.");
        } finally {
            if (reader != null) {
                reader.close();
            }
        }
    }

    /**
     * Set the current frame number.
     *
     * @param newFrameNumber
     *        Number to set the current frame number to.
     */
    public final void setCurrentFrameNumber(final int newFrameNumber) {
        currentFrameNumber = clampFrameNumber(newFrameNumber);
    }

    /**
     * Set the current frame number to the beginning of the selection or to the
     * beginning of the file if there is no selection.
     */
    public final void setCurrentFrameToStart() {
        if (selectionStartFrameNumber == selectionEndFrameNumber) {
            currentFrameNumber = 0;
        } else {
            if (selectionStartFrameNumber < selectionEndFrameNumber) {
                currentFrameNumber = selectionStartFrameNumber;
            } else {
                currentFrameNumber = selectionEndFrameNumber;
            }
        }
    }

    /**
     * Set the current selection end frame number.
     *
     * @param newFrameNumber The new selection end frame number.
     */
    public final void setSelectionEndFrameNumber(final int newFrameNumber) {
        selectionEndFrameNumber = clampFrameNumber(newFrameNumber);
    }

    /**
     * Set the current selection start frame number.
     *
     * @param newFrameNumber The new selection start frame number.
     */
    public final void setSelectionStartFrameNumber(final int newFrameNumber) {
        selectionStartFrameNumber = clampFrameNumber(newFrameNumber);
    }

    /**
     * Return true if the selection start fram number is between the
     * two specified frames.
     *
     * @param lowFrameNumber the lower bound of the range of frame numbers.
     * @param highFrameNumber the upper bound of the range of frame numbers.
     */
    // public final void isSelectionStart(final int lowFrameNumber,
    //                                    final int highFrameNumber) {
    //     return selectionStartFrameNumber >= lowFrameNumber &&
    //         selectionStartFrameNumber <= highFrameNumber;
    // }

    /**
     * Write this Kinect data file to the file at the specified path.
     *
     * @param fileName Path to the file to write.
     * @throws IOException Thrown if there is any error writing the file.
     */
    public final void writeFile(final String fileName) throws IOException {
        PrintWriter printWriter = null;
        try {
            FileWriter fileWriter;
            BufferedWriter bufferedWriter;
            int startIndex, endIndex;
            fileWriter = new FileWriter(fileName);
            bufferedWriter = new BufferedWriter(fileWriter);
            printWriter = new PrintWriter(bufferedWriter);
            printWriter.print("T 20 R 20\n");
            startIndex = selectionStartFrameNumber;
            endIndex = selectionEndFrameNumber;
            if (startIndex > endIndex) {
                final int tempIndex = startIndex;
                startIndex = endIndex;
                endIndex = tempIndex;
            }
            final Frame startFrame = frames.get(startIndex);
            final float startTime = startFrame.time;
            final Vector3f startPosition = startFrame.getJointPosition(HIP_CENTER);
            for (int frameIndex = startIndex; frameIndex <= endIndex;
                    frameIndex++) {
                final Frame frame = frames.get(frameIndex);
                frame.write(printWriter, startPosition, startTime);
            }
        } catch (final Exception exception) {
            throw new IOException("Error writing file.");
        } finally {
            if (printWriter != null) {
                printWriter.close();
            }
        }
    }

}
