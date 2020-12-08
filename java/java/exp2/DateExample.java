import java.util.*;
import javax.swing.JOptionPane;
public class DateExample
{ 
   public static void main(String args[ ]) 
   {  
      String str=JOptionPane.showInputDialog("输入第一个日期的年份:");
      int yearOne=Integer.parseInt(str);
      str=JOptionPane.showInputDialog("输入该年的月份:");
      int monthOne=Integer.parseInt(str);
      str=JOptionPane.showInputDialog("输入该月份的日期:");
      int dayOne=Integer.parseInt(str);
      str=JOptionPane.showInputDialog("输入第二个日期的年份:");
      int yearTwo=Integer.parseInt(str);
      str=JOptionPane.showInputDialog("输入该年的月份:");
      int monthTwo=Integer.parseInt(str);
      str=JOptionPane.showInputDialog("输入该月份的日期:");
      int dayTwo=Integer.parseInt(str);
      Calendar calendar= Calendar.getInstance();  //初始化日历对象
      calendar.set (yearOne, monthOne, dayOne);                 //将calendar的时间设置为yearOne年monthOne月dayOne日

      long timeOne=calendar.getTimeInMillis() ;     //calendar表示的时间转换成毫秒
      calendar.set (yearTwo, monthTwo, dayTwo);                 //将calendar的时间设置为yearTwo年monthTwo月dayTwo日
      long timeTwo= calendar.getTimeInMillis() ;    //calendar表示的时间转换成毫秒。
      Date date1= new Date(timeOne);       // 用timeOne做参数构造date1
      Date date2= new Date(timeTwo);      // 用timeTwo做参数构造date2
      if(date2.equals(date1))
        {
             System.out.println("两个日期的年、月、日完全相同");
        }
      else if(date2.after(date1))
        {
             System.out.println("您输入的第二个日期大于第一个日期");
        }
     else if(date2.before(date1))
        {
             System.out.println("您输入的第二个日期小于第一个日期");
        }
      long days= (timeTwo - timeOne) / (1000*60*60*24);//计算两个日期相隔天数
      System.out.println(yearOne+"年"+monthOne+"月"+dayOne+"日和"
                         +yearTwo+"年"+monthTwo+"月"+dayTwo+"相隔"+days+"天");
   }  
}
