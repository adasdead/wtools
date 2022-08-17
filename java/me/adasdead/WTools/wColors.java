package me.adasdead.WTools;

public enum wColors {
    BLACK('0', 30),
    RED('1', 31),
    GREEN('2', 32),
    YELLOW('3', 33),
    BLUE('4', 34),
    MAGENTA('5', 35),
    CYAN('6', 36),
    WHITE('7', 37),

    GRAY('8', 90),
    BRIGHT_RED('9', 91),
    BRIGHT_GREEN('a', 92),
    BRIGHT_YELLOW('b', 93),
    BRIGHT_BLUE('c', 94),
    BRIGHT_MAGENTA('d', 95),
    BRIGHT_CYAN('e', 96),
    BRIGHT_WHITE('f', 97);

    private short color;
    private char ch;

    wColors(char ch, int color) {
        this.color = (short) color;
        this.ch = ch;
    }

    public short getColor() {
        return color;
    }

    @Override
    public String toString() {
        return "\\" + ch;
    }
}
