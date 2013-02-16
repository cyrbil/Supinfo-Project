package com.suplink.tools;

public abstract class HTMLFilter {
    public static String filter(String message) {
        if (message == null) { return (null); }

        char content[] = new char[message.length()];
        message.getChars(0, message.length(), content, 0);
        StringBuilder result = new StringBuilder(content.length + 50);
        for (int i = 0; i < content.length; i++) {
            switch (content[i]) {
                case '\n': result.append("<br />"); break;
                case  '<': result.append("&lt;"); break;
                case  '>': result.append("&gt;"); break;
                case  '&': result.append("&amp;"); break;
                case  '"': result.append("&quot;"); break;
                default:   result.append(content[i]);
            }
        }
        return (result.toString());

    }
    public static String addSlashes(String message) {
        return message
                .replace("\\", "\\\\")
                .replace("\"", "\\\"");
    }
}
