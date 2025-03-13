import java.sql.*;

public class Conn {
    Connection c;
    Statement s;
    Conn() {
        try{
            c = DriverManager.getConnection("jdpc:mysql:///ebs", "root","");
            s = c.createStatement();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
    public static void main(String[] args) {
        new Conn();
    }
}
