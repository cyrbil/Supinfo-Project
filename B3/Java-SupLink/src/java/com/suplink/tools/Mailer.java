package com.suplink.tools;

import java.util.Properties;
import javax.mail.Message;
import javax.mail.Session;
import javax.mail.Transport;
import javax.mail.internet.InternetAddress;
import javax.mail.internet.MimeMessage;

public abstract class Mailer {
    public static String FROM               = "admin@suplink.com";
    public static String HOST               = "relais.videotron.ca";
    public static String STORE_PROTOCOL     = null;
    public static String TRANSPORT_PROTOCOL = null;
    public static String USER               = null;
    public static String PROTOCOL_HOST      = null;
    public static String PROTOCOL_USER      = null;
    
    public static void send(InternetAddress to,  String subject, String message) throws Exception {
        try {
            Properties props = new Properties();
            if(FROM != null) {
                props.setProperty("mail.from", FROM);
            }
            if(HOST != null) {
                props.setProperty("mail.host", HOST);
            }
            if(STORE_PROTOCOL != null) {
                props.setProperty("mail.store.protocol", STORE_PROTOCOL);
            }
            if(TRANSPORT_PROTOCOL != null) {
                props.setProperty("mail.transport.protocol", TRANSPORT_PROTOCOL);
            }
            if(USER != null) {
                props.setProperty("mail.user", USER);
            }
            if(PROTOCOL_HOST != null) {
                props.setProperty("mail.protocol.host", PROTOCOL_HOST);
            }
            if(PROTOCOL_USER != null) {
                props.setProperty("mail.protocol.user", PROTOCOL_USER);
            }
            Session session = Session.getInstance(props);

            Message mail = new MimeMessage(session);
            mail.setRecipient(Message.RecipientType.TO, to);
            mail.setSubject(subject);
            mail.setText(message);
            
            Transport.send(mail);
        } catch (Exception ex) {
            throw new Exception("Mail delivery failed", ex);
        }
    }
}
