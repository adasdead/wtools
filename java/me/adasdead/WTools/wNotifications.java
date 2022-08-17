package me.adasdead.WTools;

public class wNotifications {
    private wNotifications() {}

    public static native void notify(String message, String text);

    static {
        wCore.loadLibrary();
    }
}
