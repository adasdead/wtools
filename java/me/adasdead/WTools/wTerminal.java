package me.adasdead.WTools;

public class wTerminal {
    private wTerminal() {}

    public static native void write(String text);
    public static native void writeLine(String text);

    @Deprecated
    public static native void setOutColor(short color);
    
    public static native void resetColor();

    public static void setOutColor(wColors color) {
        setOutColor(color.getColor());
    }

    static {
        wCore.loadLibrary();
    }
}
